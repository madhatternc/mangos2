/**
 *     \file  src/worldserver/UpdateFields.h
 *    \brief  Defines object sizes and offsets into their data fields.
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

#ifndef __UPDATE_FIELDS_H__
#define __UPDATE_FIELDS_H__

#include "Debug.h"

// Total fields
#define UPDATE_BLOCKS   864
#define UPDATE_FIELDS   (UPDATE_BLOCKS * 32)
// Total fields in a unit
#define UNIT_BLOCKS     5
#define UNIT_FIELDS     (UNIT_BLOCKS * 32)
// Total fields in a player object
// Here we update this sucker from 27*32 to 28*32 for 1.2.1 /Yellow
#define PLAYER_BLOCKS   33
#define PLAYER_FIELDS   (PLAYER_BLOCKS * 32)

//  UPDATE FIELDS for 1.3.0

enum ObjectUpdateFields
{
    OBJECT_FIELD_GUID                       = 0x0000,
    OBJECT_FIELD_TYPE                       = 0x0002,
    OBJECT_FIELD_ENTRY                      = 0x0003,
    OBJECT_FIELD_SCALE_X                    = 0x0004,
    OBJECT_FIELD_PADDING                    = 0x0005,
    OBJECT_END                              = 0x0006
};

enum ItemUpdateFields
{
    ITEM_START                              = OBJECT_END,
    ITEM_FIELD_OWNER                        = 0x0000 + ITEM_START,
    ITEM_FIELD_CONTAINED                    = 0x0002 + ITEM_START,
    ITEM_FIELD_CREATOR                      = 0x0004 + ITEM_START,
    ITEM_FIELD_GIFTCREATOR                  = 0x0006 + ITEM_START,
    ITEM_FIELD_STACK_COUNT                  = 0x0008 + ITEM_START,
    ITEM_FIELD_DURATION                     = 0x0009 + ITEM_START,
    ITEM_FIELD_SPELL_CHARGES                = 0x000A + ITEM_START,
    ITEM_FIELD_FLAGS                        = 0x000F + ITEM_START,
    ITEM_FIELD_ENCHANTMENT                  = 0x0010 + ITEM_START,
    ITEM_FIELD_PROPERTY_SEED                = 0x0025 + ITEM_START,
    ITEM_FIELD_RANDOM_PROPERTIES_ID         = 0x0026 + ITEM_START,
    ITEM_FIELD_ITEM_TEXT_ID                 = 0x0027 + ITEM_START,
    ITEM_FIELD_DURABILITY                   = 0x0028 + ITEM_START,
    ITEM_FIELD_MAXDURABILITY                = 0x0029 + ITEM_START,
    ITEM_END                                = 0x002A + ITEM_START
};

enum ContainerUpdateFields
{
    CONTAINER_START                         = ITEM_END,
    CONTAINER_FIELD_NUM_SLOTS               = 0x0000 + CONTAINER_START,
    CONTAINER_ALIGN_PAD                     = 0x0001 + CONTAINER_START,
    CONTAINER_FIELD_SLOT_1                  = 0x0002 + CONTAINER_START,
    CONTAINER_END                           = 0x002A + CONTAINER_START
};

enum UnitUpdateFields
{
    UNIT_START                              = OBJECT_END,
    UNIT_FIELD_CHARM                        = 0x0000 + UNIT_START,
    UNIT_FIELD_SUMMON                       = 0x0002 + UNIT_START,
    UNIT_FIELD_CHARMEDBY                    = 0x0004 + UNIT_START,
    UNIT_FIELD_SUMMONEDBY                   = 0x0006 + UNIT_START,
    UNIT_FIELD_CREATEDBY                    = 0x0008 + UNIT_START,
    UNIT_FIELD_TARGET                       = 0x000A + UNIT_START,
    UNIT_FIELD_PERSUADED                    = 0x000C + UNIT_START,
    UNIT_FIELD_CHANNEL_OBJECT               = 0x000E + UNIT_START,
    UNIT_FIELD_HEALTH                       = 0x0010 + UNIT_START,
    UNIT_FIELD_POWER1                       = 0x0011 + UNIT_START,
    UNIT_FIELD_POWER2                       = 0x0012 + UNIT_START,
    UNIT_FIELD_POWER3                       = 0x0013 + UNIT_START,
    UNIT_FIELD_POWER4                       = 0x0014 + UNIT_START,
    UNIT_FIELD_POWER5                       = 0x0015 + UNIT_START,
    UNIT_FIELD_MAXHEALTH                    = 0x0016 + UNIT_START,
    UNIT_FIELD_MAXPOWER1                    = 0x0017 + UNIT_START,
    UNIT_FIELD_MAXPOWER2                    = 0x0018 + UNIT_START,
    UNIT_FIELD_MAXPOWER3                    = 0x0019 + UNIT_START,
    UNIT_FIELD_MAXPOWER4                    = 0x001A + UNIT_START,
    UNIT_FIELD_MAXPOWER5                    = 0x001B + UNIT_START,
    UNIT_FIELD_LEVEL                        = 0x001C + UNIT_START,
    UNIT_FIELD_FACTIONTEMPLATE              = 0x001D + UNIT_START,
    UNIT_FIELD_BYTES_0                      = 0x001E + UNIT_START,
    UNIT_VIRTUAL_ITEM_SLOT_DISPLAY          = 0x001F + UNIT_START,
    UNIT_VIRTUAL_ITEM_INFO                  = 0x0022 + UNIT_START,
    UNIT_FIELD_FLAGS                        = 0x0028 + UNIT_START,
    UNIT_FIELD_AURA                         = 0x0029 + UNIT_START,
    UNIT_FIELD_AURALEVELS                   = 0x0061 + UNIT_START,
    UNIT_FIELD_AURAAPPLICATIONS             = 0x006B + UNIT_START,
    UNIT_FIELD_AURAFLAGS                    = 0x0075 + UNIT_START,
    UNIT_FIELD_AURASTATE                    = 0x007C + UNIT_START,
    UNIT_FIELD_BASEATTACKTIME               = 0x007D + UNIT_START,
    UNIT_FIELD_RANGEDATTACKTIME             = 0x007F + UNIT_START,
    UNIT_FIELD_BOUNDINGRADIUS               = 0x0080 + UNIT_START,
    UNIT_FIELD_COMBATREACH                  = 0x0081 + UNIT_START,
    UNIT_FIELD_DISPLAYID                    = 0x0082 + UNIT_START,
    UNIT_FIELD_NATIVEDISPLAYID              = 0x0083 + UNIT_START,
    UNIT_FIELD_MOUNTDISPLAYID               = 0x0084 + UNIT_START,
    UNIT_FIELD_MINDAMAGE                    = 0x0085 + UNIT_START,
    UNIT_FIELD_MAXDAMAGE                    = 0x0086 + UNIT_START,
    UNIT_FIELD_MINOFFHANDDAMAGE             = 0x0087 + UNIT_START,
    UNIT_FIELD_MAXOFFHANDDAMAGE             = 0x0088 + UNIT_START,
    UNIT_FIELD_BYTES_1                      = 0x0089 + UNIT_START,
    UNIT_FIELD_PETNUMBER                    = 0x008A + UNIT_START,
    UNIT_FIELD_PET_NAME_TIMESTAMP           = 0x008B + UNIT_START,
    UNIT_FIELD_PETEXPERIENCE                = 0x008C + UNIT_START,
    UNIT_FIELD_PETNEXTLEVELEXP              = 0x008D + UNIT_START,
    UNIT_DYNAMIC_FLAGS                      = 0x008E + UNIT_START,
    UNIT_CHANNEL_SPELL                      = 0x008F + UNIT_START,
    UNIT_MOD_CAST_SPEED                     = 0x0090 + UNIT_START,
    UNIT_CREATED_BY_SPELL                   = 0x0091 + UNIT_START,
    UNIT_NPC_FLAGS                          = 0x0092 + UNIT_START,
    UNIT_NPC_EMOTESTATE                     = 0x0093 + UNIT_START,
    UNIT_TRAINING_POINTS                    = 0x0094 + UNIT_START,
    UNIT_FIELD_STAT0                        = 0x0095 + UNIT_START,
    UNIT_FIELD_STAT1                        = 0x0096 + UNIT_START,
    UNIT_FIELD_STAT2                        = 0x0097 + UNIT_START,
    UNIT_FIELD_STAT3                        = 0x0098 + UNIT_START,
    UNIT_FIELD_STAT4                        = 0x0099 + UNIT_START,
    UNIT_FIELD_RESISTANCES                  = 0x009A + UNIT_START,
    UNIT_FIELD_ATTACKPOWER                  = 0x00A1 + UNIT_START,
    UNIT_FIELD_BASE_MANA                    = 0x00A2 + UNIT_START,
    UNIT_FIELD_ATTACK_POWER_MODS            = 0x00A3 + UNIT_START,
    UNIT_FIELD_BYTES_2                      = 0x00A4 + UNIT_START,
    UNIT_FIELD_RANGEDATTACKPOWER            = 0x00A5 + UNIT_START,
    UNIT_FIELD_RANGED_ATTACK_POWER_MODS     = 0x00A6 + UNIT_START,
    UNIT_FIELD_MINRANGEDDAMAGE              = 0x00A7 + UNIT_START,
    UNIT_FIELD_MAXRANGEDDAMAGE              = 0x00A8 + UNIT_START,
    UNIT_FIELD_PADDING                      = 0x00A9 + UNIT_START,
    UNIT_END                                = 0x00AA + UNIT_START
};

enum PlayerUpdateFields
{
    PLAYER_START                            = UNIT_END,
    PLAYER_SELECTION                        = 0x0000 + PLAYER_START,
    PLAYER_DUEL_ARBITER                     = 0x0002 + PLAYER_START,
    PLAYER_FLAGS                            = 0x0004 + PLAYER_START,
    PLAYER_GUILDID                          = 0x0005 + PLAYER_START,
    PLAYER_GUILDRANK                        = 0x0006 + PLAYER_START,
    PLAYER_BYTES                            = 0x0007 + PLAYER_START,
    PLAYER_BYTES_2                          = 0x0008 + PLAYER_START,
    PLAYER_BYTES_3                          = 0x0009 + PLAYER_START,
    PLAYER_DUAL_TEAM                        = 0x000A + PLAYER_START,
    PLAYER_GUILD_TIMESTAMP                  = 0x000B + PLAYER_START,
    PLAYER_VISIBLE_ITEM_1_0                 = 0x000C + PLAYER_START,
    PLAYER_VISIBLE_ITEM_1_PROPERTIES        = 0x000D + PLAYER_START,
    PLAYER_VISIBLE_ITEM_2_0                 = 0x0015 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_2_PROPERTIES        = 0x0016 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_3_0                 = 0x001E + PLAYER_START,
    PLAYER_VISIBLE_ITEM_3_PROPERTIES        = 0x001F + PLAYER_START,
    PLAYER_VISIBLE_ITEM_4_0                 = 0x0027 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_4_PROPERTIES        = 0x0028 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_5_0                 = 0x0030 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_5_PROPERTIES        = 0x0031 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_6_0                 = 0x0039 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_6_PROPERTIES        = 0x003A + PLAYER_START,
    PLAYER_VISIBLE_ITEM_7_0                 = 0x0042 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_7_PROPERTIES        = 0x0043 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_8_0                 = 0x004B + PLAYER_START,
    PLAYER_VISIBLE_ITEM_8_PROPERTIES        = 0x004C + PLAYER_START,
    PLAYER_VISIBLE_ITEM_9_0                 = 0x0054 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_9_PROPERTIES        = 0x0055 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_10_0                = 0x005D + PLAYER_START,
    PLAYER_VISIBLE_ITEM_10_PROPERTIES       = 0x005E + PLAYER_START,
    PLAYER_VISIBLE_ITEM_11_0                = 0x0066 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_11_PROPERTIES       = 0x0067 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_12_0                = 0x006F + PLAYER_START,
    PLAYER_VISIBLE_ITEM_12_PROPERTIES       = 0x0070 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_13_0                = 0x0078 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_13_PROPERTIES       = 0x0079 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_14_0                = 0x0081 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_14_PROPERTIES       = 0x0082 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_15_0                = 0x008A + PLAYER_START,
    PLAYER_VISIBLE_ITEM_15_PROPERTIES       = 0x008B + PLAYER_START,
    PLAYER_VISIBLE_ITEM_16_0                = 0x0093 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_16_PROPERTIES       = 0x0094 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_17_0                = 0x009C + PLAYER_START,
    PLAYER_VISIBLE_ITEM_17_PROPERTIES       = 0x009D + PLAYER_START,
    PLAYER_VISIBLE_ITEM_18_0                = 0x00A5 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_18_PROPERTIES       = 0x00A6 + PLAYER_START,
    PLAYER_VISIBLE_ITEM_19_0                = 0x00AE + PLAYER_START,
    PLAYER_VISIBLE_ITEM_19_PROPERTIES       = 0x00AF + PLAYER_START,
    PLAYER_FIELD_PAD_0                      = 0x00B7 + PLAYER_START,
    PLAYER_FIELD_INV_SLOT_HEAD              = 0x00B8 + PLAYER_START,
    PLAYER_FIELD_PACK_SLOT_1                = 0x00E6 + PLAYER_START,
    PLAYER_FIELD_BANK_SLOT_1                = 0x0106 + PLAYER_START,
    PLAYER_FIELD_BANKBAG_SLOT_1             = 0x0136 + PLAYER_START,
    PLAYER_FIELD_VENDORBUYBACK_SLOT         = 0x0142 + PLAYER_START,
    PLAYER_FARSIGHT                         = 0x0144 + PLAYER_START,
    PLAYER__FIELD_COMBO_TARGET              = 0x0146 + PLAYER_START,
    PLAYER_FIELD_BUYBACK_NPC                = 0x0148 + PLAYER_START,
    PLAYER_XP                               = 0x014A + PLAYER_START,
    PLAYER_NEXT_LEVEL_XP                    = 0x014B + PLAYER_START,
    PLAYER_SKILL_INFO_1_1                   = 0x014C + PLAYER_START,
    PLAYER_QUEST_LOG_1_1                    = 0x02CC + PLAYER_START,
    PLAYER_CHARACTER_POINTS1                = 0x0308 + PLAYER_START,
    PLAYER_CHARACTER_POINTS2                = 0x0309 + PLAYER_START,
    PLAYER_TRACK_CREATURES                  = 0x030A + PLAYER_START,
    PLAYER_TRACK_RESOURCES                  = 0x030B + PLAYER_START,
    PLAYER_CHAT_FILTERS                     = 0x030C + PLAYER_START,
    PLAYER_BLOCK_PERCENTAGE                 = 0x030D + PLAYER_START,
    PLAYER_DODGE_PERCENTAGE                 = 0x030E + PLAYER_START,
    PLAYER_PARRY_PERCENTAGE                 = 0x030F + PLAYER_START,
    PLAYER_CRIT_PERCENTAGE                  = 0x0310 + PLAYER_START,
    PLAYER_EXPLORED_ZONES_1                 = 0x0311 + PLAYER_START,
    PLAYER_REST_STATE_EXPERIENCE            = 0x0331 + PLAYER_START,
    PLAYER_FIELD_COINAGE                    = 0x0332 + PLAYER_START,
    PLAYER_FIELD_POSSTAT0                   = 0x0333 + PLAYER_START,
    PLAYER_FIELD_POSSTAT1                   = 0x0334 + PLAYER_START,
    PLAYER_FIELD_POSSTAT2                   = 0x0335 + PLAYER_START,
    PLAYER_FIELD_POSSTAT3                   = 0x0336 + PLAYER_START,
    PLAYER_FIELD_POSSTAT4                   = 0x0337 + PLAYER_START,
    PLAYER_FIELD_NEGSTAT0                   = 0x0338 + PLAYER_START,
    PLAYER_FIELD_NEGSTAT1                   = 0x0339 + PLAYER_START,
    PLAYER_FIELD_NEGSTAT2                   = 0x033A + PLAYER_START,
    PLAYER_FIELD_NEGSTAT3                   = 0x033B + PLAYER_START,
    PLAYER_FIELD_NEGSTAT4                   = 0x033C + PLAYER_START,
    PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE = 0x033D + PLAYER_START,
    PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE = 0x0344 + PLAYER_START,
    PLAYER_FIELD_MOD_DAMAGE_DONE_POS        = 0x034B + PLAYER_START,
    PLAYER_FIELD_MOD_DAMAGE_DONE_NEG        = 0x0352 + PLAYER_START,
    PLAYER_FIELD_MOD_DAMAGE_DONE_PCT        = 0x0359 + PLAYER_START,
    PLAYER_FIELD_BYTES                      = 0x0360 + PLAYER_START,
    PLAYER_AMMO_ID                          = 0x0361 + PLAYER_START,
    PLAYER_FIELD_PVP_MEDALS                 = 0x0362 + PLAYER_START,
    PLAYER_FIELD_BUYBACK_ITEM_ID            = 0x0363 + PLAYER_START,
    PLAYER_FIELD_BUYBACK_RANDOM_PROPERTIES_ID = 0x0364 + PLAYER_START,
    PLAYER_FIELD_BUYBACK_SEED               = 0x0365 + PLAYER_START,
    PLAYER_FIELD_BUYBACK_PRICE              = 0x0366 + PLAYER_START,
    PLAYER_FIELD_BUYBACK_DURABILITY         = 0x0367 + PLAYER_START,
    PLAYER_FIELD_BUYBACK_COUNT              = 0x0368 + PLAYER_START,
    PLAYER_FIELD_PADDING                    = 0x0369 + PLAYER_START,
    PLAYER_END                              = 0x036A + PLAYER_START
};

enum GameObjectUpdateFields
{
    GAMEOBJECT_START                        = OBJECT_END,
    GAMEOBJECT_DISPLAYID                    = 0x0000 + GAMEOBJECT_START,
    GAMEOBJECT_FLAGS                        = 0x0001 + GAMEOBJECT_START,
    GAMEOBJECT_ROTATION                     = 0x0002 + GAMEOBJECT_START,
    GAMEOBJECT_STATE                        = 0x0006 + GAMEOBJECT_START,
    GAMEOBJECT_TIMESTAMP                    = 0x0007 + GAMEOBJECT_START,
    GAMEOBJECT_POS_X                        = 0x0008 + GAMEOBJECT_START,
    GAMEOBJECT_POS_Y                        = 0x0009 + GAMEOBJECT_START,
    GAMEOBJECT_POS_Z                        = 0x000A + GAMEOBJECT_START,
    GAMEOBJECT_FACING                       = 0x000B + GAMEOBJECT_START,
    GAMEOBJECT_DYN_FLAGS                    = 0x000C + GAMEOBJECT_START,
    GAMEOBJECT_FACTION                      = 0x000D + GAMEOBJECT_START,
    GAMEOBJECT_TYPE_ID                      = 0x000E + GAMEOBJECT_START,
    GAMEOBJECT_LEVEL                        = 0x000F + GAMEOBJECT_START,
    GAMEOBJECT_END                          = 0x0010 + GAMEOBJECT_START
};

enum DynamicObjectUpdateFields
{
    DYNAMICOBJECT_START                     = OBJECT_END,
    DYNAMICOBJECT_CASTER                    = 0x0000 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_BYTES                     = 0x0002 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_SPELLID                   = 0x0003 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_RADIUS                    = 0x0004 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_POS_X                     = 0x0005 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_POS_Y                     = 0x0006 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_POS_Z                     = 0x0007 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_FACING                    = 0x0008 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_PAD                       = 0x0009 + DYNAMICOBJECT_START,
    DYNAMICOBJECT_END                       = 0x000A + DYNAMICOBJECT_START
};

enum CorpseUpdateFields
{
    CORPSE_START                            = OBJECT_END,
    CORPSE_FIELD_OWNER                      = 0x0000 + CORPSE_START,
    CORPSE_FIELD_FACING                     = 0x0002 + CORPSE_START,
    CORPSE_FIELD_POS_X                      = 0x0003 + CORPSE_START,
    CORPSE_FIELD_POS_Y                      = 0x0004 + CORPSE_START,
    CORPSE_FIELD_POS_Z                      = 0x0005 + CORPSE_START,
    CORPSE_FIELD_DISPLAY_ID                 = 0x0006 + CORPSE_START,
    CORPSE_FIELD_ITEM                       = 0x0007 + CORPSE_START,
    CORPSE_FIELD_BYTES_1                    = 0x001A + CORPSE_START,
    CORPSE_FIELD_BYTES_2                    = 0x001B + CORPSE_START,
    CORPSE_FIELD_GUILD                      = 0x001C + CORPSE_START,
    CORPSE_FIELD_FLAGS                      = 0x001D + CORPSE_START,
    CORPSE_END                              = 0x001E + CORPSE_START
};

#endif // __UPDATE_FIELDS_H__
