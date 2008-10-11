/**
 *     \file  src/shared/Debug.h
 *    \brief  Debugging helper functions
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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Console.h"

/**
 *  \defgroup DebuggingClasses Debugging Classes
 */

/**
 *  \addtogroup DebuggingClasses
 *
 *  @{
 */

/**
 * All kind of asserts, as well as debug outputs must be activated ONLY IN DEBUG BUILDS.
 * The reason for having the following macros is to disable all kinds of debugging
 * for release builds.
 */

#ifdef DEBUG
#  include <assert.h>
#  include "Console.h"
#  define DEBUG_DUMP (f,d,s,r) DebugDump (f, d, s, r)
#  if COMPILER == COMPILER_GNU
#    define DEBUG_BREAK asm ("int $3")
#  elif (COMPILER == COMPILER_MICROSOFT) || (COMPILER == COMPILER_BORLAND)
#    define DEBUG_BREAK _asm { int 3 }
#  else
#    define DEBUG_BREAK
#  endif
#  define DEBUG_BREAK_IF(cond) { if (cond) DEBUG_BREAK; }
#  define ASSERT(cond) assert(cond)
#  if __GNUC__ >= 3
#    define DEBUG_PRINTF CONSOLE.Out ("\ax4%s\axc:\ax4%s\axc:\ax4%d\axc: \ax3", __FILE__, __FUNCTION__, __LINE__), CONSOLE.Out
#  else
#    define DEBUG_PRINTF CONSOLE.Out ("\ax4%s\axc:\ax4%d\axc: \ax3", __FILE__, __LINE__), CONSOLE.Out
#  endif
#else
#  define DEBUG_DUMP (f,d,s,r)
#  define DEBUG_BREAK
#  define DEBUG_BREAK_IF(cond)
#  define ASSERT(cond)
static inline void DEBUG_PRINTF (...) {}
#endif

// Neat for debugging
void DebugDump(FILE *Out, const void *Data, unsigned Size, const void *Base = (const void *)-1);

void printBytes(void *bytes, int l, char *name);

/**
 *  @}
 */
#endif // __DEBUG_H__
