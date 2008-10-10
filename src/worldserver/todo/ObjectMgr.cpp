/**
 *     \file  src/worldserver/todo/ObjectMgr.cpp
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

#include "ObjectMgr.h"
#include "UpdateFields.h"
#include "WorldServer.h"
#include "Character.h"
#include "Unit.h"
#include "Item.h"

//=====================================================================================================================
//  Build and Send Create Player -- Builds and sends all the messages required to Create a player and his items
//
//  pNewChar - Object to use for creation
//  createflag - 1 for current client's player, 0 for another player
//  pReceiver - the character to receive this create message.  If null, send to pNewChar
//=====================================================================================================================
void ObjectMgr::BuildAndSendCreatePlayer(Character *pNewChar, uint32 createflag, Character *pReceiver)
{
    if (!pReceiver) pReceiver = pNewChar;

    std::list<NetworkPacket*> msglist;
    BuildCreatePlayerMsg(pNewChar, &msglist, createflag);

    std::list<NetworkPacket*>::iterator msgitr;
    for (msgitr = msglist.begin(); msgitr != msglist.end();)
    {
        NetworkPacket *msg = (*msgitr);
        pReceiver->pClient->SendMsg(msg);
        delete msg;
        msgitr = msglist.erase(msgitr);
    }
}

//===================================================================================================================
//  Build Create Player Msg -- Builds a list of messages required to create a player and his items
//  msglist - The std::list of NetworkPacket message
//===================================================================================================================
char* ObjectMgr::getCharacterName(uint32 guid)
{
    /*
        CharacterList::iterator itr;
        for (itr = m_characters.begin(); itr != m_characters.end(); itr++){
                    if ((*itr)->GetGUID ().sno == guid)
                return (char *)((*itr)->m_name);
        }

        assert(!"Invalid Player_GUID in getCharacterName!");
        return NULL;
    */
    return NULL;
}

char* ObjectMgr::getCharacterGuildName(uint32 guid)
{
    /*
        CharacterList::iterator itr;
        for (itr = m_characters.begin(); itr != m_characters.end(); itr++)
        {
            if ((*itr)->GetGUID ().sno == guid)
                return (char *)((*itr)->m_guildname);
        }
        assert(!"Invalid Player_GUID in getCharacterGuildName!");
        return NULL;
    */
    return NULL;
}

void ObjectMgr::BuildCreatePlayerMsg(Character *pNewChar, std::list<NetworkPacket*>* msglist, uint32 createflag)
{
    uint16 i=0, invcount=0, maxslots=46, invslots=23;
    UpdateMask playerMask, invUpdateMask;

    SetCreatePlayerBits(&playerMask);

    if (createflag == 1)
    {
        invslots = 39;
        maxslots = 78;
        pNewChar->setQuestLogBits(&playerMask);
    }

    for(i = 0; i<maxslots; i+=2)
    {
        if (pNewChar->getGuidBySlot(i/2) != 0)
        {
            pNewChar->setUpdateValue (PLAYER_FIELD_INV_SLOT_HEAD + i,
                pNewChar->getGuidBySlot (i/2),
                playerMask.data);
            pNewChar->setUpdateValue (PLAYER_FIELD_INV_SLOT_HEAD + i + 1,
                0x00000040, playerMask.data);
        }
    }

    // Create Item for this player
    for(invcount = 0; invcount < invslots; invcount++)
    {
        if ((pNewChar->getGuidBySlot(invcount) != 0) && (pNewChar->getGuidBySlot(invcount) != 0))
        {

            invUpdateMask.SetLength (64);
            Item *tempitem = new Item;
            NetworkPacket *itemdata = new NetworkPacket;

            invUpdateMask.SetBit (OBJECT_FIELD_GUID);
            invUpdateMask.SetBit (OBJECT_FIELD_GUID+1);
            invUpdateMask.SetBit (OBJECT_FIELD_TYPE);
            invUpdateMask.SetBit (OBJECT_FIELD_ENTRY);
            invUpdateMask.SetBit (OBJECT_FIELD_SCALE_X);
            invUpdateMask.SetBit (OBJECT_FIELD_PADDING);
            invUpdateMask.SetBit (ITEM_FIELD_OWNER);
            invUpdateMask.SetBit (ITEM_FIELD_CONTAINED);
            invUpdateMask.SetBit (ITEM_FIELD_OWNER +1);
            invUpdateMask.SetBit (ITEM_FIELD_CONTAINED +1);
            invUpdateMask.SetBit (ITEM_FIELD_STACK_COUNT);
            tempitem->Create(pNewChar->getGuidBySlot(invcount),pNewChar->getItemIdBySlot(invcount));
            tempitem->setUpdateValue (OBJECT_FIELD_GUID, pNewChar->getGuidBySlot(invcount), invUpdateMask.data);
            tempitem->setUpdateValue (OBJECT_FIELD_GUID+1, 0x00000040, invUpdateMask.data);
            tempitem->setUpdateValue (OBJECT_FIELD_TYPE, 0x00000003, invUpdateMask.data);
            tempitem->setUpdateValue (OBJECT_FIELD_ENTRY, pNewChar->getItemIdBySlot(invcount), invUpdateMask.data);
            tempitem->setUpdateFloatValue (OBJECT_FIELD_SCALE_X, 1.0f, invUpdateMask.data);
            tempitem->setUpdateValue (OBJECT_FIELD_PADDING, 0xeeeeeeee, invUpdateMask.data);
            tempitem->setUpdateValue (ITEM_FIELD_OWNER, pNewChar->GetGUID().sno, invUpdateMask.data);
            tempitem->setUpdateValue (ITEM_FIELD_OWNER + 1, pNewChar->GetGUID().type, invUpdateMask.data);
            tempitem->setUpdateValue (ITEM_FIELD_CONTAINED, pNewChar->GetGUID().sno, invUpdateMask.data);
            tempitem->setUpdateValue (ITEM_FIELD_CONTAINED + 1, pNewChar->GetGUID().type, invUpdateMask.data);
            tempitem->setUpdateValue (ITEM_FIELD_STACK_COUNT, 1, invUpdateMask.data);

            tempitem->CreateObject(&invUpdateMask, itemdata, 0);
            msglist->push_front(itemdata);
            delete tempitem;
        }
    }

    NetworkPacket *data = new NetworkPacket;
    pNewChar->CreateObject(&playerMask, data, createflag);
    msglist->push_front(data);
}

