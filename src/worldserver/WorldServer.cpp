/**
 *     \file  src/worldserver/WorldServer.cpp
 *    \brief  Provides a basic implementation of the World server class.
 *
 * Copyright (C) 2005 Team OpenWoW <http://openwow.quamquam.org/>
 * Copyright (C) 2008 MaNGOS foundation <http://www.getmangos.com/>
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

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include "tolua++.h"
#include "Luawrapper.h"

#include <time.h>

#include "WorldServer.h"
#include "Database.h"
#include "GameClient.h"
#include "Player.h"
#include "version.h"

// Fool the IMPLEMENT_VECTOR_SORTED macro :)
// We don't need any freeing of the vector elements since they are contained
// in two vectors at once: in Clients and in SortedClients.
#undef IMPLEMENT_VECTOR
#define IMPLEMENT_VECTOR(Namespace, VType, CType) \
    Namespace VType::~VType () {} \
    void Namespace VType::FreeItem (Some Item) const {}

IMPLEMENT_VECTOR_SORTED_STRKEY (WorldServer::, SortedClientsVector, GameClient *, Login)

//----------------------------------------------------------------------------//

/// The static pointer to the only WorldServer object
WorldServer *World;

WorldServer::WorldServer (uint iPort, Log *iLogger) : Server (iPort, 100, iLogger),
GuidPool (16, 16)
{
    World = this;
    RealmName = strnew ("Local realm");
    MOTD = strnew ("Welcome!");
    ClientLimit = DEFCLIENTLIMIT;
    StartZone = DEFSTARTHUMANZONE;
    Cinematics = DEFSHOWINTRO;
    AuthCount = 0;
    GameFeatures = 0;

    db = rdb = NULL;

    // Set game time to current time
    time_t t = time(NULL);
    struct tm *tms = localtime (&t);
    GameTime = (3600 * tms->tm_hour) + (tms->tm_min * 60) + (tms->tm_sec);

    // Initialize the Random Number Generator
    srand (t);

    StartLua ();
}

WorldServer::~WorldServer()
{
    lua_close (Lua);

    if (db)
        db->DecRef ();
    if (rdb)
        rdb->DecRef ();

    delete [] MOTD;
    delete [] RealmName;
}

void WorldServer::SetDatabase (Database *iwdb, Database *irdb)
{
    if (iwdb != db)
    {
        if (db)
            db->DecRef ();
        if ((db = iwdb))
        {
            db->IncRef ();
            db->SetLogger (Logger);
        }
    }
    if (irdb != rdb)
    {
        if (rdb)
            rdb->DecRef ();
        if ((rdb = irdb))
        {
            rdb->IncRef ();
            rdb->SetLogger (Logger);
        }
    }
}

void WorldServer::SocketEvent (uint mask)
{
    if (mask & PF_READ)
    {
        Socket *sock = socket->Accept ();
        if (!sock)
            return;
        GameClient *c = new GameClient (sock);
        AddClient (c);
        // Free local references to refcounted objects
        c->DecRef ();
        sock->DecRef ();
    }
}

bool WorldServer::Start ()
{
    if (!db || !rdb)
        return false;

    if (!Player::PreloadStaticData ())
        return false;
    if (!Item::PreloadStaticData ())
    {
        error1: Player::UnloadStaticData ();
        return false;
    }
    if (!LoadGuidPool ())
    {
        Item::UnloadStaticData ();
        goto error1;
    }

    if (!Server::Start ())
        goto error1;

    UpdateRealm (true);
    return true;
}

void WorldServer::Stop ()
{
    UpdateRealm (false);
    Server::Stop ();

    // Clear out sorted client list -- just in case
    SortedClients.DeleteAll ();

    Item::UnloadStaticData ();
    Player::UnloadStaticData ();
    SaveGuidPool ();
}

void WorldServer::UpdateRealm (bool Online)
{
    DatabaseExecutor *dbex = rdb->GetExecutor ();
    uint numpl = Online ? GetClientsConnected () : 0;
    uint color = ClientLimit ? ((float (numpl) / ClientLimit) > 0.75 ? 1 : 0) : 0;
    dbex->ExecuteF ("UPDATE realms SET players=%d,online=%d,color=%d WHERE name='%s'",
        numpl, Online ? 1 : 0, color, RealmName);
    rdb->PutExecutor (dbex);
}

void WorldServer::Update (uint32 DeltaMs)
{
}

void WorldServer::SendGlobalPacket (NetworkPacket *data, GameClient *Self)
{
    //@@@todo
    for (int i = Clients.Length () - 1; i >= 0; i--)
    {
        //      GameClient *c = (GameClient *)Clients.Get (i);
        //      if (c != Self && c->Authenticated ())
        //          c->sock->SendData (data);
    }
}

void WorldServer::SendGlobalMessage (const char *iText, GameClient *Self)
{
    //@@@todo
}

void WorldServer::DeleteClient (uint iIndex)
{
    GameClient *c = (GameClient *)Clients.Get (iIndex);
    int idx = SortedClients.FindSortedKey (c->Login);
    DEBUG_BREAK_IF (idx < 0);
    DEBUG_PRINTF ("Removing client %s, index %d\n", c->Login, idx);
    if (idx >= 0)
        SortedClients.Delete (idx);
    Server::DeleteClient (iIndex);
}

bool WorldServer::LoadGuidPool ()
{
    GuidPool.DeleteAll ();

    DatabaseExecutor *dbex = db->GetExecutor ();
    if (dbex->Execute ("SELECT * FROM guid_pool") != dbeOk)
    {
        Logger->Out (LOG_IMPORTANT, "Failed to load GUID pools from database!\n");
        db->PutExecutor (dbex);
        return false;
    }

    while (dbex->NextRow ())
    {
        GuidPool.Push (Some (dbex->GetU32 (0)));
        GuidPool.Push (Some (dbex->GetU32 (1)));
    }
    db->PutExecutor (dbex);
    return true;
}

void WorldServer::SaveGuidPool ()
{
    DatabaseExecutor *dbex = db->GetExecutor ();
    for (int i = 0; i < GuidPool.Length (); i += 2)
        if ((dbex->ExecuteF ("UPDATE guid_pool SET guid_low=%lu WHERE guid_high=%lu",
        GuidPool.Get (i + 1), GuidPool.Get (i)) != dbeOk)
        || !dbex->GetAffectedRows ())
            dbex->ExecuteF ("INSERT INTO guid_pool (guid_high, guid_low) VALUES (%lu,%lu)",
                GuidPool.Get (i), GuidPool.Get (i + 1));
    db->PutExecutor (dbex);
}

uint64 WorldServer::GenerateGUID (uint32 GuidHigh)
{
    int i;
    for (i = 0; i < GuidPool.Length (); i += 2)
        if (GuidPool.Get (i) == Some (GuidHigh))
    {
        uint32 *gl = (uint32 *)&GuidPool.Get (i + 1);
        return ++*gl;
    }

    GuidPool.Push (Some (GuidHigh));
    // Don't start at zero... dunno why but maybe that could be useful later
    GuidPool.Push (Some (1));
    return 1;
}

void WorldServer::StartLua ()
{
    Lua = lua_open ();
    /* opens the basic library */
    luaopen_base (Lua);
    /* opens the table library */
    luaopen_table (Lua);
    /* opens the I/O library */
    luaopen_io (Lua);
    /* opens the string lib. */
    luaopen_string (Lua);
    /* opens the math lib. */
    luaopen_math (Lua);
    /* opens worldsrv wrapper */
    tolua_worldsrv_open (Lua);
    // Add World to the global table
    tolua_pushusertype (Lua, (void *)this,"WorldServer");
    lua_setglobal (Lua, "World");
}
