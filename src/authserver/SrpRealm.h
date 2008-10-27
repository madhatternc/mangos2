/**
 *     \file  src/authserver/SrpRealm.h
 *    \brief  Provides basic calculations for SRP based client authentication.
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

#ifndef __SRP_REALM_H__
#define __SRP_REALM_H__

#include "Common.h"
#include "bigint.h"

// Uncomment this to get debug output of intermediate SRP auth results
#define SRP_DEBUG

class SrpRealm
{
protected:
    char *UserName;
    uint8 b [32];
    uint8 v [32];
    uint8 BR [32];
    uint8 N [32];
    uint8 M1 [20];
    uint8 M2 [20];
    uint8 SS_Hash [40];
    uint8 salt [32];
public:
    SrpRealm ();
    ~SrpRealm ();

    void Challenge (const char *userName, char *passwd);
    void Proof (uint8 *A);
};

/**
 * Convert a hexadecimal string to a binary array.
 * @arg dst
 *   Destination array
 * @arg src
 *   Source string (e.g. "12345678abcdef0")
 * @arg size
 *   Destination array size in bytes
 */
void Hex2Bin (uint8 *dst, size_t size, char *src);

/**
 * Convert a binary array to a hexadecimal string.
 * @arg dst
 *   Destination string
 * @arg src
 *   Source binary array
 * @arg size
 *   Source binary array length in bytes
 */
void Bin2Hex (char *dst, uint8 *src, size_t size);

#endif // __SRP_REALM_H__
