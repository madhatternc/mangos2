/**
 *     \file  src/shared/Vector.h
 *    \brief  Vector class interface
 *
 * Copyright (C) 1998,1999 by Andrew Zabolotny <zap@homelink.ru>
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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Base.h"
#include "Debug.h"

/**
 *  \addtogroup FoundationClasses
 *
 *  @{
 */

typedef void *Some;
typedef const void *ConstSome;

/**
 * The following flags, if ORed with the 'Mode' parameter of FindSortedKey
 * allow some additional control over the search process.
 */
/// Find the nearest element that is smaller
#define CSV_FIND_NEAREST_SMALLER    0x40000000
/// Find the nearest element that is larger
#define CSV_FIND_NEAREST_LARGER     0x80000000
/// Search mode mask
#define CSV_FIND_MODE_MASK      0xc0000000

/**
 * Vector is an abstract class which can hold an unlimited array
 * of unspecified (void *) data. Since this is a basic object, it does
 * not presume anything about its elements, so FreeItem () is
 * effectively a NOP. If you want vector elements to free automatically
 * occupied memory upon vector destruction you should create a derived
 * class which should provide its own FreeItem () method (see csStrVector
 * for a example).
 */
class Vector : public Base
{
    protected:
        int count, limit, threshold;
        Some *root;

    public:
        /**
         * Initialize object to hold initially 'ilimit' elements, and increase
         * storage by 'ithreshold' each time the upper bound is exceeded.
         */
        Vector (int ilimit = 8, int ithreshold = 16);
        /// Destroy the vector object
        virtual ~Vector ();

        /// Exchange the contents of two vectors
        void Exchange (Vector &other)
        {
            xchg32 (&root, &other.root);
            xchg32 (&count, &other.count);
            xchg32 (&limit, &other.limit);
            xchg32 (&threshold, &other.threshold);
        }

        /// Get a reference to n-th element (n must be < Length())
        inline Some& operator [] (int n) const
        {
            DEBUG_BREAK_IF (n >= count || n < 0);
            return (root [n]);
        }
        /// Same but in function form
        inline Some& Get (int n) const
        {
            DEBUG_BREAK_IF (n >= count || n < 0);
            return (root [n]);
        }
        /// Set a vector element
        inline void Set (int n, Some Item)
        {
            DEBUG_BREAK_IF (n >= count || n < 0);
            root [n] = Item;
        }

        /// Set vector length to n
        virtual void SetLength (int n);
        /// Query vector length
        inline int Length () const
            { return count; }
        /// Set vector limit to n
        virtual void SetLimit (int n);
        /// Query vector limit
        inline int Limit () const
            { return limit; }

        /// Exchange two elements in array
        inline void Exchange (int n1, int n2)
        {
            Some tmp = root [n1];
            root [n1] = root [n2];
            root [n2] = tmp;
        }
        /// Shift one element to a different place (ROL and ROR)
        bool Shift (int n1, int n2);

        /// Find a element in array and return its index (or -1 if not found)
        int Find (Some which, bool reversedir = false) const;
        /// Find a element by key (using CompareKey method)
        int FindKey (ConstSome Key, int Mode = 0) const;
        /**
         * Find a element in a SORTED array by key (using CompareKey method).
         * \arg \c Key
         *   The search key. The key can be anything, its interpretation depends
         *   on the implementation of the possibly overrided CompareKey() method.
         * \arg \c Mode
         *   Comparison mode. This argument is passed almost as-is (after dropping
         *   the CSV_FIND_MODE_MASK bits) to the CompareKey method so that you
         *   can have several different comparison criteria in one class.
         *   If you set the CSV_FIND_NEAREST_LARGER bit in Mode (using | operator),
         *   the function will return the nearest element that is larger than
         *   specified key (note it can return -1 if all elements are smaller).
         *   If you set the CSV_FIND_NEAREST_SMALLER bit in Mode, the function
         *   will return the nearest element that is smaller than the specified key
         *   (note that it can return -1 if all elements are greater than the key).
         *   In any case, you'll most probably have to call CompareKey yourself after
         *   FindSortedKey since you can't make find out whether the found element
         *   is smaller, equal or greater than the specified key.
         * @return
         *   The index of the found element or -1 if there's no element matching
         *   the criteria you specified.
         */
        int FindSortedKey (ConstSome Key, int Mode = 0) const;

