/**
 *     \file  src/shared/Sockets.h
 *    \brief  Network objects interface
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

#ifndef __SOCKETS_H__
#define __SOCKETS_H__

#include "BaseVector.h"
#include "Log.h"

/**
 *  \defgroup NetworkClasses Networking Classes
 */

/**
 *  \addtogroup NetworkClasses
 *
 *  @{
 */

// Handle the platform differences between socket implementations here
#if PLATFORM == PLATFORM_WIN32
#  include <Winsock2.h>
#  define socket_t SOCKET
#  define socklen_t int
#  define SOCKERR(a) WSAE##a
#  define so_errno WSAGetLastError()
#  define so_ioctl ioctlsocket
#  define so_close closesocket
#else
#  include <sys/types.h>
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#  include <netdb.h>
#  define socket_t int
#  define so_errno errno
#  define SOCKERR(a) E##a
#  define SOCKET_ERROR -1
#  define INVALID_SOCKET (socket_t (-1))
#  define so_ioctl ioctl
#  define so_close close
#endif

// How much incoming connections to be able to hold until we start processing them
#if !defined (SOMAXCONN) || (SOMAXCONN < 10)
#  undef SOMAXCONN
#  define SOMAXCONN 10
#endif

/**
 * A network packet is just a buffer with data.
 * The class provides methods for conveniently filling the buffer with data.
 */
class NetworkPacket : public Base
{
	protected:
		/// Private destructor -- use DecRef () instead
		virtual ~NetworkPacket ();

	public:
		/// The data associated with this packet
		uint8 *data;										//tolua_hide temporary fix
		/// The length of the associated data
		uint length;

		/// Construct an empty network packet
		NetworkPacket ();

		/// Construct a network packet with given size
		NetworkPacket (uint newlength);

		/// Set the data array so that it can hold this many bytes
		void SetLength (uint newlength);

		/// Construct the packet data from other sources
		virtual void Assemble ();
};

// Don't process more than 64k bytes per client at once
// A packet can't be larger than that, 'cause first of the 2-byte packet len
#define RECVB_SIZE      (64*1024)
#define RECVB_MASK      (RECVB_SIZE - 1)
#define SENDB_SIZE      (16*1024)
#define SENDB_MASK      (SENDB_SIZE - 1)

/** These are flags for socket events we support */

/// Incoming data available for read on socket
#define PF_READ     1
/// Socket buffers are ready to accept some more outgoing data
#define PF_WRITE    2
/// Incoming OOB data available for read on socket (OOB not implemented for now)
#define PF_EXCEPT   4

/**
 * This class is used to encapsulate socket objects.
 * It implements buffered send and receive data operations.
 * The Socket class does not have any knowledge of the underlying
 * protocol, it just operates on the abstract data stream.
 *
 * Both receive and send buffers are designed to minimize memory allocation
 * and copy operations. Every buffer have two associated pointers: one
 * points to the first available byte in buffer, other to the first
 * free byte in buffer:
 *
 * \verbatim
 *   tail-- v
 * [........{data data data data}.........]
 *                               ^-- head
 * \endverbatim
 *
 * The pointers move as data is copied to the buffer (head) and as data is
 * being digested from the buffer (tail). The send queue can hold whole
 * NetworkPacket's until the send buffer is able to receive the data.
 * After the data from NetworkPacket is copied to the send buffer, the
 * packet's reference counter is decremented so the packet gets freed
 * as soon as no one needs it.
 *
 * Both buffers can wrap around the buffer end so that memory copy operations
 * are minimized, like this:
 *
 * \verbatim
 *                      tail-- v
 * [data data}.................{data data ]
 *           ^-- head
 * \endverbatim
 *
 * Because you cannot work with such a wrapped-around buffer like usual
 * (e.g. get a pointer to something and go ahead), no functions are present
 * to get direct access to the receive buffer; instead a set of accessor
 * functions are provided.
 *
 * For now a Socket object is NOT thread-safe, since it is expected that one
 * socket is used by a single macro-object like a 'Client' or a 'Server'
 * which runs in one thread.
 */
class Socket : public Base
{
	private:
		/// Handle of the socket encapsulated in this object
		socket_t handle;
		/// Network address of the socket
		sockaddr_in inaddr;

		/// Receiver queue
		uint8 recvb [RECVB_SIZE];
		/// Receiver buffer tail and head
		int recv_tail, recv_head;
		/// The phantom tail for data accessor functions
		int data_tail;

		/// The send queue (NetworkPacket's)
		BaseVector sendq;
		/// Amount of data sent from the first packet in queue
		uint sendq0_bytes;
		/// The already serialized send queue
		uint8 sendb [SENDB_SIZE];
		/// Send buffer tail and head
		uint send_tail, send_head;

		/// Is this socket still connected?
		bool connected;

		/// The logger associated with this and all derived sockets
		Log *Logger;

		/// Private constructor & destructor, only createable via Network
		Socket (socket_t sh, sockaddr_in *sa, Log *iLogger);
		virtual ~Socket ();

		friend class Network;

	public:
		/// Open a TCP port and listen for connections
		static Socket *Listen (int port, Log *iLogger);

