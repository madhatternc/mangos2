/**
 *     \file  src/shared/ThreadFun.h
 *    \brief  Cross-platform thread handling
 *
 * Copyright (C) 2005 by Andrew Zabolotny <zap@homelink.ru>
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

#ifndef __THREAD_FUN_H__
#define __THREAD_FUN_H__

#include "Base.h"

/**
 *  \addtogroup FoundationClasses
 *
 *  @{
 */

/**
 *  \class Thread
 *  \brief A thread.
 *
 *  \par
 *  A thread. Like all objects derived from the Base class a thread is closed
 *  by calling DecRef on it.
 */
class Thread : public Base
{
	public:
		/**
		 *  \enum ThreadPriority
		 *
		 *  Thread priorities
		 */
		enum ThreadPriority
		{
			IDLE,
			LOWER,
			LOW,
			NORMAL,
			HIGH,
			HIGHER,
			REALTIME
		};

		/**
		 *  \brief Start a new thread. Return NULL on error.
		 *
		 *  The created thread starts in the given routine, receiving the
		 *  passed argument.
		 *
		 *  \return \c NULL returend on error.
		 */
		static Thread *Start (void (*routine) (void *arg), void *arg);

		/**
		 *  \brief Set thread priority
		 */
		virtual bool SetPriority (ThreadPriority prio) = 0;
};

/**
 *  \class Mutex
 *  \brief This is a simple mutex.
 */
class Mutex : public Base
{
	public:
		/**
		 * Create a new mutex object.
		 */
		static Mutex *Create ();

		/**
		 *  \brief Lock mutex
		 */
		virtual bool Lock () = 0;

		/**
		 *  \brief Try to lock the mutex; return true on success
		 */
		virtual bool TryLock () = 0;

		/**
		 *  \brief Unblock the mutex
		 */
		virtual void Unlock () = 0;
};

/**
 *  @}
 */
#endif														// __THREAD_FUN_H__
