/**
 *     \file  src/worldserver/ObjectVector.h
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

#ifndef __OBJECT_VECTOR_H__
#define __OBJECT_VECTOR_H__

#include "BaseVector.h"
#include "HashVector.h"

class Object;

/**
 * ObjectVector can be sorted and, respectively, searched in several modes.
 * Some ObjectVector's are known to contain only object of a certain type
 * (e.g. with same HIGHGUID_XXX in their upper 32 bits of the GUID), this
 * permits sorting (and searching!) only by the lower 32 bits of the GUID.
 */
enum
{
    /// Sort by GUID, find by a pointer to the GUID
    OVSORT_GUID,
    /// Sort by serial number, find by serial number
    OVSORT_SNO
};

/**
 * Sorted Object Vector sorted by GUID -- either by the whole
 * GUID (sort mode == OVSORT_GUID) or by its lower 32 bits (OVSORT_SNO)
 */
class ObjectVector : public BaseVector
{
    public:
        /// Initialize the object vector
        ObjectVector (int ilimit = 0, int ithreshold = 16) : BaseVector (ilimit, ithreshold)
            { }

        /// Destructor
        virtual ~ObjectVector ();

        /// Get a contained object by index
        inline Object *Get (int iIndex)
        {
            DEBUG_BREAK_IF (iIndex >= count);
            return (Object *)Vector::Get (iIndex);
        }

        /// Same as Get()
        inline Object *operator [] (int iIndex) const
        {
            DEBUG_BREAK_IF (iIndex >= count);
            return (Object *)Vector::Get (iIndex);
        }

        /// Compare two objects for sorting
        virtual int Compare (Some Item1, Some Item2, int Mode);

        /// Compare a object with search key
        virtual int CompareKey (Some Item, ConstSome Key, int Mode);

        /// Find a object in the array by guid
        inline Object *GetByGUID (uint64 guid)
        {
            int n = FindSortedKey (&guid);
            if (n != -1)
                return Get (n);
            return NULL;
        }

        /// Find object index by GUID
        inline int FindByGUID (uint64 guid)
            { return FindSortedKey (&guid); }
};

/**
 * The ObjectHashVector type is similar to ObjectVector but is meant to hold
 * HUGE amounts of objects, and it always hashes/searches by full GUID.
 */
DECLARE_HASH_VECTOR (ObjectHashVector, Object *, HashGuid,
HASHFUNC_INT (HashGuid, uint64)
/* Insert element 'Item' into the hash vector */
void Insert (Object *Item););
#endif                                                      // __OBJECT_VECTOR_H__
