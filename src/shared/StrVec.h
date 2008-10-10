/**
 *     \file  src/shared/StrVec.h
 *    \brief  String vector class
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

#ifndef __STR_VEC_H__
#define __STR_VEC_H__

#include "Vector.h"

/**
 *  \addtogroup FoundationClasses
 *
 *  @{
 */

/**
 *  \class StrVector
 *  \brief StrVector is version of Vector assuming its components were allocated with 'new char *[]'.
 *
 *  \par
 *  StrVector is a version of Vector which assumes its components
 *  were allocated with 'new char *[]'. FreeItem () deletes vector elements
 *  using 'delete [] (char *)' operator.
 */
class StrVector : public Vector
{
    public:
        /**
         *  \brief Constructor just passes control to Vector's
         */
        StrVector (int ilimit = 64, int ithreshold = 64) :
        Vector (ilimit, ithreshold) {}

        /**
         *  \brief Delete all inserted strings before deleting the object itself
         */
        virtual ~StrVector ();

        /**
         *  \brief FreeItem deletes Item as if it was allocated by 'new char *[]'
         */
        virtual void FreeItem (Some Item) const;

        /**
         *  \brief Compare two array elements in given Mode
         */
        virtual int Compare (Some Item1, Some Item2, int Mode) const;

        /**
         *  \brief Compare two strings for equality (case-sensitive)
         */
        virtual int CompareKey (Some Item, ConstSome Key, int Mode) const;

        /**
         *  \brief Override Get() to avoid explicit typecasting
         */
        inline char *Get (int iIndex) const
            { return (char *)Vector::Get (iIndex); }
};

/**
 *  @}
 */
#endif                                                      // __STR_VEC_H__
