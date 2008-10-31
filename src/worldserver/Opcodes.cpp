/* AUTOGENERATED. DO NOT MODIFY !!! */
/* RULES_MTIME: 1225125631.22 */
#include "Opcodes.h"
CMSG_CHAR_CREATE_t::~CMSG_CHAR_CREATE_t ()
{
	delete [] Name;
}

CMSG_CHAR_CREATE_t *CMSG_CHAR_CREATE_t::Create (Socket *socket)
{
    CMSG_CHAR_CREATE_t *This = new CMSG_CHAR_CREATE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_CHAR_CREATE_t::Parse (Socket *socket)
{
	if (!(Name = socket->GetCStr ())) return false;
	if (!socket->Get (Race)) return false;
	if (!socket->Get (Class)) return false;
	if (!socket->Get (Gender)) return false;
	if (!socket->Get (Skin)) return false;
	if (!socket->Get (Face)) return false;
	if (!socket->Get (HairStyle)) return false;
	if (!socket->Get (HairColor)) return false;
	if (!socket->Get (FacialHair)) return false;
	if (!socket->Get (OutfitId)) return false;
    return true;
}

CMSG_CHAR_DELETE_t *CMSG_CHAR_DELETE_t::Create (Socket *socket)
{
    CMSG_CHAR_DELETE_t *This = new CMSG_CHAR_DELETE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_CHAR_DELETE_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Guid)) return false;
    return true;
}

SMSG_CHAR_CREATE_t *SMSG_CHAR_CREATE_t::Create ()
{
    SMSG_CHAR_CREATE_t *This = new SMSG_CHAR_CREATE_t;
    return This;
}

void SMSG_CHAR_CREATE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_CHAR_CREATE); cur += sizeof (uint16);
	*cur = ErrorCode; cur += sizeof (uint8);
}

SMSG_CHAR_ENUM_t *SMSG_CHAR_ENUM_t::Create ()
{
    SMSG_CHAR_ENUM_t *This = new SMSG_CHAR_ENUM_t;
    return This;
}

void SMSG_CHAR_ENUM_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8) + 0;
	for (int i1 = 0; i1 < List.Length (); i1++)
		length += sizeof (uint64) + strlen (List [i1]->Name) + 1 + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint32) + sizeof (uint32) + sizeof (float) + sizeof (float) + sizeof (float) + sizeof (uint32) + sizeof (uint32) + sizeof (uint8) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + List [i1]->SlotItems.Length () * (sizeof (uint32) + sizeof (uint8));
	length += 0;

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_CHAR_ENUM); cur += sizeof (uint16);
	*cur = Count; cur += sizeof (uint8);
	for (int i1 = 0; i1 < List.Length(); i1++)
	{
		PUT_LE64 (cur, List [i1]->GUID); cur += sizeof (uint64);
		{
		    size_t _sl = strlen (List [i1]->Name);
		    memcpy (cur, List [i1]->Name, _sl + 1);
		    cur += _sl + 1;
		}
		*cur = List [i1]->Race; cur += sizeof (uint8);
		*cur = List [i1]->Class; cur += sizeof (uint8);
		*cur = List [i1]->Gender; cur += sizeof (uint8);
		*cur = List [i1]->Skin; cur += sizeof (uint8);
		*cur = List [i1]->Face; cur += sizeof (uint8);
		*cur = List [i1]->HairStyle; cur += sizeof (uint8);
		*cur = List [i1]->HairColor; cur += sizeof (uint8);
		*cur = List [i1]->FacialHair; cur += sizeof (uint8);
		*cur = List [i1]->Level; cur += sizeof (uint8);
		PUT_LE32 (cur, List [i1]->ZoneId); cur += sizeof (uint32);
		PUT_LE32 (cur, List [i1]->MapId); cur += sizeof (uint32);
		PUT_LEF32 (cur, List [i1]->PositionX); cur += sizeof (float);
		PUT_LEF32 (cur, List [i1]->PositionY); cur += sizeof (float);
		PUT_LEF32 (cur, List [i1]->PositionZ); cur += sizeof (float);
		PUT_LE32 (cur, 0); cur += sizeof (uint32);
		PUT_LE32 (cur, 64); cur += sizeof (uint32);
		*cur = 1; cur += sizeof (uint8);
		PUT_LE32 (cur, List [i1]->PetInfoId); cur += sizeof (uint32);
		PUT_LE32 (cur, List [i1]->PetLevel); cur += sizeof (uint32);
		PUT_LE32 (cur, List [i1]->PetFamilyId); cur += sizeof (uint32);
		for (int i2 = 0; i2 < List [i1]->SlotItems.Length(); i2++)
		{
			PUT_LE32 (cur, List [i1]->SlotItems [i2]->DisplayId); cur += sizeof (uint32);
			*cur = List [i1]->SlotItems [i2]->InventoryType; cur += sizeof (uint8);
		}

	}

}

CMSG_PLAYER_LOGIN_t *CMSG_PLAYER_LOGIN_t::Create (Socket *socket)
{
    CMSG_PLAYER_LOGIN_t *This = new CMSG_PLAYER_LOGIN_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_PLAYER_LOGIN_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Guid)) return false;
    return true;
}

