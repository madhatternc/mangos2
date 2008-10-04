/**
 *     \file  src/worldserver/ObjectVector.cpp
 *    \brief  Provides a vector of basic objects.
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

#include "ObjectVector.h"
#include "Object.h"

ObjectVector::~ObjectVector ()
{
	DeleteAll ();
}

int ObjectVector::Compare (Some Item1, Some Item2, int Mode)
{
	Object *o1 = (Object *)Item1, *o2 = (Object *)Item2;
	switch (Mode)
	{
		case OVSORT_GUID:
			return SignCompare <uint64> (o1->GetGUID (), o2->GetGUID ());
		case OVSORT_SNO:
		default:
			return SignCompare <uint32> (o1->GetLowGUID (), o2->GetLowGUID ());
	}
}

int ObjectVector::CompareKey (Some Item, ConstSome Key, int Mode)
{
	Object *o = (Object *)Item;
	switch (Mode)
	{
		case OVSORT_GUID:
			return SignCompare <uint64> (o->GetGUID (), *(uint64 *)Key);
		case OVSORT_SNO:
		default:
			return SignCompare <uint32> (o->GetLowGUID (), uint32 (Key));
	}
}

//---------------------------------------------------------------------------//

//IMPLEMENT_HASH_VECTOR (, ObjectHashVector, Object *, GetLowGUID (), CMPEXPR_INT32);

ObjectHashVector::~ObjectHashVector ()
{
	DeleteAll ();
}

void ObjectHashVector::FreeItem (Some Item) const
{
	((Object *)Item)->DecRef();
}

HashKey_t ObjectHashVector::GetKey (Some Item) const
{
	return HashKey_t (((Object *)Item)->GetLowGUID ());
}

int ObjectHashVector::Compare (HashKey_t Key1, HashKey_t Key2) const
{
	return SignCompare <uint32> (uint32 (Key1), uint32 (Key2));
}

void ObjectHashVector::Insert (Object *Item)
{
	Item->IncRef ();
	HashVector::Insert (Item);
}
