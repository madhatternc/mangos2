/**
 *     \file  src/worldserver/Quadtree.h
 *    \brief  Provides a basic quad tree implementation.
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

#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Object.h"
#include "ObjectVector.h"

/**
 * A quad tree is a 2D data structure that keeps lots of objects nicely
 * sorted in a tree with four children in every node, so that queries like
 * "give me a list of objects that are near the point X,Y" works lighting
 * fast.
 */
class QuadTree
{
	private:
		class Node
		{
			public:
				ObjectVector objects;

				Node* parent;

				Node* nw;
				Node* ne;
				Node* sw;
				Node* se;

				float minx;
				float miny;
				float maxx;
				float maxy;

			public:
				Node (float _minx, float _miny, float _maxx, float _maxy, Node *_parent);
				~Node ();

				/// Add a object to this node
				void AddObject (Object *data)
					{ objects.InsertSorted (data, NULL, OVSORT_GUID); }
				/// Remove a object by GUID
				void RemoveObject (uint64 oid);
				/// Check if this node has any associated objects
				bool HasData () const
					{ return objects.Length () > 0; }
				/// Check if this node has children nodes
				bool HasChildren () const
					{ return (nw || ne || sw || se); }
				/// Test if the point is inside this node
				bool TestInside (float x, float y) const
					{ return (x >= minx && x < maxx && y >= miny && y < maxy); }
				/**
				 * Approximative test if a circle with center in x,y and
				 * given radius crosses this node.
				 */
				bool TestInRange (float x, float y, float range) const;
				/// Check if this node makes any sense to exist
				void Check ();
		};

		Node *root;

		void _InRange (Node *_root, float x, float y, float range,
			ObjectVector *Results, uint TypeMask, uint TypeValue);
		bool _Update (Node *_root, Object *data);
		void _Insert (Node *_root, Object *data);

	public:
		QuadTree (float minx, float miny, float maxx, float maxy);
		QuadTree ();
		~QuadTree ();

		/**
		 * Clear all the objects from the quadtree and set it to have
		 * given size.
		 */
		void SetSize (float minx, float miny, float maxx, float maxy);

		/**
		 * Insert a object into the quad tree.
		 */
		void Insert (Object *obj);

		/**
		 * Remove the object from the quad tree.
		 */
		void Remove (Object *obj);

		/**
		 * Remove all objects from the quad tree
		 */
		void RemoveAll ();

		/**
		 * Return a list of all objects found in the given range from the
		 * given point matching a specific type.
		 * @arg x
		 *   The X coordinate
		 * @arg y
		 *   The Y coordinate
		 * @arg range
		 *   The range to search for objects from the given point
		 * @arg Results
		 *   The output vector where all objects in this range will be placed.
		 * @arg TypeMask
		 *   The mask to AND with the Object->GetType (). If you pass 0 here,
		 *   and TypeValue is also 0, the function will return ALL objects.
		 * @arg TypeValue
		 *   This is the value that will be compared with the result of
		 *   (Object->GetType () & TypeMask). If they are equal, the object
		 *   will be considered matching.
		 */
		void InRange (float x, float y, float range, ObjectVector *Results,
			uint TypeMask = 0, uint TypeValue = 0)
			{ _InRange (root, x, y, range, Results, TypeMask, TypeValue); }

		/**
		 * Update object's position in the quad tree.
		 * Must be called after every time object changes position.
		 * It is cheap to call if the object haven't moved to a different node,
		 * so you should'nt make any unneccessary optimizations to call Update
		 * less often if the object position has't changed.
		 * @arg data
		 *   The object that possibly has changed his position.
		 * @return
		 *   true if object is still within the boundaries of the quad tree
		 *   false if object has moved outside the topmost square.
		 */
		bool Update (Object *data)
			{ return _Update ((Node *)data->QTreeData.Node, data); }
};
#endif														//__QUADTREE_H__
