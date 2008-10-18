/**
 *     \file  src/worldserver/todo/Combat.cpp
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

#include <math.h>
#include "Combat.h"
#include "Database.h"
#include "Log.h"
#include "GameClient.h"
#include "Opcodes.h"
#include "Character.h"
#include "WorldServer.h"
#include "UpdateFields.h"
#include "Stats.h"

void CombatHandler::HandleMsg (NetworkPacket & recv_data, GameClient *pClient)
{
    NetworkPacket data;
    char f[256];
    sprintf (f, "WORLD: Combat Opcode 0x%.4X from %d",
        recv_data.opcode, pClient->getCurrentChar()->GetGUID ().sno);
    LOG.outString (f);

    switch (recv_data.opcode)
    {
        case CMSG_ATTACKSWING:
        {
            guid mguid, pguid;
            pguid = pClient->getCurrentChar()->GetGUID ();
            recv_data >> mguid.sno >> mguid.type;

            // AttackSwing
            LOG.outString ("WORLD: Recvd CMSG_ATTACKSWING Message");

            Unit *pEnemy;

            if (WORLDSERVER.mCreatures.find (mguid.sno) == WORLDSERVER.mCreatures.end () ||
                ((pEnemy = WORLDSERVER.mCreatures [mguid.sno])->GetGUID ().type != mguid.type))
            {
                LOG.outString ("WORLD: Can't attack character");
                break;                                      // we do not attack PCs for now
            }

            pClient->getCurrentChar()->addStateFlag(UF_ATTACKING);
            smsg_AttackStart(pClient->getCurrentChar(), pEnemy);
        }break;

        case CMSG_ATTACKSTOP:
        {
            guid mguid = pClient->getCurrentChar()->getSelection ();
            smsg_AttackStop((Unit*)pClient->getCurrentChar(), mguid);

            pClient->getCurrentChar()->clearStateFlag(UF_ATTACKING);
            //            pClient->getCurrentChar()->removeUnitFlag(0x00080000);
        }break;
    }
}

//================================================================================================
//  AttackerStateUpdate
//  This function determines whether there is a hit, and the resultant damage
//================================================================================================
void CombatHandler::AttackerStateUpdate(Unit *pAttacker, Unit *pVictim, uint32 damage)
{
    if (pVictim->getUpdateValue(UNIT_FIELD_HEALTH) == 0 ||
        pAttacker->getUpdateValue(UNIT_FIELD_HEALTH) == 0)
        return;
    NetworkPacket data;
    uint32 absorb = 0;
    uint32 shield = 0;
    uint32 mana_dmg = 0;
    uint32 critiq = 0;
    uint32 hit_status = 0xe2;
    if (damage == 0)
    {
        damage = CalculateDamage(pAttacker);
        //printf("Damage changed to %u\n", damage);
    }                                                       // get absorb/shield stuff

    if (pAttacker->GetGUID ().type == 0)                    //if player
    {
        uint8 agi = pAttacker->getUpdateValue(UNIT_FIELD_STAT1);
        if (rand()%(agi) > (rand()%pAttacker->getLevel()+agi/2)) critiq = pAttacker->getLevel()/2+1;
        //printf("Critical changed to %u\n", critiq);
    }
    if (pVictim->m_absorb == 1)
    {
        //printf("ok we will absorb some dmg\n");
        SpellInformation spellInfo;
                                                            //get a hook for the DB
        DatabaseInterface *dbi = DATABASE.createDatabaseInterface();
                                                            //returns a SpellInformation object/struct
        spellInfo = dbi->GetSpellInformation (pVictim->m_absorbspell);
        absorb = spellInfo.DmgPlus1;
        DATABASE.removeDatabaseInterface (dbi);             //clean up used resources
    }
    if (pVictim->m_shield == 1)
    {
        //printf("ok we will shield some dmg\n");
        SpellInformation spellInfo;
                                                            //get a hook for the DB
        DatabaseInterface *dbi = DATABASE.createDatabaseInterface();
                                                            //returns a SpellInformation object/struct
        spellInfo = dbi->GetSpellInformation (pVictim->m_shieldspell);
        shield = spellInfo.DmgPlus1;
        DATABASE.removeDatabaseInterface (dbi);             //clean up used resources
    }
    //START OF LINA
    if (pVictim->getUpdateValue(UNIT_FIELD_RESISTANCES)>0)
    {
        uint32 armor=pVictim->getUpdateValue(UNIT_FIELD_RESISTANCES);
        absorb += armor;
        //printf("Armor: %u\n", armor);
    }
    //END OF LINA

    // absorb damage if damage absorb is activated
    uint32 absorbed=0;
    if (absorb > 0)
    {
        absorbed = (uint32)((float)damage/float(100)*(float(100)-(float)absorb));
        if(absorbed > damage)                               //if armor absorbe all damage
        {
            absorb = damage-1;                              //absorb all - 1
            absorbed = 1;                                   //set receive damage to 1
        }
        else
        {
            absorb = damage-absorbed;                       //set absorb to the correct value
        }
    }
    else                                                    //if no armor
    {
        absorbed=damage;                                    //give full damage to user
    }

    /*
     // absorb damage if damage absorb is activated
     uint32 absorbed = (float)damage/float(100)*(float(100)-(float)absorb);
     absorb = absorbed-damage;
     if(absorbed > damage)
     absorbed = 1;
     if(absorb < 0)
     absorb = 0;
     */

    // use mana shield if activated
    if(pVictim->m_shield)
    {
        uint32 mana = pVictim->getUpdateValue(UNIT_FIELD_POWER1);
        if(mana < shield)
            shield = pVictim->getUpdateValue(UNIT_FIELD_POWER1);

        if(absorbed-shield > absorbed)
        {                                                   // happens if shield is bigger then absorbed and that would make a char unplayable
            mana_dmg = absorbed-1;
            absorbed = 1;
            absorb = mana_dmg;
            //printf("#1 mana_dmg is %u and absorbed is %u\n", mana_dmg,absorbed);
        }
        else
        {
            absorbed = absorbed-shield;
            mana_dmg = shield;
            absorb = mana_dmg;
            //printf("#2 mana_dmg is %u and absorbed is %u\n", mana_dmg,absorbed);
        }
                                                            // if mana_dmg is >0 then absorb it or leave it as it is
        pVictim->setUpdateValue(UNIT_FIELD_POWER1,mana-mana_dmg);
    }

    uint32 some_value = 0xffffffff;
    some_value = 0x0;

    data.Clear();
    data.Initialize(61, SMSG_ATTACKERSTATEUPDATE);
    data.WriteData (hit_status);                            // Attack flags
    data.WriteData (pAttacker->GetGUID ().sno);
    data.WriteData (pAttacker->GetGUID ().type);
    data.WriteData (pVictim->GetGUID ().sno);
    data.WriteData (pVictim->GetGUID ().type);
    data.WriteData (absorbed);                              // damage
    data.WriteData (uint8 (1));                             // Damage type counter
    // for each...
    data.WriteData (uint32 (0));                            // Damage type, // 0 - white font, 1 - yellow
    data.WriteData (uint32 (0x0));                          // damage float
    data.WriteData (damage);                                // Damage amount damage
    data.WriteData (absorb);                                // damage absorbed

    data.WriteData (uint32(1));                             // new victim state
    data.WriteData (uint32(0));                             // victim round duration
    data.WriteData (uint32(0));                             // additional spell damage amount
    data.WriteData (uint32(0));                             // additional spell damage id
    data.WriteData (shield);                                // Damage amount blocked

    pAttacker->SendMessageToSet (&data, true);
    //printf("AttackerStateUpdate:  %u attacked %u for %u dmg-%u absorb=%u absorbed (shield %u).\n",
    //       pAttacker->GetGUID(), pVictim->GetGUID(), damage, absorb, absorbed, shield);
    DealDamage (pAttacker, pVictim, absorbed);
}

