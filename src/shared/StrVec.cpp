/**
 *     \file  src/shared/StrVec.cpp
 *    \brief  String vector class
 *
 * Copyright (C) 1998,1999 by Andrew Zabolotny <zap@homelink.ru>
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

#include "StrVec.h"

StrVector::~StrVector ()
{
    DeleteAll ();
}

void StrVector::FreeItem (Some Item) const
{
    delete [] (char *) Item;
}

int StrVector::Compare (Some Item1, Some Item2, int Mode) const
{
    (void)Mode;
    return strcmp ((char *)Item1, (char *)Item2);
}

int StrVector::CompareKey (Some Item, ConstSome Key, int Mode) const
{
    (void)Mode;
    return strcmp ((char *)Item, (char *)Key);
}
