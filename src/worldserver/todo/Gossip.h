/**
 *     \file  src/worldserver/todo/Gossip.h
 *    \brief  Provides basic Gossip functions.
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

#ifndef __GOSSIP_H__
#define __GOSSIP_H__

#include "Common.h"

// Npc/Creature RelationShip with a text (starting text)
class TextRelation
{
    public:
        TextRelation()
        {
            m_TextID = 0;
            m_NPCGUID = 0;
        }

        uint32 m_TextID;
        uint32 m_NPCGUID;
};

// Text Options what option Text to display and where to go if they get clicked
class TextOption
{
    public:
        TextOption()
        {
            m_OptionID = 0;
            m_OptionIconID = 0;
            m_TextID = 0;
        }

        uint32 m_OptionID;
        std::string m_OptionText;
        uint32 m_OptionIconID;
        uint32 m_TextID;
};
// Npc Gossip Text and the options it has
class NPCText
{
    public:
        NPCText()
        {
            m_TextID = 0;
            m_OptionCount = 0;
            memset(m_OptionID, 0, 60);
        }

        uint32 m_TextID;
        std::string m_Text;
        uint32 m_OptionCount;
        uint32 m_OptionID[15];                              // all the id's of options
};
#endif // __GOSSIP_H__
