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

## Sub directories to parse
SUBDIRS = todo

## CPP flags for includes, defines, etc.
AM_CPPFLAGS = $(MYSQL_INCLUDES)-I$(srcdir) -I$(srcdir)/../shared -I$(srcdir)/../../dep/src/lua -I$(srcdir)/../../dep/src/lua/lib -I$(srcdir)/../../dep/src/tolua++/include -DSYSCONFDIR=\"$(sysconfdir)/\"

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
	worldserver.lua \
	worldserver.pkg \
	worldserver.conf.dist \
	resource.h \
	worldserver.rc

## Link realm list daemon against the shared library
mangos2_worldserver_LDADD = -lmangos2 -ltolua -llua -llualib
mangos2_worldserver_LDFLAGS = \
	-L../shared/ \
	-L../../dep/src/tolua++/lib/ \
	-L../../dep/src/lua/ \
	-L../../dep/src/lua/lib/ \
	$(MYSQL_LIBS) $(ZLIB) $(COMPATLIB) $(SSLLIB) $(TERMLIB)

GameClient.o: Opcodes.inc

Luawrapper.cpp: Opcodes.h worldserver.pkg
	@echo "Generating LUA wrapper"
	$(srcdir)/../../dep/src/tolua++/bin/tolua -1 -L worldserver.lua -o Luawrapper.cpp worldserver.pkg

if USE_CODEGEN

Opcodes.h: Protocol.rules $(srcdir)/../tools/gencode/gencode.py $(srcdir)/../tools/gencode/gencxx.py
	@echo "Generating " $@
	@PYTHONPATH@ $(srcdir)/../tools/gencode/gencode.py -t cxx -f $@ -w header $<

Opcodes.cpp: Protocol.rules $(srcdir)/../tools/gencode/gencode.py $(srcdir)/../tools/gencode/gencxx.py Opcodes.h
	@echo "Generating " $@
	@PYTHONPATH@ $(srcdir)/../tools/gencode/gencode.py -t cxx -f $@ -w code $< $(DEBUG_TRUE)-n

Opcodes.inc: Protocol.rules $(srcdir)/../tools/gencode/gencode.py ../tools/gencode/gencxx.py
	@echo "Generating " $@
	@PYTHONPATH@ $(srcdir)/../tools/gencode/gencode.py -t cxx -f $@ -w parser $<

endif

