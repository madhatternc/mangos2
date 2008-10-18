/* AUTOGENERATED. DO NOT MODIFY !!! */
/* RULES_MTIME: 1223665167.0 */
#ifndef __OPCODES_H__
#define __OPCODES_H__

#include "Sockets.h"
#include "ProtocolVectors.h"

const char *GetPacketName (uint Opcode);
enum Opcodes
{
	MSG_NULL_ACTION = 0x0000,
	CMSG_BOOTME = 0x0001,
	CMSG_DBLOOKUP = 0x0002,
	SMSG_DBLOOKUP = 0x0003,
	CMSG_QUERY_OBJECT_POSITION = 0x0004,
	SMSG_QUERY_OBJECT_POSITION = 0x0005,
	CMSG_QUERY_OBJECT_ROTATION = 0x0006,
	SMSG_QUERY_OBJECT_ROTATION = 0x0007,
	CMSG_WORLD_TELEPORT = 0x0008,
	CMSG_TELEPORT_TO_UNIT = 0x0009,
	CMSG_ZONE_MAP = 0x000A,
	SMSG_ZONE_MAP = 0x000B,
	CMSG_DEBUG_CHANGECELLZONE = 0x000C,
	CMSG_EMBLAZON_TABARD_OBSOLETE = 0x000D,
	CMSG_UNEMBLAZON_TABARD_OBSOLETE = 0x000E,
	CMSG_RECHARGE = 0x000F,
	CMSG_LEARN_SPELL = 0x0010,
	CMSG_CREATEMONSTER = 0x0011,
	CMSG_DESTROYMONSTER = 0x0012,
	CMSG_CREATEITEM = 0x0013,
	CMSG_CREATEGAMEOBJECT = 0x0014,
	CMSG_MAKEMONSTERATTACKME = 0x0015,
	CMSG_MAKEMONSTERATTACKGUID = 0x0016,
	CMSG_ENABLEDEBUGCOMBATLOGGING_OBSOLETE = 0x0017,
	CMSG_FORCEACTION = 0x0018,
	CMSG_FORCEACTIONONOTHER = 0x0019,
	CMSG_FORCEACTIONSHOW = 0x001A,
	SMSG_FORCEACTIONSHOW = 0x001B,
	SMSG_ATTACKERSTATEUPDATEDEBUGINFO_OBSOLETE = 0x001C,
	SMSG_DEBUGINFOSPELL_OBSOLETE = 0x001D,
	SMSG_DEBUGINFOSPELLMISS_OBSOLETE = 0x001E,
	SMSG_DEBUG_PLAYER_RANGE_OBSOLETE = 0x001F,
	CMSG_UNDRESSPLAYER = 0x0020,
	CMSG_BEASTMASTER = 0x0021,
	CMSG_GODMODE = 0x0022,
	SMSG_GODMODE = 0x0023,
	CMSG_CHEAT_SETMONEY = 0x0024,
	CMSG_LEVEL_CHEAT = 0x0025,
	CMSG_PET_LEVEL_CHEAT = 0x0026,
	CMSG_LEVELUP_CHEAT_OBSOLETE = 0x0027,
	CMSG_COOLDOWN_CHEAT = 0x0028,
	CMSG_USE_SKILL_CHEAT = 0x0029,
	CMSG_FLAG_QUEST = 0x002A,
	CMSG_FLAG_QUEST_FINISH = 0x002B,
	CMSG_CLEAR_QUEST = 0x002C,
	CMSG_SEND_EVENT = 0x002D,
	CMSG_DEBUG_AISTATE = 0x002E,
	SMSG_DEBUG_AISTATE = 0x002F,
	CMSG_DISABLE_PVP_CHEAT = 0x0030,
	CMSG_ADVANCE_SPAWN_TIME = 0x0031,
	CMSG_PVP_PORT_OBSOLETE = 0x0032,
	CMSG_AUTH_SRP6_BEGIN = 0x0033,
	CMSG_AUTH_SRP6_PROOF = 0x0034,
	CMSG_AUTH_SRP6_RECODE = 0x0035,
	CMSG_CHAR_CREATE = 0x0036,
	CMSG_CHAR_ENUM = 0x0037,
	CMSG_CHAR_DELETE = 0x0038,
	SMSG_AUTH_SRP6_RESPONSE = 0x0039,
	SMSG_CHAR_CREATE = 0x003A,
	SMSG_CHAR_ENUM = 0x003B,
	SMSG_CHAR_DELETE = 0x003C,
	CMSG_PLAYER_LOGIN = 0x003D,
	SMSG_NEW_WORLD = 0x003E,
	SMSG_TRANSFER_PENDING = 0x003F,
	SMSG_TRANSFER_ABORTED = 0x0040,
	SMSG_CHARACTER_LOGIN_FAILED = 0x0041,
	SMSG_LOGIN_SETTIMESPEED = 0x0042,
	SMSG_GAMETIME_UPDATE = 0x0043,
	CMSG_GAMETIME_SET = 0x0044,
	SMSG_GAMETIME_SET = 0x0045,
	CMSG_GAMESPEED_SET = 0x0046,
	SMSG_GAMESPEED_SET = 0x0047,
	CMSG_SERVERTIME = 0x0048,
	SMSG_SERVERTIME = 0x0049,
	CMSG_PLAYER_LOGOUT = 0x004A,
	CMSG_LOGOUT_REQUEST = 0x004B,
	SMSG_LOGOUT_RESPONSE = 0x004C,
	SMSG_LOGOUT_COMPLETE = 0x004D,
	CMSG_LOGOUT_CANCEL = 0x004E,
	SMSG_LOGOUT_CANCEL_ACK = 0x004F,
	CMSG_NAME_QUERY = 0x0050,
	SMSG_NAME_QUERY_RESPONSE = 0x0051,
	CMSG_PET_NAME_QUERY = 0x0052,
	SMSG_PET_NAME_QUERY_RESPONSE = 0x0053,
	CMSG_GUILD_QUERY = 0x0054,
	SMSG_GUILD_QUERY_RESPONSE = 0x0055,
	CMSG_ITEM_QUERY_SINGLE = 0x0056,
	CMSG_ITEM_QUERY_MULTIPLE = 0x0057,
	SMSG_ITEM_QUERY_SINGLE_RESPONSE = 0x0058,
	SMSG_ITEM_QUERY_MULTIPLE_RESPONSE = 0x0059,
	CMSG_PAGE_TEXT_QUERY = 0x005A,
	SMSG_PAGE_TEXT_QUERY_RESPONSE = 0x005B,
	CMSG_QUEST_QUERY = 0x005C,
	SMSG_QUEST_QUERY_RESPONSE = 0x005D,
	CMSG_GAMEOBJECT_QUERY = 0x005E,
	SMSG_GAMEOBJECT_QUERY_RESPONSE = 0x005F,
	CMSG_CREATURE_QUERY = 0x0060,
	SMSG_CREATURE_QUERY_RESPONSE = 0x0061,
	CMSG_WHO = 0x0062,
	SMSG_WHO = 0x0063,
	CMSG_WHOIS = 0x0064,
	SMSG_WHOIS = 0x0065,
	CMSG_FRIEND_LIST = 0x0066,
	SMSG_FRIEND_LIST = 0x0067,
	SMSG_FRIEND_STATUS = 0x0068,
	CMSG_ADD_FRIEND = 0x0069,
	CMSG_DEL_FRIEND = 0x006A,
	SMSG_IGNORE_LIST = 0x006B,
	CMSG_ADD_IGNORE = 0x006C,
	CMSG_DEL_IGNORE = 0x006D,
	CMSG_GROUP_INVITE = 0x006E,
	SMSG_GROUP_INVITE = 0x006F,
	CMSG_GROUP_CANCEL = 0x0070,
	SMSG_GROUP_CANCEL = 0x0071,
	CMSG_GROUP_ACCEPT = 0x0072,
	CMSG_GROUP_DECLINE = 0x0073,
	SMSG_GROUP_DECLINE = 0x0074,
	CMSG_GROUP_UNINVITE = 0x0075,
	CMSG_GROUP_UNINVITE_GUID = 0x0076,
	SMSG_GROUP_UNINVITE = 0x0077,
	CMSG_GROUP_SET_LEADER = 0x0078,
	SMSG_GROUP_SET_LEADER = 0x0079,
	CMSG_LOOT_METHOD = 0x007A,
	CMSG_GROUP_DISBAND = 0x007B,
	SMSG_GROUP_DESTROYED = 0x007C,
	SMSG_GROUP_LIST = 0x007D,
	SMSG_PARTY_MEMBER_STATS = 0x007E,
	SMSG_PARTY_COMMAND_RESULT = 0x007F,
	UMSG_UPDATE_GROUP_MEMBERS = 0x0080,
	CMSG_GUILD_CREATE = 0x0081,
	CMSG_GUILD_INVITE = 0x0082,
	SMSG_GUILD_INVITE = 0x0083,
	CMSG_GUILD_ACCEPT = 0x0084,
	CMSG_GUILD_DECLINE = 0x0085,
	SMSG_GUILD_DECLINE = 0x0086,
	CMSG_GUILD_INFO = 0x0087,
	SMSG_GUILD_INFO = 0x0088,
	CMSG_GUILD_ROSTER = 0x0089,
	SMSG_GUILD_ROSTER = 0x008A,
	CMSG_GUILD_PROMOTE = 0x008B,
	CMSG_GUILD_DEMOTE = 0x008C,
	CMSG_GUILD_LEAVE = 0x008D,
	CMSG_GUILD_REMOVE = 0x008E,
	CMSG_GUILD_DISBAND = 0x008F,
	CMSG_GUILD_LEADER = 0x0090,
	CMSG_GUILD_MOTD = 0x0091,
	SMSG_GUILD_EVENT = 0x0092,
	SMSG_GUILD_COMMAND_RESULT = 0x0093,
	UMSG_UPDATE_GUILD = 0x0094,
	CMSG_MESSAGECHAT = 0x0095,
	SMSG_MESSAGECHAT = 0x0096,
	CMSG_JOIN_CHANNEL = 0x0097,
	CMSG_LEAVE_CHANNEL = 0x0098,
	SMSG_CHANNEL_NOTIFY = 0x0099,
	CMSG_CHANNEL_LIST = 0x009A,
	SMSG_CHANNEL_LIST = 0x009B,
	CMSG_CHANNEL_PASSWORD = 0x009C,
	CMSG_CHANNEL_SET_OWNER = 0x009D,
	CMSG_CHANNEL_OWNER = 0x009E,
	CMSG_CHANNEL_MODERATOR = 0x009F,
	CMSG_CHANNEL_UNMODERATOR = 0x00A0,
	CMSG_CHANNEL_MUTE = 0x00A1,
	CMSG_CHANNEL_UNMUTE = 0x00A2,
	CMSG_CHANNEL_INVITE = 0x00A3,
	CMSG_CHANNEL_KICK = 0x00A4,
	CMSG_CHANNEL_BAN = 0x00A5,
	CMSG_CHANNEL_UNBAN = 0x00A6,
	CMSG_CHANNEL_ANNOUNCEMENTS = 0x00A7,
	CMSG_CHANNEL_MODERATE = 0x00A8,
	SMSG_UPDATE_OBJECT = 0x00A9,
	SMSG_DESTROY_OBJECT = 0x00AA,
	CMSG_USE_ITEM = 0x00AB,
	CMSG_OPEN_ITEM = 0x00AC,
	CMSG_READ_ITEM = 0x00AD,
	SMSG_READ_ITEM_OK = 0x00AE,
	SMSG_READ_ITEM_FAILED = 0x00AF,
	SMSG_ITEM_COOLDOWN = 0x00B0,
	CMSG_GAMEOBJ_USE = 0x00B1,
	CMSG_GAMEOBJ_CHAIR_USE_OBSOLETE = 0x00B2,
	SMSG_GAMEOBJECT_CUSTOM_ANIM = 0x00B3,
	CMSG_AREATRIGGER = 0x00B4,
	MSG_MOVE_START_FORWARD = 0x00B5,
	MSG_MOVE_START_BACKWARD = 0x00B6,
	MSG_MOVE_STOP = 0x00B7,
	MSG_MOVE_START_STRAFE_LEFT = 0x00B8,
	MSG_MOVE_START_STRAFE_RIGHT = 0x00B9,
	MSG_MOVE_STOP_STRAFE = 0x00BA,
	MSG_MOVE_JUMP = 0x00BB,
	MSG_MOVE_START_TURN_LEFT = 0x00BC,
	MSG_MOVE_START_TURN_RIGHT = 0x00BD,
	MSG_MOVE_STOP_TURN = 0x00BE,
	MSG_MOVE_START_PITCH_UP = 0x00BF,
	MSG_MOVE_START_PITCH_DOWN = 0x00C0,
	MSG_MOVE_STOP_PITCH = 0x00C1,
	MSG_MOVE_SET_RUN_MODE = 0x00C2,
	MSG_MOVE_SET_WALK_MODE = 0x00C3,
	MSG_MOVE_TOGGLE_LOGGING = 0x00C4,
	MSG_MOVE_TELEPORT = 0x00C5,
	MSG_MOVE_TELEPORT_CHEAT = 0x00C6,
	MSG_MOVE_TELEPORT_ACK = 0x00C7,
	MSG_MOVE_TOGGLE_FALL_LOGGING = 0x00C8,
	MSG_MOVE_FALL_LAND = 0x00C9,
	MSG_MOVE_START_SWIM = 0x00CA,
	MSG_MOVE_STOP_SWIM = 0x00CB,
	MSG_MOVE_SET_RUN_SPEED_CHEAT = 0x00CC,
	MSG_MOVE_SET_RUN_SPEED = 0x00CD,
	MSG_MOVE_SET_RUN_BACK_SPEED_CHEAT = 0x00CE,
	MSG_MOVE_SET_RUN_BACK_SPEED = 0x00CF,
	MSG_MOVE_SET_WALK_SPEED_CHEAT = 0x00D0,
	MSG_MOVE_SET_WALK_SPEED = 0x00D1,
	MSG_MOVE_SET_SWIM_SPEED_CHEAT = 0x00D2,
	MSG_MOVE_SET_SWIM_SPEED = 0x00D3,
	MSG_MOVE_SET_SWIM_BACK_SPEED_CHEAT = 0x00D4,
	MSG_MOVE_SET_SWIM_BACK_SPEED = 0x00D5,
	MSG_MOVE_SET_ALL_SPEED_CHEAT = 0x00D6,
	MSG_MOVE_SET_TURN_RATE_CHEAT = 0x00D7,
	MSG_MOVE_SET_TURN_RATE = 0x00D8,
	MSG_MOVE_TOGGLE_COLLISION_CHEAT = 0x00D9,
	MSG_MOVE_SET_FACING = 0x00DA,
	MSG_MOVE_SET_PITCH = 0x00DB,
	MSG_MOVE_WORLDPORT_ACK = 0x00DC,
	SMSG_MONSTER_MOVE = 0x00DD,
	SMSG_MOVE_WATER_WALK = 0x00DE,
	SMSG_MOVE_LAND_WALK = 0x00DF,
	MSG_MOVE_SET_RAW_POSITION_ACK = 0x00E0,
	CMSG_MOVE_SET_RAW_POSITION = 0x00E1,
	SMSG_FORCE_RUN_SPEED_CHANGE = 0x00E2,
	CMSG_FORCE_RUN_SPEED_CHANGE_ACK = 0x00E3,
	SMSG_FORCE_RUN_BACK_SPEED_CHANGE = 0x00E4,
	CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK = 0x00E5,
	SMSG_FORCE_SWIM_SPEED_CHANGE = 0x00E6,
	CMSG_FORCE_SWIM_SPEED_CHANGE_ACK = 0x00E7,
	SMSG_FORCE_MOVE_ROOT = 0x00E8,
	CMSG_FORCE_MOVE_ROOT_ACK = 0x00E9,
	SMSG_FORCE_MOVE_UNROOT = 0x00EA,
	CMSG_FORCE_MOVE_UNROOT_ACK = 0x00EB,
	MSG_MOVE_ROOT = 0x00EC,
	MSG_MOVE_UNROOT = 0x00ED,
	MSG_MOVE_HEARTBEAT = 0x00EE,
	SMSG_MOVE_KNOCK_BACK = 0x00EF,
	CMSG_MOVE_KNOCK_BACK_ACK = 0x00F0,
	MSG_MOVE_KNOCK_BACK = 0x00F1,
	SMSG_MOVE_FEATHER_FALL = 0x00F2,
	SMSG_MOVE_NORMAL_FALL = 0x00F3,
	SMSG_MOVE_SET_HOVER = 0x00F4,
	SMSG_MOVE_UNSET_HOVER = 0x00F5,
	CMSG_MOVE_HOVER_ACK = 0x00F6,
	MSG_MOVE_HOVER = 0x00F7,
	CMSG_TRIGGER_CINEMATIC_CHEAT = 0x00F8,
	CMSG_OPENING_CINEMATIC = 0x00F9,
	SMSG_TRIGGER_CINEMATIC = 0x00FA,
	CMSG_NEXT_CINEMATIC_CAMERA = 0x00FB,
	CMSG_COMPLETE_CINEMATIC = 0x00FC,
	SMSG_TUTORIAL_FLAGS = 0x00FD,
	CMSG_TUTORIAL_FLAG = 0x00FE,
	CMSG_TUTORIAL_CLEAR = 0x00FF,
	CMSG_TUTORIAL_RESET = 0x0100,
	CMSG_STANDSTATECHANGE = 0x0101,
	CMSG_EMOTE = 0x0102,
	SMSG_EMOTE = 0x0103,
	CMSG_TEXT_EMOTE = 0x0104,
	SMSG_TEXT_EMOTE = 0x0105,
	CMSG_AUTOEQUIP_GROUND_ITEM = 0x0106,
	CMSG_AUTOSTORE_GROUND_ITEM = 0x0107,
	CMSG_AUTOSTORE_LOOT_ITEM = 0x0108,
	CMSG_STORE_LOOT_IN_SLOT = 0x0109,
	CMSG_AUTOEQUIP_ITEM = 0x010A,
	CMSG_AUTOSTORE_BAG_ITEM = 0x010B,
	CMSG_SWAP_ITEM = 0x010C,
	CMSG_SWAP_INV_ITEM = 0x010D,
	CMSG_SPLIT_ITEM = 0x010E,
	CMSG_PICKUP_ITEM = 0x010F,
	CMSG_DROP_ITEM = 0x0110,
	CMSG_DESTROYITEM = 0x0111,
	SMSG_INVENTORY_CHANGE_FAILURE = 0x0112,
	SMSG_OPEN_CONTAINER = 0x0113,
	CMSG_INSPECT = 0x0114,
	SMSG_INSPECT = 0x0115,
	CMSG_INITIATE_TRADE = 0x0116,
	CMSG_BEGIN_TRADE = 0x0117,
	CMSG_BUSY_TRADE = 0x0118,
	CMSG_IGNORE_TRADE = 0x0119,
	CMSG_ACCEPT_TRADE = 0x011A,
	CMSG_UNACCEPT_TRADE = 0x011B,
	CMSG_CANCEL_TRADE = 0x011C,
	CMSG_SET_TRADE_ITEM = 0x011D,
	CMSG_CLEAR_TRADE_ITEM = 0x011E,
	CMSG_SET_TRADE_GOLD = 0x011F,
	SMSG_TRADE_STATUS = 0x0120,
	SMSG_TRADE_STATUS_EXTENDED = 0x0121,
	SMSG_INITIALIZE_FACTIONS = 0x0122,
	SMSG_SET_FACTION_VISIBLE = 0x0123,
	SMSG_SET_FACTION_STANDING = 0x0124,
	CMSG_SET_FACTION_ATWAR = 0x0125,
	CMSG_SET_FACTION_CHEAT = 0x0126,
	SMSG_SET_PROFICIENCY = 0x0127,
	CMSG_SET_ACTION_BUTTON = 0x0128,
	SMSG_ACTION_BUTTONS = 0x0129,
	SMSG_INITIAL_SPELLS = 0x012A,
	SMSG_LEARNED_SPELL = 0x012B,
	SMSG_SUPERCEDED_SPELL = 0x012C,
	CMSG_NEW_SPELL_SLOT = 0x012D,
	CMSG_CAST_SPELL = 0x012E,
	CMSG_CANCEL_CAST = 0x012F,
	SMSG_CAST_RESULT = 0x0130,
	SMSG_SPELL_START = 0x0131,
	SMSG_SPELL_GO = 0x0132,
	SMSG_SPELL_FAILURE = 0x0133,
	SMSG_SPELL_COOLDOWN = 0x0134,
	SMSG_COOLDOWN_EVENT = 0x0135,
	CMSG_CANCEL_AURA = 0x0136,
	SMSG_UPDATE_AURA_DURATION = 0x0137,
	SMSG_PET_CAST_FAILED = 0x0138,
	MSG_CHANNEL_START = 0x0139,
	MSG_CHANNEL_UPDATE = 0x013A,
	CMSG_CANCEL_CHANNELLING = 0x013B,
	SMSG_AI_REACTION = 0x013C,
	CMSG_SET_SELECTION = 0x013D,
	CMSG_SET_TARGET = 0x013E,
	CMSG_UNUSED = 0x013F,
	CMSG_UNUSED2 = 0x0140,
	CMSG_ATTACKSWING = 0x0141,
	CMSG_ATTACKSTOP = 0x0142,
	SMSG_ATTACKSTART = 0x0143,
	SMSG_ATTACKSTOP = 0x0144,
	SMSG_ATTACKSWING_NOTINRANGE = 0x0145,
	SMSG_ATTACKSWING_BADFACING = 0x0146,
	SMSG_ATTACKSWING_NOTSTANDING = 0x0147,
	SMSG_ATTACKSWING_DEADTARGET = 0x0148,
	SMSG_ATTACKSWING_CANT_ATTACK = 0x0149,
	SMSG_ATTACKERSTATEUPDATE = 0x014A,
	SMSG_VICTIMSTATEUPDATE_OBSOLETE = 0x014B,
	SMSG_DAMAGE_DONE_OBSOLETE = 0x014C,
	SMSG_DAMAGE_TAKEN_OBSOLETE = 0x014D,
	SMSG_CANCEL_COMBAT = 0x014E,
	SMSG_PLAYER_COMBAT_XP_GAIN_OBSOLETE = 0x014F,
	SMSG_HEALSPELL_ON_PLAYER_OBSOLETE = 0x0150,
	SMSG_HEALSPELL_ON_PLAYERS_PET_OBSOLETE = 0x0151,
	CMSG_SHEATHE_OBSOLETE = 0x0152,
	CMSG_SAVE_PLAYER = 0x0153,
	CMSG_SETDEATHBINDPOINT = 0x0154,
	SMSG_BINDPOINTUPDATE = 0x0155,
	CMSG_GETDEATHBINDZONE = 0x0156,
	SMSG_BINDZONEREPLY = 0x0157,
	SMSG_PLAYERBOUND = 0x0158,
	SMSG_DEATH_NOTIFY_OBSOLETE = 0x0159,
	CMSG_REPOP_REQUEST = 0x015A,
	SMSG_RESURRECT_REQUEST = 0x015B,
	CMSG_RESURRECT_RESPONSE = 0x015C,
	CMSG_LOOT = 0x015D,
	CMSG_LOOT_MONEY = 0x015E,
	CMSG_LOOT_RELEASE = 0x015F,
	SMSG_LOOT_RESPONSE = 0x0160,
	SMSG_LOOT_RELEASE_RESPONSE = 0x0161,
	SMSG_LOOT_REMOVED = 0x0162,
	SMSG_LOOT_MONEY_NOTIFY = 0x0163,
	SMSG_LOOT_ITEM_NOTIFY = 0x0164,
	SMSG_LOOT_CLEAR_MONEY = 0x0165,
	SMSG_ITEM_PUSH_RESULT = 0x0166,
	SMSG_DUEL_REQUESTED = 0x0167,
	SMSG_DUEL_OUTOFBOUNDS = 0x0168,
	SMSG_DUEL_INBOUNDS = 0x0169,
	SMSG_DUEL_COMPLETE = 0x016A,
	SMSG_DUEL_WINNER = 0x016B,
	CMSG_DUEL_ACCEPTED = 0x016C,
	CMSG_DUEL_CANCELLED = 0x016D,
	SMSG_MOUNTRESULT = 0x016E,
	SMSG_DISMOUNTRESULT = 0x016F,
	SMSG_PUREMOUNT_CANCELLED_OBSOLETE = 0x0170,
	CMSG_MOUNTSPECIAL_ANIM = 0x0171,
	SMSG_MOUNTSPECIAL_ANIM = 0x0172,
	SMSG_PET_TAME_FAILURE = 0x0173,
	CMSG_PET_SET_ACTION = 0x0174,
	CMSG_PET_ACTION = 0x0175,
	CMSG_PET_ABANDON = 0x0176,
	CMSG_PET_RENAME = 0x0177,
	SMSG_PET_NAME_INVALID = 0x0178,
	SMSG_PET_SPELLS = 0x0179,
	CMSG_PET_CAST_SPELL_OBSOLETE = 0x017A,
	CMSG_GOSSIP_HELLO = 0x017B,
	CMSG_GOSSIP_SELECT_OPTION = 0x017C,
	SMSG_GOSSIP_MESSAGE = 0x017D,
	SMSG_GOSSIP_COMPLETE = 0x017E,
	CMSG_NPC_TEXT_QUERY = 0x017F,
	SMSG_NPC_TEXT_UPDATE = 0x0180,
	SMSG_NPC_WONT_TALK = 0x0181,
	CMSG_QUESTGIVER_STATUS_QUERY = 0x0182,
	SMSG_QUESTGIVER_STATUS = 0x0183,
	CMSG_QUESTGIVER_HELLO = 0x0184,
	SMSG_QUESTGIVER_QUEST_LIST = 0x0185,
	CMSG_QUESTGIVER_QUERY_QUEST = 0x0186,
	CMSG_QUESTGIVER_QUEST_AUTOLAUNCH = 0x0187,
	SMSG_QUESTGIVER_QUEST_DETAILS = 0x0188,
	CMSG_QUESTGIVER_ACCEPT_QUEST = 0x0189,
	CMSG_QUESTGIVER_COMPLETE_QUEST = 0x018A,
	SMSG_QUESTGIVER_REQUEST_ITEMS = 0x018B,
	CMSG_QUESTGIVER_REQUEST_REWARD = 0x018C,
	SMSG_QUESTGIVER_OFFER_REWARD = 0x018D,
	CMSG_QUESTGIVER_CHOOSE_REWARD = 0x018E,
	SMSG_QUESTGIVER_QUEST_INVALID = 0x018F,
	CMSG_QUESTGIVER_CANCEL = 0x0190,
	SMSG_QUESTGIVER_QUEST_COMPLETE = 0x0191,
	SMSG_QUESTGIVER_QUEST_FAILED = 0x0192,
	CMSG_QUESTLOG_SWAP_QUEST = 0x0193,
	CMSG_QUESTLOG_REMOVE_QUEST = 0x0194,
	SMSG_QUESTLOG_FULL = 0x0195,
	SMSG_QUESTUPDATE_FAILED = 0x0196,
	SMSG_QUESTUPDATE_FAILEDTIMER = 0x0197,
	SMSG_QUESTUPDATE_COMPLETE = 0x0198,
	SMSG_QUESTUPDATE_ADD_KILL = 0x0199,
	SMSG_QUESTUPDATE_ADD_ITEM = 0x019A,
	CMSG_QUEST_CONFIRM_ACCEPT = 0x019B,
	SMSG_QUEST_CONFIRM_ACCEPT = 0x019C,
	CMSG_PUSHQUESTTOPARTY = 0x019D,
	CMSG_LIST_INVENTORY = 0x019E,
	SMSG_LIST_INVENTORY = 0x019F,
	CMSG_SELL_ITEM = 0x01A0,
	SMSG_SELL_ITEM = 0x01A1,
	CMSG_BUY_ITEM = 0x01A2,
	CMSG_BUY_ITEM_IN_SLOT = 0x01A3,
	SMSG_BUY_ITEM = 0x01A4,
	SMSG_BUY_FAILED = 0x01A5,
	CMSG_TAXICLEARALLNODES = 0x01A6,
	CMSG_TAXIENABLEALLNODES = 0x01A7,
	CMSG_TAXISHOWNODES = 0x01A8,
	SMSG_SHOWTAXINODES = 0x01A9,
	CMSG_TAXINODE_STATUS_QUERY = 0x01AA,
	SMSG_TAXINODE_STATUS = 0x01AB,
	CMSG_TAXIQUERYAVAILABLENODES = 0x01AC,
	CMSG_ACTIVATETAXI = 0x01AD,
	SMSG_ACTIVATETAXIREPLY = 0x01AE,
	SMSG_NEW_TAXI_PATH = 0x01AF,
	CMSG_TRAINER_LIST = 0x01B0,
	SMSG_TRAINER_LIST = 0x01B1,
	CMSG_TRAINER_BUY_SPELL = 0x01B2,
	SMSG_TRAINER_BUY_SUCCEEDED = 0x01B3,
	SMSG_TRAINER_BUY_FAILED = 0x01B4,
	CMSG_BINDER_ACTIVATE = 0x01B5,
	SMSG_PLAYERBINDERROR = 0x01B6,
	CMSG_BANKER_ACTIVATE = 0x01B7,
	SMSG_SHOW_BANK = 0x01B8,
	CMSG_BUY_BANK_SLOT = 0x01B9,
	SMSG_BUY_BANK_SLOT_RESULT = 0x01BA,
	CMSG_PETITION_SHOWLIST = 0x01BB,
	SMSG_PETITION_SHOWLIST = 0x01BC,
	CMSG_PETITION_BUY = 0x01BD,
	CMSG_PETITION_SHOW_SIGNATURES = 0x01BE,
	SMSG_PETITION_SHOW_SIGNATURES = 0x01BF,
	CMSG_PETITION_SIGN = 0x01C0,
	SMSG_PETITION_SIGN_RESULTS = 0x01C1,
	MSG_PETITION_DECLINE = 0x01C2,
	CMSG_OFFER_PETITION = 0x01C3,
	CMSG_TURN_IN_PETITION = 0x01C4,
	SMSG_TURN_IN_PETITION_RESULTS = 0x01C5,
	CMSG_PETITION_QUERY = 0x01C6,
	SMSG_PETITION_QUERY_RESPONSE = 0x01C7,
	SMSG_FISH_NOT_HOOKED = 0x01C8,
	SMSG_FISH_ESCAPED = 0x01C9,
	CMSG_BUG = 0x01CA,
	SMSG_NOTIFICATION = 0x01CB,
	CMSG_PLAYED_TIME = 0x01CC,
	SMSG_PLAYED_TIME = 0x01CD,
	CMSG_QUERY_TIME = 0x01CE,
	SMSG_QUERY_TIME_RESPONSE = 0x01CF,
	SMSG_LOG_XPGAIN = 0x01D0,
	MSG_SPLIT_MONEY = 0x01D1,
	CMSG_RECLAIM_CORPSE = 0x01D2,
	CMSG_WRAP_ITEM = 0x01D3,
	SMSG_LEVELUP_INFO = 0x01D4,
	MSG_MINIMAP_PING = 0x01D5,
	SMSG_RESISTLOG = 0x01D6,
	SMSG_ENCHANTMENTLOG = 0x01D7,
	CMSG_SET_SKILL_CHEAT = 0x01D8,
	SMSG_START_MIRROR_TIMER = 0x01D9,
	SMSG_PAUSE_MIRROR_TIMER = 0x01DA,
	SMSG_STOP_MIRROR_TIMER = 0x01DB,
	CMSG_PING = 0x01DC,
	SMSG_PONG = 0x01DD,
	SMSG_CLEAR_COOLDOWN = 0x01DE,
	SMSG_GAMEOBJECT_PAGETEXT = 0x01DF,
	CMSG_SETSHEATHED = 0x01E0,
	SMSG_COOLDOWN_CHEAT = 0x01E1,
	SMSG_SPELL_DELAYED = 0x01E2,
	CMSG_PLAYER_MACRO = 0x01E3,
	SMSG_PLAYER_MACRO = 0x01E4,
	CMSG_GHOST = 0x01E5,
	CMSG_GM_INVIS = 0x01E6,
	CMSG_SCREENSHOT = 0x01E7,
	MSG_GM_BIND_OTHER = 0x01E8,
	MSG_GM_SUMMON = 0x01E9,
	SMSG_ITEM_TIME_UPDATE = 0x01EA,
	SMSG_ITEM_ENCHANT_TIME_UPDATE = 0x01EB,
	SMSG_AUTH_CHALLENGE = 0x01EC,
	CMSG_AUTH_SESSION = 0x01ED,
	SMSG_AUTH_RESPONSE = 0x01EE,
	MSG_GM_SHOWLABEL = 0x01EF,
	MSG_ADD_DYNAMIC_TARGET = 0x01F0,
	MSG_SAVE_GUILD_EMBLEM = 0x01F1,
	MSG_TABARDVENDOR_ACTIVATE = 0x01F2,
	SMSG_PLAY_SPELL_VISUAL = 0x01F3,
	CMSG_ZONEUPDATE = 0x01F4,
	SMSG_PARTYKILLLOG = 0x01F5,
	SMSG_COMPRESSED_UPDATE_OBJECT = 0x01F6,
	SMSG_OBSOLETE = 0x01F7,
	SMSG_EXPLORATION_EXPERIENCE = 0x01F8,
	CMSG_GM_SET_SECURITY_GROUP = 0x01F9,
	CMSG_GM_NUKE = 0x01FA,
	MSG_RANDOM_ROLL = 0x01FB,
	SMSG_ENVIRONMENTALDAMAGELOG = 0x01FC,
	CMSG_RWHOIS = 0x01FD,
	SMSG_RWHOIS = 0x01FE,
	MSG_LOOKING_FOR_GROUP = 0x01FF,
	CMSG_SET_LOOKING_FOR_GROUP = 0x0200,
	CMSG_UNLEARN_SPELL = 0x0201,
	CMSG_UNLEARN_SKILL = 0x0202,
	SMSG_REMOVED_SPELL = 0x0203,
	CMSG_DECHARGE = 0x0204,
	CMSG_GMTICKET_CREATE = 0x0205,
	SMSG_GMTICKET_CREATE = 0x0206,
	CMSG_GMTICKET_UPDATETEXT = 0x0207,
	SMSG_GMTICKET_UPDATETEXT = 0x0208,
	SMSG_ACCOUNT_DATA_MD5 = 0x0209,
	CMSG_REQUEST_ACCOUNT_DATA = 0x020A,
	CMSG_UPDATE_ACCOUNT_DATA = 0x020B,
	SMSG_UPDATE_ACCOUNT_DATA = 0x020C,
	SMSG_CLEAR_FAR_SIGHT_IMMEDIATE = 0x020D,
	SMSG_POWERGAINLOG_OBSOLETE = 0x020E,
	CMSG_GM_TEACH = 0x020F,
	CMSG_GM_CREATE_ITEM_TARGET = 0x0210,
	CMSG_GMTICKET_GETTICKET = 0x0211,
	SMSG_GMTICKET_GETTICKET = 0x0212,
	CMSG_UNLEARN_TALENTS = 0x0213,
	SMSG_GAMEOBJECT_SPAWN_ANIM = 0x0214,
	SMSG_GAMEOBJECT_DESPAWN_ANIM = 0x0215,
	MSG_CORPSE_QUERY = 0x0216,
	CMSG_GMTICKET_DELETETICKET = 0x0217,
	SMSG_GMTICKET_DELETETICKET = 0x0218,
	SMSG_CHAT_WRONG_FACTION = 0x0219,
	CMSG_GMTICKET_SYSTEMSTATUS = 0x021A,
	SMSG_GMTICKET_SYSTEMSTATUS = 0x021B,
	CMSG_SPIRIT_HEALER_ACTIVATE = 0x021C,
	CMSG_SET_STAT_CHEAT = 0x021D,
	SMSG_SET_REST_START = 0x021E,
	CMSG_SKILL_BUY_STEP = 0x021F,
	CMSG_SKILL_BUY_RANK = 0x0220,
	CMSG_XP_CHEAT = 0x0221,
	SMSG_SPIRIT_HEALER_CONFIRM = 0x0222,
	CMSG_CHARACTER_POINT_CHEAT = 0x0223,
	SMSG_GOSSIP_POI = 0x0224,
	CMSG_CHAT_IGNORED = 0x0225,
	CMSG_GM_VISION = 0x0226,
	CMSG_SERVER_COMMAND = 0x0227,
	CMSG_GM_SILENCE = 0x0228,
	CMSG_GM_REVEALTO = 0x0229,
	CMSG_GM_RESURRECT = 0x022A,
	CMSG_GM_SUMMONMOB = 0x022B,
	CMSG_GM_MOVECORPSE = 0x022C,
	CMSG_GM_FREEZE = 0x022D,
	CMSG_GM_UBERINVIS = 0x022E,
	CMSG_GM_REQUEST_PLAYER_INFO = 0x022F,
	SMSG_GM_PLAYER_INFO = 0x0230,
	CMSG_GUILD_RANK = 0x0231,
	CMSG_GUILD_ADD_RANK = 0x0232,
	CMSG_GUILD_DEL_RANK = 0x0233,
	CMSG_GUILD_SET_PUBLIC_NOTE = 0x0234,
	CMSG_GUILD_SET_OFFICER_NOTE = 0x0235,
	SMSG_LOGIN_VERIFY_WORLD = 0x0236,
	CMSG_CLEAR_EXPLORATION = 0x0237,
	CMSG_SEND_MAIL = 0x0238,
	SMSG_SEND_MAIL_RESULT = 0x0239,
	CMSG_GET_MAIL_LIST = 0x023A,
	SMSG_MAIL_LIST_RESULT = 0x023B,
	CMSG_BATTLEFIELD_LIST = 0x023C,
	SMSG_BATTLEFIELD_LIST = 0x023D,
	CMSG_BATTLEFIELD_JOIN = 0x023E,
	SMSG_BATTLEFIELD_WIN = 0x023F,
	SMSG_BATTLEFIELD_LOSE = 0x0240,
	CMSG_TAXICLEARNODE = 0x0241,
	CMSG_TAXIENABLENODE = 0x0242,
	CMSG_ITEM_TEXT_QUERY = 0x0243,
	SMSG_ITEM_TEXT_QUERY_RESPONSE = 0x0244,
	CMSG_MAIL_TAKE_MONEY = 0x0245,
	CMSG_MAIL_TAKE_ITEM = 0x0246,
	CMSG_MAIL_MARK_AS_READ = 0x0247,
	CMSG_MAIL_RETURN_TO_SENDER = 0x0248,
	CMSG_MAIL_DELETE = 0x0249,
	CMSG_MAIL_CREATE_TEXT_ITEM = 0x024A,
	SMSG_SPELLLOGMISS = 0x024B,
	SMSG_SPELLLOGEXECUTE = 0x024C,
	SMSG_DEBUGAURAPROC = 0x024D,
	SMSG_PERIODICAURALOG = 0x024E,
	SMSG_SPELLDAMAGESHIELD = 0x024F,
	SMSG_SPELLNONMELEEDAMAGELOG = 0x0250,
	CMSG_LEARN_TALENT = 0x0251,
	SMSG_RESURRECT_FAILED = 0x0252,
	CMSG_ENABLE_PVP = 0x0253,
	SMSG_ZONE_UNDER_ATTACK = 0x0254,
	MSG_AUCTION_HELLO = 0x0255,
	CMSG_AUCTION_SELL_ITEM = 0x0256,
	CMSG_AUCTION_REMOVE_ITEM = 0x0257,
	CMSG_AUCTION_LIST_ITEMS = 0x0258,
	CMSG_AUCTION_LIST_OWNER_ITEMS = 0x0259,
	CMSG_AUCTION_PLACE_BID = 0x025A,
	SMSG_AUCTION_COMMAND_RESULT = 0x025B,
	SMSG_AUCTION_LIST_RESULT = 0x025C,
	SMSG_AUCTION_OWNER_LIST_RESULT = 0x025D,
	SMSG_AUCTION_BIDDER_NOTIFICATION = 0x025E,
	SMSG_AUCTION_OWNER_NOTIFICATION = 0x025F,
	SMSG_PROCRESIST = 0x0260,
	SMSG_STANDSTATE_CHANGE_FAILURE = 0x0261,
	SMSG_DISPEL_FAILED = 0x0262,
	SMSG_SPELLORDAMAGE_IMMUNE = 0x0263,
	CMSG_AUCTION_LIST_BIDDER_ITEMS = 0x0264,
	SMSG_AUCTION_BIDDER_LIST_RESULT = 0x0265,
	SMSG_SET_FLAT_SPELL_MODIFIER = 0x0266,
	SMSG_SET_PCT_SPELL_MODIFIER = 0x0267,
	CMSG_SET_AMMO = 0x0268,
	SMSG_CORPSE_RECLAIM_DELAY = 0x0269,
	CMSG_SET_ACTIVE_MOVER = 0x026A,
	CMSG_PET_CANCEL_AURA = 0x026B,
	CMSG_PLAYER_AI_CHEAT = 0x026C,
	CMSG_CANCEL_AUTO_REPEAT_SPELL = 0x026D,
	MSG_GM_ACCOUNT_ONLINE = 0x026E,
	MSG_LIST_STABLED_PETS = 0x026F,
	CMSG_STABLE_PET = 0x0270,
	CMSG_UNSTABLE_PET = 0x0271,
	CMSG_BUY_STABLE_SLOT = 0x0272,
	SMSG_STABLE_RESULT = 0x0273,
	CMSG_STABLE_REVIVE_PET = 0x0274,
	CMSG_STABLE_SWAP_PET = 0x0275,
	MSG_QUEST_PUSH_RESULT = 0x0276,
	SMSG_PLAY_MUSIC = 0x0277,
	SMSG_PLAY_OBJECT_SOUND = 0x0278,
	CMSG_REQUEST_PET_INFO = 0x0279,
	CMSG_FAR_SIGHT = 0x027A,
	SMSG_SPELLDISPELLOG = 0x027B,
	SMSG_DAMAGE_CALC_LOG = 0x027C,
	CMSG_ENABLE_DAMAGE_LOG = 0x027D,
	CMSG_GROUP_CHANGE_SUB_GROUP = 0x027E,
	SMSG_RAID_MEMBER_STATS = 0x027F,
	CMSG_GROUP_SWAP_SUB_GROUP = 0x0280,
	CMSG_RESET_FACTION_CHEAT = 0x0281,
	CMSG_AUTOSTORE_BANK_ITEM = 0x0282,
	CMSG_AUTOBANK_ITEM = 0x0283,
	MSG_QUERY_NEXT_MAIL_TIME = 0x0284,
	SMSG_RECEIVED_MAIL = 0x0285,
	SMSG_RAID_GROUP_ONLY = 0x0286,
	CMSG_SET_DURABILITY_CHEAT = 0x0287,
	CMSG_SET_PVP_RANK_CHEAT = 0x0288,
	CMSG_ADD_PVP_MEDAL_CHEAT = 0x0289,
	CMSG_DEL_PVP_MEDAL_CHEAT = 0x028A,
	CMSG_SET_PVP_TITLE = 0x028B,
	SMSG_PVP_CREDIT = 0x028C,
	SMSG_AUCTION_REMOVED_NOTIFICATION = 0x028D,
	CMSG_GROUP_RAID_CONVERT = 0x028E,
	CMSG_GROUP_ASSISTANT_LEADER = 0x028F,
	CMSG_BUYBACK_ITEM = 0x0290,
	SMSG_SERVER_MESSAGE = 0x0291,
	CMSG_GMTICKETSYSTEM_TOGGLE = 0x0292,
	CMSG_CANCEL_GROWTH_AURA = 0x0293,
	SMSG_CANCEL_AUTO_REPEAT = 0x0294,
	SMSG_STANDSTATE_CHANGE_ACK = 0x0295,
	SMSG_LOOT_ALL_PASSED = 0x0296,
	SMSG_LOOT_ROLL_WON = 0x0297,
	CMSG_LOOT_ROLL = 0x0298,
	SMSG_LOOT_START_ROLL = 0x0299,
	SMSG_LOOT_ROLL = 0x029A,
	CMSG_LOOT_MASTER_GIVE = 0x029B,
	SMSG_LOOT_MASTER_LIST = 0x029C,
	SMSG_SET_FORCED_REACTIONS = 0x029D,
	SMSG_SPELL_FAILED_OTHER = 0x029E,
	SMSG_GAMEOBJECT_RESET_STATE = 0x029F,
	CMSG_REPAIR_ITEM = 0x02A0,
	SMSG_CHAT_PLAYER_NOT_FOUND = 0x02A1,
	MSG_TALENT_WIPE_CONFIRM = 0x02A2,
	SMSG_SUMMON_REQUEST = 0x02A3,
	CMSG_SUMMON_RESPONSE = 0x02A4,
	MSG_MOVE_TOGGLE_GRAVITY_CHEAT = 0x02A5,
	SMSG_MONSTER_MOVE_TRANSPORT = 0x02A6,
	SMSG_PET_BROKEN = 0x02A7,
	MSG_MOVE_FEATHER_FALL = 0x02A8,
	MSG_MOVE_WATER_WALK = 0x02A9,
	CMSG_SERVER_BROADCAST = 0x02AA,
	CMSG_SELF_RES = 0x02AB,
	SMSG_FEIGN_DEATH_RESISTED = 0x02AC,
	CMSG_RUN_SCRIPT = 0x02AD,
	SMSG_SCRIPT_MESSAGE = 0x02AE,
	NUM_MSG_TYPES = 0x02AF,
	RLMSG_AUTH_SSHASH = 0xFF01
};

