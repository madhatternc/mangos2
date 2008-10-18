/**
 *     \file  src/worldserver/Object.cpp
 *    \brief  Provides a basic object definition.
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

#include "Object.h"
#include "Player.h"
#include "GameClient.h"

void Object::ObjectFields::SetLength (uint n)
{
    length = n;
    data = (uint32 *)realloc (data, n * sizeof (uint32));
    Changes.SetLength (n);
}

void Object::ObjectFields::SetU32 (uint iIndex, uint32 iValue)
{
    DEBUG_BREAK_IF (iIndex >= length);
    if (data [iIndex] == iValue)
        return;

    data [iIndex] = iValue;
    Changes.Set (iIndex);
    if (HighestChange < iIndex)
        HighestChange = iIndex;
}

//----------------------------------------------------------------------------//

#define MIN_Z   -500

Object::Object () : ObjectsInRange (0, 64)
{
    MapId = 0;
    ZoneId = 0;

    PositionX = 0.0;
    PositionY = 0.0;
    PositionZ = 0.0;
    Orientation = 0.0;
    Radius = 0.5;

    WalkSpeed = 2.5;
    RunSpeed = 7.0;
    BackWalkSpeed = 2.5;
    SwimSpeed = 4.72222;
    BackSwimSpeed = 4.5;
    TurnRate = 3.14159; // 180 degrees per second

    IsInWorld = false;

    memset (&QTreeData, 0, sizeof (QTreeData));

    Field.SetLength (OBJECT_END);
    Field.Clear (0, OBJECT_END);
    Field.SetU32 (OBJECT_FIELD_TYPE, TYPE_OBJECT);
    Field.SetF32 (OBJECT_FIELD_SCALE_X, 1.0);
}

Object::~Object ()
{
}

bool Object::MoveTo (float x, float y, float z, float o)
{
    PositionX = x;
    PositionY = y;
    PositionZ = z;
    Orientation = o;

    if (z < MIN_Z)
    {
        z = 500;
        return false;
    }

    return true;
}

void Object::SendToSet (NetworkPacket *packet, bool self)
{
    if (!packet)
        return;

    for (int i = 0; i < ObjectsInRange.Length (); i++)
    {
        Object *obj = ObjectsInRange.Get (i);
        if ((obj->GetType () & TYPE_PLAYER) &&
            (self || obj != this))
        {
            // Increment refcount since GameClient::Send() will decrement it
            packet->IncRef ();
            ((Player *)obj)->Client->Send (packet);
        }
    }
    // Now get rid of the packet
    packet->DecRef ();
}

void Object::Update (uint32 iDeltaMs)
{
    // Empty for now; later will pass control to object scripts
    // that have registered interest in receiving timed updats
}

NetworkPacket *Object::BuildDestroyPacket () const
{
    SMSG_DESTROY_OBJECT_t *outpkt = SMSG_DESTROY_OBJECT_t::Create ();
    outpkt->Guid = GetGUID ();
    return outpkt;
}

NetworkPacket *Object::BuildCreatePacket () const
{
    //@@todo
    return NULL;
}
