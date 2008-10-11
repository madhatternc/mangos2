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

SUBDIRS = lib

AM_CPPFLAGS = -I$(srcdir) -DUSE_DLOPEN=1 -DUSE_DEGREES -DUSE_TMPNAME=0 -DLUA_USE_POSIX

noinst_LIBRARIES = liblua.a

liblua_a_SOURCES = \
    lapi.c \
    lcode.c \
    ldebug.c \
    ldo.c \
    ldump.c \
    lfunc.c \
    lgc.c \
    llex.c \
    lmem.c \
    lobject.c \
    lopcodes.c \
    lparser.c \
    lstate.c \
    lstring.c \
    ltable.c \
    ltests.c \
    ltm.c \
    lundump.c \
    lvm.c \
    lzio.c

EXTRA_DIST = \
    lapi.h \
    lauxlib.h \
    lcode.h \
    ldebug.h \
    ldo.h \
    lfunc.h \
    lgc.h \
    llex.h \
    llimits.h \
    lmem.h \
    lobject.h \
    lopcodes.h \
    lparser.h \
    lstate.h \
    lstring.h \
    ltable.h \
    ltm.h \
    lua.h \
    lualib.h \
    lundump.h \
    lvm.h \
    lzio.h

EXTRA_DIST += \
    config \
    README
