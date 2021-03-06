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
AM_CPPFLAGS = $(MYSQL_INCLUDES) -I$(srcdir)/../shared -I$(srcdir) -DSYSCONFDIR=\"$(sysconfdir)/\"

## Build realm list daemon as standalone program
bin_PROGRAMS = mangos2-authserver
mangos2_authserver_SOURCES = \
	Main.cpp \
	RealmClient.cpp \
	RealmClient.h \
	RealmListSrv.cpp \
	RealmListSrv.h \
	Opcodes.cpp \
	Opcodes.h \
	AccountMgr.cpp \
	AccountMgr.h \
	RealmMgr.cpp \
	RealmMgr.h \
	SrpRealm.cpp \
	SrpRealm.h \
	bigint.c \
	bigint.h

## Link realm list daemon against the shared library
mangos2_authserver_LDADD = -lmangos2
mangos2_authserver_LDFLAGS = \
	-L$(srcdir) \
	-L../shared/ \
	$(MYSQL_LIBS) $(ZLIB) $(COMPATLIB) $(SSLLIB) $(TERMLIB)

## Configuration file installation
sysconf_DATA = \
	authserver.conf.dist

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

## Additional files to include when running 'make dist'
#  Add rules files for generating realm packets
EXTRA_DIST = \
	Opcodesinc \
	Protocol.rules \
	authserver.conf.dist \
	authserver.rc \
	resource.h

## Custom rules for generated sources
RealmClient.o Opcodes.o: Opcodes.h Opcodes.inc

if USE_CODEGEN

Opcodes.h: Protocol.rules $(srcdir)/../tools/gencode/gencode.py $(srcdir)/../tools/gencode/gencxx.py
	@echo "Generating " $@
	@PYTHONPATH@ $(srcdir)/../tools/gencode/gencode.py -t cxx -f $@ -w header $<

Opcodes.inc: Protocol.rules $(srcdir)/../tools/gencode/gencode.py $(srcdir)/../tools/gencode/gencxx.py
	@echo "Generating " $@
	@PYTHONPATH@ $(srcdir)/../tools/gencode/gencode.py -t cxx -f $@ -w parser $<

Opcodes.cpp: Protocol.rules $(srcdir)/../tools/gencode/gencode.py $(srcdir)/../tools/gencode/gencxx.py
	@echo "Generating " $@
	@PYTHONPATH@ $(srcdir)/../tools/gencode/gencode.py -t cxx -f $@ -w code $<

endif
