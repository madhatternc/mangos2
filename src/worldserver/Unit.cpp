/**
 *     \file  src/worldserver/Unit.cpp
 *    \brief  Provides basic Unit functions.
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

#include "Unit.h"
#include "Affect.h"
#include "Opcodes.h"
#include "Debug.h"

#define RAD2DEG(x)  (x * (180.0 / M_PI))

IMPLEMENT_VECTOR (Affect::, ModifierVector, Modifier *)
IMPLEMENT_VECTOR (Unit::, AffectVector, Affect *)

Unit::Unit () : Object (), AttackTimer (0), Attackers (0, 16),
    Affects (0, 16)
{
    TempAffect = NULL;
    Aura = NULL;
    AuraCheck = 2000;
    CurrentSpell = NULL;
    Silenced = false;
    MeleeSpell = false;
    AddDmgOnce = 0;
    TotemSlot1 = TotemSlot2 = TotemSlot3 = TotemSlot4 = 0;
    TriggerSpell = 0;
    TriggerDamage = 0;
    DeathState = ALIVE;

    Field.SetLength (UNIT_END);
    Field.Clear (OBJECT_END, UNIT_END - OBJECT_END);
    Field.SetBits (OBJECT_FIELD_TYPE, TYPE_UNIT, TYPE_UNIT);
}

Unit::~Unit()
{
}

void Unit::Update (uint32 iDeltaMs)
{
    Object::Update (iDeltaMs);

    UpdateSpells (iDeltaMs);

    if (AttackTimer.Enabled ())
    {
        if (AttackTimer.Tick (iDeltaMs))
            AttackTimer.Disable ();
    }
}

bool Unit::CanReachWithAttack (Unit *iVictim) const
{
    float reach = Field.GetF32 (UNIT_FIELD_COMBATREACH);
    float radius = Field.GetF32 (UNIT_FIELD_BOUNDINGRADIUS);

    if (GetDistanceSq (iVictim) > Square <float> (reach + radius))
        return false;

    return true;
}

void Unit::GiveXP (uint32 iXP, Unit *iVictim, bool iGroup)
{
    // for now, do nothing -- Player will have its own overrided method
}

void Unit::ReceiveDamage (Unit *iAttacker, uint32 iDamage)
{
    uint32 Health = Field.GetU32 (UNIT_FIELD_HEALTH);

    if (Health > iDamage)
    {
        Field.SetU32 (UNIT_FIELD_HEALTH, Health - iDamage);

#if 0
        // This logic will go to corresponding class: Creature or Player
        // Every unit type has its own rules how to decide how to answer
        // when somebody hurts him.

        // this need alot of work.
        if ((World->GameFeatures & GF_PLAYER_AUTOATTACK)
         || !(GetType () & TYPE_PLAYER))
        {
            ((Creature*)iVictim)->AI_ChangeState(ATTACKING); // when attacked mobs stop moving around
            ((Creature*)iVictim)->AI_AttackReaction(this, damage);
            /*
             //uint32 max_health = Field.GetU32(UNIT_FIELD_MAXHEALTH);
             //uint32 health_porcent = (max_health*10)/100; // this if for know 10% of total healt,need changes about mobs lvls
             iVictim->AI_ChangeState(3); //if mob are attack then they stop moving around
             iVictim->AI_AttackReaction(pAttacker, damage);

             //well mobs scape if have a movement assignet atm
             //if(health<=health_porcent)
             {}
             */
        }
#endif
    }
    else // Oh well, we're killed
    {
        // Put something in our pockets if they're empty
        GenerateLoot ();
        if (!(GetType () & TYPE_PLAYER))
            Field.SetBits (UNIT_DYNAMIC_FLAGS, UDF_LOOTABLE, UDF_LOOTABLE);

        // Set our health to 0
        Field.SetU32 (UNIT_FIELD_HEALTH, 0);
        // Drop combat mode and set the 'dead' flag
        Field.SetBits (UNIT_FIELD_FLAGS, UFF_IN_COMBAT | UFF_DEAD, UFF_DEAD);

        // Remove the effect of all items & spells from the victim
//@@@       RemoveAllAffects ();

        SetDeathState (JUST_DIED);
    }
}

void Unit::SpellNonMeleeDamageLog (Unit *iVictim, uint32 iSpellId, uint32 iDamage)
{
    //@@@todo is this really required?
    //if (!IsAlive () || !iVictim->isAlive ())
    //  return;

    DEBUG_PRINTF ("%X:%u attacked %X:%u for %u damage with spell %u",
             GetHighGUID (), GetLowGUID (), iVictim->GetHighGUID (),
             iVictim->GetLowGUID (), iDamage, iSpellId);

    SMSG_SPELLNONMELEEDAMAGELOG_t *outpkt = SMSG_SPELLNONMELEEDAMAGELOG_t::Create ();
    outpkt->Victim = iVictim->GetGUID ();
    outpkt->Attacker = GetGUID ();
    outpkt->SpellId = iSpellId;
    outpkt->Damage = iDamage;
    outpkt->Assemble ();

    SendToSet (outpkt, true);
    DealDamage (iVictim, iDamage);
}

void Unit::PeriodicAuraLog (Unit *iVictim, uint32 iSpellId, uint32 iDamage, uint32 iDamageType)
{
    //@@@todo is this really required?
    //if (!IsAlive () || !iVictim->isAlive ())
    //  return;

    DEBUG_PRINTF ("PeriodicAuraLog: %X:%u attacked %X:%u for %u damage with spell %u",
             GetHighGUID (), GetLowGUID (), iVictim->GetHighGUID (),
             iVictim->GetLowGUID (), iDamage, iSpellId);

    SMSG_PERIODICAURALOG_t *outpkt = SMSG_PERIODICAURALOG_t::Create ();
    outpkt->Victim = iVictim->GetGUID ();
    outpkt->Attacker = GetGUID ();
    outpkt->SpellId = iSpellId;
    outpkt->TargetCount = 1;
    //outpkt->DamageType = iDamageType;
    outpkt->Damage = iDamage;
    outpkt->Assemble ();

    SendToSet (outpkt, true);
    DealDamage (iVictim, iDamage);
}

