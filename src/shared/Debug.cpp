/**
 *     \file  src/shared/Debug.cpp
 *    \brief  Debugging helper functions
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

#include "Common.h"
#include "Debug.h"

void DebugDump (FILE *Out, const void *Data, unsigned Size, const void *Base)
{
    if (Base == (const void *)-1)
        Base = Data;

    const uint8 *data = (const uint8 *)Data;
    unsigned int ofs = 0;
    while (ofs < Size)
    {
        fprintf (Out, "%08x | ", (uintptr)data - (uintptr)Base + ofs);

        unsigned int i;
        for (i = 0; i < 16; i++)
            if (ofs + i < Size)
                fprintf (Out, "%02x ", data [ofs + i]);
            else
                fprintf (Out, "   ");

        fprintf (Out, "| ");
        for (i = 0; i < 16; i++)
            if (ofs + i < Size)
            {
                char c = data [ofs + i];
                fprintf (Out, "%c", c > 31 ? c : '.');
            }
            else
                fprintf (Out, " ");

        ofs += 16;
        fprintf (Out, "\n");
    }
    fflush (Out);
}

void printBytes(void *bytes, int l, const char *name)
{
    if (bytes == NULL)
        return;
    printf ("%s: ", name);
    for (int i = 0; i < l; i++)
        printf ("%02X", ((uint8 *)bytes) [i]);
    printf ("\n");
}
