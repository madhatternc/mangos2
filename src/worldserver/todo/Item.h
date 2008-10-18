/**
 *     \file  src/worldserver/todo/Item.h
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

#include "Unit.h"

class Item : public Object
{
    friend class WorldServer;
    friend class DatabaseInterface;
    public:
        Item ( );
        void Create( uint32 guidlow, uint32 itemid );
        //inline const uint8 & getSlot( ) const { return slot; }
        //inline void setSlot( const uint8 & newslot ) { slot = newslot; }
        //uint8 slot;
        //uint32 * itemid;
        uint32 Class;
        uint32 SubClass;
        std::string name1;
        std::string name2;
        std::string name3;
        std::string name4;
        uint32 DisplayInfoID;
        uint32 OverallQualityID;
        uint32 Flags;
        uint32 Buyprice;
        uint32 Sellprice;
        uint32 Inventorytype;
        uint32 AllowableClass;
        uint32 AllowableRace;
        uint32 ItemLevel;
        uint32 RequiredLevel;
        uint32 RequiredSkill;
        uint32 RequiredSkillRank;
        uint32 MaxCount;
        uint32 Stackable;
        uint32 ContainerSlots;
        uint32 BonusStat[10];
        uint32 BonusAmount[10];

        uint32 MinimumDamage[5];
        uint32 MaximumDamage[5];
        uint32 DamageType[5];

        uint32 Resistances[7];                              // a new resistance has been added for 0.10?
        uint32 Delay;
        uint32 AmmunitionType;
        uint32 MaxDurability;

        uint32 SpellID[5];
        uint32 SpellTrigger[5];
        uint32 SpellCharges[5];
        uint32 SpellCooldown[5];
        uint32 SpellCategory[5];
        uint32 SpellCategoryCooldown[5];

        uint32 Bonding;
        std::string Description;
        uint32 Pagetext;
        uint32 LanguageID;
        uint32 PageMaterial;
        uint32 StartQuestID;
        uint32 LockID;
        uint32 Material;
        uint32 Sheathetype;
        uint32 Unknown1;
        uint32 Unknown2;

};
#endif // __ITEM_H__