void CombatHandler::smsg_AttackStop (Unit* pAttacker, guid victim_guid)
{
    guid attacker_guid;
    attacker_guid = pAttacker->GetGUID ();
    NetworkPacket data;
    data.Initialize (20, SMSG_ATTACKSTOP);
    data << attacker_guid.sno << attacker_guid.type << victim_guid.sno << victim_guid.type << uint32 (0);
    //    WORLDSERVER.SendUnitAreaMessage(&data, pAttacker);
    pAttacker->SendMessageToSet (&data, true);
    printf("%08x stopped attacking %d\n", attacker_guid.sno, victim_guid.sno);

    if (pAttacker->getUpdateValue (UNIT_FIELD_SUMMONEDBY) != 0)
        pAttacker->m_creatureState = STOPPED;
}

void CombatHandler::smsg_AttackStart(Unit* pAttacker, Unit* pVictim)
{
    // check if victim is close to attacker
    float dx, dy, dz, length, reach, radius;

    dx = pVictim->getPositionX() - pAttacker->getPositionX();
    dy = pVictim->getPositionY() - pAttacker->getPositionY();
    dz = pVictim->getPositionZ() - pAttacker->getPositionZ();
    length = sqrt((dx*dx) + (dy*dy) + (dz*dz));             //distance between you and mob
    radius = pVictim->getUpdateFloatValue(UNIT_FIELD_BOUNDINGRADIUS);
    reach = pAttacker->getUpdateFloatValue(UNIT_FIELD_COMBATREACH);

    if (length < reach + radius)
    {
        // Prevent user from ignoring attack speed and stopping and start combat really really fast
        if (pAttacker->isAttackReady())
        {
            AttackerStateUpdate(pAttacker, pVictim, 0);
            pAttacker->setAttackTimer();
        }

        // Send out ATTACKSTART
        NetworkPacket data;
        data.Clear();
        data.Initialize (16, SMSG_ATTACKSTART);
        data << pAttacker->GetGUID ().sno << pAttacker->GetGUID ().type <<
            pVictim->GetGUID ().sno << pVictim->GetGUID ().type;
        //    WORLDSERVER.SendUnitAreaMessage(&data, pAttacker);  //probably global
        pAttacker->SendMessageToSet(&data, true);
        LOG.outString ("WORLD: Sent SMSG_ATTACKSTART");
    }
    else
    {
        pAttacker->clearStateFlag(UF_ATTACKING);
    }

    // FLAGS changed so other players see attack animation
    //    pAttacker->addUnitFlag(0x00080000);
    //    pAttacker->setUpdateMaskBit(UNIT_FIELD_FLAGS);
}

