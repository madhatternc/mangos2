/**
 *     \file  src/shared/Log.h
 *    \brief  Logger class
 *
 * Copyright (C) 2005 Team OpenWoW <http://openwow.quamquam.org/>
 * Copyright (C) 2008 MaNGOS foundation <http://www.getmangos.com/>
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

#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include "Base.h"

/* Logger state is expressed as a bit mask consisting of the constants
 * listed below.
 */

// Enable debug logging
#define LOG_DEBUG       0x00000001
// Enable logging of common events
#define LOG_COMMON      0x00000002
// Enable logging of important events
#define LOG_IMPORTANT   0x00000004
// Enable logging to file
#define LOG_FILE        0x00000010
// Enable logging to screen
#define LOG_SCREEN      0x00000020
// A mask for the all logging flags
#define LOG_ALLMASK     ((uint)-1)

class Log : public Base
{
    protected:
        /// Log file name
        char *LogFileName;
        /// Current logging state
        uint LoggingFlags;
        /// Log file
        FILE *LogFile;
        /// True if previous output was ended with \n
        bool NewLine;

        /**
         * Put a raw string into the log.
         * @arg str
         *   The string to put into the log
         */
        void Write (uint MsgType, const char *str);

        // Private destructor -- called from DecRef ()
        virtual ~Log ();

    public:
        Log (const char *iLogFileName);

        /**
         * Output something to log.
         * @arg MsgType
         *   Message type, one of LOG_(DEBUG|COMMON|IMPORTANT)
         * @arg Format
         *   A format string, just like in printf()
         */
        void Out (uint MsgType, const char *Format, ...);

        /**
         * Output a memory dump.
         * @arg Data
         *   Data address
         * @arg Size
         *   Data size
         * @arg Base
         *   Base address for dump. Addresses in dump will be present as
         *   the real virtual address of the data minus this argument.
         *   If it is (void *)-1, it's considered same as Data
         */
        void Dump (const void *Data, unsigned Size, const void *Base = (const void *)-1);

        /**
         * Get/set protocol logging state.
         * This function can be used to change only a specific logging state
         * without touching others. Also it can be used to just query current
         * logging flags (by using iMask = 0). If you want to modify all logging
         * flags at once, use iMask = LOG_ALLMASK.
         *
         * @arg iFlags
         *   New logging flags (see LOG_XXXX)
         * @arg iMask
         *   The mask of logging flags to change.
         * @return
         *   Current logging flags state
         */
        uint Logging (uint iFlags, uint iMask);

        /**
         * Same but sets logging flags depending on a text string
         * @arg iFlags
         *   A string of characters, every character means enabling or disabling
         *   some specific logging feature. Lowercase letter means disabling the
         *   feature, uppercase means enabling it:
         *
         * - s, S: Screen logging
         * - f, F: File logging
         * - d, D: Log debug events or not
         * - c, C: Log common events or not
         * - i, I: Log important events or not
         *
         * @return
         *   Current logging flags state
         */
        uint Logging (const char *iFlags);

        /**
         * Get logging flags in a user-readable format.
         * @arg oBuffer
         *   The buffer to put the output into
         * @arg iBufferLen
         *   Buffer size
         */
        void GetLogging (char *oBuffer, size_t iBufferLen);
};
#endif // __LOG_H__
