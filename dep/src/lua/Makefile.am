# Copyright (C) 2008 MaNGOS foundation <http://getmangos.com/>
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

AM_CPPFLAGS = -I$(srcdir)/../../include -I$(srcdir)/../../include/zlib -DUSE_DLOPEN=1 -DUSE_DEGREES -DUSE_TMPNAME=0 -DLUA_USE_POSIX

noinst_LIBRARIES = liblua.a

liblua_a_SOURCES = \
    lapi.c \
    lapi.h \
    lauxlib.c \
    lauxlib.h \
    lbaselib.c \
    lcode.c \
    lcode.h \
    ldblib.c \
    ldebug.c \
    ldebug.h \
    ldo.c \
    ldo.h \
    ldump.c \
    lfunc.c \
    lfunc.h \
    lgc.c \
    lgc.h \
    linit.c \
    liolib.c \
    llex.c \
    llex.h \
    llimits.h \
    lmathlib.c \
    lmem.c \
    lmem.h \
    loadlib.c \
    lobject.c \
    lobject.h \
    lopcodes.c \
    lopcodes.h \
    loslib.c \
    lparser.c \
    lparser.h \
    lstate.c \
    lstate.h \
    lstring.c \
    lstring.h \
    lstrlib.c \
    ltable.c \
    ltable.h \
    ltablib.c \
    ltm.c \
    ltm.h \
    lua.h \
    luaconf.h \
    lualib.h \
    lundump.c \
    lundump.h \
    lvm.c \
    lvm.h \
    lzio.c \
    lzio.h \
    print.c

EXTRA_DIST = \
    lua.c \
    luac.c \
    lua.aps \
    lua.ico \
    lua.rc \
    resource.h
