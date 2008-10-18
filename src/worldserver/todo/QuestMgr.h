/**
 *     \file  src/worldserver/todo/QuestMgr.h
 *    \brief  Provides a basic Quest manager.
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

#ifndef __QUEST_MGR_H__
#define __QUEST_MGR_H__

#include "Common.h"
#include "Base.h"
#include "Vector.h"
#include "WorldServer.h"

/* QuestMgr stores all Quests. It needs lua implementaion */

QuestMgr
{
    public:
        QuestMgr(WorldServer* srv)
        {
            m_server = srv;
        }

        WorldServer m_server;

}
#endif                                                      //__QUEST_MGR_H__
