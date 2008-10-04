/**
 *     \file  src/worldserver/GameClient.h
 *    \brief  Receives and dispatches all opcodes sent from and to the client.
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

#ifndef __GAMECLIENT_H__
#define __GAMECLIENT_H__

extern "C"
{
	#include "lua.h"
}

#include "Client.h"
#include "Opcodes.h"

/**
 * Client capability flags.
 * This can be used to define an unlimited number of access levels
 * depending on your needs. The access levels are defined in the
 * access_levels table of the database.
 */

/// The client can create items
#define CAPS_MAKEITEMS      0x00000001
/// The client can create creatures
#define CAPS_MAKECREATURES  0x00000002
///@@@todo: redo the above

class Player;

class GameClient : public Client
{
	protected:
		/// Client capabilities (see CAPS_XXX)
		uint Capabilities;
		/// Used for authentification; after successful auth is reset to 0
		uint32 Seed;
		/// The session key for encryption
		uint8 SessionKey [40];
		/// Previous byte for send/receive encryption
		uint8 cs_prev, cr_prev;
		/// Session key index for send/receive encryption
		uint8 cs_idx, cr_idx;
		/// Saved receive encryptor state
		uint8 saved_cr_prev, saved_cr_idx;
		/**
		 * Account data is stored in the following format:
		 * \verbatim
		 * [ +0] uint32 UnpackedDataSize
		 * [ +4] uint32 PackedDataSize
		 * [ +8] uint8 MD5 [16]
		 * [+24] uint8 Data [PackedDataSize]
		 * \endverbatim
		 */
		uint8 *AccountData [3];

		/// Save account data to the 'accounts' table
		void SaveAccountData ();

		/// Generate the random seed used for authentification
		void GenSeed ();

		/// Initialize the packet header encryptor/decryptor
		void InitEncryptor ();
		/// Decrypt the header of received data
		void DecryptRecv (uint8 *data);
		/// Encrypt the header of outgoing data
		void EncryptSend (uint8 *data);
		/// Save receive encryptor state
		void SaveRecvEncryptor ()
			{ saved_cr_prev = cr_prev; saved_cr_idx = cr_idx; }
		/// Restore receive encryptor state
		void RestoreRecvEncryptor ()
			{ cr_prev = saved_cr_prev; cr_idx = saved_cr_idx; }

		/// Fail authenthification and return given return code to client
		void FailAuth (uint32 iCode);

		void HandleAuthSession (CMSG_AUTH_SESSION_t &inpkt);
		void HandlePing (CMSG_PING_t &inpkt);
		void HandleCharEnum ();

		/// Update number of characters owned by the user on this realm
		void UpdateNumChars ();
		void HandleCharCreate (CMSG_CHAR_CREATE_t &inpkt);
		void HandleCharDelete (CMSG_CHAR_DELETE_t &inpkt);
		void HandlePlayerLogin (CMSG_PLAYER_LOGIN_t &inpkt);

		void SendAccountDataMD5 ();
		void HandleRequestAccountData (CMSG_REQUEST_ACCOUNT_DATA_t &inpkt);
		void HandleUpdateAccountData (CMSG_UPDATE_ACCOUNT_DATA_t &inpkt);

	public:
		/// Client's login
		char *Login;
		/// The character associated with this session
		Player *Character;
		// Every client has an independend lua stack
		lua_State *Lua;										// tolua_hide

		GameClient (Socket *sock);
		virtual ~GameClient ();

		/// Handle socket events (mostly incoming data from the client).
		void SocketEvent (uint mask);

		/// Return true if client has been successfully authentificated
		bool Authenticated ()
			{ return (Seed == 0); }

		/// Assembles, encrypts and sends a packet
		void Send (NetworkPacket *packet);
};
#endif														// __GAMECLIENT_H__