void Unit::AttackerStateUpdate (Unit *iVictim, uint32 iDamage, bool DoT)
{
    uint32 hit_status = 0xe2;
    uint32 damageType = 0;

    DEBUG_PRINTF ("%X:%u attacked %X:%u for %u damage",
                  GetHighGUID (), GetLowGUID (),
                  iVictim->GetLowGUID (), iVictim->GetHighGUID(), iDamage);

    if (!iDamage)
        //@@@@@@@@todo: highly temporary
        iDamage = 10;//CalculateDamage (this);
    else
        damageType = 1;

    if (DoT)
        hit_status = 0;

    // if we are currently casting a melee spell then finish it now
#if 0
    if (MeleeSpell)
    {
        if (CurrentSpell->getState () == SPELL_STATE_IDLE)
        {
            spell = m_currentSpell->m_spellInfo->Id;
            m_currentSpell->SendCastResult(0);
            m_currentSpell->SendSpellGo();
            for(uint32 i=0;i<2;i++)
                m_currentSpell->HandleEffects(m_currentSpell->m_targets.m_unitTarget,i);
            m_currentSpell->finish();
        }
    }
#endif

    SMSG_ATTACKERSTATEUPDATE_t *outpkt = SMSG_ATTACKERSTATEUPDATE_t::Create ();
    outpkt->AttackFlags = hit_status;
    outpkt->Attacker = GetGUID ();
    outpkt->Victim = iVictim->GetGUID ();
    outpkt->TotalDamage = iDamage;
    outpkt->Count = 1;
    DamageInfo *di = new DamageInfo ();
    di->Type = damageType;
    di->Float = 0;
    di->Damage = iDamage;
    di->Absorbed = 0;
    di->VictimState = 1;
    di->RoundDuration = 0;
    di->AdditionalSpellDamage = 0;
    di->AdditionalSpellId = 0;
    di->AdditionalSpellAbsorbed = 0;
    outpkt->DamageList.Push (di);

    SendToSet (outpkt, true);
    DealDamage (iVictim, iDamage);
}

void Unit::AttackStart (Unit *iVictim)
{
    // Prevent user from ignoring attack speed and stopping
    // and start combat really really fast
    if (IsAttackReady () && CanReachWithAttack (iVictim))
    {
        AttackerStateUpdate (iVictim, 0, false);
        SetAttackTimer ();
    }

    DEBUG_PRINTF ("%X:%u attacked %X:%u",
                  GetHighGUID (), GetLowGUID (),
                  iVictim->GetHighGUID (), iVictim->GetLowGUID ());

    // Send out ATTACKSTART
    SMSG_ATTACKSTART_t *outpkt = SMSG_ATTACKSTART_t::Create ();
    outpkt->Attacker = GetGUID ();
    outpkt->Victim = iVictim->GetGUID ();

    SendToSet (outpkt, true);

    // FLAGS changed so other players see attack animation
    //    addUnitFlag (0x00080000);
    //    setUpdateMaskBit (UNIT_FIELD_FLAGS);
}

void Unit::AttackStop (uint64 iVictimGuid)
{
    DEBUG_PRINTF ("%X:%u stopped attacking %X:%u",
                  GetHighGUID (), GetLowGUID (),
                  uint32 (iVictimGuid >> 32), uint32 (iVictimGuid));

    Field.SetBits (UNIT_FIELD_FLAGS, UFF_IN_COMBAT, 0);

    SMSG_ATTACKSTOP_t *outpkt = SMSG_ATTACKSTOP_t::Create ();
    outpkt->Attacker = GetGUID ();
    outpkt->Victim = iVictimGuid;

    SendToSet (outpkt, true);
}

bool Unit::AddAffect (Affect *iAff, bool iUniq)
{
#if 0
    int i;

    DEBUG_PRINTF ("adding affect");

    for (i = 0; i < Affects.Length (); i++)
        ;

    for (i = m_affects.begin(); i != m_affects.end(); i++)
    {
        if ((*i)->GetSpellId() == aff->GetSpellId() &&
            (uniq || (*i)->GetCasterGUID() == aff->GetCasterGUID()))
        {
            break;
        }
    }

    if (i != m_affects.end())
    {
        if(i != 0)
            (*i)->SetDuration(0);
        Log::getSingleton().outDetail("Unit::AddAffect() - overwriting Affect");
    }

    m_affects.push_back(aff);

    for (Affect::ModList::const_iterator j = aff->GetModList().begin();
         j != aff->GetModList().end(); j++)
    {
        ApplyModifier(&(*j), true, aff);
    }

    _AddAura(aff);

    Log::getSingleton().outDetail("Unit::AddAffect() - affect added");

    return true;
#endif
        return false;
}

void Unit::RemoveAffect (Affect *aff)
{
    int aid = Affects.Find(aff);
    if(aid == -1)
            return;

    if(aff->CoAffect != 0)
        RemoveAffect(aff->CoAffect);

        // Remove all modifiers of this affect
    for (int i = 0; i < aff->Modifiers.Length(); i++) {
        ApplyModifier(aff->Modifiers.Get(i), false, aff);
    }

    //_RemoveAura(aff);

    Affects.Delete(aid);
}

void Unit::RemoveAffectById(uint32 spellId)
{
#if 0
    if(AuraSlot != NULL)
        if(m_aura->GetId() == spellId){
            Aurasl = NULL;
            return;
        }

    Affect* aff = FindAff(spellId);
    if(aff)
        aff->SetDuration(0);
#endif
}
#if 0

