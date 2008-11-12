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

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

## Prelude, basic settings for Autoconf
#  Autoconf version:   Autoconf 2.60 or newer
#  PACKAGE:            mangos2
#  VERSION:            0.6.0.01
#  BUG-REPORT-ADDRESS: http://mangos.lighthouseapp.com/
AC_PREREQ(2.61)
AC_INIT( [mangos2], [0.6.0.01], [http://mangos.lighthouseapp.com/])
AC_DEFINE([PACKAGE_URL],["http://getmangos.com/wiki/"],[project url])
AC_CONFIG_SRCDIR([src/shared/Base.cpp])

## Prelude, basic settings for Automake
#  Turn on all warnings and error messages, and enforce GNU
#  standards for the package.
AM_INIT_AUTOMAKE([-Wall -Werror])
AM_MAINTAINER_MODE

## Check for required dependencies.

## Check for a valid build environment.
#  Valid equals having:
#  - a C++ compiler compliant with the ISO98 C++ specification.
#  - a working library tool for creating convenience libraries.
#  - a working linker for creating static and shared libraries.
#  - a working make environment
#  - and a working python interpreter for code generation
AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

LPATH="$PATH:/usr/local/bin"

# {{{ LIBMANGOS2_VERSION / LIBMANGOS2_VERSION_INFO
LIBMANGOS2_MAJOR_VERSION="$(echo $PACKAGE_VERSION | cut -d. -f1)"
LIBMANGOS2_MINOR_VERSION="$(echo $PACKAGE_VERSION | cut -d. -f2)"
LIBMANGOS2_MICRO_VERSION="$(echo $PACKAGE_VERSION | cut -d. -f3)"

LIBMANGOS2_VERSION="$PACKAGE_VERSION"
LIBMANGOS2_VERSION_INFO=`expr $LIBMANGOS2_MAJOR_VERSION + $LIBMANGOS2_MINOR_VERSION`:$LIBMANGOS2_MICRO_VERSION:$LIBMANGOS2_MINOR_VERSION
PACKAGE_RELEASE="$LIBMANGOS2_MAJOR_VERSION.$LIBMANGOS2_MINOR_VERSION"
# }}}

# {{{ CHECK FOR CODE GENERATION
AC_PATH_PROG(PYTHONPATH, python)
if test "_$PYTHONPATH" = _ ; then
    AC_MSG_WARN([python is required to build, when the packet rule files change.])
fi
AM_CONDITIONAL([USE_CODEGEN], [test "_$PYTHONPATH" != _])
# }}}

## Check for required libraries.
AC_CHECK_LIB( pthread, pthread_create, [],
    [LDFLAGS="-pthread $LDFLAGS"
     AC_TRY_LINK([char pthread_create();],
         pthread_create();,
         [], [AC_MSG_ERROR([Missing pthread])])
    ])
AC_CHECK_LIB( z, compress, [ZLIB=-lz],[AC_MSG_ERROR([Missing zlib])] )
AC_CHECK_LIB( compat, ftime, [COMPATLIB=-lcompat] )
AC_CHECK_LIB( ssl, BN_cmp, [SSLLIB=-lssl], [AC_MSG_ERROR([Missing openssl])])
AC_CHECK_LIB( termcap, tgetent, [TERMLIB=-ltermcap],
    [AC_CHECK_LIB( ncurses, tgetent, [TERMLIB=-lncurses],
         [AC_MSG_ERROR([Either termcap or ncurses is required])]
    )]
)
# {{{ CHECK FOR WORKING MYSQL INSTALLATION
AC_ARG_WITH(mysql-libs,
[--with-mysql-libs=DIR Look for mysql libs in this dir ],
    MYSQL_LIBS="-L$withval -lmysqlclient"
)
AC_ARG_WITH(mysql-includes,
[--with-mysql-includes=DIR Look for mysql includes in this dir ],
    MYSQL_INCLUDES="-I$withval"
)

AC_PATH_PROGS(MYSQL_CONFIG, mysql_config, mysql_config, $PATH)
if test -x "$MYSQL_CONFIG"
then
    # MySQL v4 uses --include while v3 uses --cflags
    MYSQL_INCLUDES="`$MYSQL_CONFIG --include`" || \
        MYSQL_INCLUDES="`$MYSQL_CONFIG --cflags`"
    MYSQL_LIBS="`$MYSQL_CONFIG --libs_r`"
fi
# }}}

## Development settings
#  Default compiler flags
CFLAGS=${CFLAGS:--s -O3 -ffast-math -Wall -Wno-long-long}
CPPFLAGS=${CPPFLAGS:--s -O3 -ffast-math -Wall -Wno-long-long -fomit-frame-pointer -fno-exceptions}

# provide flag --enable-debug
AC_ARG_ENABLE(debug, AC_HELP_STRING([[--enable-debug]], [enable debugging output to stdout]),
[if test "$enableval" = "yes"; then
		 AC_DEFINE(DEBUG, 1, Enable this to include additional debugging code in executable)
		 CFLAGS="$CFLAGS -DDEBUG -O2 -g -Wall"
		 CPPFLAGS="$CPPFLAGS -DDEBUG -O2 -g -Wall"
fi]
)

## Check for required header files.
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h libintl.h limits.h locale.h malloc.h memory.h netdb.h netinet/in.h stddef.h stdlib.h string.h strings.h sys/ioctl.h sys/socket.h sys/time.h sys/timeb.h termios.h unistd.h])

