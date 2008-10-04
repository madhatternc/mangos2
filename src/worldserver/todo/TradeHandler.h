/**
 *     \file  src/worldserver/todo/TradeHandler.h
 *    \brief  Receives all messages related to Trade.
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

#ifndef __TRADE_HANDLER_H__
#define __TRADE_HANDLER_H__

#include "MsgHandler.h"

class DatabaseInterface;
class TradeHandler : public MsgHandler
{
	public:
		TradeHandler();
		~TradeHandler();

		void HandleMsg( NetworkPacket & recv_data, GameClient *pClient );

	protected:

};
#endif														// __TRADE_HANDLER_H__