SMSG_NEW_WORLD_t *SMSG_NEW_WORLD_t::Create ()
{
    SMSG_NEW_WORLD_t *This = new SMSG_NEW_WORLD_t;
    return This;
}

void SMSG_NEW_WORLD_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (float) + sizeof (float) + sizeof (float) + sizeof (float);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_NEW_WORLD); cur += sizeof (uint16);
	PUT_LE32 (cur, Mapid); cur += sizeof (uint32);
	PUT_LEF32 (cur, X); cur += sizeof (float);
	PUT_LEF32 (cur, Y); cur += sizeof (float);
	PUT_LEF32 (cur, Z); cur += sizeof (float);
	PUT_LEF32 (cur, O); cur += sizeof (float);
}

SMSG_TRANSFER_PENDING_t *SMSG_TRANSFER_PENDING_t::Create ()
{
    SMSG_TRANSFER_PENDING_t *This = new SMSG_TRANSFER_PENDING_t;
    return This;
}

void SMSG_TRANSFER_PENDING_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_TRANSFER_PENDING); cur += sizeof (uint16);
	PUT_LE32 (cur, Type); cur += sizeof (uint32);
}

SMSG_CHARACTER_LOGIN_FAILED_t *SMSG_CHARACTER_LOGIN_FAILED_t::Create ()
{
    SMSG_CHARACTER_LOGIN_FAILED_t *This = new SMSG_CHARACTER_LOGIN_FAILED_t;
    return This;
}

void SMSG_CHARACTER_LOGIN_FAILED_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_CHARACTER_LOGIN_FAILED); cur += sizeof (uint16);
	PUT_LE32 (cur, ErrorCode); cur += sizeof (uint32);
}

SMSG_LOGIN_SETTIMESPEED_t *SMSG_LOGIN_SETTIMESPEED_t::Create ()
{
    SMSG_LOGIN_SETTIMESPEED_t *This = new SMSG_LOGIN_SETTIMESPEED_t;
    return This;
}

void SMSG_LOGIN_SETTIMESPEED_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (float);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_LOGIN_SETTIMESPEED); cur += sizeof (uint16);
	PUT_LE32 (cur, Time); cur += sizeof (uint32);
	PUT_LEF32 (cur, Speed); cur += sizeof (float);
}

SMSG_LOGOUT_RESPONSE_t *SMSG_LOGOUT_RESPONSE_t::Create ()
{
    SMSG_LOGOUT_RESPONSE_t *This = new SMSG_LOGOUT_RESPONSE_t;
    return This;
}

void SMSG_LOGOUT_RESPONSE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (uint8);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_LOGOUT_RESPONSE); cur += sizeof (uint16);
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
	*cur = Ok; cur += sizeof (uint8);
}

CMSG_NAME_QUERY_t *CMSG_NAME_QUERY_t::Create (Socket *socket)
{
    CMSG_NAME_QUERY_t *This = new CMSG_NAME_QUERY_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_NAME_QUERY_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Guid)) return false;
    return true;
}

SMSG_FRIEND_LIST_t *SMSG_FRIEND_LIST_t::Create ()
{
    SMSG_FRIEND_LIST_t *This = new SMSG_FRIEND_LIST_t;
    return This;
}

void SMSG_FRIEND_LIST_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8) + 0;
	for (int i1 = 0; i1 < Friends.Length (); i1++)
		length += sizeof (uint64) + sizeof (uint8) + ((Friends [i1]->Status != 0) ? (sizeof (uint32) + sizeof (uint32) + sizeof (uint32)) : 0);
	length += 0;

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_FRIEND_LIST); cur += sizeof (uint16);
	*cur = Count; cur += sizeof (uint8);
	for (int i1 = 0; i1 < Friends.Length(); i1++)
	{
		PUT_LE64 (cur, Friends [i1]->PlayerGUID); cur += sizeof (uint64);
		*cur = Friends [i1]->Status; cur += sizeof (uint8);
		if (Friends [i1]->Status != 0)
		{
			PUT_LE32 (cur, Friends [i1]->Area); cur += sizeof (uint32);
			PUT_LE32 (cur, Friends [i1]->Level); cur += sizeof (uint32);
			PUT_LE32 (cur, Friends [i1]->Class); cur += sizeof (uint32);
		}

	}

}

SMSG_FRIEND_STATUS_t *SMSG_FRIEND_STATUS_t::Create ()
{
    SMSG_FRIEND_STATUS_t *This = new SMSG_FRIEND_STATUS_t;
    return This;
}

void SMSG_FRIEND_STATUS_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8) + sizeof (uint64) + ((Result == FRIEND_ADDED_ONLINE || Result == FRIEND_ONLINE || Result ==  FRIEND_OFFLINE) ? (sizeof (uint32) + sizeof (uint32) + sizeof (uint32)) : 0);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_FRIEND_STATUS); cur += sizeof (uint16);
	*cur = Result; cur += sizeof (uint8);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
	if (Result == FRIEND_ADDED_ONLINE || Result == FRIEND_ONLINE || Result ==  FRIEND_OFFLINE)
	{
		PUT_LE32 (cur, Area); cur += sizeof (uint32);
		PUT_LE32 (cur, Level); cur += sizeof (uint32);
		PUT_LE32 (cur, Class); cur += sizeof (uint32);
	}

}

CMSG_ADD_FRIEND_t::~CMSG_ADD_FRIEND_t ()
{
	delete [] Name;
}

