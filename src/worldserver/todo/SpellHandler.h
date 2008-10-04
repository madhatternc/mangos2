/**
 *     \file  src/worldserver/todo/Spellhandler.h
 *    \brief  Receives all messages related to Spells.
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

#ifndef __SPELL_HANDLER_H__
#define __SPELL_HANDLER_H__

#include <iostream>
#include <cstdlib>

#include "MsgHandler.h"

#include "Spell.h"
#include "UpdateFields.h"

class Unit;
class GameClient;
class DatabaseInterface;

class SpellHandler : public MsgHandler
{
	public:
		SpellHandler();
		~SpellHandler();
		void HandleMsg( NetworkPacket & recv_data, GameClient *pClient );
		int applySpell( GameClient *pClient, Unit* target, uint32 spell, SpellEntry spellEntry);
		int usePotion(GameClient *pClient, uint32 spell, SpellEntry spellEntry, uint32 targets);
		int setAura(Unit *pUnit, uint32 spell);
		float CalcDistance(float sx, float sy, float sz, float dx, float dy, float dz);

		guid PetCreature (GameClient *pClient, char* pName);

		float lrand, rrand;
		float abstand, winkel;
		float CalcDistance2d( float xe, float ye, float xz, float yz );
		bool inbogen( float radius,  float xM, float yM,float zM, float offnung, float drehung, float xP, float yP,float zP );
		float geteinfachererwinkel( float winkel );
		float getwinkel( float xe, float ye, float xz, float yz );

	protected:

};
#endif														// __SPELL_HANDLER_H__