        /// Returns Item searched for Key
        inline Some GetByKey (ConstSome Key, int Mode = 0) const
        {
            int n = FindSortedKey (Key, Mode);
            if (n != -1)
                return Get (n);
            return (Some)0;
        }

        /// Partially sort the array
        void QuickSort (int Left, int Right, int Mode = 0);
        /// Same but for all elements
        void QuickSort (int Mode = 0)
            { if (count > 0) QuickSort (0, count - 1, Mode); }

        /// Push a element on 'top' of vector
        inline int Push (Some what)
        {
            SetLength (count + 1);
            root [count - 1] = what;
            return count - 1;
        }
        /// Pop a element from vector 'top'
        inline Some Pop ()
        {
            Some ret = root [count - 1];
            SetLength (count - 1);
            return ret;
        }

        /// Delete element number 'n' from vector
        bool Delete (int n);
        /// Replace n-th item with another (free previous value)
        bool Replace (int n, Some what);
        /// Delete all elements
        void DeleteAll ();
        /// Insert element 'Item' before element 'n'
        bool Insert (int n, Some Item);
        /// Insert element 'Item' so that array remains sorted (assumes its already)
        int InsertSorted (Some Item, int *oEqual = 0, int Mode = 0);
        /// Virtual function which frees a vector element
        virtual void FreeItem (Some Item) const;
        /// Compare two array elements in given Mode
        virtual int Compare (Some Item1, Some Item2, int Mode) const;
        /// Compare entry with a key; for Vector just compare (int)Key vs (int)Item
        virtual int CompareKey (Some Item, ConstSome Key, int Mode) const;
        /// Float a element up or down until it becomes > previous and < next element
        int Float (int n, int Mode = 0);
        /// Copy another vector to this one
        bool Copy (Vector &Other);
};

// tolua_begin_hide
/**
 * Useful template to implement comparison functions for integer types.
 * NOTE: NEVER don't write Compare() methods like this:
 *
 * \Verbatim
 * int Compare (Some Item1, Some Item2) const
 * {
 *   return int (Item1) - int (Item2);
 * }
 * \EndVerbatim
 *
 * While you might be tempted do so because of it's visual simplicity, this is
 * wrong because the function will return wrong results if the result of the
 * subtraction overflows. For example, if Item1 = -2^31 and Item2 = 1, the
 * result of the subtraction will overflow and result in a positive number
 * even that the Compare() function should return a negative result in this
 * case (because Item1 < Item2).
 *
 * Any sane optimizing compiler will do just one comparison, so it's
 * not that suboptimal as you may think.
 */
template <typename T>
static int SignCompare (T a, T b)
{ return (a < b) ? -1 : (a == b) ? 0 : +1; }

/**
 * This macro can be used to declare simple unsorted vectors
 * that hold pointers to some structure.
 * \arg \c VType
 *   Vector class type name (SomeVector etc).
 * \arg \c CType
 *   The type of content items (SomeStruct etc). The vector is defined
 *   as if it contains pointers to SomeStruct.
 * \arg \c Extra
 *   Extra declarations you wish to put in the class
 */
#define DECLARE_VECTOR(VType, CType, Extra) \
    class VType : public Vector \
    { \
        public: \
            VType (int limit = 16, int threshold = 16) : Vector (limit, threshold) {} \
            virtual ~VType (); \
            virtual void FreeItem (Some Item) const; \
            CType &Get (int iIndex) const \
            { \
                DEBUG_BREAK_IF (iIndex >= count) \
                return (CType &)Vector::Get (iIndex); \
            } \
            inline CType &operator [] (int iIndex) const \
            { \
                DEBUG_BREAK_IF (iIndex >= count) \
                return (CType &)Vector::Get (iIndex); \
            } \
            Extra \
        }

    /**
     * This macro will implement the methods declared but not implemented
     * by the DEFINE_VECTOR macro. There's no Extra parameter as the
     * implementation is not delimited by brackets.
     *
     * \arg \c Namespace
     *   The namespace prefix of this vector, in the case when vector was
     *   declared inside of a class or something like this.
     * \arg \c VType
     *   Vector class type name (SomeVector etc).
     * \arg \c CType
     *   The type of content items (SomeStruct etc). The vector is defined
     *   as if it contains pointers to SomeStruct.
     */
