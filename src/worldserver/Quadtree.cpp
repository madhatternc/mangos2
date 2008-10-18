/**
 *     \file  src/worldserver/Quadtree.cpp
 *    \brief  Provides a basic quad tree implementation.
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

#include <math.h>
#include "Quadtree.h"

QuadTree::Node::Node (float _minx, float _miny, float _maxx, float _maxy,
                      Node *_parent)
{
    nw = 0;
    ne = 0;
    sw = 0;
    se = 0;

    minx = _minx;
    miny = _miny;
    maxx = _maxx;
    maxy = _maxy;

    parent = _parent;
}

void QuadTree::Node::RemoveObject (uint64 oid)
{
    int idx = objects.FindSortedKey (&oid);
    if (idx >= 0)
        objects.Delete (idx);
}

QuadTree::Node::~Node ()
{
    if (nw)
        delete nw;
    if (ne)
        delete ne;
    if (sw)
        delete sw;
    if (se)
        delete se;
}

bool QuadTree::Node::TestInRange (float x, float y, float range) const
{
    bool inside_x = (minx <= x) && (x < maxx);
    bool inside_y = (miny <= y) && (y < maxy);

    if (inside_x && inside_y)
        return true;

    bool closeenough_x = (fabs (minx - x) <= range || fabs (maxx - x) <= range);
    bool closeenough_y = (fabs (miny - y) <= range || fabs (maxy - y) <= range);

    if ((inside_x || closeenough_x) && (inside_y || closeenough_y))
        return true;

    return false;
}

void QuadTree::Node::Check ()
{
    if (!HasData () && !HasChildren () && parent)
    {
        if (parent->nw == this)
            parent->nw = 0;
        else if (parent->ne == this)
            parent->ne = 0;
        else if (parent->sw == this)
            parent->sw = 0;
        else if (parent->se == this)
            parent->se = 0;
        delete this;
    }
}

//---------------------------------------------------------------------------//

QuadTree::QuadTree ()
{
    root = 0;
}

QuadTree::QuadTree (float minx, float miny, float maxx, float maxy)
{
    root = new Node (minx, miny, maxx, maxy, 0);
}

QuadTree::~QuadTree ()
{
    delete root;
    root = 0;
}

void QuadTree::SetSize (float minx, float miny, float maxx, float maxy)
{
    delete root;
    root = new Node (minx, miny, maxx, maxy, 0);
}

void QuadTree::Insert (Object *obj)
{
    if (obj->QTreeData.Node)
        Remove (obj);

    _Insert (root, obj);
}

void QuadTree::Remove (Object *data)
{
    if (data->QTreeData.Node)
    {
        Node *n = (Node *)data->QTreeData.Node;
        n->RemoveObject (data->GetGUID ());
        n->Check ();
        data->QTreeData.Node = NULL;
    }
}

void QuadTree::RemoveAll ()
{
    delete root->nw;
    root->nw = 0;
    delete root->ne;
    root->ne = 0;
    delete root->sw;
    root->sw = 0;
    delete root->se;
    root->se = 0;
}

/*
 * Every Node can have data and children. Every data must be completely
 * contained inside the Node, so boundary sphere is checked.
 */
