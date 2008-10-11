/**
 *     \file  src/shared/StringFun.h
 *    \brief  Miscellaneous functions for handling C strings
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

#ifndef __STRING_FUN_H__
#define __STRING_FUN_H__

#include "Common.h"

/**
 * Allocate a new copy of the string. The allocated storage must be freed
 * when it's no longer needed with delete [].
 * @arg s
 *   Source string to make a copy of
 * @return
 *   A new allocated copy of the string.
 */
extern char *strnew (const char *s);

/**
 * Same but allocates a new string given an address and the length.
 * @arg s
 *   Source string
 * @arg l
 *   Source string length (without the trailing zero character, if any)
 * @return
 *   A new allocated copy of the string.
 */
extern char *strnew (const char *s, size_t l);

/**
 * Trim starting and ending whitespaces in a string.
 * Changes the string in-place.
 * @arg str
 *   The source (and also the destination) string.
 */
extern void trim (char *str);

/**
 * Just skip all the whitespaces at the beginning of the string.
 * @arg str
 *   The source string
 * @return
 *   A pointer to first non-whitespace character in str
 */
const char *skipspc (const char *str);

/**
 * Copy string from source to destination, trimming the string at the end
 * if the target buffer size is exceeded. Unlike with strncpy, destination
 * string is zero-terminated even if destination buffer size is exceeded.
 * @arg dst
 *   Destination buffer
 * @arg dst_len
 *   Destination buffer length, in chars
 * @arg src
 *   Source string
 * @return
 *   Number of copied characters (excluding the terminating zero)
 */
int nstrcpy (char *dst, size_t dst_len, const char *src);

/**
 * Simple lowcase, works for all SBCS locales, if you cared to setlocal().
 * @arg str
 *   The string to be lowercased in-place
 * @return
 *   Number of lowercased characters
 */
int lowerstr (char *str);

/**
 * Simple uppercase, works for all SBCS locales, if you cared to setlocal().
 * @arg str
 *   The string to be uppercased in-place
 * @return
 *   Number of uppercased characters
 */
int upperstr (char *str);

/**
 * Return the value of the hexadecimal digit.
 * @arg c
 *   The hexadecimal digit: '0'..'9', 'A'..'F', 'a'..'f'
 * @return
 *   Digit value, 0-15
 */
int HexVal (char c);

/**
 * Decode a hexadecimal string into a binary value.
 * @arg iXstr
 *   The hexadecimal string.
 * @arg oDest
 *   The output array.
 * @arg iDestSize
 *   Output array size.
 * @return
 *   true if there were enough chars in the strings for the array length.
 */
bool Hex2Bin (const char *iXstr, void *oDest, size_t iDestSize);

/**
 * Encode the data array into a text string that can be stored into
 * the SQL database.
 * @arg iData
 *   Pointer to the array that should be encoded.
 * @arg iDataSize
 *   Encoded array size in bytes.
 * @arg oData
 *   Pointer to the array where data will be encoded. If this argument
 *   is NULL, function will return the required amount of bytes for oData.
 *   If it is not NULL, the array should be GUARANTEED to be able to
 *   hold as much data as required.
 * @return
 *   Number of bytes required to hold the result (oData == NULL) or
 *   number of actual bytes in result.
 */
size_t EncodeSQL (void *iData, size_t iDataSize, void *oData);

/**
 * A simple wrapper around EncodeSQL() that allocates a new string
 * and returns it.
 * @arg iData
 *   Pointer to the array that should be encoded.
 * @arg iDataSize
 *   Encoded array size in bytes.
 * @return
 *   A newly-allocated string. Free with delete [].
 */
char *EncodeSQL (void *iData, size_t iDataSize);

/**
 * Decode a string encoded by EncodeSQL() back to binary form.
 * @arg iSqlStr
 *   The SQL encoded string.
 * @arg oData
 *   Pointer to the array where data will be decoded.
 * @arg oDataSize
 *   Output data array size in bytes.
 * @return
 *   The decoded data size. If oData is NULL, this is the value
 *   in bytes that is required to decode the whole string, otherwise
 *   the function returns how many bytes were decoded.
 */
size_t DecodeSQL (const char *iSqlStr, void *oData, size_t oDataSize);

/**
 * Quote a string so that it can be inserted into a SQL '%s' sequence without
 * fear for SQL insertion attacks. For example, imagine you have the following
 * sequence:
 * \verbatim
 *      INSERT INTO mail (body) VALUES ('%s')
 * \endverbatim
 * where %s is replaced by letter's body as entered by the user. Now I can write
 * a letter like:
 * \verbatim
 *      Hello John!');
 *      DELETE FROM characters WHERE name=%;
 *      INSERT INTO MAIL (body) VALUES ('
 * \endverbatim
 * This function replaces ' with \' and \ with \\. These two simple changes
 * are enough to render such attacks useless.
 * @arg iString
 *   Ths user-controlled string.
 * @return
 *   A new allocated string or iString if original string does not contain
 *   any special SQL characters (this is a performance enhancement). When
 *   you are done with the quoted string, you must free it like this:
 *   if (quoted_str != original_str) delete [] quoted_str;
 */
char *QuoteSQL (char *iString);

//--------------// Functions for dealing with UTF-8 strings //--------------//

/**
 * Compute the length in characters of given UTF-8 string.
 * Does not do any checking for invalid UTF-8 characters.
 * @arg iString
 *   The string who's length should be computed
 * @return
 *   The length of the string in characters.
 */
int u8strlen (const char *iString);

/**
 * Skip given number of UTF-8 characters and return the resulting pointer.
 * @arg iString
 *   The starting point to move forth from
 * @arg iChars
 *   Number of characters to move forward from starting point
 * @return
 *   The new position in string, or NULL if the position you're looking for
 *   is past end of line.
 */
const char *u8strforw (const char *iString, int iChars);

/**
 * Move backward given number of UTF-8 characters and return the resulting pointer.
 * @arg iString
 *   The starting point to move back from (the character pointed by iString
 *   is not counted)
 * @arg iChars
 *   Number of characters to move backward from starting point
 * @arg iStart
 *   The start of the string (won't move past this point)
 * @return
 *   The new position in string, or NULL if the position you're looking for
 *   is before start of line.
 */
const char *u8strback (const char *iString, int iChars, const char *iStart);

/**
 * Uppercase a string. Destination and source may be the same.
 * @arg oDestStriing
 *   Pointer to buffer for the result
 * @arg iSrcString
 *   Source string
 */
void u8strupr (char *oDestString, const char *iSrcString);

/**
 * Lowercase a string. Destination and source may be the same.
 * @arg oDestStriing
 *   Pointer to buffer for the result
 * @arg iSrcString
 *   Source string
 */
void u8strlwr (char *oDestString, const char *iSrcString);
#endif // __STRING_FUN_H__
