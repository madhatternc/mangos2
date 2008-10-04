/**
 *     \file  src/shared/Server.cpp
 *    \brief  Network Server abstraction
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
#include "SystemFun.h"

Server::Server (uint iPort, uint iStepTime, Log *iLogger)
: Client (NULL), Clients (16, 16), Running (false)
{
	Port = iPort;
	StepTimeMs = iStepTime;
	MainThread = NULL;
	SetLogger (iLogger);
}

Server::~Server ()
{
	Stop ();
}

bool Server::Start ()
{
	if (!Running)
	{
		socket = Socket::Listen (Port, Logger);
		if (!socket)
			return false;

		Running = true;
		Die = false;
		Tick = GetMilliseconds ();
		MainThread = Thread::Start (KickMainLoop, this);
		if (!MainThread)
		{
			CONSOLE.Out ("\axeFailed to create server thread\n");
			socket->DecRef ();
			socket = NULL;
			Running = false;
			return false;
		}
		MainThread->SetPriority (Thread::HIGHER);
	}
	return Running;
}

void Server::Stop ()
{
	if (!MainThread)
		return;

	// Mark ourselves as bleeding
	Die = true;
	// Wait for the server thread to shut down then force it down anyways
	SleepMs ((StepTimeMs * 5) / 4);
	// Kill server thread
	if (MainThread)
	{
		MainThread->DecRef ();
		MainThread = NULL;
	}
	if (socket)
	{
		socket->DecRef ();
		socket = NULL;
	}
	// Kick all clients
	Clients.DeleteAll ();
	Running = false;
}

void Server::KickMainLoop (void *arg)
{
	((Server *)arg)->MainLoop ();
}

void Server::MainLoop ()
{
	// Add ourselves to the start of list of clients
	// so that we can receive socket events
	Clients.Insert (0, this);

	while (!Die)
	{
		uint32 OldTick = Tick;
		Tick = GetMilliseconds ();
		// We don't really care about overflows since the time
		// difference will be always valid (unless the interval
		// between two frames will not exceed ~1193046 hours :)
		Update (Tick - OldTick);
		// Handle all new socket events, and remove dead clients
		WaitSocketEvents ();
	}

	// Remove ourselves from the list of clients
	// NOTE: This may be the last reference to our object, so make
	// sure this statement comes last in this function
	if (GetRefCount () == 1)
		Clients.DeleteAll ();
	else
		Clients.Delete (0);
}

void Server::SetLogger (Log *iLogger)
{
	if (Logger)
		Logger->DecRef ();
	Logger = iLogger;
	if (Logger)
		Logger->IncRef ();
}

void Server::DeleteClient (uint iIndex)
{
	Clients.Delete (iIndex);
}