CMSG_ADD_FRIEND_t *CMSG_ADD_FRIEND_t::Create (Socket *socket)
{
    CMSG_ADD_FRIEND_t *This = new CMSG_ADD_FRIEND_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_ADD_FRIEND_t::Parse (Socket *socket)
{
	if (!(Name = socket->GetCStr ())) return false;
    return true;
}

SMSG_GROUP_LIST_t *SMSG_GROUP_LIST_t::Create ()
{
    SMSG_GROUP_LIST_t *This = new SMSG_GROUP_LIST_t;
    return This;
}

void SMSG_GROUP_LIST_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + 1 + sizeof (uint8) + 1 + 0;
	for (int i1 = 0; i1 < Members.Length (); i1++)
		length += sizeof (uint8) + 1 + strlen (Members [i1]->Membername) + 1 + 1 + sizeof (uint32) + 1;
	length += 0 + sizeof (uint8) + 1 + sizeof (uint32) + 1 + sizeof (uint8) + sizeof (uint32) + 1 + sizeof (uint8);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_GROUP_LIST); cur += sizeof (uint16);
	*cur = 0; cur += sizeof (uint8);
	*cur = Memberscount; cur += sizeof (uint8);
	*cur = 0; cur += sizeof (uint8);
	for (int i1 = 0; i1 < Members.Length(); i1++)
	{
		*cur = Members [i1]->Slotid; cur += sizeof (uint8);
		*cur = 0; cur += sizeof (uint8);
		{
		    size_t _sl = strlen (Members [i1]->Membername);
		    memcpy (cur, Members [i1]->Membername, _sl + 1);
		    cur += _sl + 1;
		}
		*cur = 0; cur += sizeof (uint8);
		PUT_LE32 (cur, Members [i1]->Guidsno); cur += sizeof (uint32);
		*cur = 0; cur += sizeof (uint8);
	}

	*cur = 1; cur += sizeof (uint8);
	*cur = 0; cur += sizeof (uint8);
	PUT_LE32 (cur, Leaderguid); cur += sizeof (uint32);
	*cur = 0; cur += sizeof (uint8);
	*cur = Lootmethord; cur += sizeof (uint8);
	PUT_LE32 (cur, Lootmaster); cur += sizeof (uint32);
	*cur = 0; cur += sizeof (uint8);
	*cur = Lootthreshold; cur += sizeof (uint8);
}

CMSG_MESSAGECHAT_t::~CMSG_MESSAGECHAT_t ()
{
		delete [] Whisperto;

		delete [] Channel;

	delete [] Msg;
}

CMSG_MESSAGECHAT_t *CMSG_MESSAGECHAT_t::Create (Socket *socket)
{
    CMSG_MESSAGECHAT_t *This = new CMSG_MESSAGECHAT_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_MESSAGECHAT_t::Parse (Socket *socket)
{
	if (!socket->Get (Type)) return false;
	if (!socket->GetLE (Language)) return false;
	if (!socket->GetLE (Guid)) return false;
	if (!socket->GetLE (Msglength)) return false;
	if (Type == CHAT_MSG_WHISPER)
	{
		if (!(Whisperto = socket->GetCStr ())) return false;
	}

	if (Type == CHAT_MSG_CHANNEL)
	{
		if (!(Channel = socket->GetCStr ())) return false;
	}

	if (!(Msg = socket->GetCStr ())) return false;
	if (!socket->Get (Afktoggle)) return false;
    return true;
}

SMSG_MESSAGECHAT_t *SMSG_MESSAGECHAT_t::Create ()
{
    SMSG_MESSAGECHAT_t *This = new SMSG_MESSAGECHAT_t;
    return This;
}

void SMSG_MESSAGECHAT_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8) + 4 + sizeof (uint64) + 3 + sizeof (uint32) + strlen (Msg) + 1 + sizeof (uint8);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_MESSAGECHAT); cur += sizeof (uint16);
	*cur = Type; cur += sizeof (uint8);
	memset (cur, 0, sizeof (uint8)*4); cur += 4;
	PUT_LE64 (cur, Senderguid); cur += sizeof (uint64);
	memset (cur, 0, sizeof (uint8)*3); cur += 3;
	PUT_LE32 (cur, Msglength); cur += sizeof (uint32);
	{
	    size_t _sl = strlen (Msg);
	    memcpy (cur, Msg, _sl + 1);
	    cur += _sl + 1;
	}
	*cur = Afktoggle; cur += sizeof (uint8);
}

CMSG_JOIN_CHANNEL_t::~CMSG_JOIN_CHANNEL_t ()
{
	delete [] Name;
}

CMSG_JOIN_CHANNEL_t *CMSG_JOIN_CHANNEL_t::Create (Socket *socket)
{
    CMSG_JOIN_CHANNEL_t *This = new CMSG_JOIN_CHANNEL_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_JOIN_CHANNEL_t::Parse (Socket *socket)
{
	if (!(Name = socket->GetCStr ())) return false;
    return true;
}

SMSG_CHANNEL_NOTIFY_t *SMSG_CHANNEL_NOTIFY_t::Create ()
{
    SMSG_CHANNEL_NOTIFY_t *This = new SMSG_CHANNEL_NOTIFY_t;
    return This;
}

void SMSG_CHANNEL_NOTIFY_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8) + strlen (Channel) + 1 + sizeof (uint8) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_CHANNEL_NOTIFY); cur += sizeof (uint16);
	*cur = Unknown1; cur += sizeof (uint8);
	{
	    size_t _sl = strlen (Channel);
	    memcpy (cur, Channel, _sl + 1);
	    cur += _sl + 1;
	}
	*cur = Unknown2; cur += sizeof (uint8);
	PUT_LE32 (cur, Unknown3); cur += sizeof (uint32);
}

