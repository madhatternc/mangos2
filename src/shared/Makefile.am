# Copyright (C) 2005 Team OpenWoW <http://openwow.quamquam.org/>
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

## CPP flags for includes, defines, etc.
AM_CPPFLAGS = $(MYSQL_INCLUDES) -I$(srcdir) -DLIBMANGOS2_VERSION="\"@PACKAGE_VERSION@\""

## Build shared sources as shared library.
#  libmangos2 shared library will later be reused by realm list daemon
#  and world server daemon.
lib_LTLIBRARIES = libmangos2.la

#  Source files which make up libmangos2
libmangos2_la_SOURCES = \
	Base.cpp \
	Base.h \
	BaseVector.cpp \
	BaseVector.h \
	BitVector.h \
	Client.cpp \
	Client.h \
	CommandInterpreter.cpp \
	CommandInterpreter.h \
	Common.h \
	Console.cpp \
	Console.h \
	Database.cpp \
	Database.h \
	DatabaseMySQL.cpp \
	DatabaseMySQL.h \
	Debug.cpp \
	Debug.h \
	EncodeSQL.cpp \
	Errors.h \
	HashVector.cpp \
	HashVector.h \
	Log.cpp \
	Log.h \
	MemoryLeaks.cpp \
	MemoryLeaks.h \
	Server.cpp \
	Server.h \
	Singleton.h \
	Sockets.cpp \
	Sockets.h \
	StringFun.cpp \
	StringFun.h \
	StrVec.cpp \
	StrVec.h \
	SystemFun.h \
	ThreadFun.h \
	Timer.h \
	UTF8Fun.cpp \
	Vector.cpp \
	Vector.h \
	version.h \
	posix/ConsoleSysDep.cpp \
	posix/ThreadFun.cpp \
	posix/TimeFun.cpp \
	posix/WaitSockets.cpp

# Header files to installed for reusing libmangos2
libmangos2_la_HEADERS = \
	Base.h \
	BaseVector.h \
	BitVector.h \
	Client.h \
	CommandInterpreter.h \
	Common.h \
	Console.h \
	Database.h \
	DatabaseMySQL.h \
	Debug.h \
	Errors.h \
	HashVector.h \
	Log.h \
	MemoryLeaks.h \
	Server.h \
	Singleton.h \
	Sockets.h \
	StringFun.h \
	StrVec.h \
	SystemFun.h \
	ThreadFun.h \
	Timer.h \
	Vector.h \
	version.h

#  And the headers go to ...
#  header target version is set manual, since header version
#  rather equals to development milestones.
libmangos2_ladir = $(includedir)/mangos2

## libtool settings
#  Link against dependencies
libmangos2_la_LDFLAGS = -version-info $(LIBMANGOS2_VERSION_INFO)

# Link against MySQL library
libmangos2_la_LIBADD = $(MYSQL_LIBS)

## Additional files to include when running 'make dist'
#  Add win32 sources.
EXTRA_DIST = \
	win/ConsoleSysDep.cpp \
	win/ThreadFun.cpp \
	win/TimeFun.cpp \
	win/WaitSockets.cpp