bool Unit::SetAffDuration(uint32 spellId,Unit* caster,uint32 duration)
{
    Affects::iterator i;

    for (i = m_affects.begin(); i != m_affects.end(); i++)
    {
        if ((*i)->GetId() == spellId && (*i)->GetCasterGUID() == caster->GetGUID()){
            (*i)->SetDuration(duration);
            return true;
        }
    }
    return false;
}
#endif

bool Unit::RemoveAffect(uint32 spellId)
{
#if 0
    Affects::iterator i, next;
    Affect *aff;
    bool result = false;

    for (i = m_affects.begin(); i != m_affects.end(); i = next)
    {
        next = i;
        next++;

        aff = *i;

        if (aff->GetSpellId() == spellId)
        {
            for (Affect::ModList::const_iterator j = aff->GetModList().begin();
                 j != aff->GetModList().end(); i++)
            {
                ApplyModifier(&(*j), false, aff);
            }

            _RemoveAura(aff);

            m_affects.erase(i);

            delete aff;

            result = true;
        }
    }

    return result;
#endif
    return false;
}

void Unit::RemoveAllAffects()
{
#if 0
    for (int i = Affects.Length () - 1; i >= 0; i--)
    {
        Affect *aff = (Affect *)Affects.Get (i);

        for (int j = 0; j < aff->Modifiers.Length (); j++)
            ApplyModifier(aff->Modifiers.Get (j), false, aff);

        RemoveAura (aff);
        Affects.Delete (i);
    }

    return;
#endif
}


void Unit::ApplyAllAffectMods (bool iApply)
{
#if 0
    Affects::iterator i;
    Affect::ModList::const_iterator j;

    Affect *aff;

    for (i = m_affects.begin(); i != m_affects.end(); i++)
    {
        aff = *i;

        for (j = aff->GetModList().begin();
             j != aff->GetModList().end(); j++)
        {
            ApplyModifier(&(*j), true, aff);
        }

        _AddAura(aff);
    }
#endif
}