SMSG_UPDATE_OBJECT_t *SMSG_UPDATE_OBJECT_t::Create ()
{
    SMSG_UPDATE_OBJECT_t *This = new SMSG_UPDATE_OBJECT_t;
    return This;
}

void SMSG_UPDATE_OBJECT_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (uint8) + Values.Length () * (sizeof (uint8) + sizeof (uint64)) + Movement.Length () * (sizeof (uint8) + sizeof (uint64)) + CreateObject.Length () * (sizeof (uint8) + sizeof (uint64) + sizeof (uint8)) + ((OutOfRange.Length ()) ? (sizeof (uint8) + sizeof (uint32)) : 0) + OutOfRange.Length () * (sizeof (uint64));

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_UPDATE_OBJECT); cur += sizeof (uint16);
	PUT_LE32 (cur, Count); cur += sizeof (uint32);
	*cur = 0; cur += sizeof (uint8);
	for (int i1 = 0; i1 < Values.Length(); i1++)
	{
		*cur = UPDATE_VALUES; cur += sizeof (uint8);
		PUT_LE64 (cur, Values [i1]->GetGUID ()); cur += sizeof (uint64);
	}

	for (int i2 = 0; i2 < Movement.Length(); i2++)
	{
		*cur = UPDATE_MOVEMENT; cur += sizeof (uint8);
		PUT_LE64 (cur, Movement [i2]->GetGUID ()); cur += sizeof (uint64);
	}

	for (int i3 = 0; i3 < CreateObject.Length(); i3++)
	{
		*cur = UPDATE_CREATE_OBJECT; cur += sizeof (uint8);
		PUT_LE64 (cur, CreateObject [i3]->GetGUID ()); cur += sizeof (uint64);
		*cur = CreateObject [i3]->GetType (); cur += sizeof (uint8);
	}

	if (OutOfRange.Length ())
	{
		*cur = UPDATE_OUT_OF_RANGE_OBJECTS; cur += sizeof (uint8);
		PUT_LE32 (cur, OutOfRangeCount); cur += sizeof (uint32);
	}

	for (int i5 = 0; i5 < OutOfRange.Length(); i5++)
	{
		PUT_LE64 (cur, OutOfRange [i5]->GetGUID ()); cur += sizeof (uint64);
	}

}

SMSG_DESTROY_OBJECT_t *SMSG_DESTROY_OBJECT_t::Create ()
{
    SMSG_DESTROY_OBJECT_t *This = new SMSG_DESTROY_OBJECT_t;
    return This;
}

void SMSG_DESTROY_OBJECT_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_DESTROY_OBJECT); cur += sizeof (uint16);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
}

CMSG_AREATRIGGER_t *CMSG_AREATRIGGER_t::Create (Socket *socket)
{
    CMSG_AREATRIGGER_t *This = new CMSG_AREATRIGGER_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_AREATRIGGER_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Id)) return false;
    return true;
}

MSG_MOVE_HEARTBEAT_t *MSG_MOVE_HEARTBEAT_t::Create ()
{
    MSG_MOVE_HEARTBEAT_t *This = new MSG_MOVE_HEARTBEAT_t;
    return This;
}

void MSG_MOVE_HEARTBEAT_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint32) + sizeof (uint32) + sizeof (float) + sizeof (float) + sizeof (float) + sizeof (float);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, MSG_MOVE_HEARTBEAT); cur += sizeof (uint16);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
	PUT_LE32 (cur, Flag); cur += sizeof (uint32);
	PUT_LE32 (cur, Unknown1); cur += sizeof (uint32);
	PUT_LEF32 (cur, X); cur += sizeof (float);
	PUT_LEF32 (cur, Y); cur += sizeof (float);
	PUT_LEF32 (cur, Z); cur += sizeof (float);
	PUT_LEF32 (cur, O); cur += sizeof (float);
}

SMSG_TRIGGER_CINEMATIC_t *SMSG_TRIGGER_CINEMATIC_t::Create ()
{
    SMSG_TRIGGER_CINEMATIC_t *This = new SMSG_TRIGGER_CINEMATIC_t;
    return This;
}

void SMSG_TRIGGER_CINEMATIC_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_TRIGGER_CINEMATIC); cur += sizeof (uint16);
	PUT_LE32 (cur, Video); cur += sizeof (uint32);
}

SMSG_TUTORIAL_FLAGS_t *SMSG_TUTORIAL_FLAGS_t::Create ()
{
    SMSG_TUTORIAL_FLAGS_t *This = new SMSG_TUTORIAL_FLAGS_t;
    return This;
}

void SMSG_TUTORIAL_FLAGS_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8)*32;

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_TUTORIAL_FLAGS); cur += sizeof (uint16);
	memcpy (cur, TutMask, sizeof (TutMask)); cur += sizeof (TutMask);
}