//===================================================================================================================
//  Set Create Player Bits -- Sets bits required for creating a player in the updateMask.
//  Note:  Doesn't set Quest or Inventory bits
//  updateMask - the updatemask to hold the set bits
//===================================================================================================================
void ObjectMgr::SetCreatePlayerBits(UpdateMask *updateMask)
{
    // Set update mask for player creation
    // Keep the fields in the order indicated by the updatemask!
    // You dont want to end up looking like a cochroach. /Yellow
    updateMask->SetLength (PLAYER_FIELDS);
    updateMask->SetBit (OBJECT_FIELD_GUID);
    updateMask->SetBit (OBJECT_FIELD_TYPE);
    updateMask->SetBit (OBJECT_FIELD_SCALE_X);
    updateMask->SetBit (OBJECT_FIELD_PADDING);
    updateMask->SetBit (UNIT_FIELD_HEALTH);
    updateMask->SetBit (UNIT_FIELD_POWER1 );
    updateMask->SetBit (UNIT_FIELD_POWER2 );
    updateMask->SetBit (UNIT_FIELD_POWER3 );
    updateMask->SetBit (UNIT_FIELD_POWER4);
    updateMask->SetBit (UNIT_FIELD_MAXHEALTH );
    updateMask->SetBit (UNIT_FIELD_MAXPOWER1 );
    updateMask->SetBit (UNIT_FIELD_MAXPOWER2 );
    updateMask->SetBit (UNIT_FIELD_MAXPOWER3 );
    updateMask->SetBit (UNIT_FIELD_MAXPOWER4);
    updateMask->SetBit (UNIT_FIELD_LEVEL );
    updateMask->SetBit (UNIT_FIELD_FACTIONTEMPLATE );
    updateMask->SetBit (UNIT_FIELD_BYTES_0);
    updateMask->SetBit (UNIT_FIELD_FLAGS );
    updateMask->SetBit (UNIT_FIELD_BASEATTACKTIME);
    updateMask->SetBit (UNIT_FIELD_BASEATTACKTIME+1 );
    updateMask->SetBit (UNIT_FIELD_BOUNDINGRADIUS);
    updateMask->SetBit (UNIT_FIELD_COMBATREACH  );
    updateMask->SetBit (UNIT_FIELD_DISPLAYID );
    updateMask->SetBit (UNIT_FIELD_NATIVEDISPLAYID );       // NISHAVEN
    updateMask->SetBit (UNIT_FIELD_MOUNTDISPLAYID);
    updateMask->SetBit (UNIT_FIELD_MINDAMAGE);
    updateMask->SetBit (UNIT_FIELD_MAXDAMAGE);
    updateMask->SetBit (UNIT_FIELD_BYTES_1);
    updateMask->SetBit (UNIT_FIELD_STAT0 );
    updateMask->SetBit (UNIT_FIELD_STAT1);
    updateMask->SetBit (UNIT_FIELD_STAT2);
    updateMask->SetBit (UNIT_FIELD_STAT3 );
    updateMask->SetBit (UNIT_FIELD_STAT4 );
    updateMask->SetBit (UNIT_FIELD_ATTACKPOWER);
    updateMask->SetBit (PLAYER_BYTES);
    updateMask->SetBit (PLAYER_BYTES_2);
    updateMask->SetBit (PLAYER_BYTES_3);
    updateMask->SetBit (PLAYER_XP);
    updateMask->SetBit (PLAYER_NEXT_LEVEL_XP);
    updateMask->SetBit (PLAYER_REST_STATE_EXPERIENCE);
    updateMask->SetBit (PLAYER_FIELD_COINAGE );
    updateMask->SetBit (PLAYER_FIELD_POSSTAT0 );
    updateMask->SetBit (PLAYER_FIELD_POSSTAT1);
    updateMask->SetBit (PLAYER_FIELD_POSSTAT2);
    updateMask->SetBit (PLAYER_FIELD_POSSTAT3);
    updateMask->SetBit (PLAYER_FIELD_POSSTAT4);
    updateMask->SetBit (PLAYER_FIELD_NEGSTAT0);
    updateMask->SetBit (PLAYER_FIELD_NEGSTAT1);
    updateMask->SetBit (PLAYER_FIELD_NEGSTAT2);
    updateMask->SetBit (PLAYER_FIELD_NEGSTAT3);
    updateMask->SetBit (PLAYER_FIELD_NEGSTAT4);
    //    updateMask->SetBit (PLAYER_FIELD_ATTACKPOWERMODPOS);
    //    updateMask->SetBit (PLAYER_FIELD_ATTACKPOWERMODNEG);
}

