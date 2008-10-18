/**
 *     \file  src/shared/DatabaseMySQL.cpp
 *    \brief  MySQL database interface
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

#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>

#include "DatabaseMySQL.h"
#include "StringFun.h"
#include "Log.h"

/**
 * This is the interface to a object that can execute SQL queries.
 * The object changes its state while executing the query, so you
 * can't execute several queries in parralel with it: create several
 * such objects if you need parralel queries.
 */
class DatabaseMySQLExecutor : public DatabaseExecutor
{
protected:
    friend class DatabaseMySQL;

    MYSQL *Handle;
    MYSQL_RES *Result;
    MYSQL_ROW Row;
    ulong *ResultLength;

    DatabaseMySQLExecutor (Database *iParent, MYSQL *iHandle);
    virtual ~DatabaseMySQLExecutor ();

public:
    /// Check if the executor is still okay (connected to database etc)
    virtual bool Ok ();

    /// Free all the results of the previous query
    virtual void Free ();

    /// Execute a query and return success status
    virtual DatabaseError Execute (const char *Query);

    /// Get the number of fields in the result
    virtual int NumFields ();

    /// Get the number of rows in a result
    virtual int NumRows ();

    /**
     * Process to next row of the result
     * @return
     *   bool if row is valid, false if end of data reached
     */
    virtual bool NextRow ();

    /**
     * Get the i-th result in current row.
     * Before calling this function you must call NextRow() at least once.
     */
    virtual const char *Get (uint i);

    /**
     * Get the length in bytes of i-th result in current row.
     * Use if you store in database something like binary blobs.
     */
    virtual uint GetLength (uint i);

    /**
     * Get the value of the last modified auto-increment field of database.
     */
    virtual uint64 GetID ();

    /**
     * Return number of affected rows by the last query.
     */
    virtual uint GetAffectedRows ();
};

DatabaseMySQLExecutor::DatabaseMySQLExecutor (Database *iParent, MYSQL *iHandle)
    : DatabaseExecutor (iParent)
{
    Handle = iHandle;
    Result = NULL;
    ResultLength = NULL;
    Row = NULL;
}

DatabaseMySQLExecutor::~DatabaseMySQLExecutor ()
{
    Free ();
    mysql_close (Handle);
}

bool DatabaseMySQLExecutor::Ok ()
{
    switch (mysql_errno (Handle))
    {
        case CR_SERVER_GONE_ERROR:
        case CR_SERVER_LOST:
        case ER_SERVER_SHUTDOWN:
        case ER_ABORTING_CONNECTION:
            return false;
    }
    return true;
}

void DatabaseMySQLExecutor::Free ()
{
    if (Result)
    {
        mysql_free_result (Result);
        Result = NULL;
    }
    ResultLength = NULL;
}

DatabaseError DatabaseMySQLExecutor::Execute (const char *Query)
{
    Free ();

    if (!mysql_query (Handle, Query))
        return dbeOk;

    if (Parent->Logger)
    {
        char short_query [200];
        const char *query = Query;
        size_t sl = strlen (query);
        if (sl >= sizeof (short_query))
        {
            memcpy (short_query, query, sizeof (short_query) - 6);
            strcpy (short_query + sizeof (short_query) - 6, "(...)");
            query = short_query;
        }
        Parent->Logger->Out (LOG_IMPORTANT, "Error %d in query `%s': %s\n",
                             mysql_errno (Handle), query, mysql_error (Handle));
    }
    switch (mysql_errno (Handle))
    {
        case CR_SERVER_GONE_ERROR:
        case CR_SERVER_LOST:
        case ER_SERVER_SHUTDOWN:
        case ER_ABORTING_CONNECTION:
        {
            if (!mysql_ping (Handle) && !mysql_query (Handle, Query))
            {
                DEBUG_PRINTF ("Connection broke but was successfully restored\n");
                return dbeOk;
            }
            DEBUG_PRINTF ("Connection broke and the attempt to restore it failed\n");
            return dbeConnectionLost;
        }
        default:
            return dbeInvalidQuery;
    }
}

