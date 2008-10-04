/**
 *     \file  src/shared/Client.h
 *    \brief  Network Client abstraction
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

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "Base.h"
#include "Sockets.h"

/**
 *  \addtogroup NetworkClasses
 *
 *  @{
 */

class Server;

/**
 *  \class Client
 *  \brief Abstraction class for any client connection of a network server.
 *
 *  \details
 *  This is an abstraction class for any client connection of a network Server.
 *  It holds the client connection socket, and receives notifications about
 *  incoming events.
 */
class Client : public Base
{
	protected:
		friend class Server;

		/**
		 *  \brief The client socket
		 */
		Socket *socket;

		/**
		 *  \brief Private destructor -- use DecRef () instead
		 */
		virtual ~Client ();

	public:
		/**
		 *  \brief Create the client object listening to this socket
		 */
		Client (Socket *sock);								//tolua_hide abstract class can't be allociated

		/**
		 *  \brief Called when any event happens with the socket.
		 *
		 *  \details
		 *  Called when any event (one of those requested by socket->InterestedEvents())
		 *  happens with the socket.
		 *
		 *  \arg \c mask Event mask (a combination of PF_XXX flags)
		 */
		virtual void SocketEvent (uint mask) = 0;
};

/**
 *  @}
 */
#endif														// __CLIENT_H__