void CombatHandler::DealDamage(Unit *pAttacker, Unit *pVictim, uint32 damage)
{
    Unit * pPetMaster;

    uint32 health = pVictim->getUpdateValue(UNIT_FIELD_HEALTH);
    if (health <= damage)
    {
        //printf("ok now he is dead\n");

        pVictim->generateLoot();
        // victim died!
        pVictim->setDeathState(JUST_DIED);

        // Send SMSG_PARTYKILLLOG 0x1e6
        // To everyone in the party?

        // SMSG_ATTACKSTOP
        guid aguid, vguid;
        aguid = pAttacker->GetGUID ();
        vguid = pVictim->GetGUID ();
        smsg_AttackStop (pVictim, aguid);

        // Send MSG_MOVE_ROOT   0xe7

        // Set update values... try flags 917504
        // health
        pVictim->setUpdateValue(UNIT_FIELD_HEALTH, 0);

        // then another update message, sets health to 0, maxhealth to 100, and dynamic flags
        pVictim->setUpdateValue(UNIT_FIELD_HEALTH, 0);
        pVictim->setUpdateMaskBit(UNIT_FIELD_MAXHEALTH);
        pVictim->removeUnitFlag(0x00080000);

        if (!pVictim->isPlayer())
            pVictim->setUpdateValue(UNIT_DYNAMIC_FLAGS, 1);

        //LINA
        if (pAttacker->isPet())                             //if pet kill someone, give xp to summoner
        {
            //printf("It's a PET, master %u!\n", pAttacker->getUpdateValue(UNIT_FIELD_SUMMONEDBY));
            pPetMaster = WORLDSERVER.GetCharacter (pAttacker->getUpdateValue(UNIT_FIELD_SUMMONEDBY));
            if(!pPetMaster)
            {
                pPetMaster=pAttacker;
            }

            smsg_AttackStop(pAttacker, vguid);
            pAttacker->removeUnitFlag(0x00080000);
            pAttacker->setUpdateMaskBit(UNIT_FIELD_FLAGS);
            pAttacker->addStateFlag(UF_TARGET_DIED);
        }
        else
            pPetMaster=pAttacker;

        if (pPetMaster->isPlayer ())
        {
            uint32 xp = CalculateXpToGive(pVictim, pPetMaster);

            // check running quests in case this monster belongs to it
            uint32 entry = 0;
            if (!pVictim->isPlayer ())
                entry = pVictim->getUpdateValue (OBJECT_FIELD_ENTRY);

            // Is this player part of a group?
            Group *pGroup = WORLDSERVER.GetGroupByLeader(((Character*)pPetMaster)->GetGroupLeader());
            if (pGroup)
            {
                xp /= pGroup->count;
                for (uint32 c=0; c < pGroup->count; c++)
                {
                    Character *pGroupGuy = WORLDSERVER.mCharacters[pGroup->members[c].guid];
                    pGroupGuy->GiveXP (xp, pVictim->GetGUID ());

                    if (!pVictim->isPlayer())
                        pGroupGuy->KilledMonster (entry, pVictim->GetGUID());
                }
            }
            else
            {
                // update experience
                ((Character*)pPetMaster)->GiveXP (xp, pVictim->GetGUID());

                if (!pVictim->isPlayer())
                    ((Character*)pPetMaster)->KilledMonster(entry, pVictim->GetGUID());
            }
        }
        else
        {
            smsg_AttackStop(pAttacker, vguid);
            pAttacker->removeUnitFlag(0x00080000);
            pAttacker->setUpdateMaskBit(UNIT_FIELD_FLAGS);
            pAttacker->addStateFlag(UF_TARGET_DIED);

            //LINA
            if (pVictim->isPet())                           //if npc kill a pet, attack summoner
            {
                pPetMaster = WORLDSERVER.GetCharacter (pVictim->getUpdateValue(UNIT_FIELD_SUMMONEDBY));
                if(pPetMaster)
                {
                    pAttacker->AI_ChangeState(ATTACKING);   // when attacked mobs stop moving around
                    pAttacker->AI_AttackReaction(pPetMaster, damage);
                }
            }
        }
    }
    else
    {
        pVictim->setUpdateValue(UNIT_FIELD_HEALTH , health - damage);

        // <WoW Chile Dev Team> Start Change
        // this need alot of work.

        ///////////////// PET ATTACK THE ONE WHO ATTACKS ITS MASTER by nothin/////////
        if(pVictim->isPlayer())
        {
            if(pVictim->getUpdateValue(UNIT_FIELD_SUMMON) != 0)
            {
                petGUID = pVictim->getUpdateValue(UNIT_FIELD_SUMMON);
                Unit * pPet=WORLDSERVER.GetCreature(petGUID);
                if(pPet)
                {
                    if(pPet->m_pet_state != 0)
                    {
                        pPet->AI_ChangeState(ATTACKING);
                        pPet->AI_AttackReaction(pAttacker, damage);
                    }
                }
            }
        }
        /////////////////////////////////////////////////////////////////////////////
        else
        {
            pVictim->AI_ChangeState(ATTACKING);             // when attacked mobs stop moving around
            pVictim->AI_AttackReaction(pAttacker, damage);
            /*
             //uint32 max_health = getUpdateValue(UNIT_FIELD_MAXHEALTH);
             //uint32 health_porcent = (max_health*10)/100; // this if for know 10% of total healt,need changes about mobs lvls
             pVictim->AI_ChangeState(3); //if mob are attack then they stop moving around
             pVictim->AI_AttackReaction(pAttacker, damage);

             //well mobs scape if have a movement assignet atm
             //if(health<=health_porcent)
             {}
             */

        }
        // <WoW Chile Dev Team> Start Change
    }
}