CMSG_STANDSTATECHANGE_t *CMSG_STANDSTATECHANGE_t::Create (Socket *socket)
{
    CMSG_STANDSTATECHANGE_t *This = new CMSG_STANDSTATECHANGE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_STANDSTATECHANGE_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Guid)) return false;
	if (!socket->GetLE (State)) return false;
	if (!socket->Get (Animstate)) return false;
    return true;
}

SMSG_EMOTE_t *SMSG_EMOTE_t::Create ()
{
    SMSG_EMOTE_t *This = new SMSG_EMOTE_t;
    return This;
}

void SMSG_EMOTE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (uint64);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_EMOTE); cur += sizeof (uint16);
	PUT_LE32 (cur, Emote); cur += sizeof (uint32);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
}

CMSG_TEXT_EMOTE_t *CMSG_TEXT_EMOTE_t::Create (Socket *socket)
{
    CMSG_TEXT_EMOTE_t *This = new CMSG_TEXT_EMOTE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_TEXT_EMOTE_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Emote)) return false;
	if (!socket->GetLE (Guid)) return false;
    return true;
}

SMSG_TEXT_EMOTE_t *SMSG_TEXT_EMOTE_t::Create ()
{
    SMSG_TEXT_EMOTE_t *This = new SMSG_TEXT_EMOTE_t;
    return This;
}

void SMSG_TEXT_EMOTE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint32) + 1 + strlen(Name) + 1;

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_TEXT_EMOTE); cur += sizeof (uint16);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
	PUT_LE32 (cur, Emote); cur += sizeof (uint32);
	{
	    uint32 _sl = strlen (Name);
	    PUT_LE32 (cur, _sl); cur += sizeof (uint32);
	    memcpy (cur, Name, _sl);
	    cur += _sl;
	}
	*cur = 0; cur += sizeof (uint8);
}

CMSG_AUTOSTORE_LOOT_ITEM_t *CMSG_AUTOSTORE_LOOT_ITEM_t::Create (Socket *socket)
{
    CMSG_AUTOSTORE_LOOT_ITEM_t *This = new CMSG_AUTOSTORE_LOOT_ITEM_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_AUTOSTORE_LOOT_ITEM_t::Parse (Socket *socket)
{
	if (!socket->Get (Lootslot)) return false;
    return true;
}

CMSG_SET_ACTION_BUTTON_t *CMSG_SET_ACTION_BUTTON_t::Create (Socket *socket)
{
    CMSG_SET_ACTION_BUTTON_t *This = new CMSG_SET_ACTION_BUTTON_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_SET_ACTION_BUTTON_t::Parse (Socket *socket)
{
	if (!socket->Get (Button)) return false;
	if (!socket->GetLE (Action)) return false;
    return true;
}

SMSG_ACTION_BUTTONS_t *SMSG_ACTION_BUTTONS_t::Create ()
{
    SMSG_ACTION_BUTTONS_t *This = new SMSG_ACTION_BUTTONS_t;
    return This;
}

void SMSG_ACTION_BUTTONS_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32)*120;

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_ACTION_BUTTONS); cur += sizeof (uint16);

	for (uint i1 = 0; i1 < 120; i1++)
	{
	    PUT_LE32 (cur, Actions [i1]);
	    cur += sizeof (uint32);
	}

}

CMSG_CAST_SPELL_t::~CMSG_CAST_SPELL_t ()
{
		delete [] Targetstring;

}

CMSG_CAST_SPELL_t *CMSG_CAST_SPELL_t::Create (Socket *socket)
{
    CMSG_CAST_SPELL_t *This = new CMSG_CAST_SPELL_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_CAST_SPELL_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Spellid)) return false;
	// STRUCTLET STRL_SPELL_TARGET 
	if (!socket->GetLE (Targetmask)) return false;
	if (Targetmask & TARGET_FLAG_UNIT || Targetmask & TARGET_FLAG_OBJECT)
	{
		if (!socket->GetLE (Targetunit)) return false;
	}

	if (Targetmask & TARGET_FLAG_ITEM)
	{
		if (!socket->GetLE (Targetitem)) return false;
	}

	if (Targetmask & TARGET_FLAG_SOURCE_LOCATION)
	{
		if (!socket->GetLE (SrcX)) return false;
		if (!socket->GetLE (SrcY)) return false;
		if (!socket->GetLE (SrcZ)) return false;
	}

	if (Targetmask & TARGET_FLAG_DEST_LOCATION)
	{
		if (!socket->GetLE (DestX)) return false;
		if (!socket->GetLE (DestY)) return false;
		if (!socket->GetLE (DestZ)) return false;
	}

	if (Targetmask & TARGET_FLAG_STRING)
	{
		if (!(Targetstring = socket->GetCStr ())) return false;
	}

	// END STRUCTLET STRL_SPELL_TARGET 
    return true;
}

CMSG_SET_SELECTION_t *CMSG_SET_SELECTION_t::Create (Socket *socket)
{
    CMSG_SET_SELECTION_t *This = new CMSG_SET_SELECTION_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_SET_SELECTION_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Gui)) return false;
    return true;
}

