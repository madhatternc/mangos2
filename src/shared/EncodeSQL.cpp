/**
 *     \file  src/shared/EncodeSQL.cpp
 *    \brief  SQL binary data encoding and decoding
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

#include "StringFun.h"

// This is the range of allowed characters for encoding binary data
static const char *base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * The resulting string will look like: blah-blah @Z@E. Single quotes are
 * assumed at both ends of the string, but not added. The input characters
 * are translated on output according to the following rules:
 * <ul>
 *   <li>Characters in the range 0-15 are added 32, so that 0 becomes a space.
 *   <li>Characters in the range 16-47 and also the special characters @ and \ are
 *       encoded as @X, where X is the character code plus 32, so space becomes @@.
 * </ul>
 * The reason for encoding chars 0-15 in one byte is that small values are often
 * encountered in our binary data.
 */
size_t EncodeSQL (void *iData, size_t iDataSize, void *oData)
{
    // If user asks for the output data size, return it
    if (!oData)
        return 1 + (iDataSize * 8 + 5) / 6;

    uint8 *cur = (uint8 *)iData;
    uint8 *curend = cur + iDataSize;
    uint8 *out = (uint8 *)oData;

    int accbits = 0;
    uint8 acc = 0;

    while (cur < curend)
    {
        int bits = 8;
        uint8 byte = *cur++;

        while (accbits + bits >= 6)
        {
            // Fill missing lower bits of the accumulator
            acc |= (byte >> (2 + accbits));
            // Move unused bits to upper part of the byte
            byte = (byte << (6 - accbits));
            bits -= (6 - accbits);
            // We have exactly 6 bits in accumulator, spit it out
            *out++ = base64_chars [acc];
            acc = 0;
            accbits = 0;
        }
        // Keep what remained of the byte for the next round
        accbits = bits;
        acc = (byte >> 2);
    }

    // Spit out what we have left in accumulator
    if (accbits)
        *out++ = base64_chars [acc];

    *out++ = 0;

    return out - (uint8 *)oData;
}

char *EncodeSQL (void *iData, size_t iDataSize)
{
    if (!iData || !iDataSize)
        return NULL;
    size_t sl = EncodeSQL (iData, iDataSize, NULL);
    char *ret = new char [sl];
    EncodeSQL (iData, iDataSize, ret);
    return ret;
}

/**
 * The input string should not contain the single quotes.
 */
size_t DecodeSQL (const char *iSqlStr, void *oData, size_t oDataSize)
{
    if (!oData)
        if (iSqlStr)
            return (strlen (iSqlStr) * 3) / 4;
    else
        return 0;

    const uint8 *cur = (const uint8 *)iSqlStr;
    uint8 *out = (uint8 *)oData;
    uint8 *outend = out + oDataSize;

    uint8 acc = 0;
    int accbits = 0;

    while (out < outend)
    {
        char c = *cur++;
        if (!c)
            break;

        const char *s = strchr (base64_chars, c);
        if (!s)
            return 0;

        uint8 byte = (s - base64_chars) << 2;

        if (accbits + 6 >= 8)
        {
            acc |= byte >> accbits;
            *out++ = acc;
            acc = byte << (8 - accbits);
            accbits = accbits - 2;
        }
        else
        {
            acc = byte;
            accbits = 6;
        }
    }

    // Ignore any bits we could have left in the accumulator
    return out - (uint8 *)oData;
}

char *QuoteSQL (char *iString)
{
    if (!iString)
        return NULL;

    // First, count how many special characters we have
    size_t numspec = 0;
    const char *cur;
    for (cur = iString; *cur; cur++)
        if (*cur == '\'' || *cur == '\\')
            numspec++;
    // If no special characters, return original string
    if (!numspec)
        return iString;

    char *ret = new char [cur - iString + numspec + 1];
    char *out = ret;
    for (cur = iString; *cur; cur++)
    {
        if (*cur == '\'' || *cur == '\\')
            *out++ = '\\';
        *out++ = *cur;
    }
    *out = 0;
    return ret;
}
