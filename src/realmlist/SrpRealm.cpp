/**
 *     \file  src/realmlist/SrpRealm.cpp
 *    \brief  Provides basic calculations for SRP based client authentication.
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

#include <openssl/sha.h>
#include "SrpRealm.h"
#include "StringFun.h"
#include "Debug.h"

static void Reverse (uint8 *d, uint8 *s, int l)
{
    for (int i = 0; i < l; i++)
        d [i] = s [l - i - 1];
}

static char HexChar (uint8 v)
{
    return (v < 10) ? v + '0' : v - 10 + 'a';
}

void Hex2Bin (uint8 *dst, size_t size, char *src)
{
    for (size_t i = 0; i < size; i++)
        dst [i] = HexVal (*src++) * 16 + HexVal (*src++);
}

void Bin2Hex (char *dst, uint8 *src, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        *dst++ = HexChar (src [i] >> 4);
        *dst++ = HexChar (src [i] & 0x0f);
    }
    *dst = 0;
}

static void GetOdd (uint8 *d, uint8 *s, int l)
{
    for (int i = 0; i < l; i += 2)
        d [i / 2] = s [i];
}

static void GetEven (uint8 *d, uint8 *s, int l)
{
    for (int i = 0; i < l; i += 2)
        d [i / 2] = s [i + 1];
}

static void Merge (uint8 *d, uint8 *s1, uint8 *s2, int l)
{
    for (int i = 0; i < l * 2; i += 2)
    {
        d [i] = s1 [i / 2];
        d [i + 1] = s2 [i / 2];
    }
}

static void XorMerge (uint8 *d, uint8 *s1, uint8 *s2, int l)
{
    for (int i = 0; i < l; i++)
        d [i] = s1 [i] ^ s2 [i];
}

#ifdef SRP_DEBUG
static void printBigInteger (BigInteger BN, char *name)
{
    char temp[1024];
    BigIntegerToHex (BN, temp, 1024);
    printf ("%s: %s\n", name, temp);
}
#endif

static int BigIntegerToBytes2 (BigInteger src, uint8 *dest, int destlen)
{
    int shift = destlen - BigIntegerByteLen (src);
    #ifdef SRP_DEBUG
    printf("    SHIFT: %d %d %d\n", shift, destlen, BigIntegerByteLen (src));
    #endif
    return BigIntegerToBytes (src, dest + shift, destlen);
}

SrpRealm::SrpRealm ()
{
    UserName = NULL;
}

SrpRealm::~SrpRealm ()
{
    delete [] UserName;
}

void SrpRealm::Challenge (const char *userName, char *passwd)
{
    uint8 dest [32];
    uint8 dest2 [52];

    delete [] UserName;
    UserName = strnew (userName);

    // N is hard-coded
    Hex2Bin (N, 32, "894B645E89E1535BBDAD5B8B290650530801B18EBFBF5E8FAB3C82872A3E9BB7");
    uint8 NR [32];
    Reverse (NR, N, 32);
    BigInteger NR_BN = BigIntegerFromBytes ((const uchar *)NR,32);

    #ifdef SRP_DEBUG
    uint8 bt [20];
    Hex2Bin (bt, 20, "8692E3A6BA48B5B1004CEF76825127B7EB7D1AEF");
    Reverse (b, bt, 20);
    #else
    RAND_bytes (b, 20);
    #endif
    BigInteger b_BN = BigIntegerFromBytes (b, 20);

    #ifdef SRP_DEBUG
    Hex2Bin (salt, 32, "33f140d46cb66e631fdbbbc9f029ad8898e05ee533876118185e56dde843674f");
    printBytes (salt, 32, "salt");
    #else
    RAND_bytes (salt, 32);
    #endif

    BigInteger G_BN = BigIntegerFromInt (7);
    BigInteger K_BN = BigIntegerFromInt (3);

    uint8 userPass [256];
    int sl = snprintf ((char *)userPass, sizeof (userPass), "%s:%s", UserName, passwd);

    /* Generate x */
    // Generate a SHA1 hash from username:password in dest
    SHA1 (userPass, sl, dest);

    //  Copy our salt to dest2
    memcpy (dest2, salt, 32);

    // Copy our SHA1 hashed (username:password) to salt in dest2
    memcpy (dest2 + 32, dest, 20);

    // Generate a SHA1 hash from the combined string in dest. This our x.
    SHA1 (dest2, 52, dest);
    #ifdef SRP_DEBUG
    printBytes (dest, 20, "x");
    #endif
    /* So far this looks sane. x should be valid. */

    /* Generate v */
    // We need a reversed x in xR.
    uint8 xR [20];
    Reverse (xR, dest, 20);
    BigInteger xR_BN = BigIntegerFromBytes (xR, 20);
    BigInteger v_BN = BigIntegerFromInt (0);
    BigIntegerModExp (v_BN, G_BN, xR_BN, NR_BN, NULL, NULL);
    BigIntegerToBytes2 (v_BN, v, 32);
    #ifdef SRP_DEBUG
    printBigInteger (v_BN, "v");
    #endif

    /* Generate reversed B (BR) */
    BigInteger B_BN = BigIntegerFromInt (0);
    BigIntegerMul (B_BN, K_BN, v_BN, NULL);
    BigIntegerModExp (K_BN, G_BN, b_BN, NR_BN, NULL, NULL);
    BigIntegerAdd (K_BN, K_BN, B_BN);
    BigIntegerMod (B_BN, K_BN, NR_BN, NULL);
    BigIntegerToBytes2 (B_BN, dest, 32);
    Reverse (BR, dest, 32);
    #ifdef SRP_DEBUG
    printBytes (BR, 32, "BR");
    #endif

    /* Free all temporary variables used for SRP calculation */
    BigIntegerFree (NR_BN);
    BigIntegerFree (b_BN);
    BigIntegerFree (K_BN);
    BigIntegerFree (G_BN);
    BigIntegerFree (xR_BN);
    BigIntegerFree (v_BN);
    BigIntegerFree (B_BN);
}