CMSG_SET_TARGET_t *CMSG_SET_TARGET_t::Create (Socket *socket)
{
    CMSG_SET_TARGET_t *This = new CMSG_SET_TARGET_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_SET_TARGET_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Guid)) return false;
    return true;
}

SMSG_ATTACKSTART_t *SMSG_ATTACKSTART_t::Create ()
{
    SMSG_ATTACKSTART_t *This = new SMSG_ATTACKSTART_t;
    return This;
}

void SMSG_ATTACKSTART_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint64);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_ATTACKSTART); cur += sizeof (uint16);
	PUT_LE64 (cur, Attacker); cur += sizeof (uint64);
	PUT_LE64 (cur, Victim); cur += sizeof (uint64);
}

SMSG_ATTACKSTOP_t *SMSG_ATTACKSTOP_t::Create ()
{
    SMSG_ATTACKSTOP_t *This = new SMSG_ATTACKSTOP_t;
    return This;
}

void SMSG_ATTACKSTOP_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint64) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_ATTACKSTOP); cur += sizeof (uint16);
	PUT_LE64 (cur, Attacker); cur += sizeof (uint64);
	PUT_LE64 (cur, Victim); cur += sizeof (uint64);
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
}

SMSG_ATTACKERSTATEUPDATE_t *SMSG_ATTACKERSTATEUPDATE_t::Create ()
{
    SMSG_ATTACKERSTATEUPDATE_t *This = new SMSG_ATTACKERSTATEUPDATE_t;
    return This;
}

void SMSG_ATTACKERSTATEUPDATE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (uint64) + sizeof (uint64) + sizeof (uint32) + sizeof (uint8) + DamageList.Length () * (sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32));

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_ATTACKERSTATEUPDATE); cur += sizeof (uint16);
	PUT_LE32 (cur, AttackFlags); cur += sizeof (uint32);
	PUT_LE64 (cur, Attacker); cur += sizeof (uint64);
	PUT_LE64 (cur, Victim); cur += sizeof (uint64);
	PUT_LE32 (cur, TotalDamage); cur += sizeof (uint32);
	*cur = Count; cur += sizeof (uint8);
	for (int i1 = 0; i1 < DamageList.Length(); i1++)
	{
		PUT_LE32 (cur, DamageList [i1]->Type); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->Float); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->Damage); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->Absorbed); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->VictimState); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->RoundDuration); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->AdditionalSpellDamage); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->AdditionalSpellId); cur += sizeof (uint32);
		PUT_LE32 (cur, DamageList [i1]->AdditionalSpellAbsorbed); cur += sizeof (uint32);
	}

}

CMSG_LOOT_t *CMSG_LOOT_t::Create ()
{
    CMSG_LOOT_t *This = new CMSG_LOOT_t;
    return This;
}

void CMSG_LOOT_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, CMSG_LOOT); cur += sizeof (uint16);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
}

CMSG_LOOT_t *CMSG_LOOT_t::Create (Socket *socket)
{
    CMSG_LOOT_t *This = new CMSG_LOOT_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_LOOT_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Guid)) return false;
    return true;
}

CMSG_LOOT_RELEASE_t *CMSG_LOOT_RELEASE_t::Create (Socket *socket)
{
    CMSG_LOOT_RELEASE_t *This = new CMSG_LOOT_RELEASE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_LOOT_RELEASE_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Guid)) return false;
    return true;
}

SMSG_LOOT_RESPONSE_t *SMSG_LOOT_RESPONSE_t::Create ()
{
    SMSG_LOOT_RESPONSE_t *This = new SMSG_LOOT_RESPONSE_t;
    return This;
}

void SMSG_LOOT_RESPONSE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint8) + sizeof (uint32) + sizeof (uint8) + Items.Length () * (sizeof (uint8) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + 9);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_LOOT_RESPONSE); cur += sizeof (uint16);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
	*cur = Type; cur += sizeof (uint8);
	PUT_LE32 (cur, Money); cur += sizeof (uint32);
	*cur = Itemcount; cur += sizeof (uint8);
	for (int i1 = 0; i1 < Items.Length(); i1++)
	{
		*cur = Items [i1]->Slot; cur += sizeof (uint8);
		PUT_LE32 (cur, Items [i1]->Guidsno); cur += sizeof (uint32);
		PUT_LE32 (cur, Items [i1]->Quantity); cur += sizeof (uint32);
		PUT_LE32 (cur, Items [i1]->Displayid); cur += sizeof (uint32);
		memset (cur, 0, sizeof (uint8)*9); cur += 9;
	}

}

SMSG_LOOT_RELEASE_RESPONSE_t *SMSG_LOOT_RELEASE_RESPONSE_t::Create ()
{
    SMSG_LOOT_RELEASE_RESPONSE_t *This = new SMSG_LOOT_RELEASE_RESPONSE_t;
    return This;
}

void SMSG_LOOT_RELEASE_RESPONSE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint8);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_LOOT_RELEASE_RESPONSE); cur += sizeof (uint16);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
	*cur = Ok; cur += sizeof (uint8);
}

SMSG_LOOT_REMOVED_t *SMSG_LOOT_REMOVED_t::Create ()
{
    SMSG_LOOT_REMOVED_t *This = new SMSG_LOOT_REMOVED_t;
    return This;
}

void SMSG_LOOT_REMOVED_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_LOOT_REMOVED); cur += sizeof (uint16);
	*cur = Slot; cur += sizeof (uint8);
}