enum SpellCastFlags
{
	CAST_FLAG_UNKNOWN1 = 0x2,
	CAST_FLAG_UNKNOWN2 = 0x10,
	CAST_FLAG_AMMO = 0x20
};

enum SpellCastTargetFlags
{
	TARGET_FLAG_SELF = 0x0,
	TARGET_FLAG_UNIT = 0x2,
	TARGET_FLAG_OBJECT = 0x800,
	TARGET_FLAG_ITEM = 0x1010,
	TARGET_FLAG_SOURCE_LOCATION = 0x20,
	TARGET_FLAG_DEST_LOCATION = 0x40,
	TARGET_FLAG_STRING = 0x2000
};

enum WorldServerError
{
	WSE_OK = 0x0,
	WSE_FAILURE = 0x1,
	WSE_CANCELED = 0x2,
	WSE_DISCONNECT_FROM_SERVER = 0x3,
	WSE_FAILED_TO_CONNECT = 0x4,
	WSE_CONNECTED = 0x5,
	WSE_WRONG_CLIENT_VERSION_1 = 0x6,
	WSE_CONNECTING_TO_SERVER = 0x7,
	WSE_NEGOTIATING_SECURITY = 0x8,
	WSE_NEGOTIATING_SECURITY_COMPLETE_1 = 0x9,
	WSE_NEGOTIATING_SECURITY_COMPLETE_2 = 0xA,
	WSE_AUTHENTICATING = 0xB,
	WSE_AUTHENTICATION_SUCCESSFUL = 0xC,
	WSE_AUTHENTICATION_FAILED = 0xD,
	WSE_LOGIN_UNAVAILABLE = 0xE,
	WSE_SERVER_IS_NOT_VALID = 0xF,
	WSE_SYSTEM_UNAVAILABLE = 0x10,
	WSE_SYSTEM_ERROR = 0x11,
	WSE_BILLING_SYSTEM_ERROR = 0x12,
	WSE_ACCOUNT_BILLING_HAS_EXPIRED = 0x13,
	WSE_WRONG_CLIENT_VERSION_2 = 0x14,
	WSE_UNKNOWN_ACCOUNT = 0x15,
	WSE_INCORRECT_PASSWORD = 0x16,
	WSE_SESSION_EXPIRED = 0x17,
	WSE_SERVER_SHUTTING_DOWN = 0x18,
	WSE_ALREADY_LOGGED_IN = 0x19,
	WSE_INVALID_LOGIN_SERVER = 0x1A,
	WSE_POSITION_IN_QUEUE_0 = 0x1B,
	WSE_THIS_ACCOUNT_HAS_BEEN_BANNED = 0x1C,
	WSE_THIS_CHARACTER_IS_STILL_LOGGED_ON = 0x1D,
	WSE_YOUR_WOW_SUBSCRIPTION_HAS_EXPIRED = 0x1E,
	WSE_THIS_SESSION_HAS_TIMED_OUT = 0x1F,
	WSE_THIS_ACCOUNT_HAS_BEEN_TEMPORARILY_SUSPENDED = 0x20,
	WSE_RETRIEVING_REALMLIST = 0x21,
	WSE_REALMLIST_RETRIEVED = 0x22,
	WSE_UNABLE_TO_CONNECT_TO_REALMLIST_SERVER = 0x23,
	WSE_INVALID_REALMLIST = 0x24,
	WSE_THE_GAME_SERVER_IS_CURRENTLY_DOWN = 0x25,
	WSE_CREATING_ACCOUNT = 0x26,
	WSE_ACCOUNT_CREATED = 0x27,
	WSE_ACCOUNT_CREATION_FAILED = 0x28,
	WSE_RETRIEVING_CHARACTER_LIST = 0x29,
	WSE_CHARACTER_LIST_RETRIEVED = 0x2A,
	WSE_ERROR_RETRIEVING_CHARACTER_LIST = 0x2B,
	WSE_CREATING_CHARACTER = 0x2C,
	WSE_CHARACTER_CREATED = 0x2D,
	WSE_ERROR_CREATING_CHARACTER = 0x2E,
	WSE_CHARACTER_CREATION_FAILED = 0x2F,
	WSE_NAME_ALREADY_IN_USE = 0x30,
	WSE_CREATION_OF_THAT_RACECLASS_IS_DISABLED = 0x31,
	WSE_ALL_CHARACTERS_ON_A_PVP_REALM_MUST_BE_ON_THE_SAME_TEAM = 0x32,
	WSE_DELETING_CHARACTER = 0x33,
	WSE_CHARACTER_DELETED = 0x34,
	WSE_CHARACTER_DELETION_FAILED = 0x35,
	WSE_ENTERING_THE_WOW = 0x36,
	WSE_LOGIN_SUCCESSFUL = 0x37,
	WSE_WORLD_SERVER_DOWN = 0x38,
	WSE_A_CHARACTER_WITH_THAT_NAME_ALREADY_EXISTS = 0x39,
	WSE_NO_INSTANCE_SERVER_AVAILABLE = 0x3A,
	WSE_LOGIN_FAILED = 0x3B,
	WSE_LOGIN_FOR_THAT_RACECLASS_IS_DISABLED = 0x3C,
	WSE_ENTER_A_NAME_FOR_YOUR_CHARACTER = 0x3D,
	WSE_NAMES_MUST_BE_ATLEAST_2_CHARACTERS_LONG = 0x3E,
	WSE_NAMES_MUST_BE_NO_MORE_THEN_12_CHARACTERS = 0x3F,
	WSE_NAMES_CAN_ONLY_CONTAIN_LETTERS = 0x40,
	WSE_NAMES_MUST_CONTAIN_ONLY_ONE_LANGUAGE = 0x41,
	WSE_THAT_NAME_CONTAINS_PROFANITY = 0x42,
	WSE_THAT_NAME_IS_RESERVED = 0x43,
	WSE_YOU_CANNOT_USE_AN_APOSTROPHE = 0x44,
	WSE_YOU_CAN_ONLY_HAVE_ONE_APOSTROPHE = 0x45,
	WSE_YOU_CANNOT_USE_THE_SAME_LETTER_THREE_TIMES_CONSECUTIVELY = 0x46,
	WSE_INVALID_CHARACTER_NAME = 0x47,
	WSE_BLANK = 0x48
};

