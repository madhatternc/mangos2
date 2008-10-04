/**
 *     \file  src/shared/win/TimeFun.cpp
 *    \brief  Windows-specific implementation of some functions
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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#include "SystemFun.h"
#include "Common.h"

uint32 GetMilliseconds ()
{
	uint32 time_in_ms = 0;
	time_in_ms = timeGetTime();
	return time_in_ms;
}

void SleepMs (int ms)
{
	Sleep (ms);
}