SMSG_GOSSIP_MESSAGE_t *SMSG_GOSSIP_MESSAGE_t::Create ()
{
    SMSG_GOSSIP_MESSAGE_t *This = new SMSG_GOSSIP_MESSAGE_t;
    return This;
}

void SMSG_GOSSIP_MESSAGE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + strlen (Text) + 1 + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_GOSSIP_MESSAGE); cur += sizeof (uint16);
	PUT_LE64 (cur, Guid); cur += sizeof (uint64);
	PUT_LE32 (cur, Textid); cur += sizeof (uint32);
	PUT_LE32 (cur, Bpcount); cur += sizeof (uint32);
	PUT_LE32 (cur, Option); cur += sizeof (uint32);
	PUT_LE32 (cur, Icon); cur += sizeof (uint32);
	{
	    size_t _sl = strlen (Text);
	    memcpy (cur, Text, _sl + 1);
	    cur += _sl + 1;
	}
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
}

CMSG_BUG_t::~CMSG_BUG_t ()
{
	delete [] Content;
	delete [] Type;
}

CMSG_BUG_t *CMSG_BUG_t::Create (Socket *socket)
{
    CMSG_BUG_t *This = new CMSG_BUG_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_BUG_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Suggestion)) return false;
	if (!socket->GetLE (Contentlen)) return false;
	if (!(Content = socket->GetCStr ())) return false;
	if (!socket->GetLE (Typelen)) return false;
	if (!(Type = socket->GetCStr ())) return false;
    return true;
}

CMSG_PING_t *CMSG_PING_t::Create (Socket *socket)
{
    CMSG_PING_t *This = new CMSG_PING_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_PING_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Ordinal)) return false;
    return true;
}

SMSG_PONG_t *SMSG_PONG_t::Create ()
{
    SMSG_PONG_t *This = new SMSG_PONG_t;
    return This;
}

void SMSG_PONG_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_PONG); cur += sizeof (uint16);
	PUT_LE32 (cur, Acknowledge); cur += sizeof (uint32);
}

SMSG_AUTH_CHALLENGE_t *SMSG_AUTH_CHALLENGE_t::Create ()
{
    SMSG_AUTH_CHALLENGE_t *This = new SMSG_AUTH_CHALLENGE_t;
    return This;
}

void SMSG_AUTH_CHALLENGE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_AUTH_CHALLENGE); cur += sizeof (uint16);
	PUT_LE32 (cur, Seed); cur += sizeof (uint32);
}

CMSG_AUTH_SESSION_t::~CMSG_AUTH_SESSION_t ()
{
	delete [] Login;
}

CMSG_AUTH_SESSION_t *CMSG_AUTH_SESSION_t::Create (Socket *socket)
{
    CMSG_AUTH_SESSION_t *This = new CMSG_AUTH_SESSION_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_AUTH_SESSION_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Unknown1)) return false;
	if (!socket->GetLE (Unknown2)) return false;
	if (!(Login = socket->GetCStr ())) return false;
	if (!socket->GetLE (Seed)) return false;
	if (!socket->Get (Digest, sizeof (Digest))) return false;
    return true;
}

SMSG_AUTH_RESPONSE_t *SMSG_AUTH_RESPONSE_t::Create ()
{
    SMSG_AUTH_RESPONSE_t *This = new SMSG_AUTH_RESPONSE_t;
    return This;
}

void SMSG_AUTH_RESPONSE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8) + ((ErrorCode == WSE_AUTHENTICATION_SUCCESSFUL) ? (sizeof (uint8) + sizeof (uint32)) : 0);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_AUTH_RESPONSE); cur += sizeof (uint16);
	*cur = ErrorCode; cur += sizeof (uint8);
	if (ErrorCode == WSE_AUTHENTICATION_SUCCESSFUL)
	{
		*cur = Counter; cur += sizeof (uint8);
		PUT_LE32 (cur, 2002); cur += sizeof (uint32);
	}

}

CMSG_ZONEUPDATE_t *CMSG_ZONEUPDATE_t::Create (Socket *socket)
{
    CMSG_ZONEUPDATE_t *This = new CMSG_ZONEUPDATE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_ZONEUPDATE_t::Parse (Socket *socket)
{
	if (!socket->GetLE (Zone)) return false;
    return true;
}

SMSG_GMTICKET_CREATE_t *SMSG_GMTICKET_CREATE_t::Create ()
{
    SMSG_GMTICKET_CREATE_t *This = new SMSG_GMTICKET_CREATE_t;
    return This;
}

void SMSG_GMTICKET_CREATE_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_GMTICKET_CREATE); cur += sizeof (uint16);
	PUT_LE32 (cur, Id); cur += sizeof (uint32);
}

SMSG_ACCOUNT_DATA_MD5_t *SMSG_ACCOUNT_DATA_MD5_t::Create ()
{
    SMSG_ACCOUNT_DATA_MD5_t *This = new SMSG_ACCOUNT_DATA_MD5_t;
    return This;
}

void SMSG_ACCOUNT_DATA_MD5_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint8)*80;

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_ACCOUNT_DATA_MD5); cur += sizeof (uint16);
	memcpy (cur, MD5, sizeof (MD5)); cur += sizeof (MD5);
}