void Unit::ApplyModifier (Modifier *iMod, bool iApply, Affect *iParent)
{
#if 0
    WorldPacket data;
    switch(mod->GetType())
    {
        case SPELL_AURA_NONE:
            {
            }break;
        case SPELL_AURA_BIND_SIGHT:
            {
            }break;
        case SPELL_AURA_MOD_THREAT:
            {
            }break;
        case SPELL_AURA_AURAS_VISIBLE:
            {
            }break;
        case SPELL_AURA_MOD_RESISTANCE_PCT:
            {
            }break;
        case SPELL_AURA_MOD_CREATURE_ATTACK_POWER:
            {
            }break;
        case SPELL_AURA_MOD_TOTAL_THREAT:
            {
            }break;
        case SPELL_AURA_WATER_WALK:
            {
                apply ?
               data.Initialize(SMSG_MOVE_WATER_WALK)
               : data.Initialize(SMSG_MOVE_LAND_WALK);
                data << GetGUID();
                SendToSet(&data,true);
            }break;
        case SPELL_AURA_FEATHER_FALL:
            {
                apply ?
               data.Initialize(SMSG_MOVE_FEATHER_FALL)
               : data.Initialize(SMSG_MOVE_NORMAL_FALL);
                data << GetGUID();
                SendToSet(&data,true);
            }break;
        case SPELL_AURA_HOVER:
            {
            }break;
        case SPELL_AURA_ADD_FLAT_MODIFIER:
            {
            }break;
        case SPELL_AURA_ADD_PCT_MODIFIER:
            {
            }break;
        case SPELL_AURA_ADD_TARGET_TRIGGER:
            {
            }break;
        case SPELL_AURA_MOD_TAUNT:
            {
            }break;
        case SPELL_AURA_MOD_POWER_REGEN_PERCENT:
            {
            }break;
        case SPELL_AURA_ADD_CASTER_HIT_TRIGGER:
            {
            }break;
        case SPELL_AURA_OVERRIDE_CLASS_SCRIPTS:
            {
            }break;
        case SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN:
            {
            }break;
        case SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT:
            {
            }break;
        case SPELL_AURA_MOD_HEALING:
            {
            }break;
        case SPELL_AURA_IGNORE_REGEN_INTERRUPT:
            {
            }break;
        case SPELL_AURA_MOD_MECHANIC_RESISTANCE:
            {
            }break;
        case SPELL_AURA_MOD_HEALING_PCT:
            {
            }break;
        case SPELL_AURA_SHARE_PET_TRACKING:
            {
            }break;
        case SPELL_AURA_MOD_STUN:
            {
            }break;
        case SPELL_AURA_UNTRACKABLE:
            {
            }break;
        case SPELL_AURA_EMPATHY:
            {
            }break;
        case SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT:
            {
            }break;
        case SPELL_AURA_MOD_POWER_COST_PCT:
            {
            }break;
        case SPELL_AURA_MOD_RANGED_ATTACK_POWER:
            {
            }break;
        case SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN:
            {
            }break;
        case SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT:
            {
            }break;
        case SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS:
            {
            }break;
        case SPELL_AURA_MOD_POSSESS_PET:
            {
            }break;
        case SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS:
            {
                data.Initialize(MSG_MOVE_SET_RUN_SPEED);
                data << GetGUID();
                apply ? data << float(7.5+7.5/100*mod->GetAmount()) : data << float(7.5);
                SendToSet(&data,true);
            }break;
        case SPELL_AURA_MOD_DAMAGE_DONE:
            {
            }break;
        case SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS:
            {
            }break;
        case SPELL_AURA_MOD_CREATURE_RANGED_ATTACK_POWER:
            {
            }break;
        case SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT:
            {
                uint32 percent = mod->GetAmount();
                uint32 current = Field.GetU32(UNIT_FIELD_POWER4);
                apply ? Field.SetU32(UNIT_FIELD_POWER4,current+current/100*percent) : Field.SetU32(UNIT_FIELD_POWER4,current-current/(100+percent)*100);
            }break;
        case SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT:
            {
                uint32 percent = mod->GetAmount();
                uint32 current = Field.GetU32(UNIT_FIELD_MAXHEALTH);
                apply ? Field.SetU32(UNIT_FIELD_MAXHEALTH,current+current/100*percent) : Field.SetU32(UNIT_FIELD_MAXHEALTH,current-current/(100+percent)*100);
            }break;
        case SPELL_AURA_MOD_MANA_REGEN_INTERRUPT:
            {
            }break;
        case SPELL_AURA_MOD_HEALING_DONE:
            {
            }break;
        case SPELL_AURA_MOD_HEALING_DONE_PERCENT:
            {
            }break;
        case SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE:
            {
            }break;
        case SPELL_AURA_MOD_HASTE:
            {
            }break;
        case SPELL_AURA_FORCE_REACTION:
            {
            }break;
        case SPELL_AURA_MOD_DAMAGE_TAKEN:
            {
            }break;
        case SPELL_AURA_MOD_RANGED_HASTE:
            {
            }break;
        case SPELL_AURA_MOD_RANGED_AMMO_HASTE:
            {
            }break;
        case SPELL_AURA_MOD_BASE_RESISTANCE_PCT:
            {
            }break;
        case SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE:
            {
            }break;
        case SPELL_AURA_SAFE_FALL:
            {
                apply ? data.Initialize(SMSG_MOVE_FEATHER_FALL) : data.Initialize(SMSG_MOVE_NORMAL_FALL);
                data << GetGUID();
                SendToSet(&data,true);
            }break;
        case SPELL_AURA_CHARISMA:
            {
            }break;
        case SPELL_AURA_PERSUADED:
            {
            }break;
        case SPELL_AURA_ADD_CREATURE_IMMUNITY:
            {
            }break;
        case SPELL_AURA_RETAIN_COMBO_POINTS:
            {
            }break;
        case SPELL_AURA_DAMAGE_SHIELD:
            {
            }break;
        case SPELL_AURA_MOD_STEALTH:
            {
            }break;
        case SPELL_AURA_MOD_DETECT:
            {
            }break;
        case SPELL_AURA_MOD_INVISIBILITY:
            {
            }break;
        case SPELL_AURA_MOD_INVISIBILITY_DETECTION:
            {
            }break;
        case SPELL_AURA_MOD_POSSESS:
            {
            }break;
        case SPELL_AURA_MOD_RESISTANCE:
            {
                uint16 index = 0;
                uint16 index2 = 0;
                switch(mod->GetMiscValue())
                {
                    case 0:{
                        index = UNIT_FIELD_RESISTANCES;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE : index2 = PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE;
                    }break;
                    case 1:{
                        index = UNIT_FIELD_RESISTANCES+1;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+1 : index2 = PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+1;
                    }break;
                    case 2:{
                        index = UNIT_FIELD_RESISTANCES+2;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+2 : index2 = PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+2;
                    }break;
                    case 3:{
                        index = UNIT_FIELD_RESISTANCES+3;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+3 : index2 = PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+3;
                    }break;
                    case 4:{
                        index = UNIT_FIELD_RESISTANCES+4;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+4 : index2 = PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+4;
                    }break;
                    case 5:{
                        index = UNIT_FIELD_RESISTANCES+5;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+5 : index2 = PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+5;
                    }break;
                    default:{
                        printf("WARNING: Misc Value for SPELL_AURA_MOD_STAT not valid\n");
                        return;
                    }break;
                }

                if(apply){
                    Field.SetU32(index,Field.GetU32(index)+mod->GetAmount());
                    if(GetTypeId() == TYPEID_PLAYER)
                        Field.SetU32(index2,Field.GetU32(index2)+mod->GetAmount());
                }else{
                    Field.SetU32(index,Field.GetU32(index)-mod->GetAmount());
                    if(GetTypeId() == TYPEID_PLAYER)
                        Field.SetU32(index2,Field.GetU32(index2)-mod->GetAmount());
                }
            }break;
        case SPELL_AURA_PERIODIC_TRIGGER_SPELL:
            {
            }break;
        case SPELL_AURA_PERIODIC_ENERGIZE:
            {
            }break;
        case SPELL_AURA_MOD_PACIFY:
            {
            }break;
        case SPELL_AURA_MOD_ROOT:
            {
                apply ?
               data.Initialize(MSG_MOVE_ROOT)
               : data.Initialize(MSG_MOVE_UNROOT);
                data << GetGUID();
                SendToSet(&data,true);
            }break;
        case SPELL_AURA_MOD_SILENCE:
            {
                apply ? m_silenced = true : m_silenced = false;
            }break;
        case SPELL_AURA_REFLECT_SPELLS:
            {
            }break;
        case SPELL_AURA_MOD_STAT:
            {
                uint16 index = 0;
                uint16 index2 = 0;
                switch(mod->GetMiscValue())
                {
                    case 0:{
                        index = UNIT_FIELD_STAT0;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_POSSTAT0 : index2 = PLAYER_FIELD_NEGSTAT0;
                    }break;
                    case 1:{
                        index = UNIT_FIELD_STAT1;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_POSSTAT1 : index2 = PLAYER_FIELD_NEGSTAT1;
                    }break;
                    case 2:{
                        index = UNIT_FIELD_STAT2;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_POSSTAT2 : index2 = PLAYER_FIELD_NEGSTAT2;
                    }break;
                    case 3:{
                        index = UNIT_FIELD_STAT3;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_POSSTAT3 : index2 = PLAYER_FIELD_NEGSTAT3;
                    }break;
                    case 4:{
                        index = UNIT_FIELD_STAT4;
                        mod->GetMiscValue2() == 0 ? index2 = PLAYER_FIELD_POSSTAT4 : index2 = PLAYER_FIELD_NEGSTAT4;
                    }break;
                    default:{
                        printf("WARNING: Misc Value for SPELL_AURA_MOD_STAT not valid\n");
                        return;
                    }break;
                }
                if(apply){
                    Field.SetU32(index,Field.GetU32(index)+mod->GetAmount());
                    if(GetTypeId() == TYPEID_PLAYER)
                        Field.SetU32(index2,Field.GetU32(index2)+mod->GetAmount());
                }else{
                    Field.SetU32(index,Field.GetU32(index)-mod->GetAmount());
                    if(GetTypeId() == TYPEID_PLAYER)
                        Field.SetU32(index2,Field.GetU32(index2)-mod->GetAmount());
                }
            }break;
        case SPELL_AURA_PERIODIC_DAMAGE:
            {
            }break;
        case SPELL_AURA_MOD_SKILL:
            {
            }break;
        case SPELL_AURA_MOD_INCREASE_SPEED:
            {
            }break;
        case SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED:
            {
            }break;
        case SPELL_AURA_MOD_DECREASE_SPEED:
            {
                data.Initialize(MSG_MOVE_SET_RUN_SPEED);
                data << GetGUID();
                apply ? data << float(7.5-7.5/100*mod->GetAmount()) : data << float(7.5);
                SendToSet(&data,true);
            }break;
        case SPELL_AURA_MOD_INCREASE_HEALTH:
            {
                uint32 newValue;
                newValue = Field.GetU32(UNIT_FIELD_MAXHEALTH);
                apply ? newValue += mod->GetAmount() : newValue -= mod->GetAmount();
                Field.SetU32(UNIT_FIELD_MAXHEALTH,newValue);
            }break;
        case SPELL_AURA_MOD_INCREASE_ENERGY:
            {
                uint32 powerField = 23;
                uint8 powerType = (uint8)(Field.GetU32(UNIT_FIELD_BYTES_0) >> 24);
                if(powerType == 0) // Mana
                    powerField = UNIT_FIELD_POWER1;
                else if(powerType == 1) // Rage
                    powerField = UNIT_FIELD_POWER2;
                else if(powerType == 3) // Energy
                    powerField = UNIT_FIELD_POWER4;

                uint32 newValue = Field.GetU32(powerType);
                apply ? newValue += mod->GetAmount() : newValue -= mod->GetAmount();
                Field.SetU32(powerType,newValue);
            }break;
        case SPELL_AURA_MOD_SHAPESHIFT:
            {
                Affect* tmpAff;
                uint32 spellId;
                switch(mod->GetMiscValue())
                {
                    case FORM_CAT: {
                        spellId = 3025;
                    } break;
                    case FORM_TREE:{
                        spellId = 3122;
                    } break;
                    case FORM_TRAVEL:{
                        spellId = 5419;
                    } break;
                    case FORM_AQUA:{
                        spellId = 5421;
                    } break;
                    case FORM_BEAR:{
                        spellId = 1178;
                    } break;
                    case FORM_AMBIENT:{
                        spellId = 0;
                    } break;
                    case FORM_GHOUL:{
                        spellId = 0;
                    } break;
                    case FORM_DIREBEAR:{
                        spellId = 9635;
                    } break;
                    case FORM_CREATUREBEAR:{
                        spellId = 2882;
                    } break;
                    case FORM_GHOSTWOLF:{
                        spellId = 0;
                    } break;
                    case FORM_BATTLESTANCE:{
                        spellId = 0;
                    } break;
                    case FORM_DEFENSIVESTANCE:{
                        spellId = 7376;
                    } break;
                    case FORM_BERSERKERSTANCE:{
                        spellId = 7381;
                    } break;
                    case FORM_SHADOW:{
                        spellId = 0;
                    } break;
                    case FORM_STEALTH:{
                        spellId = 3025;
                    } break;
                    default:{
                        printf("Unknown Shapeshift Type\n");
                    } break;
                }
                // check for spell id
                SpellEntry *spellInfo = sSpellStore.LookupEntry( spellId );

                if(!spellInfo)
                {
                    Log::getSingleton( ).outError("WORLD: unknown spell id %i\n", spellId);
                    break;
                }
                tmpAff = new Affect(spellInfo,parent->GetDuration(),parent->GetCasterGUID());
                for(uint8 i=0;i<3;i++){
                    if(spellInfo->Effect[i] == 6){
                        uint32 value = 0;
                        uint32 type = 0;
                        uint32 damage = 0;
                        if(spellInfo->EffectBasePoints[i] < 0){
                            tmpAff->SetNegative();
                            type = 1;
                        }
                        uint32 sBasePoints = (uint32)sqrt((float)(spellInfo->EffectBasePoints[i]*spellInfo->EffectBasePoints[i]));
                        if(spellInfo->EffectApplyAuraName[i] == 3){       // Periodic Trigger Damage
                            damage = spellInfo->EffectBasePoints[i]+rand()%spellInfo->EffectDieSides[i]+1;
                            //TODO: why the hell it takes uint16?
                            tmpAff->SetDamagePerTick((uint16)damage, spellInfo->EffectAmplitude[i]);
                            tmpAff->SetNegative();
                        }else if(spellInfo->EffectApplyAuraName[i] == 23)// Periodic Trigger Spell
                            tmpAff->SetPeriodicTriggerSpell(spellInfo->EffectTriggerSpell[i],spellInfo->EffectAmplitude[i]);
                        else{
                            if(spellInfo->EffectDieSides[i] != 0)
                                value = sBasePoints+rand()%spellInfo->EffectDieSides[i];
                            else
                                value = sBasePoints;
                            if(spellInfo->EffectDieSides[i] <= 1)
                                value += 1;
                            //TODO: why the hell it takes uint8?
                            tmpAff->AddMod((uint8)spellInfo->EffectApplyAuraName[i],value,spellInfo->EffectMiscValue[i],type);
                        }
                    }
                }
                if(tmpAff){
                    parent->SetCoAffect(tmpAff);
                    AddAffect(tmpAff);
                }
            }break;
        case SPELL_AURA_EFFECT_IMMUNITY:
            {
            }break;
        case SPELL_AURA_STATE_IMMUNITY:
            {
            }break;
        case SPELL_AURA_SCHOOL_IMMUNITY:
            {
            }break;
        case SPELL_AURA_DAMAGE_IMMUNITY:
            {
            }break;
        case SPELL_AURA_DISPEL_IMMUNITY:
            {
            }break;
        case SPELL_AURA_PROC_TRIGGER_SPELL:
            {
                apply ? m_triggerSpell = mod->GetAmount() : m_triggerSpell = 0;
            }break;
        case SPELL_AURA_PROC_TRIGGER_DAMAGE:
            {
                apply ? m_triggerDamage = mod->GetAmount() : m_triggerDamage = 0;
            }break;
        case SPELL_AURA_TRACK_CREATURES:
            {
                apply ? Field.SetU32(PLAYER_TRACK_CREATURES,mod->GetMiscValue()) : Field.SetU32(PLAYER_TRACK_CREATURES,0);
            }break;
        case SPELL_AURA_TRACK_RESOURCES:
            {
                apply ? Field.SetU32(PLAYER_TRACK_RESOURCES,mod->GetMiscValue()) : Field.SetU32(PLAYER_TRACK_RESOURCES,0);
            }break;
        case SPELL_AURA_MOD_PARRY_SKILL:
            {
            }break;
        case SPELL_AURA_MOD_PARRY_PERCENT:
            {
                uint32 current = Field.GetU32(PLAYER_PARRY_PERCENTAGE);
                apply ? Field.SetU32(PLAYER_PARRY_PERCENTAGE,current+mod->GetAmount()) : Field.SetU32(PLAYER_PARRY_PERCENTAGE,current-mod->GetAmount());
            }break;
        case SPELL_AURA_MOD_DODGE_SKILL:
            {
            }break;
        case SPELL_AURA_MOD_DODGE_PERCENT:
            {
                uint32 current = Field.GetU32(PLAYER_DODGE_PERCENTAGE);
                apply ? Field.SetU32(PLAYER_DODGE_PERCENTAGE,current+mod->GetAmount()) : Field.SetU32(PLAYER_DODGE_PERCENTAGE,current-mod->GetAmount());
            }break;
        case SPELL_AURA_MOD_CONFUSE:
            {
            }break;
        case SPELL_AURA_MOD_BLOCK_SKILL:
            {
            }break;
        case SPELL_AURA_MOD_BLOCK_PERCENT:
            {
                uint32 current = Field.GetU32(PLAYER_BLOCK_PERCENTAGE);
                apply ? Field.SetU32(PLAYER_BLOCK_PERCENTAGE,current+mod->GetAmount()) : Field.SetU32(PLAYER_BLOCK_PERCENTAGE,current-mod->GetAmount());
            }break;
        case SPELL_AURA_MOD_CRIT_PERCENT:
            {
                uint32 current = Field.GetU32(PLAYER_CRIT_PERCENTAGE);
                apply ? Field.SetU32(PLAYER_CRIT_PERCENTAGE,current+mod->GetAmount()) : Field.SetU32(PLAYER_CRIT_PERCENTAGE,current-mod->GetAmount());
            }break;
        case SPELL_AURA_PERIODIC_LEECH:
            {
            }break;
        case SPELL_AURA_MOD_HIT_CHANCE:
            {
            }break;
        case SPELL_AURA_MOD_SPELL_HIT_CHANCE:
            {
            }break;
        case SPELL_AURA_TRANSFORM:
            {
            }break;
        case SPELL_AURA_MOD_SPELL_CRIT_CHANCE:
            {
            }break;
        case SPELL_AURA_MOD_INCREASE_SWIM_SPEED:
            {
            }break;
        case SPELL_AURA_MOD_DAMAGE_DONE_CREATURE:
            {
            }break;
        case SPELL_AURA_MOD_CHARM:
            {
            }break;
        case SPELL_AURA_MOD_PACIFY_SILENCE:
            {
            }break;
        case SPELL_AURA_MOD_SCALE:
            {
                float current = GetFloatValue(OBJECT_FIELD_SCALE_X);
                apply ? SetFloatValue(OBJECT_FIELD_SCALE_X,current+current/100*10) : SetFloatValue(OBJECT_FIELD_SCALE_X,current-current/110*100);
            }break;
        case SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
            {
            }break;
        case SPELL_AURA_PERIODIC_MANA_FUNNEL:
            {
            }break;
        case SPELL_AURA_PERIODIC_MANA_LEECH:
            {
            }break;
        case SPELL_AURA_MOD_CASTING_SPEED:
            {
            }break;
        case SPELL_AURA_FEIGN_DEATH:
            {
            }break;
        case SPELL_AURA_MOD_DISARM:
            {
            }break;
        case SPELL_AURA_MOD_STALKED:
            {
            }break;
        case SPELL_AURA_SCHOOL_ABSORB:
            {
            }break;
        case SPELL_AURA_MOD_FEAR:
            {
            }break;
        case SPELL_AURA_EXTRA_ATTACKS:
            {
            }break;
        case SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL:
            {
            }break;
        case SPELL_AURA_MOD_POWER_COST:
            {
            }break;
        case SPELL_AURA_MOD_POWER_COST_SCHOOL:
            {
            }break;
        case SPELL_AURA_REFLECT_SPELLS_SCHOOL:
            {
            }break;
        case SPELL_AURA_MOD_LANGUAGE:
            {
            }break;
        case SPELL_AURA_FAR_SIGHT:
            {
            }break;
        case SPELL_AURA_MECHANIC_IMMUNITY:
            {
            }break;
        case SPELL_AURA_MOUNTED:
            {
            }break;
        case SPELL_AURA_MOD_DAMAGE_PERCENT_DONE:
            {
            }break;
        case SPELL_AURA_PERIODIC_HEAL:
            {
            }break;
        case SPELL_AURA_MOD_PERCENT_STAT:
            {
            }break;
        case SPELL_AURA_SPLIT_DAMAGE:
            {
            }break;
        case SPELL_AURA_WATER_BREATHING:
            {
            }break;
        case SPELL_AURA_MOD_BASE_RESISTANCE:
            {
            }break;
        case SPELL_AURA_MOD_REGEN:
            {
            }break;
        case SPELL_AURA_MOD_POWER_REGEN:
            {
            }break;
        case SPELL_AURA_CHANNEL_DEATH_ITEM:
            {
            }break;
        case SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN:
            {
            }break;
        case SPELL_AURA_MOD_PERCENT_REGEN:
            {
            }break;
        case SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
            {
            }break;
        case SPELL_AURA_MOD_ATTACKSPEED:
            {
            }break;
        case SPELL_AURA_MOD_RESIST_CHANCE:
            {
            }break;
        case SPELL_AURA_MOD_DETECT_RANGE:
            {
            }break;
        case SPELL_AURA_PREVENTS_FLEEING:
            {
            }break;
        case SPELL_AURA_MOD_UNATTACKABLE:
            {
            }break;
        case SPELL_AURA_INTERRUPT_REGEN:
            {
            }break;
        case SPELL_AURA_GHOST:
            {
            }break;
        case SPELL_AURA_SPELL_MAGNET:
            {
            }break;
        case SPELL_AURA_MANA_SHIELD:
            {
            }break;
        case SPELL_AURA_MOD_SKILL_TALENT:
            {
            }break;
        case SPELL_AURA_MOD_ATTACK_POWER:
            {
            }break;
        default:
            {
                Log::getSingleton().outError("Unknown affect id %u", (uint32)mod->GetType());
            }
    }
#endif
}

