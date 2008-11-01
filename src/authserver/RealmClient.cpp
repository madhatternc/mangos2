/**
 *     \file  src/authserver/RealmClient.cpp
 *    \brief  Receives all messages related to authentication and ream list serving.
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

#include "RealmClient.h"
#include "Database.h"
#include "Log.h"
#include "version.h"

RealmClient::RealmClient (Socket *sock, RealmListSrv *serv) : Client (sock)
{
    Server = serv;
}

void RealmClient::SocketEvent (uint mask)
{
    if (mask & PF_READ)
    {
        socket->Rewind ();

        uint8 opcode;
        if (!socket->Get (opcode))
            return;

        NetworkPacket *packet = NULL;

        switch (opcode)
        {
#include "Opcodes.inc"
            default:
                Server->Logger->Out (LOG_COMMON, "\axcWARNING: \ax6Unknown packet type: 0x%02X\n", opcode);
        };

        if (packet)
        {
            socket->Swallow ();
            packet->DecRef ();
        }
    }
}

static char *str4 (uint8 *x)
{
    static char str4 [5];
    int i, sl;
    uint8 *eol = (uint8 *)memchr (x, 0, sizeof (uint32));
    sl = eol ? eol - x : sizeof (uint32);
    for (i = 0; i < sl; i++)
        str4 [sl - i - 1] = x [i];
    str4 [sl] = 0;
    return str4;
}

void RealmClient::FailLogin (AuthServerResults err, const char *errstr)
{
    SMSG_LOGON_PROOF_t *outpkt = SMSG_LOGON_PROOF_t::Create ();
    outpkt->ErrorCode = err;
    Send (outpkt);
    Server->Logger->Out (LOG_DEBUG, "Sent LOGON_PROOF with code '%s'\n", errstr);
    return;
}

void RealmClient::HandleLogonChallenge (CMSG_LOGON_CHALLENGE_t &inpkt)
{
    Server->Logger->Out (LOG_DEBUG, "Received LOGON_CHALLENGE\n");

    printf ("Username: %s\n", inpkt.UserName);
    printf ("Game ID: %s\n", str4 (inpkt.GameID));
    printf ("Client Version: %d.%d.%d\n", inpkt.ClientVersion [0],
        inpkt.ClientVersion [1], inpkt.ClientVersion [2]);
    printf ("Build Version: %d\n", inpkt.ClientBuild);
    printf ("Architecture: %s\n", str4 (inpkt.Arch));
    printf ("Platform: %s\n", str4 (inpkt.OS));
    printf ("Language: %s\n", str4 (inpkt.Lang));
    printf ("Error Start Byte: %d\n", inpkt.ErrorCode);
    printf ("Client internal IP address: %s\n",
        inet_ntoa (*(struct in_addr *)&inpkt.ClientIP));
    printf ("Client time zone: GMT%c%d\n",
            inpkt.TimeZone >= 0 ? '+' : '-', inpkt.TimeZone / 60);

    if ((inpkt.ClientBuild < MIN_CLIENT_BUILD) ||
        (inpkt.ClientBuild > MAX_CLIENT_BUILD))
    {
        FailLogin (ASE_BAD_VERSION, "wrong version");
        return;
    }

    DatabaseExecutor *dbex = Server->db->GetExecutor ();
    int rc = 0;
    char *passwd = NULL;
    if (!dbex)
        rc = 1;
    else if (dbex->ExecuteF ("SELECT password,level FROM accounts WHERE login='%s'", inpkt.UserName) != dbeOk)
        rc = 1;
    else if (!dbex->NextRow ())
        rc = 2;
    else
    {
        passwd = strnew (dbex->Get (0));
        upperstr (passwd);
    }

    if (dbex)
        Server->db->PutExecutor (dbex);

    switch (rc)
    {
        case 1:   // general failure
            FailLogin (ASE_CANNOT_LOGIN, "could not log in");
            return;
        case 2:   // bad username
            FailLogin (ASE_BAD_CREDENTIALS, "no such account");
            return;
    }

    // got username & pass, let's start SRP
    Challenge (inpkt.UserName, passwd);
    delete [] passwd;

    SMSG_LOGON_CHALLENGE_t *outpkt = SMSG_LOGON_CHALLENGE_t::Create ();
    memcpy (outpkt->BR, &BR, sizeof (BR));
    memcpy (outpkt->N, &N, sizeof (N));
    memcpy (outpkt->Salt, &salt, sizeof (salt));
    Send (outpkt);

    Server->Logger->Out (LOG_DEBUG, "Sent LOGON_CHALLENGE\n");
}

void RealmClient::HandleLogonProof (CMSG_LOGON_PROOF_t &inpkt)
{
    Server->Logger->Out (LOG_DEBUG, "Recieved LOGON_PROOF\n");

    Proof (inpkt.A);

#ifdef SRP_DEBUG
    printBytes (inpkt.M1, 20, "in-M1");
    printBytes (SS_Hash, 40, "SS_Hash");
#endif

    // if they differ, wrong pass
    if (memcmp (inpkt.M1, M1, 20))
    {
        FailLogin (ASE_BAD_CREDENTIALS, "bad password");
        return;
    }

    DatabaseExecutor *dbex = Server->db->GetExecutor ();
    if (!dbex)
    {
        FailLogin (ASE_CANNOT_LOGIN, "could not log in");
        return;
    }

    char sshash [81];
    Bin2Hex (sshash, SS_Hash, 40);
    if (dbex->ExecuteF ("UPDATE accounts SET authip='%s',sessionkey='%s',lastlogin=NOW() WHERE login='%s'",
                        socket->GetIP (), sshash, UserName) != dbeOk)
    {
        Server->db->PutExecutor (dbex);
        FailLogin (ASE_CANNOT_LOGIN, "could not log in");
        return;
    }

    Server->db->PutExecutor (dbex);

    SMSG_LOGON_PROOF_t *outpkt = SMSG_LOGON_PROOF_t::Create ();
    memcpy (outpkt->M2, M2, 20);
    Send (outpkt);

    Server->Logger->Out (LOG_DEBUG, "Sent LOGON_PROOF\n");
}

void RealmClient::HandleRealmList (CMSG_REALMLIST_t &inpkt)
{
    Server->Logger->Out (LOG_DEBUG, "Received REALMLIST request %d\n", inpkt.request);

    RealmVector *rv = Server->GetRealms ();
    if (!rv)
        rv = new RealmVector ();

    DatabaseExecutor *dbex = Server->db->GetExecutor ();
    if (dbex)
    {
        for (int i = 0; i < rv->Length (); i++)
        {
            char *qlogin = QuoteSQL (UserName);
            char *qrealm = QuoteSQL (rv->Get (i)->Name);
            if ((dbex->ExecuteF ("SELECT numchars FROM accountchars WHERE login='%s' AND realm='%s'",
                                 qlogin, qrealm) == dbeOk) && dbex->NextRow ())
                rv->Get (i)->NumChars = atoi (dbex->Get (0));
            if (qlogin != UserName)
                delete [] qlogin;
            if (qrealm != rv->Get (i)->Name)
                delete [] qrealm;
        }
        Server->db->PutExecutor (dbex);
    }

    SMSG_REALMLIST_t *outpkt = SMSG_REALMLIST_t::Create ();
    outpkt->Request = inpkt.request;
    outpkt->NumRealms = rv->Length ();
    outpkt->RealmList.Exchange (*rv);
    delete rv;
    outpkt->Assemble ();
    // Update the datalen field post-factum, now that we know packet length
    // Equivalent to: outpkt->DataLen = outpkt->length;
    PUT_LE16 (outpkt->data + 1, outpkt->length - 3);
    Send (outpkt);

    Server->Logger->Out (LOG_DEBUG, "Sent REALMLIST\n");
}
