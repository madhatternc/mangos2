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

AM_CPPFLAGS = -I$(srcdir) -I$(srcdir)/../ -DUSE_DLOPEN=1 -DUSE_DEGREES -DUSE_TMPNAME=0 -DLUA_USE_POSIX

noinst_LIBRARIES = liblualib.a

liblualib_a_SOURCES = \
    lauxlib.c \
    lbaselib.c \
    ldblib.c \
    liolib.c \
    lmathlib.c \
    ltablib.c \
    lstrlib.c \
    loadlib.c

EXTRA_DIST = \
    README