enum CHAT
{
	CHAT_MSG_SAY = 0x00000000,
	CHAT_MSG_PARTY = 0x00000001,
	CHAT_MSG_GUILD = 0x00000002,
	CHAT_MSG_OFFICER = 0x00000003,
	CHAT_MSG_YELL = 0x00000004,
	CHAT_MSG_WHISPER = 0x00000005,
	CHAT_MSG_WHISPER_INFORM = 0x00000006,
	CHAT_MSG_EMOTE = 0x00000007,
	CHAT_MSG_TEXT_EMOTE = 0x00000008,
	CHAT_MSG_SYSTEM = 0x00000009,
	CHAT_MSG_MONSTER_SAY = 0x0000000A,
	CHAT_MSG_MONSTER_YELL = 0x0000000B,
	CHAT_MSG_MONSTER_EMOTE = 0x0000000C,
	CHAT_MSG_CHANNEL = 0x0000000D,
	CHAT_MSG_CHANNEL_JOIN = 0x0000000E,
	CHAT_MSG_CHANNEL_LEAVE = 0x0000000F,
	CHAT_MSG_CHANNEL_LIST = 0x00000010,
	CHAT_MSG_CHANNEL_NOTICE = 0x00000011,
	CHAT_MSG_CHANNEL_NOTICE_USER = 0x00000012,
	CHAT_MSG_AFK = 0x00000013,
	CHAT_MSG_DND = 0x00000014,
	CHAT_MSG_COMBAT_LOG = 0x00000015,
	CHAT_MSG_IGNORED = 0x00000016,
	CHAT_MSG_SKILL = 0x00000017,
	CHAT_MSG_LOOT = 0x00000018
};