#if 0
void Unit::_UpdateAura()
{
   Player* pThis = objmgr.GetObject<Player>(GetGUID());
    if(!m_aura)
        return;

    m_aura->SetDuration(6000);
    Player* pGroupGuy;
    Group* pGroup;
    if(pThis)
        pGroup = objmgr.GetGroupByLeader(pThis->GetGroupLeader());
    else{
        if(!SetAffDuration(m_aura->GetId(),this,6000))
            AddAffect(m_aura);
        return;
    }
    if(!pGroup){
        if(!SetAffDuration(m_aura->GetId(),this,6000))
            AddAffect(m_aura);
        return;
    }else
        for(uint32 i=0;i<pGroup->GetMembersCount();i++){
            pGroupGuy = objmgr.GetObject<Player>(pGroup->GetMemberGUID(i));
            if(!pGroupGuy)
                continue;
            if(sqrt(
           (GetPositionX()-pGroupGuy->GetPositionX())*(GetPositionX()-pGroupGuy->GetPositionX())
           +(GetPositionY()-pGroupGuy->GetPositionY())*(GetPositionY()-pGroupGuy->GetPositionY())
           +(GetPositionZ()-pGroupGuy->GetPositionZ())*(GetPositionZ()-pGroupGuy->GetPositionZ())
                   ) <=30)
                if(!pGroupGuy->SetAffDuration(m_aura->GetId(),this,6000))
                    pGroupGuy->AddAffect(m_aura);
        }
}
#endif

