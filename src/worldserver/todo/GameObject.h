/**
 *     \file  src/worldserver/todo/GameObject.h
 *    \brief  Provides basic Game Object functions.
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

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Object.h"

class GameObject : public Object
{
    public:
        GameObject ();
        void Create (uint32 guidlow, uint32 display_id, uint8 state, float scale,
            uint16 type, uint16 faction,  float x, float y, float z, float ang);
};
#endif // __GAME_OBJECT_H__
