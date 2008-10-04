/**
 *     \file  src/shared/win/WaitSockets.cpp
 *    \brief  Wait on sockets for events
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

#include "Server.h"

void Server::WaitSocketEvents ()
{
	int nfds = 0;
	fd_set rfds, wfds, efds;

	FD_ZERO (&rfds);
	FD_ZERO (&wfds);
	FD_ZERO (&efds);

	int i;
	for (i = Clients.Length () - 1; i >= 0; i--)
	{
		Client *c = (Client *)Clients.Get (i);
		if (i && !c->socket->Connected ())
		{
			// Remove dead clients from the queue immediately
			DeleteClient (i);
			continue;
		}

		socket_t sh = c->socket->GetHandle ();
		uint ev = c->socket->InterestedEvents ();
		if (ev)
		{
			if (ev & PF_READ)
				FD_SET (sh, &rfds);
			if (ev & PF_WRITE)
				FD_SET (sh, &wfds);
			if (ev & PF_EXCEPT)
				FD_SET (sh, &efds);
			if (sh >= nfds)
				nfds = sh + 1;
		}
	}

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = StepTimeMs * 1000;

	int nh = select (nfds, &rfds, &wfds, &efds, &tv);

	// No events, or an error?
	DEBUG_BREAK_IF (nh == SOCKET_ERROR);
	if (nh == 0 || nh == SOCKET_ERROR)
		return;

	for (i = Clients.Length () - 1; i >= 0; i--)
	{
		Client *c = (Client *)Clients.Get (i);
		socket_t sh = c->socket->GetHandle ();
		uint ev = 0;
		if (FD_ISSET (sh, &rfds))
		{
			ev |= PF_READ;
			// Client 0 is always ourselves
			if (i)
				c->socket->ReceiveData ();
		}
		if (FD_ISSET (sh, &wfds))
		{
			ev |= PF_WRITE;
			// Client 0 is always ourselves
			if (i)
				c->socket->SendPending ();
		}
		if (FD_ISSET (sh, &efds))
			ev |= PF_EXCEPT;
		if (ev)
		{
			c->SocketEvent (ev);
			if (i && !c->socket->Connected ())
			{
				// Remove dead clients from the queue immediately
				DeleteClient (i);
				continue;
			}
		}
	}
}
