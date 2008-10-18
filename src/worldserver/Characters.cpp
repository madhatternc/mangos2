/**
 *     \file  src/worldserver/Characters.cpp
 *    \brief  Provides basic Character functions.
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

#include "GameClient.h"
#include "WorldServer.h"
#include "Database.h"
#include "Player.h"
#include "version.h"

void GameClient::UpdateNumChars ()
{
    DatabaseExecutor *dbex = World->db->GetExecutor ();
    if (!dbex)
        return;

    if (dbex->ExecuteF ("SELECT guid FROM characters WHERE login='%s'", Login) != dbeOk)
    {
        World->db->PutExecutor (dbex);
        return;
    }

    int n = dbex->NumRows ();

    World->db->PutExecutor (dbex);

    dbex = World->rdb->GetExecutor ();
    if (dbex)
    {
        char *qlogin = QuoteSQL (Login);
        char *qrealm = QuoteSQL (World->RealmName);

        if (n)
        {
            bool updateok = (dbex->ExecuteF ("UPDATE accountchars SET numchars=%d "
                "WHERE login='%s' AND realm='%s'", n, qlogin, qrealm) == dbeOk) &&
                dbex->GetAffectedRows ();
            if (!updateok)
                dbex->ExecuteF ("INSERT INTO accountchars (login,realm,numchars) "
                    "VALUES ('%s','%s',%d)", qlogin, qrealm, n);
        }
        else
            dbex->ExecuteF ("DELETE FROM accountchars WHERE login='%s' AND realm='%s'",
                            qlogin, qrealm);

        if (qlogin != Login)
            delete [] qlogin;
        if (qrealm != World->RealmName)
            delete [] qrealm;

        World->rdb->PutExecutor (dbex);
    }
}

void GameClient::HandleCharEnum ()
{
    SMSG_CHAR_ENUM_t *outpkt = SMSG_CHAR_ENUM_t::Create ();

    DatabaseExecutor *dbex = World->db->GetExecutor ();
    if (dbex)
    {
        if (dbex->ExecuteF ("SELECT guid FROM characters WHERE login='%s' ORDER BY guid", Login) == dbeOk)
        {
            uint64 guids [MAX_CHARS_PER_LOGIN];
            int nguids = 0;
            while (dbex->NextRow () && nguids < MAX_CHARS_PER_LOGIN)
                guids [nguids++] = dbex->GetU64 (0);

            CharacterData *cd = NULL;
            outpkt->Count = 0;
            for (int i = 0; i < nguids; i++)
            {
                if (!cd)
                    cd = new CharacterData ();

                // Re-use the executor
                dbex->Free ();
                if (cd->Load (dbex, guids [i]))
                {
                    outpkt->List.Push (cd);
                    outpkt->Count++;
                    cd = NULL;
                }
            }
            if (cd)
                delete cd;
        }
        World->db->PutExecutor (dbex);
    }

    Send (outpkt);
}

void GameClient::HandleCharCreate (CMSG_CHAR_CREATE_t &inpkt)
{
    SMSG_CHAR_CREATE_t *outpkt = SMSG_CHAR_CREATE_t::Create ();

    Player *NewPlayer = new Player;
    if ((outpkt->ErrorCode = NewPlayer->Create (inpkt, this)) == WSE_CHARACTER_CREATED)
    {
        if (NewPlayer->SaveToDB ())
            UpdateNumChars ();
        else
            outpkt->ErrorCode = WSE_NAME_ALREADY_IN_USE;
    }

    Send (outpkt);

    if (outpkt->ErrorCode == WSE_CHARACTER_CREATED)
        LOG.Out (LOG_COMMON, "%s: Created character '%s'\n", Login, NewPlayer->Name);
    NewPlayer->DecRef ();
}

void GameClient::HandleCharDelete (CMSG_CHAR_DELETE_t &inpkt)
{
    Player *plr = new Player;
    SMSG_CHAR_CREATE_t *outpkt = SMSG_CHAR_CREATE_t::Create ();

    outpkt->ErrorCode = WSE_CHARACTER_DELETION_FAILED;
    // Ignore loading errors since character may be broken
    plr->LoadFromDB (uint32 (inpkt.Guid));
    if (plr->DeleteFromDB ())
        outpkt->ErrorCode = WSE_CHARACTER_DELETED;

    Send (outpkt);

    if (outpkt->ErrorCode == WSE_CHARACTER_DELETED)
        LOG.Out (LOG_COMMON, "%s: Deleted character '%s'\n",
                 Login, plr->Name);
    plr->DecRef ();
}

void GameClient::HandlePlayerLogin (CMSG_PLAYER_LOGIN_t &inpkt)
{
    Character = new Player;

    if (!Character->LoadFromDB (uint32 (inpkt.Guid)))
    {
        SMSG_CHARACTER_LOGIN_FAILED_t *outpkt = SMSG_CHARACTER_LOGIN_FAILED_t::Create ();
        outpkt->ErrorCode = WSE_LOGIN_FAILED;
        Send (outpkt);
        Character->DecRef ();
        Character = NULL;
        return;
    }

    Character->Client = this;

    SendAccountDataMD5 ();

    // MOTD
//  sChatHandler.FillSystemMessageData(&data, this, sWorld.GetMotd());
//  SendPacket( &data );

    //data.Initialize(4, SMSG_SET_REST_START);
    //data << unsure;
    //SendPacket(&data);

    // Tell character to perform all login-time setup
    Character->Login ();

    // Now send all A9's
    // Add character to the ingame list
    // Build the in-range set
    // Send a message to other clients that a new player has entered the world
    // And let this client know we're in game

    //objmgr.AddObject( pCurrChar );
    //pCurrChar->PlaceOnMap();

    //  std::string outstring = pCurrChar->GetName();
    //  outstring.append( " has entered the world." );
    //  sWorld.SendWorldText( outstring.c_str( ) );

    LOG.Out (LOG_COMMON, "%s: Entered into world as '%s'\n",
             Login, Character->Name);
}
