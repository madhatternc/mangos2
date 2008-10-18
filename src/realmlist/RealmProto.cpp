/* AUTOGENERATED. DO NOT MODIFY !!! */
/* RULES_MTIME: 1223890737.0 */
#include "RealmProto.h"
CMSG_LOGON_CHALLENGE_t::~CMSG_LOGON_CHALLENGE_t ()
{
	delete [] UserName;
}

CMSG_LOGON_CHALLENGE_t *CMSG_LOGON_CHALLENGE_t::Create (Socket *socket)
{
    CMSG_LOGON_CHALLENGE_t *This = new CMSG_LOGON_CHALLENGE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_LOGON_CHALLENGE_t::Parse (Socket *socket)
{
	if (!socket->Get (ErrorCode)) return false;
	if (!socket->GetLE (Length)) return false;
	if (!socket->Get (GameID, sizeof (GameID))) return false;
	if (!socket->Get (ClientVersion, sizeof (ClientVersion))) return false;
	if (!socket->GetLE (ClientBuild)) return false;
	if (!socket->Get (Arch, sizeof (Arch))) return false;
	if (!socket->Get (OS, sizeof (OS))) return false;
	if (!socket->Get (Lang, sizeof (Lang))) return false;
	if (!socket->GetLE (TimeZone)) return false;
	if (!socket->Get (ClientIP, sizeof (ClientIP))) return false;
	{
	    uint8 _sl;
	    if (!socket->Get (_sl)) return false;
	    UserName = new char [_sl + 1];
	    if (!socket->Get (UserName, _sl))
	        return false;
	    UserName [_sl] = 0;
	}
    return true;
}

SMSG_LOGON_CHALLENGE_t *SMSG_LOGON_CHALLENGE_t::Create ()
{
    SMSG_LOGON_CHALLENGE_t *This = new SMSG_LOGON_CHALLENGE_t;
    This->Init ();
    return This;
}

void SMSG_LOGON_CHALLENGE_t::Init ()
{
	ErrorCode = CE_SUCCESS;
}

void SMSG_LOGON_CHALLENGE_t::Assemble ()
{
	length = sizeof (uint8) + sizeof (uint8) + ((ErrorCode == CE_SUCCESS) ? (sizeof (uint8) + sizeof (uint8)*32 + sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8)*32 + sizeof (uint8)*32 + sizeof (uint8)*16 + sizeof (uint8)) : 0);

	data = new uint8 [length]; uint8 *cur = data;
	*cur++ = SMSG_LOGON_CHALLENGE;
	*cur = ErrorCode; cur += sizeof (uint8);
	if (ErrorCode == CE_SUCCESS)
	{
		*cur = 0; cur += sizeof (uint8);
		memcpy (cur, BR, sizeof (BR)); cur += sizeof (BR);
		*cur = 1; cur += sizeof (uint8);
		*cur = 7; cur += sizeof (uint8);
		*cur = 32; cur += sizeof (uint8);
		memcpy (cur, N, sizeof (N)); cur += sizeof (N);
		memcpy (cur, Salt, sizeof (Salt)); cur += sizeof (Salt);
		memset (cur, 0, sizeof (uint8)*16); cur += sizeof (uint8)*16;
		*cur = 0; cur += sizeof (uint8);
	}

}

