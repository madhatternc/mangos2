/**
 *     \file  src/worldserver/Unit.h
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

#ifndef __UNIT_H__
#define __UNIT_H__

#include "Object.h"
#include "Timer.h"

class Affect;
class Modifier;
struct Spell;

enum UnitDeathState
{
    /// Unit is alive and well
    ALIVE,
    /// Unit has JUST died
    JUST_DIED,
    /// Unit has died but remains in the world as a corpse
    CORPSE,
    /// Unit is dead and his corpse is gone from the world
    DEAD
};

/// Bitflags for the UNIT_FIELD_FLAGS field
enum
{
    /// This unit can gossip (client sends CMSG_GOSSIP_HELLO)
    UFF_GOSSIP              = 0x00000001,
    /// Player is using the taxi and has locked movement
    UFF_LOCKED_MOVE         = 0x00000004,
    /// Player controlled, collision detection, blue name if not PvP
    UFF_PLAYER_CONTROLLED   = 0x00000008,
    /// Plus mob
    UFF_PLUS_MOB            = 0x00000040,
    /// Alliance member/Horde member
    UFF_ALLIANCE            = 0x00001000,
    /// Unit is mounted
    UFF_MOUNTED             = 0x00002000,
    /// Unit is dead
    UFF_DEAD                = 0x00004000,
    /// Alive???
    //UFF_ALIVE             = 0x00010000,
    /// Don't have full control (no rotation)
    UFF_NO_ROTATION         = 0x00040000,
    /// In combat
    UFF_IN_COMBAT           = 0x00080000,
    /// Skinnable
    UFF_SKINNABLE           = 0x04000000,
    /// Weapon sheathed
    UFF_SHEATHED            = 0x40000000,
};

/// Bitflags for UNIT_DYNAMIC_FLAGS
enum
{
    /// This is a corpse which can be looted
    UDF_LOOTABLE            = 0x00000001,
    /// The unit is tapped by some other player
    UDF_TAPPED_OTHER        = 0x00000004,
    /// The unit is tapped by you
    UDF_TAPPED_YOU          = 0x00000008,
    /// Show information about the unit - damage,armor,health
    UDF_SHOW_INFO           = 0x00000010
};

/// Bitflags for CORPSE_FIELD_FLAGS
//@@@todo: move to Corpse.h
enum
{
    /// The corpse is claimed by somebody
    CFF_CLAIMED             = 0x00000001
};

/**
 * A Unit is a live Object.
 * This is a base class for Players and Creatures.
 */
class Unit : public Object
{
protected:
    /// Temporary affection
    Affect *TempAffect;
    Affect *Aura;
    uint32 AuraCheck;

    /// True if we are silenced by a spell
    bool Silenced;

    bool MeleeSpell;
    uint32 AddDmgOnce;
    uint64 TotemSlot1;
    uint64 TotemSlot2;
    uint64 TotemSlot3;
    uint64 TotemSlot4;
    uint32 TriggerSpell;
    uint32 TriggerDamage;

    /// timer for attack
    Timer AttackTimer;

    /// The list of units attacking this unit
    ObjectVector Attackers;
    /// How dead we are
    UnitDeathState DeathState;

    /// The list of affections on this unit
    DECLARE_VECTOR (AffectVector, Affect *,) Affects; // tolua_hide

    // The spell that unit is currently casting
    Spell *CurrentSpell;

protected:
    /**
     * There aren't any objects of Unit type, it is meant to be a common
     * parent for several other classes, so the constructor is private
     * and also this class has virtual pure functions.
     */
    Unit ();

    /// Apply or remove all affect modificators
    void ApplyAllAffectMods (bool iApply);

    void AddAura (Affect *iAff);
    void RemoveAura (Affect *iAff);
    Affect *FindAffect (uint32 iSpellId);

    void UpdateSpells (uint32 iTime);
    void UpdateAura ();

    /// @@todo@@
    bool IsAffectPositive (Affect *aff)
    { return true; }

    // Some Functions for isInFront Calculation ( thanks to emperor and undefined for the formula )
    bool inarc( float radius,  float xM, float yM, float offnung, float orientation, float xP, float yP );  // Main Function called by isInFront();
    float geteasyangle( float angle );// converts to 360 > x > 0
    float getangle( float xe, float ye, float xz, float yz );
    float getdistance( float xe, float ye, float xz, float yz );

public:
    virtual ~Unit ();

    /// Update unit state depending on time passed
    virtual void Update (uint32 iDeltaMs);

    /// Apply or remove a modifier
    void ApplyModifier (Modifier *iMod, bool iApply, Affect *iParent);

    /**
     * Receive damage from another unit. This is a important function
     * which is overrided by most children classes because different
     * creatures react differently to the damage they take. Also note
     * that this is the ULTIMATE damage, e.g. all resistances, parry
     * etc is already subtracted from the attack power. Also this function
     * is responsible to call GiveXP() on the respective attacker unit
     * after this unit is killed (and it is NOT neccessary that this is
     * the iAttacker unit).
     *
     * @arg iAttacker
     *   The attacker unit.
     * @arg iDamage
     *   The damage caused by the attacker unit.
     */
    virtual void ReceiveDamage (Unit *iAttacker, uint32 iDamage);

