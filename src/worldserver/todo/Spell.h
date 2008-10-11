/**
 *     \file  src/worldserver/todo/Spell.h
 *    \brief  Provides basic Spell functions.
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

#ifndef __SPELL_H__
#define __SPELL_H__

#include "UpdateFields.h"
#include "Character.h"
#include "Opcodes.h"

struct emoteentry
{
    uint32 Id;
    uint32 name;
    uint32 textid;
    uint32 textid2;
    uint32 textid3;
    uint32 textid4;
    uint32 unk1;
    uint32 textid5;
    uint32 unk2;
    uint32 textid6;
    uint32 unk3;
    uint32 unk4;
    uint32 unk5;
    uint32 unk6;
    uint32 unk7;
    uint32 unk8;
    uint32 unk9;
    uint32 unk10;
    uint32 unk11;
};

struct skilllinespell
{
    uint32 Id;
    uint32 skilline;
    uint32 spell;
    uint32 unk1;
    uint32 unk2;
    uint32 unk3;
    uint32 unk4;
    uint32 unk5;
    uint32 minrank;
    uint32 next;
    uint32 grey;
    uint32 green;
    uint32 unk10;
    uint32 unk11;
    uint32 unk12;
};

struct SpellEntry
{
    uint32 Id;
    uint32 School;
    uint32 Category;
    uint32 field4;
    uint32 field5;
    uint32 Attributes;
    uint32 AttributesEx;
    uint32 field8;
    uint32 field9;
    uint32 Targets;
    uint32 TargetCreatureType;
    uint32 RequiresSpellFocus;
    uint32 CasterAuraState;
    uint32 TargetAuraState;
    uint32 CastingTimeIndex;
    uint32 RecoveryTime;
    uint32 CategoryRecoveryTime;
    uint32 InterruptFlags;
    uint32 AuraInterruptFlags;
    uint32 ChannelInterruptFlags;
    uint32 procFlags;
    uint32 procChance;
    uint32 procCharges;
    uint32 maxLevel;
    uint32 baseLevel;
    uint32 spellLevel;
    uint32 DurationIndex;
    uint32 powerType;
    uint32 manaCost;
    uint32 manaCostPerlevel;
    uint32 manaPerSecond;
    uint32 manaPerSecondPerLevel;
    uint32 rangeIndex;
    float speed;
    uint32 modalNextSpell;
    uint32 field36;
    uint32 field37;
    uint32 Totem1;
    uint32 Totem2;
    uint32 Reagent[8];
    uint32 ReagentCount[8];
    uint32 EquippedItemClass;
    uint32 EquippedItemSubClass;
    uint32 Effect[3];
    uint32 EffectDieSides[3];
    uint32 EffectBaseDice[3];
    uint32 EffectDicePerLevel[3];
    uint32 EffectRealPointsPerLevel[3];
    int32 EffectBasePoints[3];
    uint32 EffectImplicitTargetA[3];
    uint32 EffectImplicitTargetB[3];
    uint32 EffectRadiusIndex[3];
    uint32 EffectApplyAuraName[3];
    uint32 EffectAmplitude[3];
    uint32 Effectunknown[3];
    uint32 EffectChainTarget[3];
    uint32 EffectItemType[3];
    uint32 EffectMiscValue[3];
    uint32 EffectTriggerSpell[3];
    uint32 Effectunknown2[3];
    uint32 SpellVisual;
    uint32 field110;
    uint32 SpellIconID;
    uint32 activeIconID;
    uint32 spellPriority;
    uint32 Name;
    uint32 NameAlt1;
    uint32 NameAlt2;
    uint32 NameAlt3;
    uint32 NameAlt4;
    uint32 NameAlt5;
    uint32 NameAlt6;
    uint32 NameAlt7;
    uint32 NameFlags;
    uint32 Rank;
    uint32 RankAlt1;
    uint32 RankAlt2;
    uint32 RankAlt3;
    uint32 RankAlt4;
    uint32 RankAlt5;
    uint32 RankAlt6;
    uint32 RankAlt7;
    uint32 RankFlags;
    uint32 Description;
    uint32 DescriptionAlt1;
    uint32 DescriptionAlt2;
    uint32 DescriptionAlt3;
    uint32 DescriptionAlt4;
    uint32 DescriptionAlt5;
    uint32 DescriptionAlt6;
    uint32 DescriptionAlt7;
    uint32 DescriptionFlags;
    uint32 BuffDescription;
    uint32 BuffDescriptionAlt1;
    uint32 BuffDescriptionAlt2;
    uint32 BuffDescriptionAlt3;
    uint32 BuffDescriptionAlt4;
    uint32 BuffDescriptionAlt5;
    uint32 BuffDescriptionAlt6;
    uint32 BuffDescriptionAlt7;
    uint32 ManaCostPercentage;
    uint32 StartRecoveryCategory;
    uint32 StartRecoveryTime;
    uint32 field151;
    uint32 field152;
    uint32 field153;
    uint32 field154;
    uint32 field155;
    uint32 field156;
};
struct Trainerspell
{
    uint32 Id;
    uint32 skilline1;
    uint32 skilline2;
    uint32 skilline3;
    uint32 maxlvl;
    uint32 charclass;
};
struct SpellCastTime
{
    uint32 ID;
    uint32 CastTime;
    uint32 unk1;
    uint32 unk2;
};

struct SpellRadius
{
    uint32 ID;
    float Radius;
    float unk1;
    float Radius2;
};

struct SpellRange
{
    uint32 ID;
    float minRange;
    float Range;
    uint32 unks[18];
};

struct SpellDuration
{
    uint32 ID;
    uint32 Duration1;
    uint32 Duration2;
    uint32 Duration3;
};

/* old structure to remove
struct SpellInformation
{
    uint32 Id;      // index 0
    uint32 School;      // fire, arcane, etc.
    uint32 C;       //
    uint32 D;       //
    uint32 E;       //
    uint32 F;       // index 5
    uint32 G;       //
    uint32 H;       //
    uint32 I;       //
    uint32 J;       //
    uint32 K;       // index 10
    uint32 L;       //
    uint32 M;       //
    uint32 N;       //
    uint32 CastTime;    //
    uint32 P;       // index 15
    uint16 CoolDown;    //
    uint32 R;       //
    uint32 S;       //
    uint32 T;       //
    uint32 U;       // index 20
    uint32 V;       //
    uint32 W;       //
    uint32 X;       //
    uint32 PlayerLevel; //
    uint32 MaxLevel;    // index 25
    uint32 Duration;    //
    uint32 PowerType;   //
    uint32 ManaCost;    // Should prob. be named PowerCost, but ManaCost will do for now
    uint32 ManaCostPerLevel;// Should prob. be named PowerCostPerLevel, but ManaCostPerLevel will do for now
    uint32 AE;      // index 30
    uint32 AF;      //
    uint32 Range;       //
    uint32 AH;      //
    uint32 AI;      //
    uint32 AJ;      // index 35
    uint32 AK;      //
    uint32 AL;      //
    uint32 AM;      //
    uint32 AN;      //
    uint32 AO;      // index 40
    uint32 AP;      //
    uint32 AQ;      //
    uint32 AR;      //
    uint32 AS;      //
    uint32 AT;      // index 45
    uint32 AU;      //
    uint32 AV;      //
    uint32 AW;      //
    uint32 AX;      //
    uint32 AY;      // index 50
    uint32 AZ;      //
    uint32 BA;      //
    uint32 BB;      //
    uint32 BC;      //
    uint32 BD;      // index 55
    uint32 BE;      //
    uint32 BF;      //
    uint32 BG;      //
    uint32 RandomPercentDmg;//
    uint32 BI;      // index 60
    uint32 BJ;      //
    uint32 BK;      //
    uint32 BL;      //
    uint32 BM;      //
    uint32 BN;      // index 65
    uint32 BO;      //
    uint32 BP;      //
    uint32 Speed;       //
    uint32 BR;      //
    uint32 BS;      // index 70
    uint32 DmgPlus1;    //
    uint32 BU;      //
    uint32 BV;      //
    uint32 BW;      //
    uint32 BX;      // index 75
    uint32 BY;      //
    uint32 BZ;      //
    uint32 CA;      //
    uint32 CB;      //
    uint32 CC;      // index 80
    uint32 Radius;      //
    uint32 CE;      //
    uint32 CF;      //
    uint32 CG;      //
    uint32 CH;      // index 85
    uint32 CI;      //
    uint32 CJ;      //
    uint32 CK;      //
    uint32 CL;      //
    uint32 CM;      // index 90
    uint32 CN;      //
    uint32 CO;      //
    uint32 CP;      //
    uint32 CQ;      //
    uint32 CR;      // index 95
    uint32 CS;      //
    uint32 CT;      //
uint32 CU;      //
uint32 CV;      //
uint32 CW;      // index 100
uint32 CX;      //
uint32 CY;      //
uint32 CZ;      //
uint32 DA;      //
uint32 DB;      // index 105
uint32 DC;      //
uint32 DD;      //
uint32 DE;      //
uint32 DF;      //
uint32 DG;      // index 110
char *Name;     //
uint32 DI;      //
uint32 DJ;      //
uint32 DK;      //
uint32 DL;      // index 115
uint32 DM;      //
uint32 DN;      //
uint32 DO;      //
uint32 DP;      //
char *Rank;     // index 120
uint32 DR;      //
uint32 DS;      //
uint32 DT;      //
uint32 DU;      //
uint32 DV;      // index 125
uint32 DW;      //
uint32 DX;      //
uint32 DY;      //
char *Description;  //
uint32 EA;      // index 130
uint32 EB;      //
uint32 EC;      //
uint32 ED;      //
uint32 EE;      //
uint32 EF;      // index 135
uint32 EG;      //
uint32 EH;      //
char *EI;       // Some short damage description (Ex: $s1 damage every $t1 seconds.)
uint32 EJ;      //
uint32 EK;      // index 140
uint32 EL;      //
uint32 EM;      //
uint32 EN;      //
uint32 EO;      //
uint32 EP;      // index 145
uint32 EQ;      //
uint32 ER;      //
uint32 ES;      //
uint32 SpellId;     //
uint32 spell_type;  // index 150 - spell_type: self-, multi-, single-target,
// etc. (1 is single target / 2 is multi target / 3 is self healing / and 4 should be damage absorb)
uint32 replenish_type;  // mana_type: heal life - 1 - or mana - 2 - ? used by potions and eating/drinking
uint32 addDuration;
uint32 addDmg;
uint32 race;
};
*/
struct UnitPowerType
{
    UnitUpdateFields UNIT_FIELD_POWER;
    UnitUpdateFields UNIT_FIELD_MAXPOWER;
};

