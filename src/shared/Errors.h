/**
 *     \file  src/shared/Errors.h
 *    \brief  Error helper functions
 *
 * Copyright (C) 2005 Team OpenWoW <http://openwow.quamquam.org/>
 * Copyright (C) 2008 MaNGOS foundation <http://getmangos.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <assert.h>
#include <stdio.h>

#include <assert.h>
#include <stdio.h>

// TODO: handle errors better

// An assert isn't necessarily fatal, although if compiled with asserts enabled it will be.
#define WPAssert(assertion) { if (!(assertion)) { fprintf (stderr, "\n%s:%i ASSERTION FAILED:\n  %s\n", __FILE__, __LINE__, #assertion); assert (#assertion &&0); } }
#define WPError(assertion, errmsg) if (! (assertion)) { LOG.outError ("%s:%i ERROR:\n  %s\n", __FILE__, __LINE__, (char *)errmsg); assert (false); }
#define WPWarning(assertion, errmsg) if (! (assertion)) { LOG.outError ("%s:%i WARNING:\n  %s\n", __FILE__, __LINE__, (char *)errmsg); }

// This should always halt everything.  If you ever find yourself wanting to remove the assert (false), switch to WPWarning or WPError
#define WPFatal(assertion, errmsg) if (! (assertion)) { LOG.outError ("%s:%i FATAL ERROR:\n  %s\n", __FILE__, __LINE__, (char *)errmsg); assert (#assertion &&0); THREADS.closeCurrentThread (); }

#endif // __ERRORS_H__
