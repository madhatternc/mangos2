/**
 *     \file  src/shared/Log.cpp
 *    \brief  Logging functions
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

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>

#include "Log.h"
#include "Console.h"
#include "StringFun.h"
#include "Debug.h"

Log::Log (const char *iLogFileName)
{
    LogFileName = strnew (iLogFileName);
    LoggingFlags = 0;
    LogFile = NULL;
    NewLine = true;
}

Log::~Log ()
{
    delete [] LogFileName;
}

void Log::Write (uint MsgType, const char *str)
{
    if (LoggingFlags & LOG_SCREEN)
    {
        const char *color =
            (MsgType & LOG_DEBUG) ? "\ax2" :
            (MsgType & LOG_COMMON) ? "\ax3" : "\ax5";
        CONSOLE.Out ("\aPU%s%s\aPO", color, str);
    }

    if (LoggingFlags & LOG_FILE)
    {
        if (!LogFile)
        {
            LogFile = fopen (LogFileName, "a");
            if (!LogFile)
            {
                CONSOLE.Out ("\aPU\axcWARNING: Cannot open log file `%s'\aPO\n", LogFileName);
                return;
            }
        }
        fputs (str, LogFile);
    }

    const char *eol = strchr (str, 0);
    if (eol > str)
        NewLine = (eol [-1] == '\n');
}

void Log::Out (uint MsgType, const char *Format, ...)
{
    if (!(LoggingFlags & MsgType))
        return;

    char buff [4096];

    if ((LoggingFlags & LOG_FILE) && NewLine)
    {
        // Output the current time only to log file
        time_t t = time (NULL);
        strftime (buff, sizeof (buff), "%H:%M:%S ", localtime (&t));
        Write (MsgType & ~LOG_SCREEN, buff);
    }

    va_list ap;
    va_start (ap, Format);
    vsnprintf (buff, sizeof (buff), Format, ap);
    va_end (ap);

    Write (MsgType, buff);
}

void Log::Dump (const void *Data, unsigned Size, const void *Base)
{
    if (LoggingFlags & LOG_SCREEN)
        DebugDump (stdout, Data, Size, Base);

    if (LoggingFlags & LOG_FILE)
    {
        if (!LogFile)
        {
            LogFile = fopen (LogFileName, "a");
            if (!LogFile)
            {
                CONSOLE.Out ("\aPU\axcWARNING: Cannot open log file `%s'\aPO\n", LogFileName);
                return;
            }
        }
        DebugDump (LogFile, Data, Size, Base);
    }
}

uint Log::Logging (uint iFlags, uint iMask)
{
    uint oldlf = LoggingFlags;
    LoggingFlags = (LoggingFlags & ~iMask) | (iFlags & iMask);
    if ((oldlf ^ LoggingFlags) & LOG_FILE)
    {
        if (!(LoggingFlags & LOG_FILE) && LogFile)
        {
            fclose (LogFile);
            LogFile = NULL;
        }
    }

    return LoggingFlags;
}

uint Log::Logging (const char *iFlags)
{
    char c;
    uint newmask = 0, newstate = 0;
    while ((c = *iFlags++))
    {
        uint mask;
        switch (tolower (c))
        {
        case 's':   mask = LOG_SCREEN; break;
        case 'f':   mask = LOG_FILE; break;
        case 'd':   mask = LOG_DEBUG; break;
        case 'c':   mask = LOG_COMMON; break;
        case 'i':   mask = LOG_IMPORTANT; break;
        default:
            Out (LOG_COMMON, "Bad logging flag `%c' requested\n", c);
            continue;
        }
        newmask |= mask;
        if (isupper (c))
            newstate |= mask;
        else
            newstate &= ~mask;
    }
    return Logging (newstate, newmask);
}

void Log::GetLogging (char *oBuffer, size_t iBufferLen)
{
    iBufferLen--;

#define PUSH(str) \
    { \
        int i = nstrcpy (oBuffer, iBufferLen, str); \
        oBuffer += i; \
        iBufferLen -= i; \
    }

    bool first = true;
    if (LoggingFlags & LOG_SCREEN)
    {
        PUSH ("Screen");
        first = false;
    }
    if (LoggingFlags & LOG_FILE)
    {
        if (!first)
            PUSH (", ");
        PUSH ("File");
        first = false;
    }
    if (!first)
        PUSH (": ");

    first = true;
    if (LoggingFlags & LOG_DEBUG)
    {
        if (!first)
            PUSH (", ");
        PUSH ("Debug");
        first = false;
    }
    if (LoggingFlags & LOG_COMMON)
    {
        if (!first)
            PUSH (", ");
        PUSH ("Common");
        first = false;
    }
    if (LoggingFlags & LOG_IMPORTANT)
    {
        if (!first)
            PUSH (", ");
        PUSH ("Important");
        //first = false;
    }
}