enum SpellType
{
    TARGET_UNDEFINED = 0,
    SINGLE_TARGET = 1,
    MULTI_TARGET = 2,
    SELF_HEAL = 3,
    DAMAGE_ABSORB = 4,
    POTIONS = 5,
    TARGET_HEAL = 6,
    MANA_SHIELD = 7,
    AURA = 8,
    SEAL = 9,
    SUMMON = 10
};

enum SpellState
{
    SPELL_STATE_NULL      = 0,
    SPELL_STATE_PREPARING = 1,
    SPELL_STATE_CASTING   = 2,
    SPELL_STATE_FINISHED  = 3,
    SPELL_STATE_IDLE      = 4
};

enum ShapeshiftForm
{
    FORM_CAT              = 1,
    FORM_TREE             = 2,
    FORM_TRAVEL           = 3,
    FORM_AQUA             = 4,
    FORM_BEAR             = 5,
    FORM_AMBIENT          = 6,
    FORM_GHOUL            = 7,
    FORM_DIREBEAR         = 8,
    FORM_CREATUREBEAR     = 14,
    FORM_GHOSTWOLF        = 16,
    FORM_BATTLESTANCE     = 17,
    FORM_DEFENSIVESTANCE  = 18,
    FORM_BERSERKERSTANCE  = 19,
    FORM_SHADOW           = 28,
    FORM_STEALTH          = 30
};