int DatabaseMySQLExecutor::NumFields ()
{
    if (!Result)
    {
        Result = mysql_store_result (Handle);
        if (!Result)
            return false;
    }
    return mysql_num_fields (Result);
}

int DatabaseMySQLExecutor::NumRows ()
{
    if (!Result)
    {
        Result = mysql_store_result (Handle);
        if (!Result)
            return false;
    }
    return mysql_num_rows (Result);
}

bool DatabaseMySQLExecutor::NextRow ()
{
    if (!Result)
    {
        Result = mysql_store_result (Handle);
        if (!Result)
            return false;
    }
    Row = mysql_fetch_row (Result);
    return (Row != NULL);
}

const char *DatabaseMySQLExecutor::Get (uint i)
{
    if (!Result || !Row)
        return NULL;

#ifdef DEBUG
    // Non-effective for release builds, but helps catching bugs
    if (i >= mysql_num_fields (Result))
    {
        DEBUG_PRINTF ("Out of bounds result index %d (max: %d)!!!\n",
                  i, mysql_num_fields (Result));
        return NULL;
    }
#endif

    return Row [i];
}

uint DatabaseMySQLExecutor::GetLength (uint i)
{
    if (!Result || !Row)
        return 0;

    if (!ResultLength)
    {
        ResultLength = mysql_fetch_lengths (Result);
        if (!ResultLength)
        {
            DEBUG_PRINTF ("Failed to fetch result lengths, field %d\n", i);
            return 0;
        }
    }
    return ResultLength [i];
}

uint64 DatabaseMySQLExecutor::GetID ()
{
    return mysql_insert_id (Handle);
}

uint DatabaseMySQLExecutor::GetAffectedRows ()
{
    return mysql_affected_rows (Handle);
}

//---------------------------------------------------------------------------//

DatabaseMySQL::~DatabaseMySQL ()
{
    delete [] Host;
    delete [] User;
    delete [] Password;
    delete [] Database;
}

DatabaseError DatabaseMySQL::Open (const char *DatabaseAddress)
{
    // Parse database address
    char *params [4];
    const char *cur = DatabaseAddress;

    for (uint i = 0; i < ARRAY_LEN (params); i++)
    {
        const char *next;
        if (i < ARRAY_LEN (params) - 1)
        {
            next = strchr (cur, ',');
            if (!*next)
            {
                while (--i >= 0)
                    delete [] params [i];
                return dbeBadArguments;
            }
        }
                else
            next = strchr (cur, 0);

        params [i] = strnew (cur, next - cur);
        cur = next + 1;
    }

    // Split host into host and port
    Port = 3306;
    cur = strchr (params [0], ':');
    if (cur)
    {
        Port = atoi (cur + 1);
        *(char *)cur = 0;
    }
    if (!*params [0])
    {
        delete [] params [0];
        params [0] = strnew ("127.0.0.1");
    }

    Host = params [0];
    User = params [1];
    Password = params [2];
    Database = params [3];

    // Try a test connection now
    DatabaseExecutor *dbex = CreateExecutor ();
    if (IS_ERR (dbex))
        return DatabaseError (PTR_ERR (dbex));
    else
        PutExecutor (dbex);

    return dbeOk;
}

DatabaseExecutor *DatabaseMySQL::CreateExecutor ()
{
    MYSQL *handle = mysql_init (NULL);
    if (!mysql_real_connect (handle, Host, User, Password, Database,
                 Port, NULL, CLIENT_FOUND_ROWS))
    {
        if (Logger)
            Logger->Out (LOG_IMPORTANT, "Error %d connecting to database: %s\n",
                         mysql_errno (handle), mysql_error (handle));
        switch (mysql_errno (handle))
        {
            case ER_PASSWORD_NO_MATCH:
            case ER_PASSWORD_NOT_ALLOWED:
            case ER_PASSWORD_ANONYMOUS_USER:
                return ERR_PTR (dbeWrongCredentials, DatabaseExecutor);
            default:
                return ERR_PTR (dbeConnectionFailed, DatabaseExecutor);
        }
        return NULL;
    }

    return new DatabaseMySQLExecutor (this, handle);
}