CMSG_LOGON_PROOF_t *CMSG_LOGON_PROOF_t::Create (Socket *socket)
{
    CMSG_LOGON_PROOF_t *This = new CMSG_LOGON_PROOF_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_LOGON_PROOF_t::Parse (Socket *socket)
{
	if (!socket->Get (A, sizeof (A))) return false;
	if (!socket->Get (M1, sizeof (M1))) return false;
	if (!socket->Get (CRC, sizeof (CRC))) return false;
	if (!socket->Get (NumKeys)) return false;
    return true;
}

SMSG_LOGON_PROOF_t *SMSG_LOGON_PROOF_t::Create ()
{
    SMSG_LOGON_PROOF_t *This = new SMSG_LOGON_PROOF_t;
    This->Init ();
    return This;
}

void SMSG_LOGON_PROOF_t::Init ()
{
	ErrorCode = CE_SUCCESS;
}

void SMSG_LOGON_PROOF_t::Assemble ()
{
	length = sizeof (uint8) + sizeof (uint8) + ((ErrorCode == CE_SUCCESS) ? (sizeof (uint8)*20 + sizeof (uint32)) : 0);

	data = new uint8 [length]; uint8 *cur = data;
	*cur++ = SMSG_LOGON_PROOF;
	*cur = ErrorCode; cur += sizeof (uint8);
	if (ErrorCode == CE_SUCCESS)
	{
		memcpy (cur, M2, sizeof (M2)); cur += sizeof (M2);
		PUT_LE32 (cur, 0); cur += sizeof (uint32);
	}

}

CMSG_RECONNECT_CHALLENGE_t::~CMSG_RECONNECT_CHALLENGE_t ()
{
	delete [] UserName;
}

CMSG_RECONNECT_CHALLENGE_t *CMSG_RECONNECT_CHALLENGE_t::Create (Socket *socket)
{
    CMSG_RECONNECT_CHALLENGE_t *This = new CMSG_RECONNECT_CHALLENGE_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_RECONNECT_CHALLENGE_t::Parse (Socket *socket)
{
	if (!socket->Get (ErrorCode)) return false;
	if (!socket->GetLE (Length)) return false;
	if (!socket->Get (GameID, sizeof (GameID))) return false;
	if (!socket->Get (ClientVersion, sizeof (ClientVersion))) return false;
	if (!socket->GetLE (ClientBuild)) return false;
	if (!socket->Get (Arch, sizeof (Arch))) return false;
	if (!socket->Get (OS, sizeof (OS))) return false;
	if (!socket->Get (Lang, sizeof (Lang))) return false;
	if (!socket->GetLE (TimeZone)) return false;
	if (!socket->Get (ClientIP, sizeof (ClientIP))) return false;
	{
	    uint8 _sl;
	    if (!socket->Get (_sl)) return false;
	    UserName = new char [_sl + 1];
	    if (!socket->Get (UserName, _sl))
	        return false;
	    UserName [_sl] = 0;
	}
    return true;
}

CMSG_RECONNECT_PROOF_t *CMSG_RECONNECT_PROOF_t::Create (Socket *socket)
{
    CMSG_RECONNECT_PROOF_t *This = new CMSG_RECONNECT_PROOF_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_RECONNECT_PROOF_t::Parse (Socket *socket)
{
	if (!socket->Get (A, sizeof (A))) return false;
	if (!socket->Get (M1, sizeof (M1))) return false;
	if (!socket->Get (CRC, sizeof (CRC))) return false;
	if (!socket->Get (NumKeys)) return false;
    return true;
}

CMSG_REALMLIST_t *CMSG_REALMLIST_t::Create (Socket *socket)
{
    CMSG_REALMLIST_t *This = new CMSG_REALMLIST_t;
    if (This->Parse (socket))
        return This;
    This->DecRef (); return NULL;
}

bool CMSG_REALMLIST_t::Parse (Socket *socket)
{
	if (!socket->GetLE (request)) return false;
    return true;
}

SMSG_REALMLIST_t *SMSG_REALMLIST_t::Create ()
{
    SMSG_REALMLIST_t *This = new SMSG_REALMLIST_t;
    return This;
}

void SMSG_REALMLIST_t::Assemble ()
{
	length = sizeof (uint8) + sizeof (uint16) + sizeof (uint32) + sizeof (uint8) + 0;
	for (int i1 = 0; i1 < RealmList.Length (); i1++)
		length += sizeof (uint8) + sizeof (uint8) + sizeof (uint8) + strlen (RealmList [i1]->Name) + 1 + strlen (RealmList [i1]->Address) + 1 + sizeof (float) + sizeof (uint8) + sizeof (uint8) + sizeof (uint8);
	length += 0 + sizeof (uint16);

	data = new uint8 [length]; uint8 *cur = data;
	*cur++ = SMSG_REALMLIST;
	PUT_LE16 (cur, DataLen); cur += sizeof (uint16);
	PUT_LE32 (cur, Request); cur += sizeof (uint32);
	*cur = NumRealms; cur += sizeof (uint8);
	for (int i1 = 0; i1 < RealmList.Length(); i1++)
	{
		*cur = RealmList [i1]->Type; cur += sizeof (uint8);
		*cur = RealmList [i1]->Locked; cur += sizeof (uint8);
		*cur = RealmList [i1]->Color; cur += sizeof (uint8);
		{
		    size_t _sl = strlen (RealmList [i1]->Name);
		    memcpy (cur, RealmList [i1]->Name, _sl + 1);
		    cur += _sl + 1;
		}
		{
		    size_t _sl = strlen (RealmList [i1]->Address);
		    memcpy (cur, RealmList [i1]->Address, _sl + 1);
		    cur += _sl + 1;
		}
		PUT_LEF32 (cur, RealmList [i1]->Population); cur += sizeof (float);
		*cur = RealmList [i1]->NumChars; cur += sizeof (uint8);
		*cur = RealmList [i1]->Language; cur += sizeof (uint8);
		*cur = 1; cur += sizeof (uint8);
	}

	PUT_LE16 (cur, 15); cur += sizeof (uint16);
}

// --- THE END ---