    /**
     * This function is called directly before a unit is killed, so that
     * its pockets doesn't turn out to be dissapointly empty :)
     * If this is a player or some other object that already has something
     * in his pockets, it can safely do nothing here.
     */
    virtual void GenerateLoot () = 0;

    /**
     * Give experience points to player
     * @arg iXP
     *   Amount of experience points to give.
     * @arg iVictim
     *   The creature that has been killed.
     * @arg iGroup
     *   true if XP should be distributed amongst all group members
     *   (if player is part of group, otherwise this is ignored).
     *   If this is false, the whole XP is given only to this player.
     */
    virtual void GiveXP (uint32 iXP, Unit *iVictim, bool iGroup = true);

    /**
     * Override RemoveInRangeObject() to get a chance to remove the
     * object from the list of attackers, if it's there.
     */
    virtual void RemoveInRangeObject (Object *Obj)
    {
        if (Obj->GetType () & TYPE_UNIT)
            RemoveAttacker ((Unit *)Obj);
        Object::RemoveInRangeObject (Obj);
    }

    /**
     * Set up the attack timer: unit will be ready to attack only
     * when this timer expires.
     */
    void SetAttackTimer ()
    { AttackTimer.SetInterval (Field.GetU32 (UNIT_FIELD_BASEATTACKTIME)); }

    /// Check if unit is ready to attack again
    bool IsAttackReady () const
    { return !AttackTimer.Enabled (); }

    /// Check if victim is reachable with current weapon
    bool CanReachWithAttack (Unit *iVictim) const;

    /// Remove an attacker from attackers list
    inline void RemoveAttacker (Unit *iAttacker)
    {
        int idx = Attackers.FindByGUID (iAttacker->GetGUID ());
        if (idx >= 0)
            Attackers.Delete (idx);
    }

    /// Get unit level
    inline uint8 GetLevel ()
    { return Field.GetU32 (UNIT_FIELD_LEVEL); }
    /// Get unit race
    inline uint8 GetRace ()
    { return Field.GetU32 (UNIT_FIELD_BYTES_0); }
    /// Get unit class
    inline uint8 GetClass ()
    { return Field.GetU32 (UNIT_FIELD_BYTES_0) >> 8; }
    /// Get unit gender
    inline uint8 GetGender ()
    { return Field.GetU32 (UNIT_FIELD_BYTES_0) >> 16; }

    /// Combat
    void DealDamage (Unit *iVictim, uint32 iDamage)
    { iVictim->ReceiveDamage (this, iDamage); }

    void AttackerStateUpdate (Unit *iVictim, uint32 iDamage, bool DoT);

    /**
     * Send a message to client to display messages like "Wolf suffers
     * 15 fire damage from your fireball". Only for damages from spells.
     */
    void SpellNonMeleeDamageLog (Unit *iVictim, uint32 iSpellID, uint32 iDamage);

    void PeriodicAuraLog (Unit *iVictim, uint32 iSpellID, uint32 iDamage,
                          uint32 iDamageType);

    /// Notify all in-range players that the attack has started
    void AttackStart (Unit *iVictim);
    /// Notify all in-range players that the attack has stopped
    void AttackStop (uint64 iVictimGuid);

    /// Check if unit is alive
    bool IsAlive ()
    { return DeathState == ALIVE; }
    /// Check if unit is dead
    bool IsDead ()
    { return DeathState != ALIVE; }
    /// Set corpse state :)
    void SetDeathState (UnitDeathState iState)
    { DeathState = iState; }
    /// Get current corpse state
    UnitDeathState GetDeathState ()
    { return DeathState; }

    /// Add affect to unit
    bool AddAffect (Affect *iAff, bool iUniq = false);
    /// Remove affect from unit
    void RemoveAffect (Affect *iAff);
    /// Remove all affects with specified type
    bool RemoveAffect (uint32 iType);
    /// Remove affect given the spell id that caused it
    void RemoveAffectById (uint32 iSpellId);
    /// Remove all affects
    void RemoveAllAffects ();
    /// Set the aura
    void SetAura (Affect *iAff)
    { Aura = iAff; }
    bool SetAffectDuration (uint32 iSpellId, Unit *iCaster, uint32 iDuration); // tolua_hide

    /// Start spell casting
    void CastSpell (Spell *iSpell); // tolua_hide
    /// Interrupt current casting, if any
    void InterruptSpell (); // tolua_hide

    /**
     * Use it to Check if a Unit is in front of this one
     * @arg iTarget
     *   The unit to check if it's in front of us.
     * @arg iDistance
     *   Return false if target is farther than this.
     */
    bool IsInFront (Unit *iTarget, float iDistance); // tolua_hide
};

#endif // __UNIT_H__
