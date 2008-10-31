/**
 *     \file  src/authserver/RealmClient.h
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

#ifndef __REALM_CLIENT_H__
#define __REALM_CLIENT_H__

#include "Client.h"
#include "SrpRealm.h"
#include "StringFun.h"
#include "Opcodes.h"

class RealmListSrv;

/**
 * This is the realm network client.
 */
class RealmClient : public Client, public SrpRealm
{
protected:
    /// A pointer to parent realm server
    RealmListSrv *Server;

    /// Send the packet and free it
    void Send (NetworkPacket *outpkt)
    { socket->SendData (outpkt); outpkt->DecRef (); }

    void FailChallenge (RealmErrors err, const char *errstr);
    void FailLogin (RealmErrors err, const char *errstr);

    void HandleLogonChallenge (CMSG_LOGON_CHALLENGE_t &inpkt);
    void HandleReconnectChallenge (CMSG_RECONNECT_CHALLENGE_t &inpkt)
    { HandleLogonChallenge (*(CMSG_LOGON_CHALLENGE_t *)&inpkt); }
    void HandleLogonProof (CMSG_LOGON_PROOF_t &inpkt);
    void HandleRealmList (CMSG_REALMLIST_t &inpkt);

public:
    /**
     * Initialize the realm network client.
     */
    RealmClient (Socket *sock, RealmListSrv *serv);

    /**
     * Called when any event (one of those requested by socket->InterestedEvents())
     * happens with the socket.
     * @arg mask
     *   Event mask (a combination of PF_XXX flags)
     */
    virtual void SocketEvent (uint mask);
};

#endif // __REALM_CLIENT_H__