		/// Open new socket and try to connect to host:port
		static Socket *Connect (int port, char *host, Log *iLogger);

		/// Get the name of an errorcode
		static char *ErrorString (uint32 code);

		/**
		 * Receive some more data. Returns true if there's anything new
		 * in the receive buffer.
		 */
		bool ReceiveData ();

		/**
		 * Send a network packet.
		 * The network packet is put into the send queue array if the send
		 * buffer is full, and will be sent at a later time. In this case
		 * the reference counter on data is incremented, and it will be
		 * decremented only after the packet will be actually sent.
		 */
		void SendData (NetworkPacket *data);

		/**
		 * Send just a buffer of data: blocks if send queue is full,
		 * so it's not recommended to use this function for large amounts.
		 */
		void SendData (const void *data, uint length);

		/**
		 * Try to send what's yet unsent.
		 */
		void SendPending ();

		/**
		 * Accept an incoming connection request if one exists
		 * @return
		 *   A new socket or NULL if error.
		 */
		Socket *Accept ();

		/**
		 * Return a combination of PF_XXX flags for which events
		 * we're interested to see right now.
		 */
		uint InterestedEvents ();

		/// Is this socket still connected?
		bool Connected () const
			{ return connected; }

		/// Get socket handle (for internal use only)
		socket_t GetHandle ()								// tolua_hide
		{													// tolua_hide
			return handle;
		}

		inline char * GetIP ()
			{ return inet_ntoa (inaddr.sin_addr); }

		/// Set the logger used to log miscelaneous network events
		void SetLogger (Log *iLogger);

		/**
		 * This function starts a receive buffer access sequence.
		 * The virtual pointers are set to the beginning of the available
		 * data in the receive buffer.
		 */
		void Rewind ()
			{ data_tail = recv_tail; }

		/**
		 * This function can be called only AFTER initializing non-destructive
		 * data analysis by calling Rewind ().
		 * @return
		 *   Number of bytes *STILL* available in the receive buffers.
		 */
		uint Avail ()
			{ return (recv_head - data_tail) & RECVB_MASK; }

		/**
		 * Get how much data would be swallowed if we would call Swallow()
		 */
		uint Chewed ()
			{ return (data_tail - recv_tail) & RECVB_MASK; }

		/**
		 * Tell the socket that the data consumed since the call to Rewind ()
		 * and until now (by calling the Get () methods) has been successfully
		 * digested.
		 */
		void Swallow ()
			{ recv_tail = data_tail; }

		/**
		 * Skip some bytes from the data sequence
		 * @arg iLength
		 *   Number of bytes to skip
		 * @return
		 *   false if receive buffer contains less data
		 */
		bool Skip (uint iLength)
		{
			if (iLength > Avail ())
				return false;
			data_tail = (data_tail + iLength) & RECVB_MASK;
			return true;
		}

		/**
		 * Copy a number of bytes from receive buffer to user buffer.
		 * @arg oData
		 *   Pointer to output data buffer.
		 * @arg iDataSize
		 *   Data buffer size in bytes.
		 * @return
		 *   true if byte has been read; false if buffer is empty
		 */
		bool Get (void *oData, uint iDataSize);

		/**
		 * Get next byte from the receive buffer.
		 * @arg b
		 *   The output byte
		 * @return
		 *   true if byte has been read; false if buffer is empty
		 */
		bool Get (uint8 &b)
		{
			if (data_tail == recv_head)
				return false;
			b = recvb [data_tail];
			data_tail = (data_tail + 1) & RECVB_MASK;
			return true;
		}

		/**
		 * Get next little-endian 16-bit word from the receive buffer.
		 * @arg w16
		 *   The output word
		 * @return
		 *   true if data has been read; false if buffer is empty
		 */
		bool GetLE (uint16 &w16);

		/**
		 * Get next little-endian 32-bit word from the receive buffer.
		 * @arg w32
		 *   The output word
		 * @return
		 *   true if data has been read; false if buffer is empty
		 */
		bool GetLE (uint32 &w32);

		/**
		 * Get next little-endian 64-bit word from the receive buffer.
		 * @arg w64
		 *   The output word
		 * @return
		 *   true if data has been read; false if buffer is empty
		 */
		bool GetLE (uint64 &w64);

		/**
		 * Get next little-endian 32-bit float from the receive buffer.
		 * @arg f32
		 *   The output floating-point variable
		 * @return
		 *   true if data has been read; false if buffer is empty
		 */
		bool GetLE (float &f32)
			{ return GetLE (*(uint32 *)&f32); }

		/**
		 * Get next big-endian 16-bit word from the receive buffer.
		 * @arg w16
		 *   The output word
		 * @return
		 *   true if data has been read; false if buffer is empty
		 */
		bool GetBE (uint16 &w16);

		/**
		 * Get next big-endian 32-bit word from the receive buffer.
		 * @arg w32
		 *   The output word
		 * @return
		 *   true if data has been read; false if buffer is empty
		 */
		bool GetBE (uint32 &w32);

		/**
		 * Get a C string from the buffer.
		 * @return
		 *   NULL if there's no zero-terminated string in the buffer.
		 */
		char *GetCStr ();
};

/**
 *  @}
 */
#endif														// __SOCKETS_H__