void SrpRealm::Proof (uint8 *A)
{
    // init
    uint8 dest [32];
    uint8 dest2 [20+20+32+32+32+40];

    #ifdef SRP_DEBUG
    printBytes (A, 32, "A");
    #endif

    // we got it over net
    //  Hex2Bin (M1, 20, "eeb4adca80f4de02f9a9fe8d000d682e3ddfad6f");
    uint8 AR [32];
    //  Hex2Bin (A, 32, "232fb1b88529643d95b8dce78f2750c75b2df37acba873eb31073839eda0738d");
    Reverse (AR, A, 32);
    BigInteger AR_BN = BigIntegerFromBytes (AR, 32);
    uint8 NR [32];
    Reverse (NR, N, 32);
    BigInteger NR_BN = BigIntegerFromBytes (NR, 32);
    BigInteger b_BN = BigIntegerFromBytes (b, 20);
    BigInteger v_BN = BigIntegerFromBytes (v, 32);
    BigInteger G_BN = BigIntegerFromInt (7);

    // U
    memcpy (dest2, A, 32);
    memcpy (dest2 + 32, BR, 32);
    SHA1 (dest2, 32 + 32, dest);
    #ifdef SRP_DEBUG
    printBytes(dest, 20, "U");
    #endif
    uint8 UR [20];
    Reverse (UR, dest, 20);
    BigInteger UR_BN = BigIntegerFromBytes (UR, 20);

    // S
    BigInteger S_BN = BigIntegerFromInt (0);
    BigIntegerModExp (S_BN, v_BN, UR_BN, NR_BN, NULL, NULL);
    BigIntegerMul (S_BN, S_BN, AR_BN, NULL);
    BigIntegerModExp (S_BN, S_BN, b_BN, NR_BN, NULL, NULL);
    #ifdef SRP_DEBUG
    printBigInteger(S_BN, "S");
    #endif

    BigIntegerToBytes2 (S_BN, dest, 32);
    uint8 SR[32], odd[16], even[16];
    Reverse (SR, dest, 32);
    GetOdd (odd, SR, 32);
    GetEven (even, SR, 32);

    SHA1 (odd, 16, dest);
    SHA1 (even, 16, dest2);
    Merge (SS_Hash, dest, dest2, 20);

    BigIntegerToBytes2 (G_BN, dest, 1);
    SHA1 (dest, 1, dest2);                                  // G_Hash
    SHA1 (N, 32, dest);                                     // N_Hash
    uint8 NG_Hash [20];
    XorMerge (NG_Hash, dest, dest2, 20);                    // NG_Hash
    SHA1 ((uint8 *)UserName, strlen (UserName), dest);      // User_Hash

    memcpy (dest2, NG_Hash, 20);
    memcpy (dest2+20, dest, 20);
    memcpy (dest2+20+20, salt, 32);
    memcpy (dest2+20+20+32, A, 32);
    memcpy (dest2+20+20+32+32, BR, 32);
    memcpy (dest2+20+20+32+32+32, SS_Hash, 40);

    SHA1 (dest2, 20+20+32+32+32+40, M1);
    #ifdef SRP_DEBUG
    printBytes(M1, 20, "M1");
    #endif

    memcpy (dest2, A, 32);
    memcpy (dest2+32, M1, 20);
    memcpy (dest2+32+20, SS_Hash, 40);

    SHA1 (dest2, 32+20+40, M2);

    #ifdef SRP_DEBUG
    printBytes(M2, 20, "M2");
    #endif

    BigIntegerFree (AR_BN);
    BigIntegerFree (NR_BN);
    BigIntegerFree (b_BN);
    BigIntegerFree (v_BN);
    BigIntegerFree (G_BN);
    BigIntegerFree (UR_BN);
    BigIntegerFree (S_BN);
}