enum FriendsResult
{
	FRIEND_DB_ERROR = 0x0,
	FRIEND_LIST_FULL = 0x1,
	FRIEND_ONLINE = 0x2,
	FRIEND_OFFLINE = 0x3,
	FRIEND_NOT_FOUND = 0x4,
	FRIEND_REMOVED = 0x5,
	FRIEND_ADDED_ONLINE = 0x6,
	FRIEND_ADDED_OFFLINE = 0x7,
	FRIEND_ALREADY = 0x8,
	FRIEND_SELF = 0x9,
	FRIEND_ENEMY = 0xA,
	FRIEND_IGNORE_FULL = 0xB,
	FRIEND_IGNORE_SELF = 0xC,
	FRIEND_IGNORE_NOT_FOUND = 0xD,
	FRIEND_IGNORE_ALREADY = 0xE,
	FRIEND_IGNORE_ADDED = 0xF,
	FRIEND_IGNORE_REMOVED = 0x10
};

class CMSG_CHAR_CREATE_t : public NetworkPacket
{
public:
	char * Name;
	uint8 Race;
	uint8 Class;
	uint8 Gender;
	uint8 Skin;
	uint8 Face;
	uint8 HairStyle;
	uint8 HairColor;
	uint8 FacialHair;
	uint8 OutfitId;

