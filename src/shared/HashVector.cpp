/**
 *     \file  src/shared/HashVector.cpp
 *    \brief  Hash Vector class
 *
 * Copyright (C) 2005 by Andrew Zabolotny <zap@homelink.ru>
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

#include "HashVector.h"

HashVector::HashVector (int MvsS, int HashBits) : Vector (0, 16)
{
    MemVsSpeed = MvsS;
    Hash = DefaultHash;
    SetBuckets (1 << HashBits);
}

HashVector::HashVector (HashVector *other)
{
    Hash = other->Hash;
    HashMask = other->HashMask;
    root = other->root;
    count = other->count;
    limit = other->limit;
}

HashVector::~HashVector ()
{
    DeleteAll ();
}

void HashVector::FreeItem (Some Item) const
{
    (void)Item;
}

void HashVector::DeleteAll ()
{
    if (!count)
    return;

    for (int i = 0; i < limit; i += HASHVECT_BUCKET_SIZE)
    {
    Some *cur = root + i;
        uintptr numel = uintptr (*cur);
    if (IS_LARGE_BUCKET (numel))
        lhbDestroy ((LargeHashBucket *)cur);
    else
        for (cur++; numel--; cur++)
        FreeItem (*cur);
    root [i] = 0;
    }
    // Mark hash vector as empty
    count = 0;
}

void HashVector::SetBuckets (int iBuckets)
{
    // Save our old state
    HashVector old_state (this);
    // Clear our fields so that we won't mess them
    root = NULL; limit = 0; count = 0;

    HashMask = iBuckets - 1;
    SetLimit (iBuckets * HASHVECT_BUCKET_SIZE);
    // A 1st level hash bucket has number of elements as the 1st bucket element.
    // When we create a Vector in its place, there can't be <{very much} in this place
    // because there lies either VMT or RTTI, and any of them cannot be so small
    for (int i = 0; i < limit; i += HASHVECT_BUCKET_SIZE)
    root [i] = 0;

    if (old_state.root)
    {
    Iterator i = old_state.Begin ();
    Some el;
    while ((el = i.Next ()))
        _Insert (el);
    }
}

void HashVector::Insert (Some Item)
{
    // The effective count of objects is how many elements fits in our tiny buckets
    // plus allow a little more to get the binary trees into the game,
    // If we exceed this number, resize the hash vector
    // @@@do we also have to shrink the vector automatically as the items are removed?
    if (count >= (limit >> 1) * MemVsSpeed)
    SetBuckets ((HashMask + 1) * 2);

    _Insert (Item);
}

void HashVector::_Insert (Some Item)
{
    count++;

    HashResult_t hash = Hash (GetKey (Item)) & HashMask;
    Some *cur = root + hash * HASHVECT_BUCKET_SIZE;
    // Number of elements in the tiny bucket
    uintptr numel = uintptr (*cur);
    if (IS_LARGE_BUCKET (numel))
    lhbInsertSorted ((LargeHashBucket *)cur, Item);
    else
    {
    if (numel < HASHVECT_BUCKET_SIZE - 1)
    {
        *cur = Some (++numel);
        cur [numel] = Item;
    }
    else
    {
        // Transform a tiny bucket into a large bucket
        Some old_data [HASHVECT_BUCKET_SIZE - 1];
        memcpy (old_data, cur + 1, (HASHVECT_BUCKET_SIZE - 1) * sizeof (Some));
        // Use placement allocator to create a Vector in the place of the tiny bucket
        LargeHashBucket *lhb = (LargeHashBucket *) cur;
        lhb->Init (HASHVECT_BUCKET_SIZE * 2);
        // Now copy the data into the vector and sort it
        for (uint i = 0; i < HASHVECT_BUCKET_SIZE - 1; i++)
        lhbInsertSorted (lhb, old_data [i]);
        lhbInsertSorted (lhb, Item);
    }
    }
}

// We could use FindKey() but for the sake of performance ...
// (iterator creation will be just a waste of resources ...)
Some HashVector::GetByKey (HashKey_t Key) const
{
    // Find the right bucket
    HashResult_t hash = Hash (Key) & HashMask;
    Some *cur = root + hash * HASHVECT_BUCKET_SIZE;
    // Number of elements in the tiny bucket
    uintptr numel = uintptr (*cur);
    if (IS_LARGE_BUCKET (numel))
    // Binary search in the large bucket
    return lhbGetByKey ((LargeHashBucket *)cur, Key);
    else
    // Linear search in the tiny bucket
    for (cur++; numel--; cur++)
        if (Compare (GetKey (*cur), Key) == 0)
        return *cur;
    return NULL;
}

HashVector::Iterator HashVector::FindKey (HashKey_t Key) const
{
    // Find the right bucket
    HashResult_t hash = Hash (Key) & HashMask;
    int delta, bucket = hash * HASHVECT_BUCKET_SIZE;
    Some *cur = root + bucket;
    // Number of elements in the tiny bucket
    uintptr numel = uintptr (*cur);
    if (IS_LARGE_BUCKET (numel))
    {
    delta = lhbFind ((LargeHashBucket *)cur, Key);
    if (delta >= 0)
        return Iterator (this, bucket, delta);
    }
    else
    // Linear search in the tiny bucket
    for (delta = 0, cur++; numel--; cur++, delta++)
        if (Compare (GetKey (*cur), Key) == 0)
        return Iterator (this, bucket, delta);
    // Return an invalid iterator
    return Iterator (this, -HASHVECT_BUCKET_SIZE, 0);
}

int HashVector::Compare (HashKey_t Key1, HashKey_t Key2) const
{
    return (intptr (Key1) > intptr (Key2)) ? +1 : (intptr (Key1) == intptr (Key2)) ? 0 : -1;
}

HashResult_t HashVector::DefaultHash (HashKey_t Key)
{
    uintptr hash = uintptr (Key);
    hash += ((hash << 3) + (hash << 2)) ^ (hash >> 4);
    return HashResult_t (hash);
}

//--------// LargeHashBucket //--------//

void HashVector::LargeHashBucket::Init (uint iLimit)
{
    count = 0;
    limit = iLimit;
    root = (Some *)malloc (iLimit * sizeof (Some));
}

void HashVector::LargeHashBucket::Insert (uint Pos, Some Item)
{
    count++;
    if (count > limit)
    {
    limit *= 2;
    root = (Some *)realloc (root, limit * sizeof (Some));
    }
    uint movebytes = (count - Pos - 1) * sizeof (Some);
    if (movebytes)
        memmove (&root [Pos + 1], &root [Pos], movebytes);
    root [Pos] = Item;
}

void HashVector::lhbDestroy (LargeHashBucket *lhb)
{
    for (uint i = 0; i < lhb->count; i++)
    FreeItem (lhb->root [i]);
    free (lhb->root);
}

void HashVector::lhbInsertSorted (LargeHashBucket *lhb, Some Item)
{
    int m = 0, l = 0, r = lhb->count - 1;
    HashKey_t key = GetKey (Item);
    while (l <= r)
    {
        m = (l + r) / 2;
        int cmp = Compare (GetKey (lhb->root [m]), key);

        if (cmp == 0)
        {
            lhb->Insert (++m, Item);
            return;
        }
        else if (cmp < 0)
            l = m + 1;
        else
            r = m - 1;
    }
    if (r == m)
        m++;
    lhb->Insert (m, Item);
}

int HashVector::lhbFind (LargeHashBucket *lhb, HashKey_t Key) const
{
    int l = 0, r = lhb->count - 1;
    int m = 0, cmp = 0;

    while (l <= r)
    {
        m = (l + r) / 2;
        cmp = Compare (GetKey (lhb->root [m]), Key);

        if (cmp == 0)
            return m;
        else if (cmp < 0)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}
