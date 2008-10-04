/**
 *     \file  src/shared/UTF8Fun.cpp
 *    \brief  Miscelkaneous functions for handling C strings
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

#include <ctype.h>
#include "StringFun.h"

int u8strlen (const char *iString)
{
	// Ignore characters in range 0x80 - 0xBF
	int len = 0;
	while (*iString)
	{
		if ((*iString & 0xc0) != 0x80)
			len++;
		iString++;
	}
	return len;
}

const char *u8strforw (const char *iString, int iChars)
{
	if (!*iString && iChars)
		return NULL;
	while (iChars--)
	{
		if (!*++iString)
			return NULL;
		while ((*iString & 0xc0) == 0x80)
			if (!*++iString)
				return NULL;
	}
	return iString;
}

const char *u8strback (const char *iString, int iChars, const char *iStart)
{
	if (iString <= iStart && iChars)
		return NULL;
	while (iChars--)
	{
		if (--iString < iStart)
			return NULL;
		while ((*iString & 0xc0) != 0x80)
			if (--iString < iStart)
				return NULL;
	}
	return iString;
}

void u8strupr (char *oDestString, const char *iSrcString)
{
	// For now we ignore non-ASCII characters :(
	while (*iSrcString)
		*oDestString++ = toupper (*iSrcString++);
	*oDestString = 0;
}

void u8strlwr (char *oDestString, const char *iSrcString)
{
	// For now we ignore non-ASCII characters :(
	while (*iSrcString)
		*oDestString++ = tolower (*iSrcString++);
	*oDestString = 0;
}
