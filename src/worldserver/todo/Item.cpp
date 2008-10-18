/**
 *     \file  src/worldserver/todo/Item.cpp
 *    \brief  Provides basic Item functions.
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

#include "Item.h"

Item::Item () : Object()
{
    m_objectType |= TYPE_ITEM;
    m_objectTypeId = 1;

}

void Item::Create (uint32 guidlow, uint32 itemid)
{
    Object::Create (guidlow);
    m_guid->sno = guidlow;
    m_guid->type = 0x00000040;
    setUpdateValue (OBJECT_FIELD_ENTRY, itemid);
}
