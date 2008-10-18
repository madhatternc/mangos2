/**
 *     \file  src/shared/win/ThreadFun.cpp
 *    \brief  Windows-specific thread handling
 *
 * Copyright (C) 2005 by Andrew Zabolotny <zap@homelink.ru>
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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Common.h"
#include "ThreadFun.h"

#define WIN32_THREAD_STACK_SIZE 0x10000

class Win32Thread : public Thread
{
    public:
        bool terminate;
        HANDLE th;
        ULONG id;
        void (*routine) (void *arg);
        void *arg;

        Win32Thread ();
        virtual ~Win32Thread ();

        virtual bool SetPriority (ThreadPriority prio);
};

Win32Thread::Win32Thread ()
{
    th = NULL;
    terminate = false;
}

Win32Thread::~Win32Thread ()
{
    /* Kill thread if this is not current thread */
    if (th && (GetCurrentThreadId () != id))
    {
        TerminateThread (th, 0);
        WaitForSingleObject (th, INFINITE);
        CloseHandle (th);
    }
}

bool Win32Thread::SetPriority (ThreadPriority prio)
{
    int p;
    switch (prio)
    {
        case IDLE:  p = THREAD_PRIORITY_IDLE; break;
        case LOWER: p = THREAD_PRIORITY_LOWEST; break;
        case LOW:   p = THREAD_PRIORITY_BELOW_NORMAL; break;
        case NORMAL:    p = THREAD_PRIORITY_NORMAL; break;
        case HIGH:  p = THREAD_PRIORITY_ABOVE_NORMAL; break;
        case HIGHER:    p = THREAD_PRIORITY_HIGHEST; break;
        case REALTIME:  p = THREAD_PRIORITY_TIME_CRITICAL; break;
        default:    p = THREAD_PRIORITY_NORMAL; break;
    }
    return SetThreadPriority (th, p);
}

static DWORD WINAPI thread_start_routine (void *arg)
{
    Win32Thread *newthr = (Win32Thread *)arg;
    newthr->id = GetCurrentThreadId ();
    newthr->routine (newthr->arg);
    return 0;
}

Thread *Thread::Start (void (*routine) (void *arg), void *arg)
{
    DWORD dwtid;
    Win32Thread *newthr = new Win32Thread ();
    newthr->routine = routine;
    newthr->arg = arg;
    newthr->th = CreateThread (NULL, WIN32_THREAD_STACK_SIZE,
        thread_start_routine, newthr, 0, &dwtid);
    if (!newthr->th)
    {
        newthr->DecRef ();
        return NULL;
    }

    return newthr;
}

class Win32Mutex : public Mutex
{
    public:
        HANDLE sem;

        Win32Mutex ();
        virtual ~Win32Mutex ();
        virtual bool Lock ();
        virtual bool TryLock ();
        virtual void Unlock ();
};

Win32Mutex::Win32Mutex ()
{
    sem = CreateMutex (NULL, FALSE, NULL);
}

Win32Mutex::~Win32Mutex ()
{
    CloseHandle (sem);
}

bool Win32Mutex::Lock ()
{
    return (WaitForSingleObject (sem, INFINITE) != WAIT_FAILED);
}

bool Win32Mutex::TryLock ()
{
    DWORD state = WaitForSingleObject (sem, 0);
    return (state == WAIT_OBJECT_0) && (state != WAIT_ABANDONED);
}

void Win32Mutex::Unlock ()
{
    ReleaseMutex (sem);
}

Mutex *Mutex::Create ()
{
    Win32Mutex *mutex = new Win32Mutex ();
    if (!mutex->sem)
    {
        mutex->DecRef ();
        return NULL;
    }
    return mutex;
}
