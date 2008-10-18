/**
 *     \file  src/shared/BitVector.h
 *    \brief  Defines functions for handling vectors containing bits
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

#ifndef __BIT_VECTOR_H__
#define __BIT_VECTOR_H__

#include <stdlib.h>
#include "Common.h"
#include "Debug.h"

//-------------------// Elementary bitfield operations //-------------------//

static inline void BitSet (void *oData, uint iBitIndex)
{
    ((ulong *)oData) [iBitIndex / BITS_PER_LONG] |= (1 << (iBitIndex & (BITS_PER_LONG - 1)));
}

static inline void BitReset (void *oData, uint32 iBitIndex)
{
    ((ulong *)oData) [iBitIndex / BITS_PER_LONG] &= (1 << (iBitIndex & (BITS_PER_LONG - 1)));
}

static inline bool BitGet (void *iData, uint iBitIndex)
{
    return !!(((ulong *)iData) [iBitIndex / BITS_PER_LONG] &
            (1 << (iBitIndex & (BITS_PER_LONG - 1))));
}

static inline bool BitGetSet (void *ioData, uint32 iBitIndex)
{
    ulong mask = (1 << (iBitIndex & (BITS_PER_LONG - 1)));
    if (((ulong *)ioData) [iBitIndex / BITS_PER_LONG] & mask)
        return true;
    ((ulong *)ioData) [iBitIndex / BITS_PER_LONG] |= mask;
    return false;
}

/**
 * A bit vector is a object that can hold any number of bits, and
 * provides handy functions for setting/resetting, querying the bits
 * and for dynamically resizing the array.
 */
class BitVector
{
    /// The bit vector itself
    uint32 *data;
    /// The length of the bit vector
    uint length;

public:
    /// Create an empty bit array
    BitVector () : data (NULL), length (0) { }
    /// Free the memory occupied by the vector
    ~BitVector () { free (data); }

    /// Free the allocated memory
    void Free ()
    {
        if (data)
            free (data);
        data = 0;
        length = 0;
    }

    /// Set vector length in bits
    void SetLength (int BitLength)
    {
        length = BitLength;
        uint length_uint = (BitLength + BITS_PER_INT - 1) / BITS_PER_INT;
        data = (uint32 *)realloc (data, length_uint * sizeof (uint32));
        memset (data, 0, length_uint * sizeof (uint32));
    }

    /// Clear all the bits in the array
    void Clear ()
    {
        uint length_uint = Blocks (BITS_PER_INT);
        memset (data, 0, length_uint * sizeof (uint32));
    }

    /// Return array length in bits
    inline uint Length ()
    { return length; }

    /// Get the array data as a whole
    inline const uint32 *GetData ()
    { return data; }

    /**
     * Get array length in blocks of specified size
     * @arg BlockSize
     *   Block size in bits. Must be a power of two.
     */
    inline int Blocks (int BlockSize)
    {
        // Any decent compiler when inlining will replace div by shifts
        return (length + (BlockSize - 1)) / BlockSize;
    }

    /// Get bit state
    inline bool Get (uint32 index) const
    {
        DEBUG_BREAK_IF (index >= length);
        return BitGet (data, index);
    }

    /// Set a bit to 1
    inline void Set (uint32 index)
    {
        DEBUG_BREAK_IF (index >= length);
        BitSet (data, index);
    }

    /// Set a bit to 0
    inline void Reset (uint32 index)
    {
        DEBUG_BREAK_IF (index >= length);
        BitReset (data, index);
    }

    /// Set a bit to 1 and return the previous state of the bit
    inline bool GetSet (uint32 index)
    {
        DEBUG_BREAK_IF (index >= length);
        return BitGetSet (data, index);
    }

    /// Assignment operator
    BitVector& operator = (const BitVector& mask)
    {
        SetLength (mask.length);
        memcpy (data, mask.data, (mask.length + BITS_PER_INT - 1) / BITS_PER_INT);
        return *this;
    }

    /// this &= other
    void operator &= (const BitVector& mask)
    {
        DEBUG_BREAK_IF (mask.length > length);
        for (uint i = 0; i < length; i++)
            data [i] &= mask.data [i];
    }

    /// this |= other
    void operator |= (const BitVector& mask)
    {
        DEBUG_BREAK_IF (mask.length > length);
        for (uint i = 0; i < length; i++)
            data [i] |= mask.data [i];
    }

    /// something = this & other
    BitVector operator & (const BitVector& mask) const
    {
        DEBUG_BREAK_IF (mask.length > length);

        BitVector newmask;
        newmask = *this;
        newmask &= mask;

        return newmask;
    }

    /// something = this | other
    BitVector operator | (const BitVector& mask) const
    {
        DEBUG_BREAK_IF (mask.length > length);

        BitVector newmask;
        newmask = *this;
        newmask |= mask;

        return newmask;
    }
};

#endif // __BIT_VECTOR_H__
