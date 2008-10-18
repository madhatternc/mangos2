/**
 *     \file  src/realmlist/RealmListSrv.h
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

#ifndef __REALM_LIST_SRV_H__
#define __REALM_LIST_SRV_H__

#include "Server.h"
#include "StringFun.h"

class Database;

struct Realm
{
    /// Realm name
    char *Name;
    /// Server address (x.x.x.x:port)
    char *Address;
    /// Low/Medium/High, absolute values do not matter, everything is relative
    float Population;
    /// 0 - Normal, 1 - PvP, 2 - Offline
    uint32 Type;
    /// 0 - Unlocked, 1 - Locked
    uint8 Locked;
    /// 0 - Orange, 1 - Red, 2 - Disabled
    uint8 Color;
    /// 0,1 - English, 2 - German, 3 - French, 4 - Other
    uint8 Language;
    /// Number of characters owned by the client on this server
    uint8 NumChars;

    Realm (const char *name, const char *address, float population, uint32 type,
           uint8 locked, uint8 color, uint8 language)
    {
        Name = strnew (name);
        Address = strnew (address);
        Population = population;
        Type = type;
        Locked = locked;
        Color = color;
        Language = language;
        NumChars = 0;
    }

    ~Realm ()
    {
        delete [] Name;
        delete [] Address;
    }
};

/// The list of realms, sorted by name
DECLARE_VECTOR_SORTED (RealmVector, Realm *, );

class RealmListSrv : public Server
{
protected:
    // Private destructor (use DecRef ())
    virtual ~RealmListSrv();

public:
    /// The realm database
    Database *db;

public:
    /**
     * Initialize the realm list server
     * @arg iPort
     *   Port number to listen on
     * @arg iLogger
     *   The logger used to log interesting events
     */
    RealmListSrv (uint iPort, Log *iLogger);

    /**
     * Set the database object used to check accounts/passwords.
     * @arg iDb
     *   The database interface object
     */
    void SetDatabase (Database *iDb);

    /**
     * Called when any event (one of those requested by socket->InterestedEvents())
     * happens with the socket.
     * @arg mask
     *   Event mask (a combination of PF_XXX flags)
     */
    virtual void SocketEvent (uint mask);

    /**
     * Override the Server::Start() method to perform additional
     * initialization before server actually starts
     */
    virtual bool Start ();

    /**
     * Get a list of currently active realms (as seen by currently logging on users).
     * The active realms may go on and off, so the list returned by this function
     * is not guaranteed to be the same if you call it twice in a row.
     * @return
     *   A list of currently active realms.
     *   NULL on errors (mostly if database-related errors).
     */
    RealmVector *GetRealms ();
};

#endif // __REALM_LIST_SRV_H__
