/**
 *     \file  src/worldserver/GameClient.cpp
 *    \brief  Receives and dispatches all opcodes sent from and to the client.
 *
 * Copyright (C) 2005 Team OpenWoW <http://openwow.quamquam.org/>
 * Copyright (C) 2008 MaNGOS foundation <http://getmangos.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <openssl/sha.h>
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
}

#include "tolua++.h"

#include "GameClient.h"
#include "WorldServer.h"
#include "Opcodes.h"
#include "Log.h"
#include "Database.h"
#include "Player.h"

GameClient::GameClient (Socket *sock) : Client (sock)
{
    Capabilities = 0;
    Login = NULL;
    GenSeed ();

    memset (&AccountData, 0, sizeof (AccountData));

    Lua = lua_newthread (World->Lua);

    // Initiate authentification sequence
    SMSG_AUTH_CHALLENGE_t *outpkt = SMSG_AUTH_CHALLENGE_t::Create ();
    outpkt->Seed = Seed;
    outpkt->Assemble ();
    Send (outpkt);
}

GameClient::~GameClient ()
{
    LOG.Out (LOG_IMPORTANT, "User %s logged out\n", Login);
    if (Character)
    {
        Character->SaveToDB ();
        Character->DecRef ();
    }
    SaveAccountData ();
    delete [] Login;
}

void GameClient::SocketEvent (uint mask)
{
    /*
     * Process one packet at a time, giving a chance to be serviced
     * to other players that may be handled by this thread (also protect
     * ourselves from someone that may flood the server with random data
     * which would otherwise cause a DoS.
     */
    if (!(mask & PF_READ))
        return;

    /// Eat as many packets as we can
    for (;;)
    {
        socket->Rewind ();

        uint8 header [2+4];
        if (!socket->Get (header, sizeof (header)))
            break;

        if (Authenticated ())
        {
            SaveRecvEncryptor ();
            DecryptRecv (header);
        }
        uint pktlen = GET_BE16 (header) + 2;
        if (socket->Avail () + sizeof (header) < pktlen)
        {
            DEBUG_PRINTF ("Got incomplete packet [%02x %02x %02x %02x %02x %02x], waiting for packet tail\n",
                          header [0],header [1],header [2],header [3],header [4],header [5]);
            RestoreRecvEncryptor ();
            break;
        }

        NetworkPacket *packet = NULL;
        uint32 opcode = GET_LE32 (header + 2);

        DEBUG_PRINTF ("Packet %s len %d\n", GetPacketName (opcode), pktlen);

        if (Authenticated ())
        {
            switch (opcode)
            {
#include "Parser.inc"
                default:
                    LOG.Out (LOG_DEBUG, "Unhandled opcode %s\n", GetPacketName (opcode));
                    socket->Skip (pktlen - sizeof (header));
                    break;
            }
        }
        else
        {
            switch (opcode)
            {
                case CMSG_PING:
                {
                    packet = CMSG_PING_t::Create (socket);
                    if (packet)
                        HandlePing (*(CMSG_PING_t *)packet);
                    break;
                }
                case CMSG_AUTH_SESSION:
                {
                    packet = CMSG_AUTH_SESSION_t::Create (socket);
                    if (packet)
                        HandleAuthSession (*(CMSG_AUTH_SESSION_t *)packet);
                    break;
                }
                default:
                    LOG.Out (LOG_DEBUG, "PRE-AUTH: Unhandled opcode: %s\n",
                             GetPacketName (opcode));
                    socket->Skip (pktlen - sizeof (header));
                    break;
            }
        }

        if (packet && socket->Chewed () != pktlen)
            LOG.Out (LOG_IMPORTANT, "BAD PACKET OR PARSER: Chewed %d bytes, packet is %d bytes - OpCode: %s\n",
                                 socket->Chewed (), pktlen, GetPacketName (opcode));

        socket->Swallow ();
        if (packet)
            packet->DecRef ();
    }
}

void GameClient::GenSeed ()
{
    do {
        Seed = rand ();
    } while (!Seed);
}

void GameClient::Send (NetworkPacket *packet)
{
    if (!packet->data)
        packet->Assemble ();

    if (Authenticated ())
        EncryptSend (packet->data);

    socket->SendData (packet);
    packet->DecRef ();
}

void GameClient::SaveAccountData ()
{
    if (!Login)
        return;

    char *ad [ARRAY_LEN (AccountData)];
    for (uint i = 0; i < ARRAY_LEN (AccountData); i++)
    {
        ad [i] = !AccountData [i] ? NULL :
            EncodeSQL (AccountData [i], sizeof (uint32) * 2 + 16 + GET_LE32 (AccountData [i] + 4));
        delete [] AccountData [i];
        AccountData [i] = 0;
    }

    DatabaseExecutor *dbex = World->rdb->GetExecutor ();
    if (dbex)
    {
        dbex->ExecuteF ("UPDATE accounts SET data0='%s',data1='%s',data2='%s' WHERE login='%s'",
                        NN_STR (ad [0]), NN_STR (ad [1]), NN_STR (ad [2]), Login);
        World->rdb->PutExecutor (dbex);
    }

    for (uint i = 0; i < ARRAY_LEN (AccountData); i++)
        delete [] ad [i];
}

//-----------------------------// Encryption //------------------------------//

#define CRYPTED_SEND_LEN 4
#define CRYPTED_RECV_LEN 6

void GameClient::InitEncryptor ()
{
    Seed = 0;
    cs_prev = cr_prev = 0;
    cs_idx = cr_idx = 0;
}