#define IMPLEMENT_VECTOR(Namespace, VType, CType) \
    Namespace VType::~VType () \
    { \
        DeleteAll (); \
    } \
    void Namespace VType::FreeItem (Some Item) const \
    { \
        delete (CType)Item; \
    }

    /**
     * This macro can be used to declare simple sorted vectors that contain
     * pointers to some structure.
     * \arg \c VType
     *   Vector class type name (SomeVector etc).
     * \arg \c CType
     *   The type of content items (SomeStruct etc). The vector is defined
     *   as if it contains pointers to SomeStruct.
     * \arg \c Extra
     *   Extra declarations you wish to put in the class
     */
#define DECLARE_VECTOR_SORTED(VType, CType, Extra) \
    DECLARE_VECTOR (VType, CType, \
    virtual int Compare (Some Item1, Some Item2, int Mode) const; \
    virtual int CompareKey (Some Item, ConstSome Key, int Mode) const; \
    CType GetByKey (ConstSome Key, int Mode =  0) const; \
    Extra)

    /**
     * This macro will implement the methods declared but not implemented
     * by the DEFINE_VECTOR_SORTED macro. The vector is sorted by a string
     * key, which is a field in the structures contained in the vector.
     *
     * \arg \c Namespace
     *   The namespace prefix of this vector, in the case when vector was
     *   declared inside of a class or something like this.
     * \arg \c VType
     *   Vector class type name (SomeVector etc).
     * \arg \c CType
     *   The type of content items (SomeStruct etc). The vector is defined
     *   as if it contains pointers to SomeStruct.
     * \arg \c SField
     *   The field of the structure that is used for sorting.
     */
#define IMPLEMENT_VECTOR_SORTED_STRKEY(Namespace, VType, CType, SField) \
    IMPLEMENT_VECTOR(Namespace, VType, CType) \
    int Namespace VType::Compare (Some Item1, Some Item2, int Mode) const \
    { \
        return strcmp (((CType)Item1)->SField, ((CType)Item2)->SField); \
    } \
    int Namespace VType::CompareKey (Some Item, ConstSome Key, int Mode) const \
    { \
        return strcmp (((CType)Item)->SField, (char *)Key); \
    } \
    CType Namespace VType::GetByKey (ConstSome Key, int Mode) const \
    { \
        return (CType)Vector::GetByKey (Key, Mode); \
    }

    /**
     * Implement a sorted vector that compares its elements by a element in the
     * stored records that can be compared with the SignCompare() templated function.
     *
     * \arg \c Namespace
     *   The namespace prefix of this vector, in the case when vector was
     *   declared inside of a class or something like this.
     * \arg \c VType
     *   Vector class type name (SomeVector etc).
     * \arg \c CType
     *   The type of content items (SomeStruct etc). The vector is defined
     *   as if it contains pointers to SomeStruct.
     * \arg \c SField
     *   The field of the structure that is used for sorting.
     * \arg \c SType
     *   The type of SField.
     */
#define IMPLEMENT_VECTOR_SORTED(Namespace, VType, CType, SField, SType) \
    IMPLEMENT_VECTOR(Namespace, VType, CType) \
    int Namespace VType::Compare (Some Item1, Some Item2, int Mode) const \
    { \
        return SignCompare <SType> (((CType)Item1)->SField, ((CType)Item2)->SField); \
    } \
    int Namespace VType::CompareKey (Some Item, ConstSome Key, int Mode) const \
    { \
        return SignCompare <SType> (((CType)Item)->SField, SType (uintptr (Key))); \
    } \
    CType Namespace VType::GetByKey (ConstSome Key, int Mode) const \
    { \
        return (CType)Vector::GetByKey (Key, Mode); \
    }

// tolua_end_hide

    /**
     *  @}
     */
#endif                                                      // __VECTOR_H__