void ObjectMgr::SetCreateUnitBits(UpdateMask &npcMask)
{
    npcMask.SetLength (UNIT_FIELDS);
    npcMask.SetBit (OBJECT_FIELD_GUID);
    npcMask.SetBit (OBJECT_FIELD_GUID+1);
    npcMask.SetBit (OBJECT_FIELD_TYPE);
    npcMask.SetBit (OBJECT_FIELD_ENTRY);
    npcMask.SetBit (OBJECT_FIELD_SCALE_X);
    npcMask.SetBit (UNIT_FIELD_HEALTH);
    npcMask.SetBit (UNIT_FIELD_MAXHEALTH);
    npcMask.SetBit (UNIT_FIELD_LEVEL);
    npcMask.SetBit (UNIT_FIELD_FACTIONTEMPLATE);
    npcMask.SetBit (UNIT_FIELD_FLAGS );
    npcMask.SetBit (UNIT_FIELD_BASEATTACKTIME);
    npcMask.SetBit (UNIT_FIELD_BASEATTACKTIME+1);
    npcMask.SetBit (UNIT_FIELD_BOUNDINGRADIUS);
    npcMask.SetBit (UNIT_FIELD_COMBATREACH);
    npcMask.SetBit (UNIT_FIELD_DISPLAYID);
    npcMask.SetBit (UNIT_FIELD_NATIVEDISPLAYID);
    npcMask.SetBit (UNIT_FIELD_MINDAMAGE);
    npcMask.SetBit (UNIT_FIELD_MAXDAMAGE );
    npcMask.SetBit (UNIT_NPC_FLAGS);
}

void ObjectMgr::BuildCreateUnitMsg(Unit *pNewUnit, NetworkPacket *data, Character *pPlayer)
{
    UpdateMask unitMask;
    if (!pNewUnit->isDead())
    {
        SetCreateUnitBits(unitMask);
        if (pNewUnit->CheckQuestgiverFlag(pPlayer, &unitMask, data) == 1)  return;
        pNewUnit->CreateObject(&unitMask, data, 0);
    }
}

// FIXME: REWRITE
/*
Unit * GetClosestUnit(Unit * pUnite)
{
    Unit * pUnit = NULL;
    pUnite->closest_dist = 1000;
    uint32 unitguid = pUnite->GetGUID ().sno;
    CreatureMap::iterator itr;
    for (itr = mCreatures.begin(); itr != mCreatures.end(); itr++)
    {
        if(itr->second->isAlive())
        {
            uint32 distance = (uint32)CalcDistance(pUnite, itr->second);
            if (distance < pUnite->closest_dist)
            {
                if(itr->second->GetGUID ().sno != unitguid)
                {
                    pUnit = itr->second;
                    pUnite->closest_dist = distance;
                }
            }
        }
    }
    return pUnit;
}

Character * GetClosestChar(Unit * pUnite)
{
    Character * pChar = NULL;
    pUnite->closest_dist = 1000;
    uint32 unitguid = pUnite->GetGUID ().sno;
    CharacterMap::iterator itr;
    for (itr = mCharacters.begin(); itr != mCharacters.end(); ++itr)
    {
        if(itr->second->isAlive())
        {
            uint32 distance = (uint32)CalcDistance(pUnite, itr->second);
            if (distance < pUnite->closest_dist)
            {
                if(itr->second->GetGUID ().sno != unitguid)
                {
                    pChar = itr->second;
                    pUnite->closest_dist = distance;
                }
            }
        }
    }
    return pChar;
}

*/
