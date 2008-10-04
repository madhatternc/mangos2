/**
 *     \file  src/shared/Vector.cpp
 *    \brief  Vector clas
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

#include "Vector.h"

Vector::Vector (int ilimit, int ithreshold)
{
	limit = ilimit;
	if (ilimit)
		root = (Some *)malloc (ilimit * sizeof (Some));
	else
		root = NULL;
	count = 0; threshold = ithreshold;
}

Vector::~Vector ()
{
	//not much sense to call DeleteAll () since even for inherited classes
	//anyway will be called Vector::FreeItem which is empty.
	//DeleteAll ();
	if (root) free (root);
}

void Vector::DeleteAll ()
{
	while (count > 0)
		FreeItem (root [--count]);
	SetLength (0);
}

void Vector::SetLength (int n)
{
	count = n;
	SetLimit (n);
}

void Vector::SetLimit (int n)
{
	if ((n > limit) || ((limit > threshold) && (n < limit - threshold)))
	{
		n = ((n + threshold - 1) / threshold) * threshold;
		if (n)
			root = (Some *)realloc (root, n * sizeof (Some));
		else
		{
			free (root);
			root = NULL;
		}
		limit = n;
	}
}

void Vector::FreeItem (Some Item) const
{
	(void)Item;
}

bool Vector::Delete (int n)
{
	if (n < count)
	{
		FreeItem (root [n]);
		int ncount = count - 1;
		if (ncount != n)
			memmove (&root [n], &root [n + 1], (ncount - n) * sizeof (Some));
		SetLength (count = ncount);
		return true;
	}
	else
		return false;
}

bool Vector::Replace (int n, Some what)
{
	if (n < count)
	{
		FreeItem (root [n]);
		root [n] = what;
		return true;
	}
	else
		return false;
}

bool Vector::Insert (int n, Some Item)
{
	if (n <= count)
	{
		SetLength (count + 1);								// Increments 'count' as a side-effect.
		uint movebytes = (count - n - 1) * sizeof (Some);
		if (movebytes)
			memmove (&root [n + 1], &root [n], movebytes);
		root [n] = Item;
		return true;
	}
	else
		return false;
}

bool Vector::Shift (int n1, int n2)
{
	if (n1 < 0 || n2 < 0 || n2 >= count || n2 >= count)
		return false;

	Some x = root [n1];
	if (n1 < n2)
		memmove (&root [n1], &root [n1 + 1], (n2 - n1) * sizeof (Some));
	else
		memmove (&root [n2 + 1], &root [n2], (n1 - n2) * sizeof (Some));

	root [n2] = x;

	return true;
}

int Vector::Find (Some which, bool reversedir) const
{
	int i;

	if (reversedir)
	{
		for (i = Length () - 1; i >= 0; i--)
			if (root [i] == which)
				return i;
	}
	else
	{
		for (i = 0; i < Length (); i++)
			if (root [i] == which)
				return i;
	}

	return -1;
}

int Vector::FindKey (ConstSome Key, int Mode) const
{
	for (int i = 0; i < Length (); i++)
		if (CompareKey (root [i], Key, Mode) == 0)
			return i;
	return -1;
}

int Vector::FindSortedKey (ConstSome Key, int Mode) const
{
	int l = 0, r = Length () - 1;
	int CompMode = Mode & ~CSV_FIND_MODE_MASK;
	int m = 0, cmp = 0;

	while (l <= r)
	{
		m = (l + r) / 2;
		cmp = CompareKey (root [m], Key, CompMode);

		if (cmp == 0)
			return m;
		else if (cmp < 0)
			l = m + 1;
		else
			r = m - 1;
	}

	switch (Mode & CSV_FIND_MODE_MASK)
	{
		case CSV_FIND_NEAREST_SMALLER:
			return cmp < 0 ? m : m - 1;
		case CSV_FIND_NEAREST_LARGER:
			return cmp >= 0 ? m : m + 1;
	}

	return -1;
}

int Vector::InsertSorted (Some Item, int *oEqual, int Mode)
{
	int m = 0, l = 0, r = Length () - 1;
	while (l <= r)
	{
		m = (l + r) / 2;
		int cmp = Compare (root [m], Item, Mode);

		if (cmp == 0)
		{
			if (oEqual)
				*oEqual = m;
			Insert (++m, Item);
			return m;
		}
		else if (cmp < 0)
			l = m + 1;
		else
			r = m - 1;
	}
	if (r == m)
		m++;
	Insert (m, Item);
	if (oEqual)
		*oEqual = -1;
	return m;
}

void Vector::QuickSort (int Left, int Right, int Mode)
{
	recurse:
	int i = Left, j = Right;
	int x = (Left + Right) / 2;
	do
	{
		while ((i != x) && (Compare (Get (i), Get (x), Mode) < 0))
			i++;
		while ((j != x) && (Compare (Get (j), Get (x), Mode) > 0))
			j--;
		if (i < j)
		{
			Exchange (i, j);
			if (x == i)
				x = j;
			else if (x == j)
				x = i;
		}
		if (i <= j)
		{
			i++;
			if (j > Left)
				j--;
		}
	} while (i <= j);

	if (j - Left < Right - i)
	{
		if (Left < j)
			QuickSort (Left, j, Mode);
		if (i < Right)
		{
			Left = i;
			goto recurse;
		}
	}
	else
	{
		if (i < Right)
			QuickSort (i, Right, Mode);
		if (Left < j)
		{
			Right = j;
			goto recurse;
		}
	}
}

int Vector::Compare (Some Item1, Some Item2, int Mode) const
{
	(void)Mode;
	return (intptr (Item1) > intptr (Item2)) ? +1 : (intptr (Item1) == intptr (Item2)) ? 0 : -1;
}

int Vector::CompareKey (Some Item, ConstSome Key, int Mode) const
{
	(void)Mode;
	return (intptr (Item) > intptr (Key)) ? +1 : (intptr (Item) == intptr (Key)) ? 0 : -1;
}

bool Vector::Copy (Vector &Other)
{
	DeleteAll ();
	threshold = Other.threshold;
	SetLength (Other.count);
	memcpy (root, Other.root, count * sizeof (Some));
	return true;
}

int Vector::Float (int n, int Mode)
{
	if (n < 0 || n >= count || count == 1)
		return n;

	int n1 = n;

	while ((n > 0) && (Compare (root [n], root [n - 1], Mode) < 0))
	{
		Exchange (n, n - 1);
		n--;
	}

	if (n1 != n)
		return n;

	// Re-use the variable
	n1 = count - 1;
	while ((n < n1) && (Compare (root [n], root [n + 1], Mode) > 0))
	{
		Exchange (n, n + 1);
		n++;
	}

	return n;
}
