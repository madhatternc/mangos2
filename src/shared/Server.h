/**
 *     \file  src/shared/Server.h
 *    \brief  Network Server abstraction
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

#ifndef __SERVER_H__
#define __SERVER_H__

#include "Client.h"
#include "ThreadFun.h"
#include "Log.h"

/**
 * This is an abstract server that listens on some TCP port for incoming
 * connections and forks a new socket for every one. For every new connection
 * it creates a new Client object and then handles all the input/output
 * for all sockets.
 */
class Server : public Client
{
protected:
    /// The list of connected clients (Client *)
    BaseVector Clients;

    /// Port this server is listening on
    int Port;

    /// Max milliseconds between calls to Update ()
    int StepTimeMs;

    /// Is this server accepting connections?
    bool Running;

    /// Has this server been instructed to stop?
    bool Die;

    /// The thread object of the main server thread
    Thread *MainThread;

    /// Main server loop: does all the dirty work
    void MainLoop ();

    /// Callback function for the thread
    static void KickMainLoop (void *arg);

    /// Called not less than once in StepTimeMs milliseconds
    virtual void Update (uint32 DeltaMs) { (void)DeltaMs; }

    /// Wait on the listening and all client sockets for incoming events
    void WaitSocketEvents ();

    /// Delete given client by index
    virtual void DeleteClient (uint iIndex);

public:
    /// Time when the tick started
        uint32 Tick;

    /// The logger for this server
    Log *Logger;

    /**
     * Initialize the server.
     * @arg port
     *   Port number the server is listening to
     * @arg steptime
         *   Maximum delta time between calls to Update()
     * @arg iLogger
     *   The logger to log socket events on
         */
    Server (uint iPort, uint iStepTime, Log *iLogger); //tolua_hide
    /// Destructor
    virtual ~Server (); //tolua_hide

    /// Start listening for inbound connections
    virtual bool Start ();

    /// Stop accepting connections and disconnect all clients
    virtual void Stop ();

    /// Check if server is running
    bool IsRunning ()
    { return Running; }

    /// Add a client forked off the main socket (usually after accept())
    void AddClient (Client *client)
    { Clients.Push (client); }

    /**
     * Called when any event (one of those requested by socket->InterestedEvents())
     * happens with the socket.
     * @arg mask
     *   Event mask (a combination of PF_XXX flags)
     */
    virtual void SocketEvent (uint mask) = 0;

    /// Set the logger used to log miscelaneous network events
    void SetLogger (Log *iLogger);
};

#endif // __SERVER_H__