class SpellCastTargets
{
    public:
        void read ( SPELL_TARGET * data,uint64 caster );
        void write ( SPELL_TARGET * data);

        SpellCastTargets& operator=(const SpellCastTargets &target)
        {
            m_unitTarget = target.m_unitTarget;
            m_itemTarget = target.m_itemTarget;

            m_srcX = target.m_srcX;
            m_srcY = target.m_srcY;
            m_srcZ = target.m_srcZ;

            m_destX = target.m_destX;
            m_destY = target.m_destY;
            m_destZ = target.m_destZ;

            m_strTarget = target.m_strTarget;

            m_targetMask = target.m_targetMask;

            return *this;
        }

        uint64 m_unitTarget;
        uint64 m_itemTarget;
        float m_srcX, m_srcY, m_srcZ;
        float m_destX, m_destY, m_destZ;
        std::string m_strTarget;

        uint16 m_targetMask;
};

#define SPELL_SPELL_CHANNEL_UPDATE_INTERVAL 1000
// Spell instance
class Affect;

class Spell
{
    public:
        Spell( Unit* Caster, SpellEntry *info, bool triggered, Affect* aff );

        void FillTargetMap();
        void prepare(SpellCastTargets * targets);
        void cancel();
        void update(uint32 difftime);
        void cast();
        void finish();
        void HandleEffects(uint64 guid,uint32 i);
        void TakePower();
        void TriggerSpell();
        uint8 CanCast();

        inline uint32 getState() { return m_spellState; }

        void SendCastResult(uint8 result);
        void SendSpellStart();
        void SendSpellGo();
        void SendLogExecute();
        void SendInterrupted(uint8 result);
        void SendChannelUpdate(uint32 time);
        void SendChannelStart(uint32 duration);
        void HandleAddAffect(uint64 guid);
        //    void writeSpellGoTargets(ProtocolPacket * data );

        SpellEntry * m_spellInfo;
        Item* m_CastItem;
        SpellCastTargets m_targets;

    protected:

        float _CalcDistance(float sX, float sY, float sZ, float dX, float dY, float dZ)
        {
            return sqrt((dX-sX)*(dX-sX)+(dY-sY)*(dY-sY)+(dZ-sZ)*(dZ-sZ));
        }

        Unit* m_caster;

        std::list<uint64> m_targetUnits1;
        std::list<uint64> m_targetUnits2;
        std::list<uint64> m_targetUnits3;
        std::list<uint64> UniqueTargets;
        uint8 m_targetCount;

        uint32 m_spellState;
        uint32 m_timer;
        uint32 m_intervalTimer;                             // used to update channel bar
        uint32 TriggerSpellId;                              // used to set next spell to use

        float m_castPositionX;
        float m_castPositionY;
        float m_castPositionZ;
        bool m_triggeredSpell;
        Affect* m_triggeredByAffect;
        bool m_AreaAura;

};

enum ReplenishType
{
    REPLENISH_UNDEFINED = 0,
    REPLENISH_HEALTH = 20,
    REPLENISH_MANA = 21,
    REPLENISH_RAGE = 22                                     //don't know if rage is 22 or what, but will do for now
};
#endif // __SPELL_H__