void Unit::UpdateSpells (uint32 iDeltaMs)
{
#if 0
    if (CurrentSpell)
    {
        CurrentSpell->Update (time);
        if (CurrentSpell->GetState () == SPELL_STATE_FINISHED)
        {
            delete CurrentSpell;
            CurrentSpell = NULL;
        }
    }

    for (int i = Affects.Length () - 1; i >= 0; i--)
    {
        Affect *aff = Affects.Get (i);

        uint8 AffResult = aff->Update (iDeltaMs);
        if (AffResult == 2 || AffResult == 6)
        {
            Unit *attacker = (Unit*) objmgr.GetObject<Player>(aff->GetCasterGUID());
            if(!attacker)
                attacker = (Unit*) objmgr.GetObject<Creature>(aff->GetCasterGUID());

            // FIXME: we currently have a way to inflict damage w/o attacker, this should be changed
            if(attacker)
            {
                if(this->isAlive())
                    attacker->PeriodicAuraLog(this, aff->GetId(), aff->GetDamagePerTick(),aff->GetSpellProto()->School);
            }
        }
        if( AffResult == 4 || AffResult == 6 )
        {
            // Trigger Spell
            // check for spell id
            SpellEntry *spellInfo = sSpellStore.LookupEntry( aff->GetSpellPerTick() );

            if(!spellInfo)
            {
                Log::getSingleton( ).outError("WORLD: unknown spell id %i\n", aff->GetSpellPerTick());
                return;
            }

            Spell *spell = new Spell(this, spellInfo, true, aff);
            SpellCastTargets targets;
            WorldPacket dump;
            dump.Initialize(0);
            dump << uint16(2) << Field.GetU32(UNIT_FIELD_CHANNEL_OBJECT) << Field.GetU32(UNIT_FIELD_CHANNEL_OBJECT+1);
            targets.read(&dump,GetGUID());

            spell->prepare(&targets);

        }

        if ( !aff->GetDuration() )
        {
            printf("remove aff %u from player %u\n",aff->GetId(),GetGUID());
            RemoveAffect(aff);
        }
    }
#endif
}

