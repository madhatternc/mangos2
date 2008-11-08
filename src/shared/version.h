/**
 *     \file  src/shared/version.h
 *    \brief  Version info and basic definitions
 *
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

#ifndef __VERSION_H__
#define __VERSION_H__

// Server Settings [ Connection ]
#define COPYRIGHT           "2008 MaNGOS foundation <http://getmangos.com/"

#define DEFDBTYPE           "MySQL"
#define DEFDBADDR           "localhost,mangos2,mangos2,mangos2"

// Start human zone (0 = off / 1 = on)
#define DEFSTARTHUMANZONE   0
// Play Cinematics  (false = off / true = on)
#define DEFSHOWINTRO        1
// Max number of clients
#define DEFCLIENTLIMIT      100

// Max characters per login
#define MAX_CHARS_PER_LOGIN 10

#if PLATFORM == PLATFORM_WIN32
# define FULLVERSION        VERSION "-win"
#else
# define FULLVERSION        VERSION "-nix"
#endif

// Compatible client build range
#define MIN_CLIENT_BUILD    9056 // client version 3.0.2 build 9056
#define MAX_CLIENT_BUILD    9183 // client version 3.0.3 build 9183

// The path to data files
#ifndef DATADIR
#  define DATADIR       ""
#endif

#define CLIENT_PATCHES      DATADIR"client-patches"
#define COLLISION_MAPS      DATADIR"collision-maps"
#define DBC_DATA_FILES      DATADIR"dbc-data"
#define EXPORT_FILES        DATADIR"exports"
#define IMPORT_FILES        DATADIR"imports"
#define STANDARD_MAPS       DATADIR"maps"

// The path to config files
#ifndef SYSCONFDIR
#  define SYSCONFDIR        ""
#endif

#define RL_CONFIG_FILE      SYSCONFDIR"authserver.conf"
#define WS_CONFIG_FILE      SYSCONFDIR"worldserver.conf"
#define VC_CONFIG_FILE      SYSCONFDIR"voicechat.conf"
#endif // __VERSION_H__
