/**
 *     \file  src/worldserver/todo/ObjectMgr.h
 *    \brief  Provides basic Object manager functions.
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

#ifndef __OBJECT_MGR_H__
#define __OBJECT_MGR_H__

#include "Common.h"
#include "Unit.h"
#include "Object.h"
#include "ObjectVector.h"
#include "HashVector.h"

struct UpdateMask;
class NetworkPacket;
class Character;
class Unit;

#define UPDATE_DISTANCE     155.8

/**
 * The ObjectManager class is the ultimate storage and request class.
 * All requests for Objects visible in the world should go through it.
 * If you have some list types you should use Vectors for small lists,
 * and HashVectors for large lists that are often accessed.
 */
class ObjectManager
{
    private:

        // Stroage instrances. We store every type in an own Vector to keep them reasonable small
        ObjectVector m_areatrigger;

    public:
        ObjectManager () {}
        ~ObjectManager () {}

        /**
         * Request a Vector of all Objects in distance.
         * If the Object is up to date it will return the Objects nearest vector if the distance is the same
         * @arg Object
         *   Object for which the list is requested
         * @arg distance
         *   Distance to other Objects to request
         */

        ObjectVector* GetDistantObjects(Object *, uint32 distance=UPDATE_DISTANCE);

        /**
         * Request a Object
         * @guid guid
         *   Guid of the Object to return
         */
        Object* GetObject(guid guid);
        /**
         * Request a Object
         * @arg guidsno
         *   Sno of the Object
         * @arg type
         *   Type of the Object
         */
        Object* GetObject(uint32 guidsno, uint32 type);

        /**
         * Add a visible Object in the World.
         * @arg Object
         *   Object to add to the World
         * @arg skipNearestUpdate
         *   Does not update the nearest Vector of the Objects
         */
        bool AddObject(Object *, bool skipNearestUpdate = false);

        /**
         * Updates the Quadtree of the ObjectMgr to reflect position changes
         * @arg Object
         *   Object to update
         * @arg skipNearestUpdate
         *   Does not update the nearest Vector of the Objects
         * @arg skipNetworkPackets
         *   Don't send update packet to all Players is visible range
         */
        bool Update(Object *, bool skipNearestUpdate = false, bool skipNetworkPackets = false);

        //@@FIXME: update this functions
        void BuildAndSendCreatePlayer (Character *pNewChar, uint32 createflag, Character *pReceiver);
        void BuildCreatePlayerMsg (Character *pNewChar, std::list<NetworkPacket*>* msglist, uint32 createflag = 0);
        void SetCreatePlayerBits (UpdateMask *updateMask);

        void BuildCreateUnitMsg (Unit *pNewUnit, NetworkPacket* data, Character *pPlayer);
        void SetCreateUnitBits (UpdateMask &updateMask);

    private:

    protected:

};
#endif // __OBJECT_MGR_H__
