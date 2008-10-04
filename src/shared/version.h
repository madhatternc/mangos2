/**
 *     \file  src/shared/version.h
 *    \brief  Version info and basic definitions
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

#ifndef __VERSION_H__
#define __VERSION_H__

#include "svn_revision.h"

// Server Settings [ Connection ]
#define COPYRIGHT           "2008 MaNGOS foundation <http://www.getmangos.com/"

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
# define FULLVERSION        VERSION "-win" " (Revision " SVN_REVISION " )"
#else
# define FULLVERSION        VERSION "-nix" " (Revision " SVN_REVISION " )"
#endif

// Compatible client build range
#define MIN_CLIENT_BUILD    8606							// client 2.4.3
#define MAX_CLIENT_BUILD    8606							// client 2.4.3

// The path to data files
#ifndef DATADIR
#  define DATADIR       ""
#endif

#define CLIENT_PATCHES      DATADIR"client-patches"
#define COLLISION_MAPS      DATADIR"collision-maps"
#define DBC_DATA_FILES      DATADIR"dbc-data"
#define EXPORT_FILES        DATADIR"exports"
#define IMPORT_FILES        DATADIR"imports"

// The path to config files
#ifndef SYSCONFDIR
#  define SYSCONFDIR        ""
#endif

#define RL_CONFIG_FILE      SYSCONFDIR"realmlist.conf"
#define WS_CONFIG_FILE      SYSCONFDIR"worldserver.conf"
#define VC_CONFIG_FILE      SYSCONFDIR"voicechat.conf"
#endif														// __VERSION_H__
