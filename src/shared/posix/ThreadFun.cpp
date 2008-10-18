/**
 *     \file  src/shared/posix/ThreadFun.cpp
 *    \brief  POSIX-specific thread handling
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

#include <pthread.h>
#include "Common.h"
#include "ThreadFun.h"

class PosixThread : public Thread
{
    public:
        pthread_t tid;
        void (*routine) (void *arg);
        void *arg;

        PosixThread ();
        virtual ~PosixThread ();

        virtual bool SetPriority (ThreadPriority prio);
};

PosixThread::PosixThread ()
{
    tid = 0;
}

PosixThread::~PosixThread ()
{
    /* Kill thread if this is not the current thread */
    if (tid && (pthread_self () != tid))
    {
        pthread_cancel (tid);
        pthread_join (tid, NULL);
    }
}

bool PosixThread::SetPriority (ThreadPriority prio)
{
    int p;
    int min = sched_get_priority_min (SCHED_OTHER);
    int max = sched_get_priority_max (SCHED_OTHER);
    switch (prio)
    {
        case IDLE:  p = min; break;
        case LOWER: p = min + (max - min) / 6; break;
        case LOW:   p = min + (max - min) / 3; break;
        case NORMAL:    p = min + (max - min) / 2; break;
        case HIGH:  p = max - (max - min) / 3; break;
        case HIGHER:    p = max - (max - min) / 6; break;
        case REALTIME:  p = max; break;
        default:    p = min + (max - min) / 2; break;
    }

    sched_param schedparams;
    schedparams.sched_priority = p;
    return (pthread_setschedparam (tid, SCHED_OTHER, &schedparams) == 0);
}

static void *thread_start_routine (void *arg)
{
    PosixThread *newthr = (PosixThread *)arg;
    pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    newthr->routine (newthr->arg);
    return NULL;
}

Thread *Thread::Start (void (*routine) (void *arg), void *arg)
{
    PosixThread *newthr = new PosixThread ();
    newthr->routine = routine;
    newthr->arg = arg;
    int rc = pthread_create (&newthr->tid, NULL, thread_start_routine, newthr);
    if (rc)
    {
        newthr->DecRef ();
        return NULL;
    }

    return newthr;
}

class PosixMutex : public Mutex
{
    public:
        pthread_mutex_t mutex;
        static pthread_mutexattr_t attr;
        static int attr_refcount;

        PosixMutex ();
        virtual ~PosixMutex ();
        virtual bool Lock ();
        virtual bool TryLock ();
        virtual void Unlock ();
};

pthread_mutexattr_t PosixMutex::attr;
int PosixMutex::attr_refcount = 0;

PosixMutex::PosixMutex ()
{
    if (!attr_refcount++)
    {
        pthread_mutexattr_init (&attr);
        pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    }

    pthread_mutex_init (&mutex, &attr);
}

PosixMutex::~PosixMutex ()
{
    pthread_mutex_destroy (&mutex);
    if (!--attr_refcount)
        pthread_mutexattr_destroy (&attr);
}

bool PosixMutex::Lock ()
{
    return (pthread_mutex_lock (&mutex) == 0);
}

bool PosixMutex::TryLock ()
{
    return pthread_mutex_trylock (&mutex) == 0;
}

void PosixMutex::Unlock ()
{
    pthread_mutex_unlock (&mutex);
}

Mutex *Mutex::Create ()
{
    return new PosixMutex ();
}
