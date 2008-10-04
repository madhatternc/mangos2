/**
 *     \file  src/shared/DatabaseMySQL.h
 *    \brief  MySQL database interface
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

#ifndef __DATABASE_MYSQL_H__
#define __DATABASE_MYSQL_H__

#include "Database.h"

/**
 *  \addtogroup DatabaseClasses
 *
 *  @{
 */

/**
 * A variant of the Database interface running on top of MySQL.
 * Database address format is as follows:
 *
 * [host[:port]],user,password,database
 *
 * host can be omited, in which case it is assumed "127.0.0.1"
 * port can be omited, in which case it is assumed 3306
 * if both host and port are omited, database address must start with ','
 */
class DatabaseMySQL : public Database
{
	protected:
		char *Host;
		int Port;
		char *User;
		char *Password;
		char *Database;

		virtual ~DatabaseMySQL ();

		virtual DatabaseError Open (const char *dbAddress);

		/**
		 * Create a Database Executor object, suitable for issuing
		 * SQL requests and then working with the results.
		 * @return
		 *    A new object or NULL if we're out of resources.
		 */
		virtual DatabaseExecutor *CreateExecutor ();
	public:
};

/**
 *  @}
 */
#endif														// __DATABASE_MYSQL_H__
