/**
 *     \file  src/worldserver/todo/PetHandler.h
 *    \brief  Receives all messages related to combat and non-combat pets.
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

#ifndef __PET_HANDLER_H__
#define __PET_HANDLER_H__

#include "MsgHandler.h"

#include "Spell.h"
#include "UpdateFields.h"

class Unit;
class GameClient;
class DatabaseInterface;

class PetHandler : public MsgHandler
{
    public:
        PetHandler();
        ~PetHandler();
        void HandleMsg( NetworkPacket & recv_data, GameClient *pClient );
    protected:

};
#endif // __PET_HANDLER_H__
