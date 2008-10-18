/**
 *     \file  src/worldserver/ProtocolVectors.h
 *    \brief  Defines vectors used by packets of the world server protocol.
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

#include "Vector.h"
#include "Object.h"

#ifndef __PROTOCOL_VECTORS_H__
#define __PROTOCOL_VECTORS_H__

class DatabaseExecutor; //tolua_hide

//----// SMSG_LOOT_RESPONSE

struct LootItem
{
    uint8 Slot;
    uint32 Guidsno;
    uint32 Quantity;
    uint32 Displayid;
};

DECLARE_VECTOR (LootResponseVector, LootItem *, );

//----// SMSG_FRIEND_LIST

struct FriendStr
{
    uint64 PlayerGUID;
    unsigned char Status;

    int Area;
    int Level;
    int Class;
};

DECLARE_VECTOR (FriendsVector, FriendStr *, );

//----// SMSG_GROUP_LIST
struct Member
{
    uint8 Slotid;
    char * Membername;
    uint32 Guidsno;

    ~Member ()
    { delete [] Membername; }
};

DECLARE_VECTOR (MembersVector, Member *, );

//----// SMSG_CHAR_ENUM

/**
 * This is a simplified version of Player class containing only
 * the minimally required data fields, to reduce database load
 * on character enumeration.
 */
struct CharacterData
{
    uint64 GUID;
    const char *Name;
    uint8 Race;
    uint8 Class;
    uint8 Gender;
    uint8 Skin;
    uint8 Face;
    uint8 HairStyle;
    uint8 HairColor;
    uint8 FacialHair;
    uint8 Level;
    uint32 ZoneId;
    uint32 MapId;
    float PositionX;
    float PositionY;
    float PositionZ;
    uint32 Guild;
    uint32 Unknown;
    uint8 RestState;
    uint32 PetInfoId;
    uint32 PetLevel;
    uint32 PetFamilyId;

    struct SlotItemData
    {
        uint32 DisplayId;
        uint8 InventoryType;
    };
    DECLARE_VECTOR (SlotItemsVector, SlotItemData *, ) SlotItems;

    CharacterData ()
    { Name = NULL; }

    ~CharacterData ()
    { delete [] Name; }

    /**
     * Load character data from database, given the lower part of GUID
     * (the upper part is supposed to be HIGHGUID_PLAYER).
     */
    bool Load (DatabaseExecutor *dbex, uint32 iLowGuid);
};

DECLARE_VECTOR (CharsVector, CharacterData *, );

struct DamageInfo
{
    /// Damage type: 0 - white font, 1 - yellow
    uint32 Type;
    /// damage float
    uint32 Float;
    /// Damage amount
    uint32 Damage;
    /// damage absorbed
    uint32 Absorbed;
    /// new victim state
    uint32 VictimState;
    /// victim round duraction
    uint32 RoundDuration;
    /// additional spell damage amount
    uint32 AdditionalSpellDamage;
    /// additional spell damage id
    uint32 AdditionalSpellId;
    /// Damage amount blocked
    uint32 AdditionalSpellAbsorbed;
};

DECLARE_VECTOR (DamageVector, DamageInfo *, );

#endif // __PROTOCOL_VECTORS_H__
