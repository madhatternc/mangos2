/**
 *     \file  src/shared/SystemFun.h
 *    \brief  System-dependent functions
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

#ifndef __SYSTEM_FUN_H__
#define __SYSTEM_FUN_H__

#include "Common.h"

/**
 * Sleep given number of milliseconds (1/1000 seconds, that is).
 */
void SleepMs (int ms);

/**
 * Get number of milliseconds passed since doesn't matter when.
 */
uint32 GetMilliseconds ();
#endif                                                      // __SYSTEM_FUN_H__
