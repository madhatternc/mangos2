/**
 *     \file  src/shared/Database.cpp
 * @brief General database interface
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

#include <stdlib.h>
#include <stdarg.h>

#include "Database.h"
#include "DatabaseMySQL.h"
#include "StringFun.h"
#include "Log.h"

Database::Database ()
{
    Logger = NULL;
    ExecutorsMutex = Mutex::Create ();
}

Database::~Database ()
{
    ExecutorsMutex->DecRef ();
    SetLogger (NULL);
}

Database *Database::Create (DatabaseType dbType, const char *dbAddress)
{
    Database *db;
    switch (dbType)
    {
        case dbMySQL:
            db = new DatabaseMySQL ();
            break;
        default:
            return ERR_PTR (dbeBadArguments, Database);
    }

    DatabaseError dbe = db->Open (dbAddress);
    if (dbe != dbeOk)
    {
        db->DecRef ();
        return ERR_PTR (dbe, Database);
    }

    return db;
}

DatabaseType Database::ParseType (const char *dbType)
{
    char buff [32];
    nstrcpy (buff, ARRAY_LEN (buff), dbType);
    trim (buff);
    lowerstr (buff);
    if (strcmp (buff, "mysql") == 0)
        return dbMySQL;
    return dbUnknown;
}

const char *Database::ErrorString (DatabaseError err)
{
    switch (err)
    {
        case dbeOk:
            return "No error";
        case dbeBadArguments:
            return "Bad function arguments";
        case dbeConnectionFailed:
            return "Connection to server failed";
        case dbeWrongCredentials:
            return "Wrong username/password";
        case dbeConnectionLost:
            return "Connection to server unexpectedly closed or lost";
        case dbeInvalidQuery:
            return "Invalid database query";
        default:
            return "Unknown error";
    }
}

DatabaseExecutor *Database::GetExecutor ()
{
    DatabaseExecutor *dbex;
    ExecutorsMutex->Lock ();
    if (Executors.Length ())
    {
        // Pop doesn't decrement refcount to prevent object destruction
        dbex = (DatabaseExecutor *)Executors.Pop ();
        ExecutorsMutex->Unlock ();
    }
    else
    {
        ExecutorsMutex->Unlock ();
        dbex = CreateExecutor ();
        if (IS_ERR (dbex))
            return NULL;
    }
    return dbex;
}

void Database::PutExecutor (DatabaseExecutor *dbEx)
{
#ifdef DEBUG
    if (dbEx->GetParent () != this)
    {
        DEBUG_PRINTF ("ERROR: Returning an DatabaseExecutor for the wrong Database!!!");
        dbEx->DecRef ();
        return;
    }
#endif

    // We don't want dead executors :)
    if (dbEx->Ok ())
    {
        dbEx->Free ();
        ExecutorsMutex->Lock ();
        Executors.Push (dbEx);
        ExecutorsMutex->Unlock ();
    }
    // Push increments refcount
    dbEx->DecRef ();
}

void Database::SetLogger (Log *iLogger)
{
    if (Logger != iLogger)
    {
        if (Logger)
            Logger->DecRef ();
        if ((Logger = iLogger))
            Logger->IncRef ();
    }
}

//--------------------------------------------------------------------------------------//

DatabaseError DatabaseExecutor::ExecuteF (const char *QueryF, ...)
{
    // Support SQL queries up to 16k
    char buff [4096 * 4];
    va_list args;
    va_start (args, QueryF);
    vsnprintf (buff, sizeof (buff), QueryF, args);
    va_end (args);
    return Execute (buff);
}

int32 DatabaseExecutor::GetI32 (uint i)
{
    const char *s = Get (i);
    if (!s)
        return 0; // dunno what really we can return here :)
    return strtol (s, NULL, 0);
}

uint32 DatabaseExecutor::GetU32 (uint i)
{
    const char *s = Get (i);
    if (!s)
        return 0; // dunno what really we can return here :)
    return strtoul (s, NULL, 0);
}

uint64 DatabaseExecutor::GetU64 (uint i)
{
    const char *s = Get (i);
    if (!s)
        return 0; // dunno what really we can return here :)
    return strtoull (s, NULL, 0);
}

float DatabaseExecutor::GetFloat (uint i)
{
    const char *s = Get (i);
    if (!s)
        return 0; // dunno what really we can return here :)
    return strtod (s, NULL);
}
