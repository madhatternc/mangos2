/**
 *     \file  src/shared/Sockets.cpp
 *    \brief  Network objects
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

#include "Sockets.h"
#include "SystemFun.h"
#include "Log.h"

// Define this if you want to see hex dumps of sent and received data
#define LOWLEVEL_DEBUG_PACKETS

NetworkPacket::NetworkPacket () : Base (), data (NULL), length (0)
{
}

NetworkPacket::NetworkPacket (uint newlength) : Base (), data (NULL)
{
    SetLength (newlength);
}

NetworkPacket::~NetworkPacket ()
{
    delete [] data;
}

void NetworkPacket::SetLength (uint newlength)
{
    delete [] data;
    if ((length = newlength))
        data = new uint8 [length];
    else
        data = NULL;
}

void NetworkPacket::Assemble ()
{
    DEBUG_PRINTF ("\axcYou shall never get here! This indicates a error in code.");
}

//-----------------------------------------------------------------------------

Socket::Socket (socket_t sh, sockaddr_in *sa, Log *iLogger) : Base (), sendq (8, 8)
{
    handle = sh;
    memcpy (&inaddr, sa, sizeof (inaddr));
    connected = true;
    recv_tail = recv_head = 0;
    send_tail = send_head = 0;
    sendq0_bytes = 0;

    Logger = iLogger;
    if (Logger)
        Logger->IncRef ();

    DEBUG_PRINTF ("Created socket %d\n", handle);

    // ALWAYS switch socket to non-blocking mode
    u_long flag = 1;
    so_ioctl (sh, FIONBIO, &flag);
    int value;
    // We don't care what happens to the client after we close connection
    value = 0;
    setsockopt (sh, SOL_SOCKET, SO_LINGER, (char*)&value, sizeof (value));
    // Turn off Nagle's algorithm so that delays are minimized
    value = 0;
    setsockopt (sh, SOL_SOCKET, TCP_NODELAY, (char*)&value, sizeof (value));
    // Set larger receiver and sender buffers
    //value = SENDB_SIZE;
    //setsockopt (sh, SOL_SOCKET, SO_SNDBUF, (char*)&value, sizeof (value));
    //value = RECVB_SIZE;
    //setsockopt (sh, SOL_SOCKET, SO_RCVBUF, (char*)&value, sizeof (value));
}

Socket::~Socket ()
{
    DEBUG_PRINTF ("Closing socket %d\n", handle);
    so_close (handle);
    SetLogger (NULL);
}

Socket *Socket::Accept ()
{
    sockaddr_in inaddr;
    socklen_t inaddr_len = sizeof (sockaddr_in);
    socket_t sh = accept (handle, (struct sockaddr *) &inaddr, &inaddr_len);
    if (sh == SOCKET_ERROR)
        return NULL;
    if (inaddr_len != sizeof (sockaddr_in))
    {
        // TODO: what was that?! IPX?
        so_close (sh);
        return NULL;
    }

    if (Logger)
        Logger->Out (LOG_IMPORTANT, "Incoming connection from %s\n", inet_ntoa (inaddr.sin_addr));

    return new Socket (sh, &inaddr, Logger);
}

Socket *Socket::Listen (int port, Log *iLogger)
{
    /// Create the socket
    socket_t sh = (uint32) socket (AF_INET, SOCK_STREAM, 0);
    if (sh == SOCKET_ERROR)
    {
        if (iLogger)
            iLogger->Out (LOG_IMPORTANT, "Cannot create socket: %s\n", ErrorString (so_errno));
        return NULL;
    }

    // Re-use address even if there's some half-closed connection
    // from this address/port in the WAIT/CLOSING state
    int opt = 1;
    setsockopt (sh, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof (opt));

    // Bind socket to address
    sockaddr_in inaddr;
    inaddr.sin_family = AF_INET;
    inaddr.sin_port = htons (port);
    inaddr.sin_addr.s_addr = htonl (INADDR_ANY); // Listen on any interface
    if (bind (sh, (struct sockaddr *)&inaddr, sizeof (inaddr)) == SOCKET_ERROR)
    {
        if (iLogger)
            iLogger->Out (LOG_IMPORTANT, "Cannot bind socket: %s\n", ErrorString (so_errno));
error:  so_close (sh);
        return NULL;
    }

    if (listen (sh, SOMAXCONN) == SOCKET_ERROR)
    {
        if (iLogger)
            iLogger->Out (LOG_IMPORTANT, "Cannot listen to socket: %s\n", ErrorString (so_errno));
        goto error;
    }

    return new Socket (sh, &inaddr, iLogger);
}

Socket *Socket::Connect (int port, char *host, Log *iLogger)
{
    struct hostent *he;
    if ((he = gethostbyname (host)) == NULL)
    {
        if (iLogger)
            iLogger->Out (LOG_IMPORTANT, "Cannot resolve `%s': %s\n", host, ErrorString (so_errno));
        return NULL;
    }

    socket_t sh = socket (AF_INET, SOCK_STREAM, 0);
    if (sh == SOCKET_ERROR)
    {
        if (iLogger)
            iLogger->Out (LOG_IMPORTANT, "Cannot create socket: %s\n", ErrorString (so_errno));
        return NULL;
    }

    sockaddr_in inaddr;
    inaddr.sin_family = AF_INET;
    inaddr.sin_port = htons (port);
    inaddr.sin_addr = *((struct in_addr *)he->h_addr);

    if (connect (sh, (struct sockaddr *)&inaddr, sizeof(inaddr)) == SOCKET_ERROR)
    {
        if (iLogger)
            iLogger->Out (LOG_IMPORTANT, "Couldn't connect to %s:%d: %s\n",
                          host, port, ErrorString (so_errno));
        so_close (sh);
        return NULL;
    }

    if (iLogger)
        iLogger->Out (LOG_IMPORTANT, "Connected to: %s:%d", host, port);

    // Create the socket
    return new Socket (sh, &inaddr, iLogger);
}

bool Socket::ReceiveData ()
{
    if (!Connected ())
        return false;

    bool rc = false;

    // Read as much as we can swallow
    uint dstofs = recv_head;
    int freespace = (recv_tail - recv_head - 1) & RECVB_MASK;

    // The receive buffer is full? wait ...
    if (!freespace)
    {
        DEBUG_PRINTF ("PERFORMANCE WARNING: Socket buffers are full\n");
        return false;
    }

    while (freespace)
    {
        int max = RECVB_SIZE - dstofs;
        if (max > freespace)
            max = freespace;
        int len = recv (handle, (char *)recvb + dstofs, max, 0);
        if (len == SOCKET_ERROR)
        {
            int err = so_errno;
            if (err != SOCKERR (WOULDBLOCK))
            {
                // Fatal socket error
                connected = false;
                if (Logger)
                    Logger->Out (LOG_IMPORTANT, "Broken connection from %s\n",
                                 inet_ntoa (inaddr.sin_addr));
            }

            // No more data for now
            break;
        }

        if (!len)
        {
            // Client closing session
            connected = false;
            if (Logger)
                Logger->Out (LOG_IMPORTANT, "Closing connection from %s\n",
                             inet_ntoa (inaddr.sin_addr));
            break;
        }

        DEBUG_BREAK_IF (len < 0);

#ifdef LOWLEVEL_DEBUG_PACKETS
        CONSOLE.Out ("\r\aPU\axeReceived data:\n\ax6");
        DebugDump (stdout, (char*)recvb + dstofs, len);
        CONSOLE.Out ("\aPO");
#endif
        recv_head = (recv_head + len) & RECVB_MASK;
        freespace -= len;
        dstofs = (dstofs + len) & RECVB_MASK;
        rc = true;
    }

    return rc;
}

void Socket::SendPending ()
{
    // Since we disabled the Nagle algorithm, we have to assemble packets
    // ourselves. We'll assemble them in blocks as large as 5x the
    // minimal recommended MTU size, so we won't make a bad bargain ...

    while (true)
    {
        // If tail > head, reset buffer pointers
        if (send_tail >= send_head)
            send_tail = send_head = 0;
        // If the leftover in sendb is too small, move it to
        // the beginning of the buffer so that we don't fragment
        // packets too much
        else if (send_tail && (send_tail < send_head) && (send_head - send_tail < 500))
        {
            memmove (sendb, sendb + send_tail, send_head - send_tail);
            send_head -= send_tail;
            send_tail = 0;
        }

        while (sendq.Length ())
        {
            // How much bytes we can copy to send buffer
            uint cpy_bytes = SENDB_SIZE - send_head;
            // Check if send buffer is full
            if (!cpy_bytes)
                break;

            NetworkPacket *pkt = (NetworkPacket *)sendq.Get (0);

            // Assemble packet if it has no data
            if (!pkt->data)
                pkt->Assemble ();

            uint pkt_bytes = pkt->length - sendq0_bytes;

            // Check if packet is not shorter than free space
            if (cpy_bytes > pkt_bytes)
                cpy_bytes = pkt_bytes;

            // Copy all or partial data from the packet to output queue
            memcpy (sendb + send_head, pkt->data + sendq0_bytes, cpy_bytes);

            // Advance pointers
            send_head += cpy_bytes;
            sendq0_bytes += cpy_bytes;
            if (sendq0_bytes >= pkt->length)
            {
                sendq.Delete (0);
                sendq0_bytes = 0;
            }
        }

        uint8 *data = sendb + send_tail;
        int datalen = send_head - send_tail;
        if (datalen <= 0)
            // Nothing to send
            break;

#ifdef LOWLEVEL_DEBUG_PACKETS
        CONSOLE.Out ("\r\aPU\axeSending data:\n\ax6");
        DebugDump (stdout, (char*)data, datalen);
        CONSOLE.Out ("\aPO");
#endif
        int len = send (handle, (char*)data, datalen, 0);
        if (len == SOCKET_ERROR)
        {
            int err = so_errno;
            if (err != SOCKERR (WOULDBLOCK))
                // Fatal socket error
                connected = false;
            // Temporary failure
            break;
        }
        if (len == 0)
            // TCP buffers are full, later
            break;
        DEBUG_BREAK_IF (len < 0);
        send_tail += len;
    }
}

void Socket::SendData (NetworkPacket *data)
{
    if (!Connected ())
        return;

    // Push the network packet to our queue
    sendq.Push (data);
}

void Socket::SendData (const void *data, uint length)
{
    // If buffer is empty, reset buffer pointers to start position
    if (send_tail >= send_head)
        send_tail = send_head = 0;
    // If the leftover in sendb is too small, move it to
    // the beginning of the buffer so that we don't fragment
    // packets too much
    else if (send_tail && (send_tail < send_head) && (send_head - send_tail < length))
    {
        memmove (sendb, sendb + send_tail, send_head - send_tail);
        send_head -= send_tail;
        send_tail = 0;
    }

    // If there are packets in the queue but there is also free space
    // in the send buffers, try to fill them now ...
    if (sendq.Length ())
        SendPending ();

    // How much bytes we can copy to send buffer
    uint cpy_bytes = SENDB_SIZE - send_head;
    // If we have packets ahead or buffer is full, create a packet for later
    if (sendq.Length () || cpy_bytes < length)
    {
        // The buffer space is too small to hold the data.
        // Create a new NetworkPacket and queue it
        NetworkPacket *np = new NetworkPacket (length);
        memcpy (np->data, data, length);
        sendq.Push (np);
    }
    else
    {
        // There's enough space in the send buffer, copy data to buffer
        memcpy (sendb + send_tail, data, length);
        send_head += length;
    }
}

char *Socket::ErrorString (uint32 code)
{
    switch (code)
    {
    case SOCKERR (FAULT):
        return "Bad address";
    case SOCKERR (INTR):
        return "Interrupted function call";
    case SOCKERR (MFILE):
        return "Too many open files";
    case SOCKERR (CONNRESET):
        return "Connection reset by peer";
    case SOCKERR (ACCES):
        return "Permission denied";
    case SOCKERR (WOULDBLOCK):
        return "Resource temporarily unavailable";
    case SOCKERR (INVAL):
        return "Invalid argument";
    case SOCKERR (CONNABORTED):
        return "Software caused connection abort";
    case SOCKERR (SHUTDOWN):
        return "Cannot send after socket shutdown.";
    case SOCKERR (ADDRINUSE):
        return "Address already in use.";
#if PLATFORM != PLATFORM_WIN32
    case SOCKERR (PIPE):
        return "Broken pipe.";
#endif
    case SOCKERR (TIMEDOUT):
        return "Connection timed out.";
    }

    return "UNKNOWN ERROR";
}

uint Socket::InterestedEvents ()
{
    uint retval = 0;
    if ((send_tail < send_head) || sendq.Length ())
        retval |= PF_WRITE;
    if (int (recv_head - recv_tail) < int (sizeof (recvb)))
        retval |= PF_READ;
    return retval;
}

void Socket::SetLogger (Log *iLogger)
{
    if (Logger != iLogger)
    {
        if (Logger)
            Logger->DecRef ();
        Logger = iLogger;
        if (Logger)
            Logger->IncRef ();
    }
}

bool Socket::Get (void *oData, uint iDataSize)
{
    if (Avail () < iDataSize)
        return false;

    uint8 *out = (uint8 *)oData;
    while (iDataSize)
    {
        uint bytes = RECVB_SIZE - data_tail;
        if (bytes > iDataSize)
            bytes = iDataSize;
        memcpy (out, recvb + data_tail, bytes);
        out += bytes;
        data_tail = (data_tail + bytes) & RECVB_MASK;
        iDataSize -= bytes;
    }
    return true;
}

bool Socket::GetLE (uint16 &w16)
{
    if (Avail () < sizeof (uint16))
        return false;

    if (data_tail < int (RECVB_SIZE - sizeof (uint16)))
    {
        w16 = GET_LE16 (recvb + data_tail);
        data_tail += sizeof (uint16);
        return true;
    }

    Get (&w16, sizeof (uint16));
    w16 = LE16_TO_HOST (w16);
    return true;
}

bool Socket::GetLE (uint32 &w32)
{
    if (Avail () < sizeof (uint32))
        return false;

    if (data_tail < int (RECVB_SIZE - sizeof (uint32)))
    {
        w32 = GET_LE32 (recvb + data_tail);
        data_tail += sizeof (uint32);
        return true;
    }

    Get (&w32, sizeof (uint32));
    w32 = LE32_TO_HOST (w32);
    return true;
}

bool Socket::GetLE (uint64 &w64)
{
    if (Avail () < sizeof (uint64))
        return false;

    if (data_tail < int (RECVB_SIZE - sizeof (uint64)))
    {
        w64 = GET_LE64 (recvb + data_tail);
        data_tail += sizeof (uint64);
        return true;
    }

    Get (&w64, sizeof (uint64));
    w64 = LE64_TO_HOST (w64);
    return true;
}

bool Socket::GetBE (uint16 &w16)
{
    if (Avail () < sizeof (uint16))
        return false;

    if (data_tail < int (RECVB_SIZE - sizeof (uint16)))
    {
        w16 = GET_BE16 (recvb + data_tail);
        data_tail += sizeof (uint16);
        return true;
    }

    Get (&w16, sizeof (uint16));
    w16 = BE16_TO_HOST (w16);
    return true;
}

bool Socket::GetBE (uint32 &w32)
{
    if (Avail () < sizeof (uint32))
        return false;

    if (data_tail < int (RECVB_SIZE - sizeof (uint32)))
    {
        w32 = GET_BE32 (recvb + data_tail);
        data_tail += sizeof (uint32);
        return true;
    }

    Get (&w32, sizeof (uint32));
    w32 = BE32_TO_HOST (w32);
    return true;
}

char *Socket::GetCStr ()
{
    uint len = Avail ();
    uint sl = 0;
    uint tail = data_tail;
    while (len)
    {
        uint max = RECVB_SIZE - tail;
        if (max > len)
            max = len;
        void *r = memchr (recvb + tail, 0, max);
        if (r)
        {
            sl += (uint8 *)r - (recvb + tail) + 1;
            char *str = new char [sl];
            Get (str, sl);
            return str;
        }
        sl += max;
        len -= max;
        tail = 0;
    }

    return false;
}
