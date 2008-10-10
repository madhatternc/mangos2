/**
 *     \file  src/shared/BaseVector.h
 *    \brief  This file defines a vector of objects derived from Base class.
 *
 * Copyright (C) 1998,1999 by Andrew Zabolotny <zap@homelink.ru>
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

#ifndef __BASE_VECTOR_H__
#define __BASE_VECTOR_H__

#include "Vector.h"

/**
 *  \addtogroup FoundationClasses
 *
 *  @{
 */

/**
 *  \class BaseVector
 *  \brief BaseVector holds any number of pointers to Base objects.
 *
 *  \details
 *  Every inserted object gets its reference counter incremented, and after
 *  removing a object from the vector it is the caller's responsibility to
 *  decrement the reference counter after the object is no longer used.
 */
class BaseVector : public Vector
{
    public:
        /**
         *  \brief Create the object
         */
        BaseVector (int ilimit = 8, int ithreshold = 16) : Vector (ilimit, ithreshold) {}

        /**
         *  \brief Decrement reference count for all objects
         */
        virtual ~BaseVector ();

        /**
         *  \brief Decrement object's reference count
         */
        virtual void FreeItem (Some Item) const;

        /**
         *  \brief Append object to array, increment object's reference counter.
         */
        inline int Push (Base *what)
            { what->IncRef (); return Vector::Push (what); }

        /**
         *  \brief Pick the top object from the array.
         *
         *  \note
         *  THIS FUNCTION DOES NOT decrement object's reference counter.
         */
        inline Base *Pop ()
            { return (Base *)Vector::Pop (); }

        /**
         *  \brief Get a pointer to object by index
         */
        inline Base *Get (int iIndex) const
            { return (Base *)Vector::Get (iIndex); }

        /**
         *  \brief Insert element 'Item' before element 'n'
         */
        inline bool Insert (int n, Base *Item)
            { Item->IncRef (); return Vector::Insert (n, Item); }

        /**
         *  \brief Insert element 'Item' so that array remains sorted (assumes its already sorted)
         */
        inline int InsertSorted (Base *Item, int *oEqual = 0, int Mode = 0)
            { Item->IncRef (); return Vector::InsertSorted (Item, oEqual, Mode); }
};

/**
 *  @}
 */
#endif                                                      // __BASE_VECTOR_H__
