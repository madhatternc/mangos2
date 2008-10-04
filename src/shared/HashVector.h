/**
 *     \file  src/shared/HashVector.h
 *    \brief  Hashed Vector class interface
 *
 * Copyright (C) 2005 by Andrew Zabolotny <zap@homelink.ru>
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

#ifndef __HASH_VECTOR_H__
#define __HASH_VECTOR_H__

#include <limits.h>
#include "Vector.h"

/**
 *  \addtogroup FoundationClasses
 *
 *  @{
 */

/**
 *  \brief Return type of the hash function
 */
typedef uint32 HashResult_t;

/**
 *  \brief The search key type: it is actually a POINTER to the value
 */
typedef const void *HashKey_t;

/**
 *  \class HashVector
 *  \brief A hash vector is somehow similar to Vector, but uses hash tables.
 *
 *  \par
 *  A hash vector is somehow similar to Vector, but uses hash tables to
 *  store data, thus greatly decreasing search times. For big arrays
 *  (> 5000 elements) the search time is faster than with binary trees
 *  for the regular vector, although you should keep in mind that nothing
 *  comes for free: you get speed in exchange for memory usage. Usually
 *  a HashVector will take about 1.5-2x as much memory as a Vector of the
 *  same size would.
 */
class HashVector : protected Vector
{
	protected:
		/**
		 *  \brief The bitmask to AND with the hash result
		 */
		HashResult_t HashMask;

		/**
		 *  \brief Memory-vs-speed coefficient
		 */
		int MemVsSpeed;

		/**
		 *  \brief This is a highly optimized vector for holding sorted buckets.
		 *
		 *  Initially this was subclassed from Vector but it has been rewritten
		 *  into a separate class to squeeze some more percents of performance.
		 */
		struct LargeHashBucket
		{
			uint count;
			uint limit;
			Some *root;

			/**
			 *  \brief Initialize the large hash bucket
			 */
			void Init (uint iLimit);

			/**
			 *  \brief Insert a element into the large hash bucket at given position
			 */
			void Insert (uint Pos, Some Item);
		};

		/**
		 *  \def HASHVECT_BUCKET_SIZE
		 *
		 *  "Bucket size" is the size of the 1st level buckets in bucket chain...
		 *  As soon as we have more than BUCKET_SIZE-1 elements, a sorted tiny
		 *  vector is created in place of the bucket. So if we have too much
		 *  elements in a bucket, we will perform a binary search on them
		 *  which is faster than linear search on large buckets.
		 *  ((sizeof (LargeHashBucket) + sizeof (Some) - 1) / sizeof (Some))
		 */
	#define HASHVECT_BUCKET_SIZE 5

		/**
		 *  \def IS_LARGE_BUCKET(el0)
		 *
		 *  The bucket is tiny if 1st element is less than HASHVECT_BUCKET_SIZE
		 *  (it's number of elements in the tiny bucket)
		 */
	#define IS_LARGE_BUCKET(el0) \
		(uintptr (el0) >= HASHVECT_BUCKET_SIZE)

		// The following routines are intentionaly made member functions of HashVector
		// and not of LargeHashBucket because they use HashVector methods, and you can't
		// do that effectively in a LargeHashBucket method.

		/**
		 *  \brief Destroy the large hash bucket, and free all elements
		 */
		void lhbDestroy (LargeHashBucket *lhb);

		/**
		 *  \brief Insert a element into the large hash bucket so that bucket remains sorted
		 */
		void lhbInsertSorted (LargeHashBucket *lhb, Some Item);

		/**
		 *  \brief Find a element in a large hash bucket by key and return its index
		 */
		int lhbFind (LargeHashBucket *lhb, HashKey_t Key) const;

		/**
		 *  \brief Same as lhbFind but return the element itself
		 */
		Some lhbGetByKey (LargeHashBucket *lhb, HashKey_t Key) const
			{ int x = lhbFind (lhb, Key); return (x >= 0) ? lhb->root [x] : Some (0); }

		/**
		 *  \brief Default hash function
		 */
		static HashResult_t DefaultHash (HashKey_t Key);

		/**
		 *  \brief Copy this hash vector (without reallocating pointers!)
		 */
		HashVector (HashVector *other);

		/**
		 *  \brief Resize the hash vector so that it uses so much buckets.
		 *
		 *  The hash vector really adjusts its size automatically, so there's
		 *  no need to call this function.
		 *
		 *  \arg \c iBuckets Number of buckets used. MUST BE A POWER OF TWO.
		 */
		void SetBuckets (int iBuckets);

		/**
		 *  \brief Slightly faster Insert without sanity checks.
		 *
		 */
		void _Insert (Some Item);

	public:
		/**
		 *  \brief This is a pointer to the hash function
		 */
		HashResult_t (*Hash) (HashKey_t Key);

	#define MVS_FAST    1
	#define MVS_NORMAL  2
	#define MVS_SMALL   3