void CombatHandler::Heal(Unit *pAttacker, Unit *pVictim, uint32 damage)
{
    uint32 health = pVictim->getUpdateValue(UNIT_FIELD_HEALTH);
    if (health <= damage)
    {
        pVictim->generateLoot();
        // victim died!
        pVictim->setDeathState(JUST_DIED);

        // Send SMSG_PARTYKILLLOG 0x1e6
        // To everyone in the party?

        // SMSG_ATTACKSTOP
        guid aguid, vguid;
        aguid = pAttacker->GetGUID ();
        vguid = pVictim->GetGUID ();
        smsg_AttackStop (pVictim, aguid);

        // Send MSG_MOVE_ROOT   0xe7

        // Set update values... try flags 917504
        // health
        pVictim->setUpdateValue(UNIT_FIELD_HEALTH, 0);

        // then another update message, sets health to 0, maxhealth to 100, and dynamic flags
        pVictim->setUpdateValue(UNIT_FIELD_HEALTH, 0);
        pVictim->setUpdateMaskBit(UNIT_FIELD_MAXHEALTH);
        pVictim->removeUnitFlag(0x00080000);

        if (!pVictim->isPlayer())
            pVictim->setUpdateValue(UNIT_DYNAMIC_FLAGS, 1);

        if (pAttacker->isPlayer())
        {
            uint32 xp = CalculateXpToGive(pVictim, pAttacker);

            // check running quests in case this monster belongs to it
            uint32 entry = pVictim->getUpdateValue(OBJECT_FIELD_ENTRY);

            // Is this player part of a group?
            Group *pGroup = WORLDSERVER.GetGroupByLeader(((Character*)pAttacker)->GetGroupLeader());
            if (pGroup)
            {
                xp /= pGroup->count;
                for (uint32 c=0; c < pGroup->count; c++)
                {
                    Character *pGroupGuy = WORLDSERVER.mCharacters[pGroup->members[c].guid];
                    pGroupGuy->GiveXP(xp, pVictim->GetGUID ());
                    pGroupGuy->KilledMonster(entry, pVictim->GetGUID ());
                }
            }
            else
            {
                // update experience
                ((Character*)pAttacker)->GiveXP(xp, pVictim->GetGUID ());
                ((Character*)pAttacker)->KilledMonster(entry, pVictim->GetGUID ());
            }
        }
        else
        {
            smsg_AttackStop(pAttacker, vguid);
            pAttacker->removeUnitFlag(0x00080000);
            pAttacker->setUpdateMaskBit(UNIT_FIELD_FLAGS);
            pAttacker->addStateFlag(UF_TARGET_DIED);
        }
    }
    else
    {
        pVictim->setUpdateValue(UNIT_FIELD_HEALTH , health + damage);

    }
}