AC_CHECK_HEADERS([pthread.h])
AC_CHECK_HEADERS([openssl/bn.h openssl/engine.h openssl/opensslv.h openssl/sha.h])
AC_CHECK_HEADERS([mysql.h mysql/mysql.h mysqld_error.h mysql/mysqld_error.h])
AC_CHECK_HEADERS([termcap.h])

## Check for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_C_VOLATILE
AC_CHECK_TYPES([ptrdiff_t])

## Check for required library functions.
AC_FUNC_ERROR_AT_LINE
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STRCOLL
AC_FUNC_STRFTIME
##AC_FUNC_STRNLEN
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit bzero floor ftime gethostbyname gettimeofday inet_ntoa localtime_r memchr memmove memset pow rint select setlocale socket sqrt stpcpy strcasecmp strchr strcspn strerror strpbrk strrchr strspn strstr strtol strtoul strtoull])

## Export defined variables
AC_SUBST(ZLIB)
AC_SUBST(COMPATLIB)
AC_SUBST(SSLLIB)
AC_SUBST(TERMLIB)
AC_SUBST(MYSQL_INCLUDES)
AC_SUBST(MYSQL_LIBS)
AC_SUBST(PYTHONPATH)
AC_SUBST(USE_CODEGEN)
AC_SUBST(LIBMANGOS2_VERSION)
AC_SUBST(LIBMANGOS2_VERSION_INFO)
AC_SUBST(PACKAGE_RELEASE)

## Set output files.
AC_CONFIG_HEADER([config.h])

AC_CONFIG_FILES([Makefile
         dep/Makefile
         dep/inc/Makefile
         dep/lib/Makefile
         dep/src/Makefile
         dep/src/lua/Makefile
         dep/src/lua/lib/Makefile
         dep/src/tolua++/Makefile
         dep/src/tolua++/lib/Makefile
         dep/src/tolua++/bin/Makefile
         doc/Doxyfile
         doc/Makefile
         sql/Makefile
         sql/authserver/Makefile
         sql/worlddata/Makefile
         src/Makefile
         src/authserver/Makefile
         src/authserver/authserver.conf.dist
         src/shared/Makefile
         src/tools/Makefile
         src/tools/gencode/Makefile
         src/tools/gencode/yaml/Makefile
         src/worldserver/Makefile
         src/worldserver/worldserver.conf.dist
         src/worldserver/todo/Makefile])

## Additional processing

## Output files.
AC_OUTPUT
