/**
 *     \file  src/worldserver/todo/Group.h
 *    \brief  Provides basic Group functions.
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

#ifndef __GROUP_H__
#define __GROUP_H__

#include "ObjectVector.h"

#define MAXGROUPSIZE 5

class Group
{
	public:
		Group()
		{
			leaderguid = 0;
			lootmethod = 0;
			looterguid = 0;
		}
		~Group()
		{
			Members.DeleteAll();
		}
		void Create(Object* Leader)
		{
			AddMember(Leader, true);
		}
		void AddMember(Object* Member, bool tisleader)
		{
			Members.Insert(Member);
			if(thisleader)
			{
				Leaderguid = Member.GetGUID();
				Leader = Member.GetName();
			}
		}

		void ChangeLeader(char * tname);
		int DelMember(char * tname);
		int IsFull()
		{
			return Members.Length() == MAXGROUPSIZE ? 1 : 0;
		}

		void SendUpdate();
		void Disband();

		uint64 Leaderguid;
		char *Leader;

		//MemberSlot members[MAXGROUPSIZE];
		ObjectVector *Members;

		uint32 Lootthreshold;								// 0 2 4
		uint32 Lootmethod;
		uint32 Looterguid;

};
#endif														// __GROUP_H__
