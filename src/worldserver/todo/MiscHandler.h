/**
 *     \file  src/worldserver/todo/MiscHandler.h
 *    \brief  Receives all messages that do not fit into any category.
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

#ifndef __MISC_HANDLER_H__
#define __MISC_HANDLER_H__

#include "MsgHandler.h"
#include "Opcodes.h"

struct SocialUserData
{
	uint32 guid;
	char *charname;
};

struct SocialData
{
	int pArraySize;
	SocialUserData *pSudata;
};

struct FriendData
{
	uint64 pGuid;
	unsigned char Status;
	uint32 tmpStatus;
	uint32 Level;
	uint32 Class;
	uint32 Area;
};

class MiscHandler
{
	friend class GameClient;
	public:
		MiscHandler();
		~MiscHandler();

		void Repop (CMSG_REPOP_REQUEST_t & recv_data, GameClient *pClient);
		void Autostore (CMSG_AUTOSTORE_LOOT_ITEM_t & recv_data, GameClient *pClient);
		void LootMoney (CMSG_LOOT_MONEY_t & recv_data, GameClient *pClient);
		void Loot (CMSG_LOOT_t & recv_data, GameClient *pClient);
		void LootRelease(CMSG_LOOT_RELEASE_t & recv_data, GameClient *pClient);
		void Who(CMSG_WHO_t & recv_data, GameClient *pClient);
		void LogoutRequest(CMSG_LOGOUT_REQUEST_t & recv_data, GameClient *pClient);
		void Ping(CMSG_PING_t & recv_data, GameClient *pClient);
		void GmticketGetticket(CMSG_GMTICKET_GETTICKET_t & recv_data, GameClient *pClient);
		void GmticketCreate(CMSG_GMTICKET_CREATE_t & recv_data, GameClient *pClient);
		void GmticketSystemstatus(CMSG_GMTICKET_CREATE_t & recv_data, GameClient *pClient);
		void Zoneupdate(CMSG_GMTICKET_CREATE_t & recv_data, GameClient *pClient);
		void SetActionButton(CMSG_SET_ACTION_BUTTON_t & recv_data, GameClient *pClient);
		void Areatrigger(CMSG_AREATRIGGER_t & recv_data, GameClient *pClient);
		void PlayerJoin(CMSG_PLAYER_LOGIN_t & recv_data, GameClient *pClient);
		void HandleMsgSET_TARGET(CMSG_SET_TARGET_t & recv_data, GameClient *pClient);
		void HandleMsgSET_SELECTION(CMSG_SET_SELECTION_t & recv_data, GameClient *pClient);
		void HandleMsgSTANDSTATECHANGE(CMSG_STANDSTATECHANGE_t & recv_data, GameClient *pClient);
		void HandleMsgNAME_QUERY(CMSG_NAME_QUERY_t & recv_data, GameClient *pClient);
		void HandleMsgFRIEND_LIST(CMSG_FRIEND_LIST_t & recv_data, GameClient *pClient);
		void HandleMsgADD_FRIEND(CMSG_ADD_FRIEND_t & recv_data, GameClient *pClient);
		void HandleMsgDEL_FRIEND(CMSG_DEL_FRIEND_t & recv_data, GameClient *pClient);
		void HandleMsgBUG(CMSG_BUG_t & recv_data, GameClient *pClient);
		void HandleMsgJOIN_CHANNEL(CMSG_JOIN_CHANNEL_t & recv_data, GameClient *pClient);
		void PlayerLogout(CMSG_PLAYER_LOGOUT_t & recv_data, GameClient *pClient);
		void LogoutCancel(CMSG_LOGOUT_CANCEL_t & recv_data, GameClient *pClient);

	protected:

};
#endif														// __MISC_HANDLER_H__