#if 0
void Unit::castSpell( Spell * pSpell )
{
    // check if we have a spell already casting etc
    if(m_currentSpell)
    {
        m_currentSpell->cancel();
        delete m_currentSpell;
    }

    m_currentSpell = pSpell;
}
#endif

void Unit::InterruptSpell()
{
#if 0
    if(m_currentSpell){
        m_currentSpell->SendInterrupted(0x1f);
        m_currentSpell->cancel();
        m_currentSpell = NULL;
    }
#endif
}

#if 0
void Unit::_AddAura(Affect *aff)
{
    ASSERT(aff);

    if (!aff->GetId())
    {
        Log::getSingleton().outDetail("Unit::_AddAura() - affect doesn't have id");
        return;
    }

    //UNIT_FIELD_AURAFLAGS 0-7;UNIT_FIELD_AURAFLAGS+1 8-15;UNIT_FIELD_AURAFLAGS+2 16-23 ... For each Aura 1 Byte

    WorldPacket data;

    uint8 slot, i;

    slot = 0xFF;

    if (aff->IsPositive())
    {
        for (i = 0; i < MAX_POSITIVE_AURAS; i++)
        {
            if (Field.GetU32((uint16)(UNIT_FIELD_AURA + i)) == 0)
            {
                slot = i;
                break;
            }
        }
    }
    else
    {
        for (i = MAX_POSITIVE_AURAS; i < MAX_AURAS; i++)
        {
            if (Field.GetU32((uint16)(UNIT_FIELD_AURA + i)) == 0)
            {
                slot = i;
                break;
            }
        }
    }

    if (slot == 0xFF)
    {
        Log::getSingleton().outDetail("Unit::_AddAura() - no free aura slots found");
        return;
    }

    Log::getSingleton().outDetail("Unit::_AddAura() - found slot %u", (uint32)slot);

    Field.SetU32((uint16)(UNIT_FIELD_AURA + slot), aff->GetId());

    uint8 flagslot = slot >> 3;
    uint32 value = Field.GetU32((uint16)(UNIT_FIELD_AURAFLAGS + flagslot));
    Log::getSingleton().outDetail("Unit::_AddAura() - val: %X", value);
    value |= 0xFFFFFFFF & (AFLAG_SET << ((slot & 7) << 2));
    Log::getSingleton().outDetail("Unit::_AddAura() - new val: %X", value);
    Field.SetU32((uint16)(UNIT_FIELD_AURAFLAGS + flagslot), value);

    //  0000 0000 original
    //  0000 1001 AFLAG_SET
    //  1111 1111 0xFF

    uint8 appslot = slot >> 1;

    /*
     value = Field.GetU32(UNIT_FIELD_AURAAPPLICATIONS + appslot);
     uint16 *dmg = ((uint16*)&value) + (slot & 1);
     *dmg = 5; // FIXME: use correct value
     Field.SetU32(UNIT_FIELD_AURAAPPLICATIONS + appslot, value);
     */

    if( GetTypeId() == TYPEID_PLAYER )
    {
        data.Initialize(SMSG_UPDATE_AURA_DURATION);
        data << (uint8)slot << (uint32)aff->GetDuration();
        ((Player*)this)->GetSession()->SendPacket(&data);
    }

    aff->SetAuraSlot( slot );

    return;
}


