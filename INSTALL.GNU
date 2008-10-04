= MaNGOS2 -- Installation =

Copyright (c) 2005 Team OpenWoW <http://openwow.quamquam.org/>
Copyright (c) 2008 MaNGOS foundation <http://www.getmangos.com/>

See the COPYING file for copying conditions.

== Installation Instructions ==
This documents describes the installation process for MaNGOS2 on Unix
platforms using the standard Makefile build process. This includes systems
like Fedora Core, Debian, Ubuntu, FreeBSD, etc.

=== Configuring ===
MaNGOS2 uses the standard autoconf configure, thus all autoconf options
apply. In common we will assume that you do have a working C++ compiler on
your systems. If not, GCC (http://gcc.gnu.org/) is your friend.

In case you have checked out MaNGOS2 from the SubVersion repository,
please run the following command to create a working build environment:

$ autoreconf --install --force

You may otherwise not be able to run a build.

There are several programs and libraries required in order to compile MaNGOS2
successfully:

 * pthread development package (headers) are required, as MaNGOS2 uses
   threads. 
   Note: on some systems, the pthread development files are part of the
   glibc packages.
 * zlib development package (headers) are required, as we use them for data
   compression.
 * MySQL development package (headers) are required, because we are using
   this backend for storing all data.
 * OpenSSL development package (headers) are required, because we are using
   them for authenticating the game client.
 * Curses or termcap headers are not required but highly recommended because
   you'll get a much nicer console input/output.

Here's a list of options that is specifically useful for configuring MaNGOS2:

 --sysconfdir=/etc/mangos2
   
   This will set the directory where the compiled daemons will look for the
   configuration files.

 --prefix=/home/your-username
   local user directory

 --enable-debug
   If you use this option, the DEBUG_PRINTF macro and some other debugging
   macros will be enabled. This means you will get much more information
   about what goes on, so use this option if something doesn't work and you
   don't understand what happens.

To configure for production use, you can create a shell script like this one:

#!/bin/sh

OPT="-s -O3 -ffast-math -Wall -Wno-long-long"
CFLAGS="$OPT" \
CXXFLAGS="$OPT -fomit-frame-pointer -fno-exceptions" \
LDFLAGS="-s" ./configure --sysconfdir=/etc/mangos2

I especially recommend the -fno-exceptions switch, since the resulting
executable will be around 20% smaller and we don't use exceptions anyway.

=== Compiling ===
Well, it should be fairly simple if you got all the pre-requisites. Just
type

$ make

If you have a problem during compilation, we can't tell you what to do.
Figure it out yourself. If we would know in advance what problems you would
encounter, we would fix it in advance, or put a warning message in configure
at least.

Until this development branch will be merged into the trunk of our
SubVersion repository, no support will be provided.

Thank you for understanding.

=== Installing ===
Installation is straight-forward and only requires you to run a short
command line:

$ make install

