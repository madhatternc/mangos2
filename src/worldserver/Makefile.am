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

## Sub directories to parse
SUBDIRS = todo

## CPP flags for includes, defines, etc.
AM_CPPFLAGS = $(MYSQL_INCLUDES)-I$(srcdir) -I$(srcdir)/../shared -I$(srcdir)/../shared/lua -I$(srcdir)/../tools/tolua/include -DSYSCONFDIR=\"$(sysconfdir)/\"

## Build world daemon as standalone program
bin_PROGRAMS = mangos2-worldserver

mangos2_worldserver_SOURCES = \
	Luawrapper.cpp \
	Luawrapper.h \
	Opcodes.cpp \
	Opcodes.h \
	Quadtree.cpp \
	Quadtree.h \
	GameClient.cpp \
	GameClient.h \
	Characters.cpp \
	ProtocolVectors.cpp \
	ProtocolVectors.h \
	WorldServer.cpp \
	WorldServer.h \
	Main.cpp \
	ObjectVector.cpp \
	ObjectVector.h \
	Unit.cpp \
	Unit.h \
	Player.cpp \
	Player.h \
	Item.cpp \
	Item.h \
	AccountData.cpp \
	Affect.h \
	AuctionHouse.h \
	Mail.h \
	Object.cpp \
	Object.h \
	UpdateFields.h

sysconf_DATA = \
	worldserver.conf.dist

install-data-hook:
	@list='$(sysconf_DATA)'; for p in $$list; do \
      dest=`echo $$p | sed -e s/.dist//`; \
	  if test -f $(DESTDIR)$(sysconfdir)/$$dest; then \
        echo "$@ will not overwrite existing $(DESTDIR)$(sysconfdir)/$$dest"; \
      else \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(sysconfdir)/$$dest"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(sysconfdir)/$$dest; \
	  fi; \
	done

clean-local:
	rm -f $(sysconf_DATA)

EXTRA_DIST = \
	Opcodes.inc \
	Protocol.rules \
	worldsrv.lua \
	worldsrv.pkg \
	worldserver.conf.dist

## Link realm list daemon against the shared library
mangos2_worldserver_LDADD = -lmangos2 -ltolua -llua -llualib
mangos2_worldserver_LDFLAGS = \
	-L../shared/ \
	-L../tools/tolua/lib/ \
	-L../shared/lua/ \
	-L../shared/lua/lib/ \
	$(MYSQL_LIBS) $(ZLIB) $(COMPATLIB) $(SSLLIB) $(TERMLIB)

GameClient.o: Opcodes.inc

Luawrapper.cpp: Opcodes.h worldsrv.pkg
	@echo "Generating LUA wrapper"
	../tools/tolua/bin/tolua -1 -L worldsrv.lua -o Luawrapper.cpp worldsrv.pkg

if USE_CODEGEN

Opcodes.h: Protocol.rules ../tools/gencode/gencode.py ../tools/gencode/gencxx.py
	@echo "Generating " $@
	@PYTHONPATH@ ../tools/gencode/gencode.py -t cxx -f $@ -w header $<

Opcodes.cpp: Protocol.rules ../tools/gencode/gencode.py ../tools/gencode/gencxx.py Opcodes.h
	@echo "Generating " $@
	@PYTHONPATH@ ../tools/gencode/gencode.py -t cxx -f $@ -w code $< $(DEBUG_TRUE)-n

Opcodes.inc: Protocol.rules ../tools/gencode/gencode.py ../tools/gencode/gencxx.py
	@echo "Generating " $@
	@PYTHONPATH@ ../tools/gencode/gencode.py -t cxx -f $@ -w parser $<

endif

