/**
 *     \file  src/shared/Base.h
 *    \brief  Base class interface
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

#ifndef __BASE_H__
#define __BASE_H__

#include "Common.h"

/**
 *  \defgroup FoundationClasses Foundation Classes
 *
 *  The Foundation Classes provide a basic framework upon we build the whole
 *  project.
 *
 *  These classes are internal classes, and should only be re-used by the
 *  project itself. We provide child classes with enhanced functionality for
 *  3rd party development.
 */

/**
 *  \addtogroup FoundationClasses
 *
 *  @{
 */

/**
 *  \class Base
 *  \brief This class is intended to be a base class for every other class.
 *
 *  \details
 *  It defines the basic interface available for any object.
 */
class Base
{
	private:
		/**
		 *  \brief Object reference count
		 *
		 *  \details
		 *  Stores the number of references to an object.
		 */
		int RefCount;

	protected:
		/**
		 *  \brief Destroy this object.
		 *
		 *  \details
		 *  Destructor is virtual, because class contains virtual methods; also it
		 *  is private because it is never intended to be called directly;
		 *  use DecRef() instead: when reference counter reaches zero, the object
		 *  will be destroyed.
		 */
		virtual ~Base ();

	public:
		/**
		 *  \brief Object initialization.
		 *
		 *  \details
		 *  The initial reference count is set to one; this means if you call
		 *  DecRef() immediately after creating the object, it will be destroyed.
		 */
		Base ()
			{ RefCount = 1; }

		/**
		 *  \brief Increment reference count.
		 *
		 *  \details
		 *  Every time when you copy a pointer to a object and store it for
		 *  later use you MUST call IncRef() on it; this will allow to keep
		 *  objects as long as they are referenced by some entity.
		 */
		void IncRef ()
			{ RefCount++; }

		/**
		 *  \brief Decrement object's reference count.
		 *
		 *  \details
		 *  As soon as the last reference to the object is removed, it is destroyed.
		 */
		void DecRef ();

		/**
		 *  \brief Query number of references to this object.
		 *
		 *  \details
		 *  I would rather prefer to have the reference counter strictly private,
		 *  but sometimes, mostly for debugging, such a function can help.
		 */
		int GetRefCount ()
			{ return RefCount; }
};

/**
 *  @}
 */
#endif														// __BASE_H__
