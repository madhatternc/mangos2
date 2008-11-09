/**
 *     \file  src/worldserver/WorldServer.h
 *    \brief  Provides a basic implementation of the World server class.
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

#ifndef __WORLD_SERVER_H__
#define __WORLD_SERVER_H__

extern "C"
{
    #include "lua.h"
}

#include "Server.h"
#include "Timer.h"
#include "StringFun.h"

// Distance a Player can "see" other objects and receive updates from them
//#define UPDATE_DISTANCE       155.8

// Bitflags for GameFeatures
enum
{
    /**
     * If a creature attacks a player, and player is in non-combat mode,
     * player automaticaly switches to combat mode and attacks the creep.
     */
    GF_PLAYER_AUTOATTACK = 0x00000001
};

class Database;
class GameClient;

/**
 * The World server. This class handles all incoming connections and creates
 * a GameClient object for every connecting client.
 */
class WorldServer : public Server
{
protected:
    friend class GameClient;

    /// The name of the realm handled by this server
    char *RealmName;
    /// Current date+time in the game
    time_t GameTime;
    /// The limit on the number of simultaneously connected clients
    uint ClientLimit;
    /// The starting zone: 0 - normal, 1 - human
    uint StartZone;
    /// Enable or disable the cinematics
    bool Cinematics;
    /// Message Of The Day
    char *MOTD;
    /// The list of clients sorted by login
    DECLARE_VECTOR_SORTED (SortedClientsVector, GameClient *,) SortedClients;
    /// Some counter increased by 1 on every authentification
    uint8 AuthCount;
    /// GUID pools: last used 32-bit GuidLow
    Vector GuidPool;

    // Private destructor (use DecRef)
    virtual ~WorldServer ();

    /// Delete client by index
    virtual void DeleteClient (uint iIndex);

    /// Load the GUID pool
    bool LoadGuidPool ();
    /// Save the GUID pool
    void SaveGuidPool ();

public:
    /// The world data base object
    Database *db;
    /// The realm data base object
    Database *rdb;
    /// Game features (see GF_XXX flags)
    uint GameFeatures;
    /// Global Lua interpreter state
    lua_State *Lua; // tolua_hide

    /**
     * World server constructor
     * @arg iPort
     *   Port number to listen on
     * @arg iLogger
     *   The logger used to log interesting events
     */
    WorldServer (uint iPort, Log *iLogger);

    /// Update the status of this realm (on logins/logouts)
    void UpdateRealm (bool Online);

    /// Handle socket events
    virtual void SocketEvent (uint mask);

    /**
     * Override the Server::Start() method to perform additional
     * initialization before server actually starts
     */
    virtual bool Start ();

    /**
     * Perform additional operations on server shutdown.
     */
    virtual void Stop ();

    /// Update the world every frame
    virtual void Update (uint32 DeltaMs);

    /// Set the database interface objects
    void SetDatabase (Database *iwdb, Database *irdb);

    /// Get the name of this realm
    const char *GetRealmName ()
    { return RealmName; }
    /// Change realm name
    void SetRealmName (const char *iRealmName)
    { delete [] RealmName; RealmName = strnew (iRealmName); }

    /// Get current time in the game
    time_t GetGameTime ()
    { return GameTime; };

    /// Get the client limit
    inline uint GetClientLimit ()
    { return ClientLimit; }
    // @@@todo: Kick excess players off server?
    inline void SetClientLimit (int Limit)
    { ClientLimit = Limit; }

    /// Get players start zone
    inline uint GetStartZone ()
    { return StartZone; }
    /// Set start zone for new players
    inline void SetStartZone (int Zone)
    { StartZone = Zone; }

    /// Get the 'show cinematics on new character' flag
    inline bool GetCinematics ()
    { return Cinematics; }
    /// Set the 'show cinematics on new character' flag
    inline void SetCinematics (bool Enable)
    { Cinematics = Enable; }

    /// Set Message Of The Day
    void SetMotd (const char *motd)
    { delete [] MOTD; MOTD = strnew (motd); }
    /// Get current Message Of The Day
    const char *GetMotd ()
    { return MOTD; }

    /// Query how many clients are connected right now
    uint32 GetClientsConnected ()
    { return SortedClients.Length (); }

    /**
     * Send a packet to every client connected to the world server,
     * except the Client specified as Self (which can be NULL)
     */
    void SendGlobalPacket (NetworkPacket *data, GameClient *Self);

    /**
     * Send a text message to all the connected users except the client
     * specified by the Self variable (which can be NULL)
     */
    void SendGlobalMessage (const char *iText, GameClient *Self);

    /**
     * Generate a new Globally Unique IDentifier (haha) having given
     * high 32 bits.
     * @arg GuidHigh
     *   The top 32 bits of the generated GUID
     * @return
     *   A new GUID
     */
    uint64 GenerateGUID (uint32 GuidHigh);

    /**
     * Start global Lua interpreter
     */
    void StartLua (); // tolua_hide
};

/// The static pointer to the only WorldServer object
extern WorldServer *World; // tolua_hide

/// Easy access to logger
#define LOG     (*World->Logger) // tolua_hide

#endif // __WORLD_SERVER_H__
