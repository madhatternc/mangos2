/**
 *     \file  src/worldserver/todo/AuraHandler.h
 *    \brief  Receives all messages releated to Auras and Seals, extending the SpellHandler.
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

#ifndef __AURA_HANDLER_H__
#define __AURA_HANDLER_H__

#include "MsgHandler.h"

#include "Spell.h"
#include "UpdateFields.h"

class Unit;
class GameClient;
class DatabaseInterface;

class AuraHandler : public MsgHandler
{
    public:
        AuraHandler();
        ~AuraHandler();
        void HandleMsg( NetworkPacket & recv_data, GameClient *pClient );
        int setAura(Unit *pUnit, uint32 spell);

    protected:

};
#endif // __AURA_HANDLER_H__
