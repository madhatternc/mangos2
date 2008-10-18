/**
 *     \file  src/worldserver/Item.h
 *    \brief  Provides basic Item functions.
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

#ifndef __ITEM_H__
#define __ITEM_H__

#include "Object.h"

enum ITEM_STAT_TYPE
{
    HEALTH     = 1,
    UNKNOWN    = 2,
    AGILITY    = 3,
    STRENGHT   = 4,
    INTELLECT  = 5,
    SPIRIT     = 6,
    STAMINA    = 7,
};

enum ITEM_DAMAGE_TYPE
{
    NORMAL_DAMAGE  = 0,
    HOLY_DAMAGE    = 1,
    FIRE_DAMAGE    = 2,
    NATURE_DAMAGE  = 3,
    FROST_DAMAGE   = 4,
    SHADOW_DAMAGE  = 5,
    ARCANE_DAMAGE  = 6,
};

enum ITEM_SPELLTRIGGER_TYPE
{
    USE           = 0,
    ON_EQUIP      = 1,
    CHANCE_ON_HIT = 2,
    SOULSTONE     = 4,
};

enum ITEM_QUALITY_NAMES
{
    ITEM_QUALITY_POOR_GREY              = 0,
    ITEM_QUALITY_NORMAL_WHITE           = 1,
    ITEM_QUALITY_UNCOMMON_GREEN         = 2,
    ITEM_QUALITY_RARE_BLUE              = 3,
    ITEM_QUALITY_EPIC_PURPLE            = 4,
    ITEM_QUALITY_LEGENDARY_ORANGE       = 5,
    ITEM_QUALITY_ARTIFACT_LIGHT_YELLOW  = 6,
};

enum ITEM_BONDING_TYPE
{
    NO_BIND             = 0,
    BIND_WHEN_PICKED_UP = 1,
    BIND_WHEN_EQUIPED   = 2,
};

enum INVENTORY_TYPES
{
    INVTYPE_NON_EQUIP      = 0x0,
    INVTYPE_HEAD           = 0x1,
    INVTYPE_NECK           = 0x2,
    INVTYPE_SHOULDERS      = 0x3,
    INVTYPE_BODY           = 0x4,
    INVTYPE_CHEST          = 0x5,
    INVTYPE_WAIST          = 0x6,
    INVTYPE_LEGS           = 0x7,
    INVTYPE_FEET           = 0x8,
    INVTYPE_WRISTS         = 0x9,
    INVTYPE_HANDS          = 0xa,
    INVTYPE_FINGER         = 0xb,
    INVTYPE_TRINKET        = 0xc,
    INVTYPE_WEAPON         = 0xd,
    INVTYPE_SHIELD         = 0xe,
    INVTYPE_RANGED         = 0xf,
    INVTYPE_CLOAK          = 0x10,
    INVTYPE_2HWEAPON       = 0x11,
    INVTYPE_BAG            = 0x12,
    INVTYPE_TABARD         = 0x13,
    INVTYPE_ROBE           = 0x14,
    INVTYPE_WEAPONMAINHAND = 0x15,
    INVTYPE_WEAPONOFFHAND  = 0x16,
    INVTYPE_HOLDABLE       = 0x17,
    INVTYPE_AMMO           = 0x18,
    INVTYPE_THROWN         = 0x19,
    INVTYPE_RANGEDRIGHT    = 0x1a,
    NUM_INVENTORY_TYPES    = 0x1b,
};

enum ITEM_CLASS
{
    ITEM_CLASS_CONSUMABLE   = 0,
    ITEM_CLASS_CONTAINER    = 1,
    ITEM_CLASS_WEAPON       = 2,
    ITEM_CLASS_ARMOR        = 4,
    ITEM_CLASS_REAGENT      = 5,
    ITEM_CLASS_PROJECTILE   = 6,
    ITEM_CLASS_TRADE_GOODS  = 7,
    ITEM_CLASS_RECIPE       = 9,
    ITEM_CLASS_QUIVER       = 11,
    ITEM_CLASS_QUEST        = 12,
    ITEM_CLASS_KEY          = 13,
    ITEM_CLASS_MISC         = 15,
};
struct ItemPrototype
{
    uint32 ItemId;
    uint32 Class;
    uint32 SubClass;
    char *Name1;
    char *Name2;
    char *Name3;
    char *Name4;
    uint32 DisplayId;
    uint32 Quality;
    uint32 Flags;
    uint32 BuyPrice;
    uint32 SellPrice;
    uint32 InventoryType;
    uint32 AllowableClass;
    uint32 AllowableRace;
    uint32 ItemLevel;
    uint32 RequiredLevel;
    uint32 RequiredSkill;
    uint32 RequiredSkillRank;
    uint32 Field20;
    uint32 Field21;
    uint32 Field22;
    uint32 Field23;
    uint32 MaxCount;
    uint32 Field25;
    uint32 ItemStatType [10]; //tolua_hide
    uint32 ItemStatValue [10]; //tolua_hide
    float DamageMin [5]; //tolua_hide
    float DamageMax [5]; //tolua_hide
    uint32 DamageType [5];//tolua_hide
    uint32 Armor;
    uint32 Field62;
    uint32 FireRes;
    uint32 NatureRes;
    uint32 FrostRes;
    uint32 ShadowRes;
    uint32 ArcaneRes;
    uint32 Delay;
    uint32 Field69;
    uint32 SpellId [5];   //tolua_hide
    uint32 SpellTrigger [5]; //tolua_hide
    uint32 SpellCharges [5]; //tolua_hide
    uint32 SpellCooldown [5];//tolua_hide
    uint32 SpellCategory [5];//tolua_hide
    uint32 SpellCategoryCooldown [5];//tolua_hide
    uint32 Bonding;
    char *Description;
    uint32 Field102;
    uint32 Field103;
    uint32 Field104;
    uint32 Field105;
    uint32 Field106;
    uint32 Field107;
    uint32 Field108;
    uint32 Field109;
    uint32 Field110;
    uint32 Field111;
    uint32 MaxDurability;

    ~ItemPrototype ()
    {
        delete [] Name1;
        delete [] Name2;
        delete [] Name3;
        delete [] Name4;
        delete [] Description;
    }
};

class Unit;

/**
 * This class represents any wearable, useable, careable, droppable item
 * in the world.
 */
