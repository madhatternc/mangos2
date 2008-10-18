/**
 *     \file  src/worldserver/todo/Combat.h
 *    \brief  Provides basic Combat functions.
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

#ifndef __COMBAT_H__
#define __COMBAT_H__

#include "MsgHandler.h"
#include "Object.h"

class Unit;
class GameClient;
class NetworkPacket;
struct UpdateMask;
class CombatHandler
{
    public:
        CombatHandler() {};
        virtual ~CombatHandler() {};

        void HandleMsg (NetworkPacket & recv_data, GameClient *pClient);

        /////////////////////////////////////////////////////////////////////////
        //  Deals damage from pAttacker to pVictim
        //  Does checks for death and lots of other keen things
        void DealDamage (Unit *pAttacker, Unit *pVictim, uint32 damage);

        void smsg_AttackStart (Unit* pAttacker, Unit* pVictim);
        void smsg_AttackStop (Unit* pAttacker, guid victim_guid);

        void AttackerStateUpdate (Unit *pAttacker, Unit *pVictim, uint32 damage);
        void Heal (Unit *pAttacker, Unit *pVictim, uint32 damage);

        uint32 petGUID;

};
#endif // __COMBAT_H__