void QuadTree::_Insert (Node *_root, Object *data)
{
    float dividerx = (_root->minx + _root->maxx) / 2;
    float dividery = (_root->miny + _root->maxy) / 2;

    /*
     * Logic:
     *
     * 1) We have Objects in this Node. The Node has no children.
     *    - Squaring was not yet needed, so we do it now and move
     *      all the objects down into the squares that arent locked.
     *
     * 2) We have Objects in this Node. The Node has children.
     *    - All those objects must be locked, else they would have been
     *    moved down on squaring. So we dont worry about moving them.
     *
     * 3) The Node is empty. We add the object.
     */

    // Initially assume the object is not crossing any boundaries
    data->QTreeData.Bounding = false;

    if (_root->HasData () && !_root->HasChildren())
    {
        /*
         * We want to Insert another object, so we square this Node up and move
         * all the Objects that arent locked (cause they cross a boundary) down.
         */
        if ((_root->maxx - _root->minx <= 0.1) &&
            (_root->maxy - _root->miny <= 0.1))
        {
            /*
             * This protects from killing the stack. If something is messed up it may
             * blow the stack because the recursion runs forever. Stop squaring when
             * it doesnt make sense anymore. If the two objects have the same coordinate
             * we add the new one to the map. The search is linear for objects inside
             * .1 Unit. So what.
             */
            _root->AddObject (data);
            return;
        }

        /**
         * Proceed objects in node in reverse direction since this
         * makes handling deletions from the vector easier.
         */
        for (int i = _root->objects.Length () - 1; i >= 0; i--)
        {
            Object *existing = _root->objects.Get (i);

            // We remove the Object from the Node if its not locked
            // for crossing boundaries to add it to another Node
            if (existing->QTreeData.Bounding)
                continue;

            // Increment the refcount on the Object since if this is the
            // last reference ever, the object will be destroyed by Delete()
            existing->IncRef ();
            _root->objects.Delete (i);

            // First find out which square it needs, then Insert it into it
            // We divide the Node area into 4 squares, reusing existing children

            if (existing->PositionX >= _root->minx && existing->PositionX < dividerx &&
                existing->PositionY >= _root->miny && existing->PositionY < dividery)
            {
                if (!_root->nw)
                    _root->nw = new Node (_root->minx, _root->miny, dividerx, dividery, _root);

                _Insert (_root->nw, existing);
            }
            else if (existing->PositionX >= dividerx && existing->PositionX < _root->maxx &&
                     existing->PositionY >= _root->miny && existing->PositionY < dividery)
            {
                if (!_root->ne)
                    _root->ne = new Node (dividerx, _root->miny, _root->maxx, dividery, _root);

                _Insert (_root->ne, existing);
            }
            else if (existing->PositionX >= _root->minx && existing->PositionX < dividerx &&
                     existing->PositionY >= dividery && existing->PositionY < _root->maxy)
            {
                if (!_root->sw)
                    _root->sw = new Node (_root->minx, dividery, dividerx, _root->maxy, _root);

                _Insert (_root->sw, existing);
            }
            else /*if (existing->PositionX >= dividerx && existing->PositionX < _root->maxx &&
                     existing->PositionY >= dividery && existing->PositionY < _root->maxy)*/
            {
                if (!_root->se)
                    _root->se = new Node (dividerx, dividery, _root->maxx, _root->maxy, _root);

                _Insert (_root->se, existing);
            }
            // Okay, we don't need this reference anymore
            existing->DecRef ();
        }
    }

    /*
     * Maybe we squared, maybe we didnt. Anyway, this object extends beyond one
     * of the boundaries, so we cannot put it into a lower node. It will be
     * placed in this one regardless and locked.
     */

    if ((data->PositionX + data->Radius > dividerx &&
         data->PositionX - data->Radius < dividerx) ||
        (data->PositionY + data->Radius > dividery &&
         data->PositionY - data->Radius < dividery))
    {
        data->QTreeData.Bounding = true;
        _root->AddObject (data);
        return;
    }

    /*
     * The Node has been squared because there was already an object inside.
     * Also, the new object is contained in one of those new squares.
     * So we search for the right one and insert the object there.
     */
    if (_root->HasChildren ())
    {
        if (data->PositionX >= _root->minx && data->PositionX < dividerx &&
            data->PositionY >= _root->miny && data->PositionY < dividery)
        {
            if (!_root->nw)
                _root->nw = new Node (_root->minx, _root->miny, dividerx, dividery, _root);

            _Insert (_root->nw, data);
        }
        else if (data->PositionX >= dividerx && data->PositionX < _root->maxx &&
                 data->PositionY >= _root->miny && data->PositionY < dividery)
        {
            if (!_root->ne)
                _root->ne = new Node (dividerx, _root->miny, _root->maxx, dividery, _root);

            _Insert (_root->ne, data);
        }
        else if (data->PositionX >= _root->minx && data->PositionX < dividerx &&
                 data->PositionY >= dividery && data->PositionY < _root->maxy)
        {
            if (!_root->sw)
                _root->sw = new Node (_root->minx, dividery, dividerx, _root->maxy, _root);

            _Insert (_root->sw, data);
        }
        else /*if (data->PositionX >= dividerx && data->PositionX < _root->maxx &&
                 data->PositionY >= dividery && data->PositionY < _root->maxy)*/
        {
            if (!_root->se)
                _root->se = new Node (dividerx, dividery, _root->maxx, _root->maxy, _root);

            _Insert (_root->se, data);
        }

        return;
    }

    // Node is not squared, and we have only one data entry, so it can stay
    // this way. Data can be Inserted, and the recursion is over.
    _root->AddObject (data);
}

/* The difference to the Insert is that it starts at the current node
 * and tries to find the right place to be now that the position changed.
 */
bool QuadTree::_Update (QuadTree::Node *_root, Object *data)
{
    // Whew, still in the same square. Lucky bastards we are.
    if (_root->TestInside (data->PositionX, data->PositionY))
        return true;

    // Since we'll have to temporarily remove the object from the Quad Tree,
    // make sure it won't be deleted as we do that
    data->IncRef ();
    Remove (data);

    // Go upwards til the object is inside the square.
    Node *cur = _root->parent;
    while (cur && !cur->TestInside (data->PositionX, data->PositionY))
        cur = cur->parent;

    // Here is the right spot for the object, so lets drop it in.
    // May result in another squaring frenzy.
    if (cur)
        _Insert (cur, data);

    // We don't need the reference anymore. If the object goes out of the
    // quadtree and there aren't any references left... well... goodbye
    data->DecRef ();
    return (cur != NULL);
}

void QuadTree::_InRange (QuadTree::Node *_root, float x, float y, float range,
                           ObjectVector *Results, uint TypeMask, uint TypeValue)
{
    float rangesq = range * range;
    for (int i = 0; i < _root->objects.Length (); i++)
    {
        Object *o = _root->objects.Get (i);
        if ((o->GetType () & TypeMask) == TypeValue)
        {
            float deltax = x - o->PositionX;
            float deltay = y - o->PositionY;

            if (deltax * deltax + deltay * deltay <= rangesq)
                Results->Push (o);
        }
    }

    if (_root->HasChildren ())
    {
        if (_root->nw && _root->nw->TestInRange (x, y, range))
            _InRange (_root->nw, x, y, range, Results, TypeMask, TypeValue);
        if (_root->ne && _root->ne->TestInRange (x, y, range))
            _InRange (_root->ne, x, y, range, Results, TypeMask, TypeValue);
        if (_root->sw && _root->sw->TestInRange (x, y, range))
            _InRange (_root->sw, x, y, range, Results, TypeMask, TypeValue);
        if (_root->se && _root->se->TestInRange (x, y, range))
            _InRange (_root->se, x, y, range, Results, TypeMask, TypeValue);
    }
}
