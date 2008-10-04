/**
 *     \file  src/worldserver/AuctionHouse.h
 *    \brief  Provides basic Auction House functions.
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

#ifndef __AUCTION_HOUSE_H__
#define __AUCTION_HOUSE_H__

struct bidentry
{
	uint32 AuctionID;
	uint32 amt;
};
struct AuctionEntry
{
	uint32 auctioneer;
	uint32 item;
	uint32 owner;
	uint32 bid;
	uint32 buyout;
	time_t time;
	uint32 bidder;
	uint32 Id;
};
#endif														// __AUCTION_HOUSE_H__