		/**
		 *  \brief Initialize the hash vector.
		 *
		 *  Initialize the hash vector so that it initially contains the
		 *  requested number of buckets.
		 *
		 * \arg \c MvsS Memory usage vs Speed. You can somewhat modify the behaviour
		 *   of the hash vector by setting this to a value different that default.
		 *   If it is MVS_FAST, the lookups will be faster but the vector will
		 *   take more memory; if it is MVS_SMALL, the vector will take less memory
		 *   but will be slightly slower (still much faster than regular Vector).
		 * \arg \c HashBits This parameter defines how much bits to use from the
		 *   hash function. Basically this defines how much buckets there are
		 *   initially: 2^HashBits. The larger you expect the amount of items, the
		 *   larger numbers you should use here. The default value is good for hash
		 *   tables of around 4000 elements; the optimal value can be ~ computed as
		 *   log2(n/HASHVECT_BUCKET_SIZE), and it depends of the quality
		 *   of the used hash function.
		 */
		HashVector (int MvsS = MVS_NORMAL, int HashBits = 10);

		/**
		 *  \brief Free all the data associated with this hash vector
		 */
		virtual ~HashVector ();

		/**
		 *  \brief Return the number of elements in this vector
		 */
		uint Length ()
			{ return Vector::Length (); }

		/**
		 *  \brief Get number of buckets used
		 */
		uint Buckets ()
			{ return HashMask + 1; }

		/**
		 *  \brief Virtual function which frees a vector element
		 */
		virtual void FreeItem (Some Item) const;

		/**
		 *  \brief Delete all elements
		 */
		void DeleteAll ();

		/**
		 *  \brief Extract the sort key from a item
		 */
		virtual HashKey_t GetKey (Some Item) const
			{ return (HashKey_t)Item; }

		/**
		 *  \brief Compare two array elements in given Mode
		 */
		virtual int Compare (HashKey_t Key1, HashKey_t Key2) const;

		/**
		 *  \brief Insert element 'Item' into the hash vector
		 */
		void Insert (Some Item);

		/**
		 *  \brief Delete element 'Item' from the hash vector
		 */
		void Delete (Some Item);

		/**
		 *  \brief Find a hash vector element by search key; returns 0 if not found
		 */
		Some GetByKey (HashKey_t Key) const;

	public:
		///--- Expose the hidden Base interface ---///

		void IncRef ()
			{ Base::IncRef (); }

		void DecRef ()
			{ Base::DecRef (); }

		int GetRefCount ()
			{ return Base::GetRefCount (); }

	public:
		friend class Iterator;

		/**
		 *  \class Iterator
		 *  \brief Iterator will help you traverse the hash vector items back and forth.
		 */
		class Iterator
		{
			friend class HashVector;

			const HashVector *Parent;
			int CurrentBucket;
			int BucketDelta;

			/**
			 *  \brief Private constructor to initialize an iterator pointing to arbitrary place
			 */
			Iterator (const HashVector *parent, int curbucket, int delta)
				{ Parent = parent; CurrentBucket = curbucket; BucketDelta = delta; }

			public:
				/**
				 *  \brief Get the hash vector element pointed by this iterator
				 */
				Some operator * ()
				{
					if ((CurrentBucket < 0) || (CurrentBucket >= Parent->limit))
						return Some (0);
					Some *cur = Parent->root + CurrentBucket;
					intptr numel = intptr (*cur);
					if (IS_LARGE_BUCKET (numel))
						return ((LargeHashBucket *)cur)->root [BucketDelta];
					return cur [1 + BucketDelta];
				}

				/**
				 *  \brief Move to next element
				 */
				Iterator &operator ++ ()
				{
					BucketDelta++;
					for (;;)
					{
						intptr numel = (CurrentBucket < 0) ? INT_MIN : intptr (Parent->root [CurrentBucket]);
						if (BucketDelta < numel)
							return *this;
						CurrentBucket += HASHVECT_BUCKET_SIZE;
						if (CurrentBucket > Parent->limit)
							return *this;
						BucketDelta = 0;
					}
				}

				/**
				 *  \brief Postfix increment
				 */
				Iterator operator ++ (int)
				{
					Iterator __tmp = *this;
					++(*this);
					return __tmp;
				}

				/**
				 *  \brief Move to previous element
				 */
				Iterator &operator -- ()
				{
					if (CurrentBucket < 0)
						return *this;
					BucketDelta--;
					while (BucketDelta < 0)
					{
						CurrentBucket -= HASHVECT_BUCKET_SIZE;
						if (CurrentBucket < 0)
							return *this;
						BucketDelta = (CurrentBucket >= Parent->limit) ? -1 :
						intptr (Parent->root [CurrentBucket]) - 1;
					}
					return *this;
				}

				/**
				 *  \brief Postfix decrement
				 */
				Iterator operator -- (int)
				{
					Iterator __tmp = *this;
					--(*this);
					return __tmp;
				}

				/**
				 *  \brief Get the current element or NULL and move forward
				 */
				Some Next ()
					{ return *(*this)++; }

