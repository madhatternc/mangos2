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

AM_CPPFLAGS = -I$(srcdir) -I$(srcdir)/../include -I$(srcdir)/../../lua

noinst_PROGRAMS = tolua

tolua_LDADD = -lm -ltolua -llua
tolua_LDFLAGS = \
    -L../lib/ \
    -L../../lua/

tolua_SOURCES = \
    tolua.c \
    toluabind.c \
    toluabind.h

EXTRA_DIST = \
    toluabind_default.c \
    toluabind_default.h

EXTRA_DIST += \
    lua/all.lua \
    lua/array.lua \
    lua/basic.lua \
    lua/class.lua \
    lua/clean.lua \
    lua/code.lua \
    lua/compat-5.1.lua \
    lua/compat.lua \
    lua/container.lua \
    lua/custom.lua \
    lua/declaration.lua \
    lua/define.lua \
    lua/doit.lua \
    lua/enumerate.lua \
    lua/feature.lua \
    lua/function.lua \
    lua/module.lua \
    lua/namespace.lua \
    lua/operator.lua \
    lua/package.lua \
    lua/typedef.lua \
    lua/variable.lua \
    lua/verbatim.lua