	protected:
	virtual ~CMSG_CHAR_CREATE_t ();
	public:

	static CMSG_CHAR_CREATE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_CHAR_DELETE_t : public NetworkPacket
{
public:
	uint64 Guid;

	static CMSG_CHAR_DELETE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_CHAR_CREATE_t : public NetworkPacket
{
public:
	uint8 ErrorCode;

	static SMSG_CHAR_CREATE_t *Create ();

	virtual void Assemble ();
};

class SMSG_CHAR_ENUM_t : public NetworkPacket
{
public:
	uint8 Count;
	CharsVector List;

	static SMSG_CHAR_ENUM_t *Create ();

	virtual void Assemble ();
};

class CMSG_PLAYER_LOGIN_t : public NetworkPacket
{
public:
	uint64 Guid;

	static CMSG_PLAYER_LOGIN_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_NEW_WORLD_t : public NetworkPacket
{
public:
	uint32 Mapid;
	float X;
	float Y;
	float Z;
	float O;

	static SMSG_NEW_WORLD_t *Create ();

	virtual void Assemble ();
};

class SMSG_TRANSFER_PENDING_t : public NetworkPacket
{
public:
	uint32 Type;

	static SMSG_TRANSFER_PENDING_t *Create ();

	virtual void Assemble ();
};

class SMSG_CHARACTER_LOGIN_FAILED_t : public NetworkPacket
{
public:
	uint32 ErrorCode;

	static SMSG_CHARACTER_LOGIN_FAILED_t *Create ();

	virtual void Assemble ();
};

class SMSG_LOGIN_SETTIMESPEED_t : public NetworkPacket
{
public:
	uint32 Time;
	float Speed;

	static SMSG_LOGIN_SETTIMESPEED_t *Create ();

	virtual void Assemble ();
};

class SMSG_LOGOUT_RESPONSE_t : public NetworkPacket
{
public:
	uint8 Ok;

	static SMSG_LOGOUT_RESPONSE_t *Create ();

	virtual void Assemble ();
};

class CMSG_NAME_QUERY_t : public NetworkPacket
{
public:
	uint64 Guid;

	static CMSG_NAME_QUERY_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_FRIEND_LIST_t : public NetworkPacket
{
public:
	uint8 Count;
	FriendsVector Friends;

	static SMSG_FRIEND_LIST_t *Create ();

	virtual void Assemble ();
};

class SMSG_FRIEND_STATUS_t : public NetworkPacket
{
public:
	uint8 Result;
	uint64 Guid;
	uint32 Area;
	uint32 Level;
	uint32 Class;

	static SMSG_FRIEND_STATUS_t *Create ();

	virtual void Assemble ();
};

class CMSG_ADD_FRIEND_t : public NetworkPacket
{
public:
	char * Name;

	protected:
	virtual ~CMSG_ADD_FRIEND_t ();
	public:

	static CMSG_ADD_FRIEND_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_GROUP_LIST_t : public NetworkPacket
{
public:
	uint8 Memberscount;
	MembersVector Members;
	uint32 Leaderguid;
	uint8 Lootmethord;
	uint32 Lootmaster;
	uint8 Lootthreshold;

	static SMSG_GROUP_LIST_t *Create ();

	virtual void Assemble ();
};

class CMSG_MESSAGECHAT_t : public NetworkPacket
{
public:
	uint8 Type;
	uint32 Language;
	uint64 Guid;
	uint32 Msglength;
	char * Whisperto;
	char * Channel;
	char * Msg;
	uint8 Afktoggle;

	protected:
	virtual ~CMSG_MESSAGECHAT_t ();
	public:

	static CMSG_MESSAGECHAT_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_MESSAGECHAT_t : public NetworkPacket
{
public:
	uint8 Type;
	uint64 Senderguid;
	uint32 Msglength;
	char * Msg;
	uint8 Afktoggle;

	static SMSG_MESSAGECHAT_t *Create ();

	virtual void Assemble ();
};

class CMSG_JOIN_CHANNEL_t : public NetworkPacket
{
public:
	char * Name;

	protected:
	virtual ~CMSG_JOIN_CHANNEL_t ();
	public:

	static CMSG_JOIN_CHANNEL_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_CHANNEL_NOTIFY_t : public NetworkPacket
{
public:
	uint8 Unknown1;
	char * Channel;
	uint8 Unknown2;
	uint32 Unknown3;

	static SMSG_CHANNEL_NOTIFY_t *Create ();

	virtual void Assemble ();
};

class SMSG_UPDATE_OBJECT_t : public NetworkPacket
{
public:
	uint32 Count;
	ObjectVector Values;
	ObjectVector Movement;
	ObjectVector CreateObject;
	uint32 OutOfRangeCount;
	ObjectVector OutOfRange;

	static SMSG_UPDATE_OBJECT_t *Create ();

	virtual void Assemble ();
};

class SMSG_DESTROY_OBJECT_t : public NetworkPacket
{
public:
	uint64 Guid;

	static SMSG_DESTROY_OBJECT_t *Create ();

	virtual void Assemble ();
};

class CMSG_AREATRIGGER_t : public NetworkPacket
{
public:
	uint32 Id;

	static CMSG_AREATRIGGER_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class MSG_MOVE_HEARTBEAT_t : public NetworkPacket
{
public:
	uint64 Guid;
	uint32 Flag;
	uint32 Unknown1;
	float X;
	float Y;
	float Z;
	float O;

	static MSG_MOVE_HEARTBEAT_t *Create ();

	virtual void Assemble ();
};

class SMSG_TRIGGER_CINEMATIC_t : public NetworkPacket
{
public:
	uint32 Video;

	static SMSG_TRIGGER_CINEMATIC_t *Create ();

	virtual void Assemble ();
};

class SMSG_TUTORIAL_FLAGS_t : public NetworkPacket
{
public:
	uint8 TutMask[32];

	static SMSG_TUTORIAL_FLAGS_t *Create ();

	virtual void Assemble ();
};

class CMSG_STANDSTATECHANGE_t : public NetworkPacket
{
public:
	uint64 Guid;
	uint32 State;
	uint8 Animstate;

	static CMSG_STANDSTATECHANGE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_EMOTE_t : public NetworkPacket
{
public:
	uint32 Emote;
	uint64 Guid;

	static SMSG_EMOTE_t *Create ();

	virtual void Assemble ();
};

class CMSG_TEXT_EMOTE_t : public NetworkPacket
{
public:
	uint32 Emote;
	uint64 Guid;

	static CMSG_TEXT_EMOTE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_TEXT_EMOTE_t : public NetworkPacket
{
public:
	uint64 Guid;
	uint32 Emote;
	char * Name;

	static SMSG_TEXT_EMOTE_t *Create ();

	virtual void Assemble ();
};

class CMSG_AUTOSTORE_LOOT_ITEM_t : public NetworkPacket
{
public:
	uint8 Lootslot;

	static CMSG_AUTOSTORE_LOOT_ITEM_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_SET_ACTION_BUTTON_t : public NetworkPacket
{
public:
	uint8 Button;
	uint32 Action;

	static CMSG_SET_ACTION_BUTTON_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_ACTION_BUTTONS_t : public NetworkPacket
{
public:
	uint32 Actions[120];

	static SMSG_ACTION_BUTTONS_t *Create ();

	virtual void Assemble ();
};

struct SPELL_TARGET
{
	uint16 Targetmask;
	uint64 Targetunit;
	uint64 Targetitem;
	float SrcX;
	float SrcY;
	float SrcZ;
	float DestX;
	float DestY;
	float DestZ;
	char * Targetstring;
};

class CMSG_CAST_SPELL_t : public NetworkPacket, SPELL_TARGET
{
public:
	uint32 Spellid;
	// STRUCTLET STRL_SPELL_TARGET 
	uint16 Targetmask;
	uint64 Targetunit;
	uint64 Targetitem;
	float SrcX;
	float SrcY;
	float SrcZ;
	float DestX;
	float DestY;
	float DestZ;
	char * Targetstring;
	// END STRUCTLET STRL_SPELL_TARGET 

	protected:
	virtual ~CMSG_CAST_SPELL_t ();
	public:

	static CMSG_CAST_SPELL_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_SET_SELECTION_t : public NetworkPacket
{
public:
	uint64 Gui;

	static CMSG_SET_SELECTION_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_SET_TARGET_t : public NetworkPacket
{
public:
	uint64 Guid;

	static CMSG_SET_TARGET_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_ATTACKSTART_t : public NetworkPacket
{
public:
	uint64 Attacker;
	uint64 Victim;

	static SMSG_ATTACKSTART_t *Create ();

	virtual void Assemble ();
};

class SMSG_ATTACKSTOP_t : public NetworkPacket
{
public:
	uint64 Attacker;
	uint64 Victim;

	static SMSG_ATTACKSTOP_t *Create ();

	virtual void Assemble ();
};

class SMSG_ATTACKERSTATEUPDATE_t : public NetworkPacket
{
public:
	uint32 AttackFlags;
	uint64 Attacker;
	uint64 Victim;
	uint32 TotalDamage;
	uint8 Count;
	DamageVector DamageList;

	static SMSG_ATTACKERSTATEUPDATE_t *Create ();

	virtual void Assemble ();
};

class CMSG_LOOT_t : public NetworkPacket
{
public:
	uint64 Guid;

	static CMSG_LOOT_t *Create ();

	virtual void Assemble ();

	static CMSG_LOOT_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_LOOT_RELEASE_t : public NetworkPacket
{
public:
	uint64 Guid;

	static CMSG_LOOT_RELEASE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_LOOT_RESPONSE_t : public NetworkPacket
{
public:
	uint64 Guid;
	uint8 Type;
	uint32 Money;
	uint8 Itemcount;
	LootResponseVector Items;

	static SMSG_LOOT_RESPONSE_t *Create ();

	virtual void Assemble ();
};

class SMSG_LOOT_RELEASE_RESPONSE_t : public NetworkPacket
{
public:
	uint64 Guid;
	uint8 Ok;

	static SMSG_LOOT_RELEASE_RESPONSE_t *Create ();

	virtual void Assemble ();
};

class SMSG_LOOT_REMOVED_t : public NetworkPacket
{
public:
	uint8 Slot;

	static SMSG_LOOT_REMOVED_t *Create ();

	virtual void Assemble ();
};

class SMSG_GOSSIP_MESSAGE_t : public NetworkPacket
{
public:
	uint64 Guid;
	uint32 Textid;
	uint32 Bpcount;
	uint32 Option;
	uint32 Icon;
	char * Text;

	static SMSG_GOSSIP_MESSAGE_t *Create ();

	virtual void Assemble ();
};

class CMSG_BUG_t : public NetworkPacket
{
public:
	uint32 Suggestion;
	uint32 Contentlen;
	char * Content;
	uint32 Typelen;
	char * Type;

	protected:
	virtual ~CMSG_BUG_t ();
	public:

	static CMSG_BUG_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_PING_t : public NetworkPacket
{
public:
	uint32 Ordinal;

	static CMSG_PING_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_PONG_t : public NetworkPacket
{
public:
	uint32 Acknowledge;

	static SMSG_PONG_t *Create ();

	virtual void Assemble ();
};

class SMSG_AUTH_CHALLENGE_t : public NetworkPacket
{
public:
	uint32 Seed;

	static SMSG_AUTH_CHALLENGE_t *Create ();

	virtual void Assemble ();
};

class CMSG_AUTH_SESSION_t : public NetworkPacket
{
public:
	uint32 Unknown1;
	uint32 Unknown2;
	char * Login;
	uint32 Seed;
	uint8 Digest[20];

	protected:
	virtual ~CMSG_AUTH_SESSION_t ();
	public:

	static CMSG_AUTH_SESSION_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_AUTH_RESPONSE_t : public NetworkPacket
{
public:
	uint8 ErrorCode;
	uint8 Counter;

	static SMSG_AUTH_RESPONSE_t *Create ();

	virtual void Assemble ();
};

class CMSG_ZONEUPDATE_t : public NetworkPacket
{
public:
	uint32 Zone;

	static CMSG_ZONEUPDATE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_GMTICKET_CREATE_t : public NetworkPacket
{
public:
	uint32 Id;

	static SMSG_GMTICKET_CREATE_t *Create ();

	virtual void Assemble ();
};

class SMSG_ACCOUNT_DATA_MD5_t : public NetworkPacket
{
public:
	uint8 MD5[80];

	static SMSG_ACCOUNT_DATA_MD5_t *Create ();

	virtual void Assemble ();
};

class CMSG_REQUEST_ACCOUNT_DATA_t : public NetworkPacket
{
public:
	uint32 FileIndex;

	static CMSG_REQUEST_ACCOUNT_DATA_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_UPDATE_ACCOUNT_DATA_t : public NetworkPacket
{
public:
	uint32 FileIndex;
	uint32 UncompressedSize;
	uint CompressedData_Size;
	uint8 *CompressedData;

	static CMSG_UPDATE_ACCOUNT_DATA_t *Create (Socket *socket, uint pktlen);
	bool Parse (Socket *socket, uint pktlen);
};

class SMSG_UPDATE_ACCOUNT_DATA_t : public NetworkPacket
{
public:
	uint32 FileIndex;
	uint32 UncompressedSize;
	uint CompressedData_Size;
	uint8 *CompressedData;

	static SMSG_UPDATE_ACCOUNT_DATA_t *Create ();

	virtual void Assemble ();
};

class SMSG_GMTICKET_GETTICKET_t : public NetworkPacket
{
public:
	uint32 Unknown1;
	uint32 Unknown2;
	uint8 Unknown3;
	uint8 Unknown4;

	static SMSG_GMTICKET_GETTICKET_t *Create ();

	virtual void Assemble ();
};

class SMSG_GMTICKET_SYSTEMSTATUS_t : public NetworkPacket
{
public:
	uint32 Data;

	static SMSG_GMTICKET_SYSTEMSTATUS_t *Create ();

	virtual void Assemble ();
};

class SMSG_PERIODICAURALOG_t : public NetworkPacket
{
public:
	uint64 Victim;
	uint64 Attacker;
	uint32 SpellId;
	uint32 TargetCount;
	uint32 Damage;

	static SMSG_PERIODICAURALOG_t *Create ();

	virtual void Assemble ();
};

class SMSG_SPELLNONMELEEDAMAGELOG_t : public NetworkPacket
{
public:
	uint64 Victim;
	uint64 Attacker;
	uint32 SpellId;
	uint32 Damage;

	static SMSG_SPELLNONMELEEDAMAGELOG_t *Create ();

	virtual void Assemble ();
};
#endif // __OPCODES_H__