void GameClient::DecryptRecv (uint8 *data)
{
    for (size_t i = 0; i < CRYPTED_RECV_LEN; i++)
    {
        uint8 b = data [i];
        data [i] = (b - cr_prev) ^ SessionKey [cr_idx];
        cr_prev = b;
        if (++cr_idx >= sizeof (SessionKey))
            cr_idx = 0;
    }
}

void GameClient::EncryptSend (uint8 *data)
{
    for (size_t i = 0; i < CRYPTED_SEND_LEN; i++)
    {
        data [i] = cs_prev = (data [i] ^ SessionKey [cs_idx]) + cs_prev;
        if (++cs_idx >= sizeof (SessionKey))
            cs_idx = 0;
    }
}

//------------------------------// Handlers //-------------------------------//

void GameClient::FailAuth (uint32 iCode)
{
    SMSG_AUTH_RESPONSE_t *outpkt = SMSG_AUTH_RESPONSE_t::Create ();
    outpkt->ErrorCode = iCode;
    outpkt->Assemble ();
    Send (outpkt);
    LOG.Out (LOG_DEBUG, "Rejecting user '%s' with code %d\n", Login, iCode);
    // Switch back to unencrypted mode
    GenSeed ();

    if (Login)
    {
        delete [] Login;
        Login = NULL;
    }
    if (Character)
    {
        Character->DecRef ();
        Character = NULL;
    }
}

void GameClient::HandleAuthSession (CMSG_AUTH_SESSION_t &inpkt)
{
    // Save old account data, if any
    SaveAccountData ();

    Login = inpkt.Login;
    inpkt.Login = NULL; // steal this field from packet ;)

    DatabaseExecutor *dbex = World->rdb->GetExecutor ();
    if (!dbex ||
        dbex->ExecuteF ("SELECT level,sessionkey FROM accounts WHERE login='%s'", Login) != dbeOk ||
        !dbex->NextRow ())
    {
        FailAuth (WSE_UNKNOWN_ACCOUNT);
error:  if (dbex)
            World->rdb->PutExecutor (dbex);
        return;
    }

    uint level = dbex->GetU32 (0);
    const char *seskey = dbex->Get (1);
    if (!seskey
     || !Hex2Bin (seskey, SessionKey, sizeof (SessionKey)))
    {
        FailAuth (WSE_LOGIN_UNAVAILABLE);
        goto error;
    }

    World->rdb->PutExecutor (dbex);

    // Set the 'authentificated' flag
    uint32 auth_seed = Seed;
    InitEncryptor ();

    // Check if server is full
    if (World->ClientLimit && World->GetClientsConnected () >= World->ClientLimit)
    {
        FailAuth (WSE_POSITION_IN_QUEUE_0);
        return;
    }

    // check if player is already connected
    if (World->SortedClients.FindSortedKey (Login) >= 0)
    {
        FailAuth (WSE_THIS_CHARACTER_IS_STILL_LOGGED_ON);
        return;
    }

    // Check client' hash
    size_t sl = strlen (Login);
    size_t buffsize = sl + 3 * sizeof (uint32) + sizeof (SessionKey);
    uint8 *buff = new uint8 [buffsize];
    uint8 *cur = buff;

    memcpy (cur, Login, sl);    cur += sl;
    PUT_LE32 (cur, 0);          cur += sizeof (uint32);
    PUT_LE32 (cur, inpkt.Seed); cur += sizeof (uint32);
    PUT_LE32 (cur, auth_seed);  cur += sizeof (uint32);
    memcpy (cur, SessionKey, sizeof (SessionKey)); cur += sizeof (SessionKey);

    uint8 digest [20];
    SHA1 (buff, buffsize, digest);

    if (memcmp (digest, inpkt.Digest, sizeof (digest)))
    {
        FailAuth (WSE_AUTHENTICATION_FAILED);
        return;
    }

    World->SortedClients.InsertSorted (this);

    SMSG_AUTH_RESPONSE_t *outpkt = SMSG_AUTH_RESPONSE_t::Create ();
    outpkt->ErrorCode = WSE_AUTHENTICATION_SUCCESSFUL;
    outpkt->Counter = World->AuthCount++;
    outpkt->Assemble ();
    Send (outpkt);

    char *PrivName = NULL;

    dbex = World->db->GetExecutor ();
    if (dbex)
    {
        // Get user privileges
        if (dbex->ExecuteF ("SELECT name,flags FROM access_levels WHERE level=%d", level) == dbeOk &&
            dbex->NextRow ())
        {
            PrivName = strnew (dbex->Get (0));
            Capabilities = dbex->GetU32 (1);
        }

        World->db->PutExecutor (dbex);
    }

    dbex = World->rdb->GetExecutor ();
    if (dbex)
    {
        // Get account data
        if (dbex->ExecuteF ("SELECT data0,data1,data2 FROM accounts WHERE login='%s'", Login) == dbeOk &&
            dbex->NextRow ())
            for (uint i = 0; i < 3; i++)
            {
                size_t sz = DecodeSQL (dbex->Get (i), NULL, 0);
                if (sz)
                {
                    AccountData [i] = new uint8 [sz];
                    DecodeSQL (dbex->Get (i), AccountData [i], sz);
                }
            }

        World->rdb->PutExecutor (dbex);
    }
    // Update realm load etc
    World->UpdateRealm (true);

    LOG.Out (LOG_DEBUG, "%s '%s' logged in\n",
             PrivName ? PrivName : "Stranger", Login);
    delete [] PrivName;
}

void GameClient::HandlePing (CMSG_PING_t &inpkt)
{
    SMSG_PONG_t *outpkt = SMSG_PONG_t::Create ();
    outpkt->Acknowledge = inpkt.Ordinal;
    outpkt->Assemble ();
    Send (outpkt);
}
