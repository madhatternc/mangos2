/**
 *     \file  src/worldserver/todo/AreaTrigger.h
 *    \brief  Provides basic AreaTrigger functions.
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

#ifndef __AREA_TRIGGER_H__
#define __AREA_TRIGGER_H__

class AreaTrigger
{
    public:
        AreaTrigger()
        {
            m_AreaTriggerID = 0;
            m_MapID = 0;
            m_X = 0;
            m_Y = 0;
            m_Z = 0;
            m_O = 0;
            m_TargetTriggerID = 0;
        }

        uint32 m_AreaTriggerID;
        uint32 m_MapID;
        float m_X;
        float m_Y;
        float m_Z;
        float m_O;
        uint32 m_TargetTriggerID;
};
#endif                                                      // __AREA_TRIGGER_H__
