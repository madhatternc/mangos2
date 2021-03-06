/**
 *     \file  src/worldserver/todo/Affect.cpp
 *    \brief  Provides basic Affect (aka. DoT) functions.
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

#include "Vector.h"
#include "Affect.h"

IMPLEMENT_VECTOR(Affect, ModifierVector, Modifier));

void Affect::AddMod(uint8 t, int32 a,uint32 miscValue, uint32 miscValue2)
{
    m_modList.Push(Modifier(t, a,miscValue,miscValue2));
};
