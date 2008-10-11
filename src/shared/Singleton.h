/**
 *     \file  src/shared/Singleton.h
 *    \brief  The Singleton class
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

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "Errors.h"

/**
 *  \addtogroup FoundationClasses
 *
 *  @{
 */

/// Should be placed in the appropriate .cpp file somewhere
#define InitializeSingleton( type ) \
    template < > type * Singleton < type > :: mSingleton = 0

/// To be used as a replacement for InitializeSingleton( )
///  Creates a file-scoped Singleton object, to be retrieved with getSingleton
#define createFileSingleton( type ) \
    InitializeSingleton( type ); \
    type the##type

template < class type > class Singleton
{
    protected:
        /// Singleton pointer, must be set to 0 prior to creating the object
        static type *mSingleton;

    public:
        /// Constructor
        Singleton ()
        {
            /// If you hit this assert, this singleton already exists -- you can't create another one!
            WPAssert (mSingleton == 0);
            mSingleton = (type *) this;
        }
        /// Destructor
        ~Singleton () { }

        /// Retrieve the singleton object, if you hit this assert this singleton object doesn't exist yet
        static type &getSingleton () { WPAssert (mSingleton); return *mSingleton; }

        /// Retrieve a pointer to the singleton object
        static type *getSingletonPtr () { return mSingleton; }
};

/**
 *  @}
 */
#endif // __SINGLETON_H__