				/**
				 *  \brief Get the current element or NULL and move backward
				 */
				Some Prev ()
					{ return *(*this)--; }
		};

		/**
		 *  \brief Get an iterator pointing to the start of hash vector
		 */
		Iterator Begin () const
			{ return ++Iterator (this, -HASHVECT_BUCKET_SIZE, 0); }

		/**
		 *  \brief Get an iterator pointing to the end of hash vector
		 */
		Iterator End () const
			{ return --Iterator (this, limit, 0); }

		/**
		 *  \brief Like GetByKey but return an iterator
		 */
		Iterator FindKey (HashKey_t Key) const;
};

/**
 *  \def DECLARE_HASH_VECTOR(VType, CType, HashFunc, Extra)
 *
 *  This macro can be used to declare hash vectors containing some specific structure
 *  that hold pointers to some structure.
 *  \arg \c VType HashVector class type name (SomeHashVector etc).
 *  \arg \c CType The type of content items (SomeStruct etc). The vector is
 *    defined as if it contains pointers to SomeStruct.
 *  \arg \c HashFunc Pointer to a hash function; if 0, the default hash function
 *    will be used
 *  \arg \c Extra Extra declarations you wish to put in the class
 */
#define DECLARE_HASH_VECTOR(VType, CType, HashFunc, Extra) \
	class VType : public HashVector \
	{ \
		public: \
			VType (int MvsS = MVS_NORMAL, int HashBits = 9) : HashVector (MvsS, HashBits) \
			{ if (HashFunc != 0) Hash = HashFunc; } \
			virtual ~VType (); \
			virtual void FreeItem (Some Item) const; \
			virtual HashKey_t GetKey (Some Item) const; \
			virtual int Compare (HashKey_t Key1, HashKey_t Key2) const; \
			CType GetByKey (HashKey_t Key) const \
			{ \
				return (CType)HashVector::GetByKey (Key); \
			} \
			Extra \
		}

	/**
	 *  \def IMPLEMENT_HASH_VECTOR(Namespace, VType, CType, KField, CmpExpr)
	 *
	 *  This macro will implement the methods declared but not implemented
	 *  by the DEFINE_HASH_VECTOR macro. There's no Extra parameter as the
	 *  implementation is not delimited by brackets.
	 *
	 *  \arg \c Namespace The namespace prefix of this vector, in the case when
	 *    vector was declared inside of a class or something like this.
	 *  \arg \c VType Vector class type name (SomeVector etc).
	 *  \arg \c CType The type of content items (SomeStruct* etc). The vector is
	 *    defined as if it contains this kind of items.
	 *  \arg \c KField The key field of the structure
	 *  \arg \c CmpExpr The expression to compare two keys, Key1 and Key2 and return
	 *    -1, 0 or +1.
	 */
#define IMPLEMENT_HASH_VECTOR(Namespace, VType, CType, KField, CmpExpr) \
	Namespace VType::~VType () \
	{ \
		DeleteAll (); \
	} \
	void Namespace VType::FreeItem (Some Item) const \
	{ \
		delete (CType)Item; \
	} \
	HashKey_t Namespace VType::GetKey (Some Item) const \
	{ \
		return HashKey_t (&((CType)Item)->KField); \
	} \
	int Namespace VType::Compare (HashKey_t Key1, HashKey_t Key2) const \
	{ \
		CmpExpr; \
	}

	/**
	 *  \def CMPEXPR_CSTR
	 *
	 *  This comparison expression can be used to handle keys expressed as C-strings.
	 */
#define CMPEXPR_CSTR \
	return strcmp (*(char **)Key1, *(char **)Key2)

	/**
	 *  \def HASHFUNC_INT(Name, Type)
	 *
	 *  This macro (meant to be used in the Extra parameter of DECLARE_HASH_VECTOR)
	 *  will define a hash function for integer keys of any bitsize.
	 */
#define HASHFUNC_INT(Name, Type) \
	static HashResult_t Name (HashKey_t Key) \
	{ \
		Type hash = *(Type *)Key; \
		hash += ((hash << 3) + (hash << 2)) ^ (hash >> 4); \
		return HashResult_t (hash); \
	}

	/**
	 *  \def HASHFUNC_CSTR(Name)
	 *
	 *  This macro (meant to be used in the Extra parameter of DECLARE_HASH_VECTOR)
	 *  will define a hash function for char * keys.
	 */
#define HASHFUNC_CSTR(Name) \
	static HashResult_t Name (HashKey_t Key) \
	{ \
		uchar c, *str = *(uchar **)Key; \
		uintptr hash = 0; \
		while ((c = *str++)) \
		{ \
			hash += (hash << 3) + (hash << 2) ^ (hash >> sizeof (hash) * 8 - 5); \
			hash += c; \
		} \
		return HashResult_t (hash); \
	}

		/**
		 *  @}
		 */
#endif														// __HASH_VECTOR_H__