CMSG_REQUEST_ACCOUNT_DATA_t *CMSG_REQUEST_ACCOUNT_DATA_t::Create (Socket *socket)
{
    CMSG_REQUEST_ACCOUNT_DATA_t *This = new CMSG_REQUEST_ACCOUNT_DATA_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_REQUEST_ACCOUNT_DATA_t::Parse (Socket *socket)
{
	if (!socket->GetLE (FileIndex)) return false;
    return true;
}

CMSG_UPDATE_ACCOUNT_DATA_t *CMSG_UPDATE_ACCOUNT_DATA_t::Create (Socket *socket, uint pktlen)
{
    CMSG_UPDATE_ACCOUNT_DATA_t *This = new CMSG_UPDATE_ACCOUNT_DATA_t;
    if (This->Parse (socket, pktlen))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_UPDATE_ACCOUNT_DATA_t::Parse (Socket *socket, uint pktlen)
{
	if (!socket->GetLE (FileIndex)) return false;
	if (!socket->GetLE (UncompressedSize)) return false;
	CompressedData = new uint8 [CompressedData_Size = pktlen - socket->Chewed ()];
	if (!socket->Get (CompressedData, CompressedData_Size)) return false;
    return true;
}

SMSG_UPDATE_ACCOUNT_DATA_t *SMSG_UPDATE_ACCOUNT_DATA_t::Create ()
{
    SMSG_UPDATE_ACCOUNT_DATA_t *This = new SMSG_UPDATE_ACCOUNT_DATA_t;
    return This;
}

void SMSG_UPDATE_ACCOUNT_DATA_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (uint32) + CompressedData_Size;

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_UPDATE_ACCOUNT_DATA); cur += sizeof (uint16);
	PUT_LE32 (cur, FileIndex); cur += sizeof (uint32);
	PUT_LE32 (cur, UncompressedSize); cur += sizeof (uint32);
	memcpy (cur, CompressedData, CompressedData_Size); cur += CompressedData_Size;
}

SMSG_GMTICKET_GETTICKET_t *SMSG_GMTICKET_GETTICKET_t::Create ()
{
    SMSG_GMTICKET_GETTICKET_t *This = new SMSG_GMTICKET_GETTICKET_t;
    return This;
}

void SMSG_GMTICKET_GETTICKET_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32) + sizeof (uint32) + sizeof (uint8) + sizeof (uint8);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_GMTICKET_GETTICKET); cur += sizeof (uint16);
	PUT_LE32 (cur, Unknown1); cur += sizeof (uint32);
	PUT_LE32 (cur, Unknown2); cur += sizeof (uint32);
	*cur = Unknown3; cur += sizeof (uint8);
	*cur = Unknown4; cur += sizeof (uint8);
}

SMSG_GMTICKET_SYSTEMSTATUS_t *SMSG_GMTICKET_SYSTEMSTATUS_t::Create ()
{
    SMSG_GMTICKET_SYSTEMSTATUS_t *This = new SMSG_GMTICKET_SYSTEMSTATUS_t;
    return This;
}

void SMSG_GMTICKET_SYSTEMSTATUS_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_GMTICKET_SYSTEMSTATUS); cur += sizeof (uint16);
	PUT_LE32 (cur, Data); cur += sizeof (uint32);
}

SMSG_PERIODICAURALOG_t *SMSG_PERIODICAURALOG_t::Create ()
{
    SMSG_PERIODICAURALOG_t *This = new SMSG_PERIODICAURALOG_t;
    return This;
}

void SMSG_PERIODICAURALOG_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint64) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_PERIODICAURALOG); cur += sizeof (uint16);
	PUT_LE64 (cur, Victim); cur += sizeof (uint64);
	PUT_LE64 (cur, Attacker); cur += sizeof (uint64);
	PUT_LE32 (cur, SpellId); cur += sizeof (uint32);
	PUT_LE32 (cur, TargetCount); cur += sizeof (uint32);
	PUT_LE32 (cur, Damage); cur += sizeof (uint32);
	PUT_LE32 (cur, 5); cur += sizeof (uint32);
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
}

SMSG_SPELLNONMELEEDAMAGELOG_t *SMSG_SPELLNONMELEEDAMAGELOG_t::Create ()
{
    SMSG_SPELLNONMELEEDAMAGELOG_t *This = new SMSG_SPELLNONMELEEDAMAGELOG_t;
    return This;
}

void SMSG_SPELLNONMELEEDAMAGELOG_t::Assemble ()
{
	length = sizeof(uint16)+sizeof(uint16) + sizeof (uint64) + sizeof (uint64) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32) + sizeof (uint32);

	data = new uint8 [length]; uint8 *cur = data;
	PUT_BE16 (cur, length - 2); cur += sizeof (uint16);
	PUT_LE16 (cur, SMSG_SPELLNONMELEEDAMAGELOG); cur += sizeof (uint16);
	PUT_LE64 (cur, Victim); cur += sizeof (uint64);
	PUT_LE64 (cur, Attacker); cur += sizeof (uint64);
	PUT_LE32 (cur, SpellId); cur += sizeof (uint32);
	PUT_LE32 (cur, Damage); cur += sizeof (uint32);
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
	PUT_LE32 (cur, 0); cur += sizeof (uint32);
}

// --- THE END ---