class Item : public Object
{
protected:
    friend class WorldServer;
    friend class Player;

    /// Item prototype data
    ItemPrototype *ItemProto;

    /// Item prototype data
    static DECLARE_VECTOR_SORTED (ItemProtoVector, ItemPrototype *, ) ItemPrototypes; //tolua_hide

    /// Preload all static data from database
    static bool PreloadStaticData ();
    /// Unload any static data we loaded before
    static void UnloadStaticData ();

protected:
    /// Private destructor -- use DecRef
    virtual ~Item ();

public:
    /// Owner unit
    Unit *Owner;

    /// Create an empty item
    Item ();

    /// Create a new item and assign it a newly allocated GUID
    bool Create (uint32 iItemId, Unit *iOwner);

    /// Create the item with known GUID
    bool Create (uint32 iLowGuid, uint32 iItemId, Unit *iOwner);

    /// Query item prototype data
    ItemPrototype *GetProto ()
    { return ItemProto; }

    /// Return the prototype of the idem with given identifier
    static ItemPrototype *FindProto (uint iItemId);

    /// Item Properties
    void SetDurability (uint32 Value); //tolua_hide
    void SetDurabilityToMax (); //tolua_hide

    //----------------// Object saving & loading //----------------//

    /// Save this object to database
    virtual bool SaveToDB ();
    /// Load this object from database
    bool LoadFromDB (uint32 iLowGuid);
    /// Delete this object from database
    virtual bool DeleteFromDB ();
};

#endif // __ITEM_H__
