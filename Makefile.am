# Copyright (C) 2005 Team OpenWoW <http://openwow.quamquam.org/>
# Copyright (C) 2008 MaNGOS foundation <http://www.getmangos.com/>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in

SUBDIRS = dep doc sql src

EXTRA_DIST = \
    INSTALL.GNU \
    INSTALL.Win.txt \
    TODO

EXTRA_DIST += \
    win/beforerealm.bat \
    win/beforeworld.bat \
    win/config.win.h

EXTRA_DIST += \
    win/VC9/MaNGOS2.sln \
    win/VC9/lua.vcproj \
    win/VC9/libmangos2.vcproj \
    win/VC9/realmlist.vcproj \
    win/VC9/worldserver.vcproj

AM_MAKEFLAGS = --no-print-directory
