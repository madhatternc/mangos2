/**
 *     \file  src/realmlist/RealmListSrv.cpp
 *    \brief  Provides a basic realm list server class.
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

#include "RealmListSrv.h"
#include "RealmClient.h"
#include "Database.h"

IMPLEMENT_VECTOR_SORTED_STRKEY (, RealmVector, Realm *, Name);

RealmListSrv::RealmListSrv (uint iPort, Log *iLogger) : Server (iPort, 1000, iLogger)
{
}

RealmListSrv::~RealmListSrv ()
{
}

bool RealmListSrv::Start ()
{
    if (!db)
        return false;

    return Server::Start ();
}

void RealmListSrv::SocketEvent (uint mask)
{
    if (mask & PF_READ)
    {
        Socket *sock = socket->Accept ();
        if (!sock)
            return;
        // Free local references to refcounted objects
        RealmClient *c = new RealmClient (sock, this);
        AddClient (c);
        c->DecRef ();
        sock->DecRef ();
    }
}

void RealmListSrv::SetDatabase (Database *iDb)
{
    if (db != iDb)
    {
        if (db)
            db->DecRef ();
        if ((db = iDb))
        {
            db->IncRef ();
            db->SetLogger (Logger);
        }
    }
}

RealmVector *RealmListSrv::GetRealms ()
{
    DatabaseExecutor *dbex = db->GetExecutor ();
    if (!dbex)
        return NULL;

    RealmVector *rv = NULL;
    if (dbex->Execute ("SELECT name,address,population,type,locked,color,language,online "
                       "FROM realms") == dbeOk)
    {
        rv = new RealmVector (9, 9);
        while (dbex->NextRow ())
        {
            Realm *r = new Realm (dbex->Get (0), dbex->Get (1),
                                  atof (dbex->Get (2)), atoi (dbex->Get (3)),
                                  atoi (dbex->Get (4)), atoi (dbex->Get (5)),
                                  atoi (dbex->Get (6)));
            // Mark server with the 'offline' color if it is offline
            if (!atoi (dbex->Get (7)))
                r->Color = 2;
            rv->Push (r);
        }
    }

    db->PutExecutor (dbex);

    return rv;
}
