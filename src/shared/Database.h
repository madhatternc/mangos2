/**
 *     \file  src/shared/Database.h
 *    \brief  General database interface
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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "Common.h"
#include "BaseVector.h"
#include "ThreadFun.h"

/**
 *  \defgroup DatabaseClasses Database Classes
 */

/**
 *  \addtogroup DatabaseClasses
 *
 *  @{
 */

/**
 *  \enum DatabaseError
 *  \brief Error codes for database operations.
 */
enum DatabaseError
{
    /**
     *  \brief Everything in good shape.
     */
    dbeOk = 0,

    /**
     *  \brief Bad function arguments
     */
    dbeBadArguments,

    /**
     *  \brief Connection to server failed
     */
    dbeConnectionFailed,

    /**
     *  \brief Wrong username/password
     */
    dbeWrongCredentials,

    /**
     *  \brief Connection to server unexpectedly closed or lost
     */
    dbeConnectionLost,

    /**
     *  \brief Invalid database query
     */
    dbeInvalidQuery
};

/**
 *  \enum DatabaseType
 *  \brief Supported database types
 */
enum DatabaseType
{
    dbUnknown = 0,
    dbMySQL
};

class DatabaseExecutor;
class Log;

/**
 *  \class Database
 *  \brief Generic database interface.
 *
 *  \details
 *  This is a generic interface to any supported SQL database.
 *
 *  \note
 *  There's only one object of this type and all database queries
 *  are going through this object.
 */
class Database : public Base
{
    protected:
        /// Utility class: vector of unsorted DatabaseExecutor's
        //tolua_begin_hide
        class ExecutorPool : public BaseVector
        {
            public:
                ExecutorPool () : BaseVector (16, 16) {}
                DatabaseExecutor *Get (int iIndex)
                    { return (DatabaseExecutor *)Vector::Get (iIndex); }
        } Executors;
        //tolua_end_hide
        Mutex *ExecutorsMutex;

        Database ();
        virtual ~Database ();
        virtual DatabaseError Open (const char *dbAddress) = 0;

        /**
         *  \brief Create a Database Executor object
         *
         *  \details
         *  Create a Database Executor object, suitable for issuing
         *  SQL requests and then working with the results.
         *
         *  \return A new object or NULL if we're out of resources.
         */
        virtual DatabaseExecutor *CreateExecutor () = 0;

    public:
        /**
         *  \brief The logger object associated with this database
         */
        Log *Logger;

        /**
         *  \brief Create a new database interface.
         *
         *  \arg \c dbType
         *    The type of database (see DatabaseType)
         *  \arg \c dbAddress
         *    Database address/user/password/whatever. The exact format
         *    of this parameter depends of the database backend.
         */
        static Database *Create (DatabaseType dbType, const char *dbAddress);

        /**
         * Parse a string (like MySQL etc) and return the corresponding
         *
         * @arg
         *   A case-insensitive string that is examined for a vague remind
         *   of some known database type.
         * @return
         *   dbUnknown if string cannot be parsed
         */
        /**
         *  \brief Parse a string and return the database type.
         *
         *  \details
         *  Parse a string (like MySQL etc) and return the corresponding
         *  constant of the DatabaseType type.
         *
         *  \arg \c dbType
         *    A case-insensitive string that is examined for a vague remind
         *    of some known database type.
         *  \return
         *    dbUnknown if string cannot be parsed
         */
        static DatabaseType ParseType (const char *dbType);

        /**
         *  \brief Query the error string corresponding to given error code.
         */
        static const char *ErrorString (DatabaseError err);

        /**
         * Get a spare or create a new Database Executor object, suitable
         * for issuing SQL requests and then working with the results.
         * @return
         *    A new object or NULL if we're out of resources.
         */
        DatabaseExecutor *GetExecutor ();

        /**
         *  \brief Return a executor to the pool of spare executors.
         *
         *  \arg \c dbEx
         *    Pointer to executor got by a previous call to GetExecutor().
         */
        void PutExecutor (DatabaseExecutor *dbEx);

        /**
         *  \brief Set up the logger object used to log database errors.
         */
        void SetLogger (Log *iLogger);
};

/**
 *  \class DatabaseExecutor
 *  \brief Generic database query execution.
 *
 *  \details
 *  This is the interface to a object that can execute SQL queries.
 *
 *  \par
 *  The object changes its state while executing the query, so you
 *  can't execute several queries in parralel with it: create several
 *  such objects if you need parralel queries.
 */
class DatabaseExecutor : public Base
{
    protected:
        /// Parent database object
        Database *Parent;

    public:
        /// Initialize the database executor skeleton
        DatabaseExecutor (Database *iParent)                //tolua_hide
        {                                                   //tolua_hide
            Parent = iParent;
        }

        Database *GetParent ()
            { return Parent; }

        /// Check if the executor is still okay (connected to database etc)
        virtual bool Ok () = 0;

        /// Free all the results of the previous query
        virtual void Free () = 0;

        /**
         * Execute a query and return success status.
         * After a successful query execution you can examine NumFields() to see
         * how many fields you got, and you must call NextRow() before examining
         * any of the results with Get().
         * @arg Query
         *   The SQL query to execute
         */
        virtual DatabaseError Execute (const char *Query) = 0;

        /**
         * Same but allows printf-like string formatting.
         * The resulting query length must not exceed 4k
         */
        DatabaseError ExecuteF (const char *QueryF, ...);   //tolua_hide

        /// Get the number of fields in the result
        virtual int NumFields () = 0;

        // Get the number of Rows in a result
        virtual int NumRows () = 0;

        /**
         * Process to next row of the result
         * @return
         *   bool if row is valid, false if end of data reached
         */
        virtual bool NextRow () = 0;

        /**
         * Get the i-th result in current row.
         * Before calling this function you must call NextRow() at least once.
         */
        virtual const char *Get (uint i) = 0;

        /**
         * Get the length in bytes of i-th result in current row.
         * Use if you store in database something like binary blobs.
         */
        virtual uint GetLength (uint i) = 0;

        /**
         * Wrapper around Get() to convert the string to int32.
         */
        int32 GetI32 (uint i);

        /**
         * Wrapper around Get() to convert the string to uint32.
         */
        uint32 GetU32 (uint i);

        /**
         * Wrapper around Get() to convert the string to uint64.
         */
        uint64 GetU64 (uint i);

        /**
         * Wrapper around Get() to convert the string to float.
         */
        float GetFloat (uint i);

        /**
         * Get the value of the last modified auto-increment field of database.
         */
        virtual uint64 GetID () = 0;

        /**
         * Return number of affected rows by the last query.
         */
        virtual uint GetAffectedRows () = 0;
};

/**
 *  @}
 */
#endif                                                      // __DATABASE_H__
