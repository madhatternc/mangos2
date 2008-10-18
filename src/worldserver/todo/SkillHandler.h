/**
 *     \file  src/worldserver/todo/SkillHandler.h
 *    \brief  Receives all messages related to skills.
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

#ifndef __SKILL_HANDLER_H__
#define __SKILL_HANDLER_H__

#include "MsgHandler.h"
struct TALENT_RANK_BYTES
{
    uint8 Byte1;                                            //SPELL ID LOWID -> Changed based on rank
    uint8 Byte2;                                            //SPELL ID HIGHID -> Constant
    uint8 Byte3;                                            //UNKNOWN
    uint8 Byte4;                                            //UNKNOWN
};

struct TALENT
{
    uint32 TalentId;
    uint32 Class;
    uint32 MaxRank;
    TALENT_RANK_BYTES Ranks[4];
};

class DatabaseInterface;
class SkillHandler : public MsgHandler
{
    public:
        SkillHandler();
        ~SkillHandler();

        void HandleMsg( NetworkPacket & recv_data, GameClient *pClient );

    protected:

};
#endif // __SKILL_HANDLER_H__
