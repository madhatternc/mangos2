/* AUTOGENERATED. DO NOT MODIFY !!! */
/* RULES_MTIME: 1225482740.0 */
#ifndef __REALMPROTO_H__
#define __REALMPROTO_H__

#include "RealmListSrv.h"
enum RealmOpcodes
{
	CMSG_LOGON_CHALLENGE = 0x0000,
	SMSG_LOGON_CHALLENGE = 0x0000,
	CMSG_LOGON_PROOF = 0x0001,
	SMSG_LOGON_PROOF = 0x0001,
	CMSG_RECONNECT_CHALLENGE = 0x0002,
	CMSG_RECONNECT_PROOF = 0x0003,
	CMSG_REALMLIST = 0x0010,
	SMSG_REALMLIST = 0x0010
};

enum RealmErrors
{
	CE_SUCCESS = 0x0,
	CE_WRONG_BUILDNUMBER = 0x1,
	CE_SERVER_FULL = 0x2,
	CE_ACCOUNT_CLOSED = 0x3,
	CE_BAD_CREDENTIALS = 0x4,
	CE_BAD_CREDENTIALS_DUP = 0x5,
	CE_ALREADY_LOGGED_IN = 0x6,
	CE_PREPAID_TIME_EXPIRED = 0x7,
	CE_CANNOT_LOGIN = 0x8,
	CE_BAD_VERSION = 0x9
};

class CMSG_LOGON_CHALLENGE_t : public NetworkPacket
{
public:
	uint8 ErrorCode;
	uint16 Length;
	uint8 GameID[4];
	uint8 ClientVersion[3];
	uint16 ClientBuild;
	uint8 Arch[4];
	uint8 OS[4];
	uint8 Lang[4];
	uint32 TimeZone;
	uint32 ClientIP;
	char * UserName;

	protected:
	virtual ~CMSG_LOGON_CHALLENGE_t ();
	public:

	static CMSG_LOGON_CHALLENGE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_LOGON_CHALLENGE_t : public NetworkPacket
{
public:
	uint8 BR[32];
	uint8 N[32];
	uint8 Salt[32];

	static SMSG_LOGON_CHALLENGE_t *Create ();

	virtual void Assemble ();
};

class CMSG_LOGON_PROOF_t : public NetworkPacket
{
public:
	uint8 A[32];
	uint8 M1[20];
	uint8 CRC[20];
	uint8 NumKeys;

	static CMSG_LOGON_PROOF_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_LOGON_PROOF_t : public NetworkPacket
{
public:
	uint8 ErrorCode;
	uint8 M2[20];

	static SMSG_LOGON_PROOF_t *Create ();
	void Init ();

	virtual void Assemble ();
};

class CMSG_RECONNECT_CHALLENGE_t : public NetworkPacket
{
public:
	uint8 ErrorCode;
	uint16 Length;
	uint8 GameID[4];
	uint8 ClientVersion[3];
	uint16 ClientBuild;
	uint8 Arch[4];
	uint8 OS[4];
	uint8 Lang[4];
	uint32 TimeZone;
	uint32 ClientIP;
	char * UserName;

	protected:
	virtual ~CMSG_RECONNECT_CHALLENGE_t ();
	public:

	static CMSG_RECONNECT_CHALLENGE_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class CMSG_REALMLIST_t : public NetworkPacket
{
public:
	uint32 request;

	static CMSG_REALMLIST_t *Create (Socket *socket);
	bool Parse (Socket *socket);
};

class SMSG_REALMLIST_t : public NetworkPacket
{
public:
	uint16 DataLen;
	uint32 Request;
	uint8 NumRealms;
	RealmVector RealmList;

	static SMSG_REALMLIST_t *Create ();

	virtual void Assemble ();
};
#endif // __REALMPROTO_H__
