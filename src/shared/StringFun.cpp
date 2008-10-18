/**
 *     \file  src/shared/StringFun.cpp
 *    \brief  Miscellaneous functions for handling C strings
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

#include <ctype.h>
#include "StringFun.h"
#include "Debug.h"

char *strnew (const char *s)
{
    if (!s)
        return NULL;

    size_t sl = strlen (s) + 1;
    char *ret = new char [sl];
    memcpy (ret, s, sl);
    return ret;
}

char *strnew (const char *s, size_t l)
{
    if (!s || !l)
        return NULL;

    char *ret = new char [l + 1];
    memcpy (ret, s, l);
    ret [l] = 0;
    return ret;
}

void trim (char *str)
{
    char *first = str;
    while (*first && isspace (*first))
        first++;
    char *last = strchr (str, 0);
    while ((last > first) && isspace (first [-1]))
        last--;
    memmove (str, first, last - first);
    str [last - first] = 0;
}

const char *skipspc (const char *str)
{
    while (*str && isspace (*str))
        str++;
    return str;
}

int nstrcpy (char *dst, size_t dst_len, const char *src)
{
    char *old_dst = dst;
    while (*src && --dst_len)
        *dst++ = *src++;
    *dst = 0;
    return dst - old_dst;
}

int lowerstr (char *str)
{
    char *old_str = str;
    for (uchar c = *str; c; c = *++str)
        *str = tolower (c);
    return str - old_str;
}

int upperstr (char *str)
{
    char *old_str = str;
    for (uchar c = *str; c; c = *++str)
        *str = toupper (c);
    return str - old_str;
}

int HexVal (char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    DEBUG_PRINTF ("Invalid hex digit: %c\n", c);
    return 0;
}

bool Hex2Bin (const char *iXstr, void *oDest, size_t iDestSize)
{
    for (size_t i = 0; i < iDestSize; i++)
    {
        char hc = *iXstr++;
        if (!hc)
            return false;
        char lc = *iXstr++;
        if (!lc)
            return false;
        ((uint8 *)oDest) [i] = (HexVal (hc) << 4) | HexVal (lc);
    }
    return true;
}