void Unit::_RemoveAura(Affect *aff)
{
    ASSERT(aff);

    //UNIT_FIELD_AURAFLAGS 0-7;UNIT_FIELD_AURAFLAGS+1 8-15;UNIT_FIELD_AURAFLAGS+2 16-23 ... For each Aura 1 Byte

    uint8 slot = aff->GetAuraSlot();

    Field.SetU32((uint16)(UNIT_FIELD_AURA + slot), 0);

    uint8 flagslot = slot >> 3;

    uint32 value = Field.GetU32((uint16)(UNIT_FIELD_AURAFLAGS + flagslot));
    value &= 0xFFFFFFFF ^ (0xF << ((slot & 7) << 2));
    Field.SetU32((uint16)(UNIT_FIELD_AURAFLAGS + flagslot), value);

    /*
     uint8 appslot = slot >> 1;
     value = Field.GetU32(UNIT_FIELD_AURAAPPLICATIONS + appslot);
     uint16 *dmg = ((uint16*)&value) + (slot & 1);
     *dmg = 0;
     Field.SetU32(UNIT_FIELD_AURAAPPLICATIONS + appslot, value);
     */

    aff->SetAuraSlot(0);

    return;
}

Affect* Unit::FindAff(uint32 spellId)
{
    Affects::iterator i;
    for (i = m_affects.begin(); i != m_affects.end(); i++)
        if((*i)->GetId() == spellId)
            return (*i);
    return NULL;
}
#endif

float Unit::getdistance( float xe, float ye, float xz, float yz )
{
    return sqrt( ( xe - xz ) * ( xe - xz ) + ( ye - yz ) * ( ye - yz ) );
}

float Unit::getangle( float xe, float ye, float xz, float yz )
{
    float w;
    w = RAD2DEG (atan ((yz - ye) / (xz - xe)));
    if (xz>=xe) {
        w = 90+w;
    } else {
        w = 270+w;
    }
    return w;
}

float Unit::geteasyangle( float angle )
{
    if(angle < 0)
        return fmod(fabs(angle),360.0);
    return fmod(angle,360.0);
}

bool Unit::inarc( float radius,  float xM, float yM, float offnung, float orientation, float xP, float yP )
{
    float distance = getdistance( xM, yM, xP, yP );
    float angle = getangle( xM, yM, xP, yP );
    float lborder = geteasyangle( ( orientation - (offnung/2) ) );
    float rborder = geteasyangle( ( orientation + (offnung/2) ) );
    if(radius>=distance &&( ( angle >= lborder ) &&
                           ( angle <= rborder ) ||
                           ( lborder > rborder && ( angle < rborder || angle > lborder ) ) ) ) {
        return true;
    } else {
        return false;
    }
}
#if 0
bool Unit::isInFront(Unit* target,float distance)
{
    float orientation = GetOrientation()/float(2*M_PI)*360;
    orientation += 90.0f;
    return inarc(distance,GetPositionX(),GetPositionY(),float(180),orientation,target->GetPositionX(),target->GetPositionY());

}
#endif
