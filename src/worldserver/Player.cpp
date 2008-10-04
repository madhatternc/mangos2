/**
 *     \file  src/worldserver/Player.cpp
 *    \brief  Provides basic Player functions.
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

#include "Player.h"
#include "WorldServer.h"
#include "Database.h"
#include "Mail.h"
#include "GameClient.h"

//temporary instead of #include Channel.h
struct Channel
{
	char *Name;
};

IMPLEMENT_VECTOR_SORTED (Player::, QuestStatusVector, QuestStatus *, QuestId, uint32)
IMPLEMENT_VECTOR_SORTED_STRKEY (Player::, ChannelsVector, Channel *, Name)
IMPLEMENT_VECTOR_SORTED (Player::, MailVector, Mail *, MessageId, uint32)
IMPLEMENT_VECTOR (Player::, SpellsVector, Spell *)
IMPLEMENT_VECTOR_SORTED (Player::, PlayerCreateInfoVector, PlayerCreateInfo *, Race, uint8)

Player::PlayerCreateInfoVector Player::PlayerCreateData (64, 64);

Player::Player () : Unit (), RegenTimer (0), DismountTimer (0),
Quests (0, 64), Channels (0, 16), MailBox (0, 16),
Spells (0, 32)
{
	DismountCost = 0;
	DismountPosX = DismountPosY = DismountPosZ = 0.0;

	AFK = false;

	memset (&Items, 0, sizeof (Items));
	memset (&TaxiMask, 0, sizeof (TaxiMask));
	memset (&TutorMask, 0, sizeof (TutorMask));
	memset (&Actions, 0, sizeof (Actions));
	memset (&AccountData, 0, sizeof (AccountData));

	// Initialize action bar to something
	Actions [0] = uint32 (0x19CB);

	Name = NULL;
	Client = NULL;

	CurSelection = 0;
	CurTarget = 0;
	GroupLeader = 0;

	IsInvited = false;
	IsInGroup = false;

	LootGuid = 0;

	Field.SetLength (PLAYER_END);
	Field.Clear (UNIT_END, PLAYER_END - UNIT_END);
	Field.SetBits (OBJECT_FIELD_TYPE, TYPE_PLAYER, TYPE_PLAYER);
}

Player::~Player ()
{
	delete [] Name;

	for (int i = 0; i < INVENTORY_SLOT_ITEM_END; i++)
		if (Items [i])
			Items [i]->DecRef ();

	CleanupChannels ();
}

bool Player::PreloadStaticData ()
{
	LOG.Out (LOG_COMMON, "Loading character prototype table ...\n");

	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (dbex->Execute ("SELECT * FROM protochar") != dbeOk)
	{
		LOG.Out (LOG_IMPORTANT, "Failed to load character prototypes from database!\n");
		World->db->PutExecutor (dbex);
		return false;
	}

	if (dbex->NumFields () != 52)
	{
		LOG.Out (LOG_IMPORTANT, "Character prototype table has wrong number of fields!\n");
		World->db->PutExecutor (dbex);
		return false;
	}

	PlayerCreateData.DeleteAll ();
	while (dbex->NextRow ())
	{
		PlayerCreateInfo *pci = new PlayerCreateInfo ();
		pci->Race = dbex->GetU32 (0);
		pci->Class = dbex->GetU32 (1);
		pci->MapId = dbex->GetU32 (2);
		pci->ZoneId = dbex->GetU32 (3);
		pci->PositionX = dbex->GetFloat (4);
		pci->PositionY = dbex->GetFloat (5);
		pci->PositionZ = dbex->GetFloat (6);
		pci->Orientation = dbex->GetFloat (7);
		pci->DisplayId = dbex->GetU32 (8);
		pci->Strength = dbex->GetU32 (9);
		pci->Ability = dbex->GetU32 (10);
		pci->Stamina = dbex->GetU32 (11);
		pci->Intellect = dbex->GetU32 (12);
		pci->Spirit = dbex->GetU32 (13);
		pci->Health = dbex->GetU32 (14);
		pci->Mana = dbex->GetU32 (15);
		pci->Rage = dbex->GetU32 (16);
		pci->Focus = dbex->GetU32 (17);
		pci->Energy = dbex->GetU32 (18);
		pci->AttackPower = dbex->GetU32 (19);
		pci->MinDmg = dbex->GetFloat (20);
		pci->MaxDmg = dbex->GetFloat (21);
		int x = 21;
		for (uint i = 0; i < ARRAY_LEN (pci->Item); i++)
		{
			pci->Item [i] = dbex->GetU32 (x++);
			pci->ItemSlot [i] = dbex->GetU32 (x++);
		}
		for (uint i = 0; i < ARRAY_LEN (pci->Spell); i++)
			pci->Spell [i] = dbex->GetU32 (x++);
		PlayerCreateData.Push (pci);
	}

	PlayerCreateData.QuickSort ();

	World->db->PutExecutor (dbex);
	return true;
}

void Player::UnloadStaticData ()
{
	PlayerCreateData.DeleteAll ();
}

PlayerCreateInfo *Player::FindCreateInfo (int iRace, int iClass, uint32 *err)
{
	int idx = PlayerCreateData.FindSortedKey (Some (uintptr (iRace)));
	if (idx < 0)
	{
		if (err)
			*err = WSE_CREATION_OF_THAT_RACECLASS_IS_DISABLED;
		return NULL;
	}

	// FindSortedKey is not guaranteed to find the first entry with this race,
	// since there are many entries with same race index in the array ...
	// So roll back a little to find the first entry.
	while (idx > 0 && PlayerCreateData.Get (idx - 1)->Race == iRace)
		idx--;

	PlayerCreateInfo *pci = NULL;
	bool found = false;
	while (idx < PlayerCreateData.Length () &&
		(pci = PlayerCreateData.Get (idx))->Race == iRace)
	{
		if (pci->Class == iClass)
		{
			found = true;
			break;
		}
		idx++;
	}

	if (!found)
	{
		if (err)
			*err = WSE_CREATION_OF_THAT_RACECLASS_IS_DISABLED;
		return NULL;
	}
	return pci;
}

static uint32 CheckName (const char *iName)
{
	if (strlen (iName) <= 2)
		return WSE_INVALID_CHARACTER_NAME;

	size_t sl = u8strlen (iName);
	if (sl > 12)
		return WSE_NAMES_MUST_BE_NO_MORE_THEN_12_CHARACTERS;

	char namebuff [6 * 12 + 1];
	u8strlwr (namebuff, iName);

	const char *prev = iName;
	const char *cur = u8strforw (iName, 1);
	int n = 0;
	while (cur && *cur)
	{
		const char *next = u8strforw (cur,1);
		if (memcmp (prev, cur, cur - prev) == 0)
		{
			n++;
			if (n > 1)
				return WSE_YOU_CANNOT_USE_THE_SAME_LETTER_THREE_TIMES_CONSECUTIVELY;
		}
		else
			n = 0;
		prev = cur;
		cur = next;
	}

	return 0;
}

uint32 Player::Create (CMSG_CHAR_CREATE_t &inpkt, GameClient *iClient)
{
	uint32 err;

	err = CheckName (inpkt.Name);
	if (err)
		return err;

	Client = iClient;

	Field.SetU64 (OBJECT_FIELD_GUID, World->GenerateGUID (HIGHGUID_PLAYER));

	PlayerCreateInfo *pci = FindCreateInfo (inpkt.Race, inpkt.Class, &err);
	if (!pci)
		return err;

	uint8 powertype;
	switch (inpkt.Class)
	{
		case CLASS_WARRIOR : powertype = 1; break;			// Rage
		case CLASS_PALADIN : powertype = 0; break;			// Mana
		case CLASS_HUNTER  : powertype = 0; break;
		case CLASS_ROGUE   : powertype = 3; break;			// Energy
		case CLASS_PRIEST  : powertype = 0; break;
		case CLASS_SHAMAN  : powertype = 0; break;
		case CLASS_MAGE    : powertype = 0; break;
		case CLASS_WARLOCK : powertype = 0; break;
		case CLASS_DRUID   : powertype = 0; break;
		default:
			return WSE_ERROR_CREATING_CHARACTER;
	}														// 2 = Focus (unused)

	delete [] Name;
	// Steal inpkt.Name since its allocated for us anyway ...
	Name = inpkt.Name;
	inpkt.Name = NULL;

	MapId = pci->MapId;
	ZoneId = pci->ZoneId;
	PositionX = pci->PositionX;
	PositionY = pci->PositionY;
	PositionZ = pci->PositionZ;

	// Set Starting stats for char
	Field.SetF32 (OBJECT_FIELD_SCALE_X, 1.0f);
	Field.SetU32 (UNIT_FIELD_HEALTH, pci->Health);
	Field.SetU32 (UNIT_FIELD_POWER1, pci->Mana);
	Field.SetU32 (UNIT_FIELD_POWER2, 0);					// this gets divided by 10
	Field.SetU32 (UNIT_FIELD_POWER3, pci->Focus);
	Field.SetU32 (UNIT_FIELD_POWER4, pci->Energy);
	//Field.SetU32 (UNIT_FIELD_POWER5, 0xEEEEEEEE);
	Field.SetU32 (UNIT_FIELD_MAXHEALTH, pci->Health);
	Field.SetU32 (UNIT_FIELD_MAXPOWER1, pci->Mana);
	Field.SetU32 (UNIT_FIELD_MAXPOWER2, pci->Rage);
	Field.SetU32 (UNIT_FIELD_MAXPOWER3, pci->Focus);
	Field.SetU32 (UNIT_FIELD_MAXPOWER4, pci->Energy);
	//Field.SetU32 (UNIT_FIELD_MAXPOWER5, 5);
	Field.SetU32 (UNIT_FIELD_LEVEL, 1);
	Field.SetU32 (UNIT_FIELD_FACTIONTEMPLATE, 1);
	Field.SetU32 (UNIT_FIELD_BYTES_0, uint32 (inpkt.Race ) | (uint32 (inpkt.Class) << 8 ) | \
		(uint32 (inpkt.Gender) << 16 ) | (uint32 (powertype) << 24));
	Field.SetU32 (UNIT_FIELD_BYTES_1, 0x0011EE00);
	Field.SetU32 (UNIT_FIELD_BYTES_2, 0xEEEEEE00);
	Field.SetU32 (UNIT_FIELD_FLAGS , 0x08);
	Field.SetU32 (UNIT_FIELD_STAT0, pci->Strength);
	Field.SetU32 (UNIT_FIELD_STAT1, pci->Ability);
	Field.SetU32 (UNIT_FIELD_STAT2, pci->Stamina);
	Field.SetU32 (UNIT_FIELD_STAT3, pci->Intellect);
	Field.SetU32 (UNIT_FIELD_STAT4, pci->Spirit);
	Field.SetU32 (UNIT_FIELD_BASEATTACKTIME, 2000);
	Field.SetU32 (UNIT_FIELD_BASEATTACKTIME+1, 2000);
	Field.SetF32 (UNIT_FIELD_BOUNDINGRADIUS, 0.388999998569489f);
	Field.SetF32 (UNIT_FIELD_COMBATREACH, 1.5f);
	Field.SetU32 (UNIT_FIELD_DISPLAYID, pci->DisplayId + inpkt.Gender);
	Field.SetU32 (UNIT_FIELD_NATIVEDISPLAYID, pci->DisplayId + inpkt.Gender);
	Field.SetF32 (UNIT_FIELD_MINDAMAGE, pci->MinDmg);
	Field.SetF32 (UNIT_FIELD_MAXDAMAGE, pci->MaxDmg);
	Field.SetU32 (UNIT_FIELD_ATTACKPOWER, pci->AttackPower);
	Field.SetU32 (PLAYER_BYTES, uint32 (inpkt.Skin) | (uint32 (inpkt.Face) << 8) | \
		(uint32 (inpkt.HairStyle) << 16) | (uint32 (inpkt.HairColor) << 24));
	Field.SetU32 (PLAYER_BYTES_2, uint32 (inpkt.FacialHair) | (uint32 (inpkt.OutfitId) << 8) | \
		(0x01 << 16) | (0x01 << 24));
	Field.SetU32 (PLAYER_NEXT_LEVEL_XP, 800);
	Field.SetU32 (PLAYER_FIELD_BYTES, 0xEEEE0000);

	for (uint i = 0; i < ARRAY_LEN (pci->Item); i++)
		if (pci->Item [i] && pci->ItemSlot [i])
	{
		Item *item = new Item ();
		item->Create (World->GenerateGUID (HIGHGUID_THING), pci->Item [i], this);
		AddItemToSlot (pci->ItemSlot [i], item);
		item->DecRef ();
	}

	for (uint i = 0; i < ARRAY_LEN (pci->Spell); i++)
		if (pci->Spell [i])
			AddSpell (pci->Spell [i], 0);

	return WSE_CHARACTER_CREATED;
}

#if 0

void Player::Update(uint32 p_time )
{
	if(!IsInWorld())
		return;

	Unit::Update(p_time);

	if(m_regenTimer > 0)
	{
		if(p_time >= m_regenTimer)
			m_regenTimer = 0;
		else
			m_regenTimer -= p_time;
	}

	if (m_state & UF_ATTACKING)
	{
		// In combat!
		if (isAttackReady())
		{
			Unit *pVictim = NULL;

			pVictim = objmgr.GetObject<Creature>(m_curSelection);

			if (!pVictim)
			{
				Log::getSingleton().outDetail("Player::Update:  No valid current selection to attack, stopping attack\n");
				clearStateFlag(UF_ATTACKING);
				smsg_AttackStop(m_curSelection);
			}
			else
			{
				if(canReachWithAttack(pVictim))
				{
					AttackerStateUpdate(pVictim,0,false);
					setAttackTimer();
				}
			}
		}
	}

	// only regenerate if NOT in combat, and if alive
	else if (isAlive())
	{
		// Regenerate health, mana and energy if necessary.
		Regenerate(UNIT_FIELD_HEALTH, UNIT_FIELD_MAXHEALTH, true);
		Regenerate(UNIT_FIELD_POWER1, UNIT_FIELD_MAXPOWER1, true);
		Regenerate(UNIT_FIELD_POWER2, UNIT_FIELD_MAXPOWER2, false);
		Regenerate(UNIT_FIELD_POWER4, UNIT_FIELD_MAXPOWER4, true);
	}

	// Dead System
	if (m_deathState == JUST_DIED)
	{
		KillPlayer();
	}

	// Auto-Dismount after Taxiride
	if(m_dismountTimer > 0)
	{
		if(p_time >= m_dismountTimer)
		{
			m_dismountTimer = 0;

			Field.SetU32 (PLAYER_FIELD_COINAGE , m_dismountCost);
			m_dismountCost = 0;

			SetPosition(m_mount_pos_x,
				m_mount_pos_y,
				m_mount_pos_z, true);

			Field.SetU32 (UNIT_FIELD_MOUNTDISPLAYID , 0);
			RemoveFlag(UNIT_FIELD_FLAGS ,0x000004);
			RemoveFlag(UNIT_FIELD_FLAGS, 0x002000);

			SetPlayerSpeed(RUN,7.5f,false);

		}
		else
			m_dismountTimer -= p_time;
	}

	/*
	 //This was replaced by teleporting to spirit healer.
	 if (m_timeOfDeath > 0 && (uint32)time(NULL) > m_timeOfDeath + m_corpseDelay){
	 m_timeOfDeath = 0;
	 m_respawnDelay = 5000;
	 session->GetPlayer()->Field.SetU32 (PLAYER_BYTES_2, (0xffffffff - 0x10) & session->GetPlayer()->GetUInt32Value(PLAYER_BYTES_2 ));
	 session->GetPlayer()->Field.SetU32 (UNIT_FIELD_FLAGS, (0xffffffff - 65536) & session->GetPlayer()->GetUInt32Value(UNIT_FIELD_FLAGS ));
	 session->GetPlayer()->setDeathState(ALIVE);
	 }
	 */

	//UpdateObject();
}

/// Regenerates the regenField's curValue to the maxValue
/// Right now, everything regenerates at the same rate
/// A possible mod is to add another parameter, the stat regeneration is based off of
/// (Intelligence for mana, Strength for HP)
/// And build a regen rate based on that
void Player::Regenerate(uint16 field_cur, uint16 field_max, bool switch_)
{
	uint32 curValue = GetUInt32Value(field_cur);
	uint32 maxValue = GetUInt32Value(field_max);

	if (switch_)
	{
		if (curValue >= maxValue)
			return;
	}
	else
	{
		if (curValue == 0)
			return;
	}

	uint32 regenDelay = 2000;

	// check if it's time to regen health
	if (m_regenTimer != 0)
		return;

	m_regenTimer = regenDelay;

	switch (field_cur)
	{
		case UNIT_FIELD_HEALTH:
															//FIXME
			curValue+=uint32((GetUInt32Value(UNIT_FIELD_STAT4) * .15));
			break;
		case UNIT_FIELD_POWER1:
															//FIXME
			curValue+=uint32((GetUInt32Value(UNIT_FIELD_STAT4) * .15));
			break;
		case UNIT_FIELD_POWER2:
															//FIXME
			curValue-=uint32((GetUInt32Value(UNIT_FIELD_STAT4) * 1.5));
			break;
		case UNIT_FIELD_POWER4:
															//FIXME
			curValue+=uint32((GetUInt32Value(UNIT_FIELD_STAT4) * .15));
			break;
	}

	if (switch_)
	{
		if (curValue > maxValue) curValue = maxValue;
		Field.SetU32 (field_cur, curValue);
	}
	else
	{
		if (curValue > maxValue) curValue = 0;
		Field.SetU32 (field_cur, curValue);
	}
}

/////////////////////////////////// QUESTS ////////////////////////////////////////////
uint32 Player::getQuestStatus(uint32 quest_id)
{
	if(mQuestStatus.find(quest_id ) == mQuestStatus.end() ) return 0;
	return mQuestStatus[quest_id].status;
}

uint32 Player::addNewQuest(uint32 quest_id, uint32 status)
{
	quest_status qs;
	qs.quest_id = quest_id;
	qs.status = status;

	mQuestStatus[quest_id] = qs;
	return status;
};

void Player::loadExistingQuest(quest_status qs)
{
	mQuestStatus[qs.quest_id] = qs;
}

void Player::setQuestStatus(uint32 quest_id, uint32 new_status)
{
	assert(mQuestStatus.find(quest_id ) != mQuestStatus.end());
	mQuestStatus[quest_id].status = new_status;
}

uint16 Player::getOpenQuestSlot()
{
	uint16 start = PLAYER_QUEST_LOG_1_1;
	uint16 end = PLAYER_QUEST_LOG_1_1 + 80;
	for (uint16 i = start; i <= end; i+=4)
		if (GetUInt32Value(i) == 0)
			return i;

	return 0;
}

uint16 Player::getQuestSlot(uint32 quest_id)
{
	uint16 start = PLAYER_QUEST_LOG_1_1;
	uint16 end = PLAYER_QUEST_LOG_1_1 + 80;
	for (uint16 i = start; i <= end; i+=4)
		if (GetUInt32Value(i) == quest_id)
			return i;

	return 0;
}

/*
 void Player::setQuestLogBits(UpdateMask *updateMask)
 {
 for(StatusMap::iterator i = mQuestStatus.begin(); i != mQuestStatus.end(); ++ i ) {
 if (i->second.status == 3)
 {
 // incomplete, put the quest in the log
 uint16 log_slot = getQuestSlot(i->second.quest_id);
 struct quest_status qs = i->second;

 if (log_slot == 0){ // in case this quest hasnt been added to the updateValues (but it shoudl have been!)
 log_slot = getOpenQuestSlot();
 Field.SetU32 (log_slot, qs.quest_id);
 Field.SetU32 (log_slot+1, 0x337);
 }

 updateMask->setBit(log_slot);
 updateMask->setBit(log_slot+1);

 if (qs.m_questMobCount[0] > 0 || qs.m_questMobCount[1] > 0 ||
 qs.m_questMobCount[2] > 0 || qs.m_questMobCount[3] > 0)
 {
 updateMask->setBit(log_slot+2);
 }
 }
 }
 }*/

void Player::KilledMonster(uint32 entry, const uint64 &guid)
{
	for(StatusMap::iterator i = mQuestStatus.begin(); i != mQuestStatus.end(); ++ i )
	{
		if (i->second.status == 3)
		{
			Quest *pQuest = objmgr.GetQuest(i->first);
			for (int j=0; j<4; j++)
			{
				if (pQuest->m_questMobId[j] == entry)
				{
					if (i->second.m_questMobCount[j]+1 <= pQuest->m_questMobCount[j])
					{
						i->second.m_questMobCount[j]++ ;

						// Send Update quest update kills message
						WorldPacket data;
						data.Initialize(SMSG_QUESTUPDATE_ADD_KILL);
						data << pQuest->m_questId;
						data << uint32(pQuest->m_questMobId[j]);
						data << uint32(i->second.m_questMobCount[j]);
						data << uint32(pQuest->m_questMobCount[j]);
						data << guid;
						GetSession()->SendPacket(&data);

						// update journal
						// this is crazy.  each bit corresponds to a kill, set multiple bits to signify multiple kills
						uint32 start_bit=0;
						if (j-1 < 0) start_bit = 0;
						else
							for (int n=j-1; n>=0; n--)
								start_bit += pQuest->m_questMobCount[n];

						uint16 log_slot = getQuestSlot(pQuest->m_questId);
						uint32 kills = GetUInt32Value(log_slot+2);

						int exp = start_bit + i->second.m_questMobCount[j]-1;
						kills |= 1 << exp;
						Field.SetU32 (log_slot+2, kills);
					}

					checkQuestStatus(i->second.quest_id);
					// Ehh, I think a packet should be sent here, but I havent found one in the official logs yet

					return;
				}											// end if mobId == entry
			}												// end for each mobId
		}													// end if status == 3
	}														// end for each quest
}

//======================================================
///  Check to see if all the required monsters and items
///  have been killed and collected.
//======================================================
bool Player::checkQuestStatus(uint32 quest_id)
{
	assert(mQuestStatus.find(quest_id ) != mQuestStatus.end());
	quest_status qs = mQuestStatus[quest_id];
	Quest *pQuest = objmgr.GetQuest(quest_id);

	if (qs.m_questItemCount[0] == pQuest->m_questItemCount[0] &&
		qs.m_questItemCount[1] == pQuest->m_questItemCount[1] &&
		qs.m_questItemCount[2] == pQuest->m_questItemCount[2] &&
		qs.m_questItemCount[3] == pQuest->m_questItemCount[3] &&
		qs.m_questMobCount[0] == pQuest->m_questMobCount[0] &&
		qs.m_questMobCount[1] == pQuest->m_questMobCount[1] &&
		qs.m_questMobCount[2] == pQuest->m_questMobCount[2] &&
		qs.m_questMobCount[3] == pQuest->m_questMobCount[3])
	{
		// Quest complete!
		return true;
	}

	return false;
}

///  This function sends the message displaying the purple XP gain for the char
///  It assumes you will send out an UpdateObject packet at a later time.
void Player::GiveXP(uint32 xp, const uint64 &guid)
{
	if (xp == 0)
		return;

	WorldPacket data;
	if (guid != 0)
	{
		// Send out purple XP gain message, but ONLY if a valid GUID was passed in
		// This message appear to be only for gaining XP from a death
		data.Initialize(SMSG_LOG_XPGAIN);
		data << guid;
		data << uint32(xp) << uint8(0);
		data << uint16(xp) << uint8(0);
		data << uint8(0);
		GetSession()->SendPacket(&data);
	}

	uint32 curXP = GetUInt32Value(PLAYER_XP);
	uint32 nextLvlXP = GetUInt32Value(PLAYER_NEXT_LEVEL_XP);
	uint32 newXP = curXP + xp;

	// Check for level-up
	if (newXP >= nextLvlXP)
	{
		uint32 healthGain = 0, newHealth = 0, manaGain = 0, newMana=0;
		// Level-Up!
		newXP = newXP - nextLvlXP;							// reset XP to 0, but add extra from this xp add
		nextLvlXP += nextLvlXP/2;							// set the new next level xp

															// increment the level
		uint16 level = (uint16)GetUInt32Value(UNIT_FIELD_LEVEL) + 1;

		healthGain = GetUInt32Value(UNIT_FIELD_STAT2) / 2;
		newHealth = GetUInt32Value(UNIT_FIELD_MAXHEALTH) + healthGain;

		if (GetUInt32Value(UNIT_FIELD_POWER1) > 0)
		{
			manaGain = GetUInt32Value(UNIT_FIELD_STAT4) / 2;
			newMana = GetUInt32Value(UNIT_FIELD_MAXPOWER1) + manaGain;
		}

		// TODO: UNEQUIP everything and remove affects

		Field.SetU32 (PLAYER_NEXT_LEVEL_XP, nextLvlXP);
		Field.SetU32 (UNIT_FIELD_LEVEL, level);
		Field.SetU32 (UNIT_FIELD_MAXHEALTH, newHealth);
		Field.SetU32 (UNIT_FIELD_HEALTH, newHealth);
		Field.SetU32 (UNIT_FIELD_POWER1, newMana);
		Field.SetU32 (UNIT_FIELD_MAXPOWER1, newMana);

		// TODO: REEQUIP everything and add effects

		data.Initialize(SMSG_LEVELUP_INFO);

		data << uint32(level);
		data << uint32(healthGain);							// health gain
		data << uint32(manaGain);							// mana gain
		data << uint32(0);
		data << uint32(0);
		data << uint32(0);

		// 6 new fields
		data << uint32(0);
		data << uint32(0);
		data << uint32(0);
		data << uint32(0);
		data << uint32(0);
		data << uint32(0);

		WPAssert(data.size() == 48);
		GetSession()->SendPacket(&data);
	}

	// Set the update bit
	Field.SetU32 (PLAYER_XP, newXP);
}

void Player::smsg_InitialSpells()
{
	WorldPacket data;
	uint16 spellCount = m_spells.size();

	data.Initialize(SMSG_INITIAL_SPELLS);
	data << uint8(0);
	data << uint16(spellCount);								// spell count

	std::list<struct spells>::iterator itr;
	for (itr = m_spells.begin(); itr != m_spells.end(); ++itr)
	{
		data << uint16(itr->spellId);						// spell id
		data << uint16(itr->slotId);						// slot
	}
	data << uint16(0);

	WPAssert(data.size() == 5+(4*spellCount));

	GetSession()->SendPacket(&data);

	Log::getSingleton().outDetail("CHARACTER: Sent Initial Spells");
}

void Player::RemoveMail(uint32 id)
{
	std::list<Mail*>::iterator itr;
	for (itr = m_mail.begin(); itr != m_mail.end();)
	{
		if ((*itr)->messageID == id)
		{
			m_mail.erase(itr++);
		}
		else
		{
			++itr;
		}
	}
}

void Player::AddMail(Mail *m)
{
	std::list<Mail*>::iterator itr;
	for (itr = m_mail.begin(); itr != m_mail.end();)
	{
		if ((*itr)->messageID == m->messageID)
		{
			m_mail.erase(itr++);
		}
		else
		{
			++itr;
		}
	}
	m_mail.push_back(m);
}

void Player::addSpell(uint16 spell_id, uint16 slot_id)
{
	struct spells newspell;
	newspell.spellId = spell_id;

	if (slot_id == 0xffff)
	{
		uint16 maxid = 0;
		std::list<struct spells>::iterator itr;
		for (itr = m_spells.begin(); itr != m_spells.end(); ++itr)
		{
			if (itr->slotId > maxid) maxid = itr->slotId;
		}

		slot_id = maxid + 1;
	}

	newspell.slotId = slot_id;
	m_spells.push_back(newspell);
}

Mail* Player::GetMail(uint32 id)
{
	std::list<Mail*>::iterator itr;
	for (itr = m_mail.begin(); itr != m_mail.end(); itr++)
	{
		if ((*itr)->messageID == id)
		{
			return (*itr);
		}
	}
	return NULL;
}

//===================================================================================================================
//  Set Create Player Bits -- Sets bits required for creating a player in the updateMask.
//  Note:  Doesn't set Quest or Inventory bits
//  updateMask - the updatemask to hold the set bits
//===================================================================================================================
void Player::_SetCreateBits(UpdateMask *updateMask, Player *target) const
{
	if(target == this)
	{
		Object::_SetCreateBits(updateMask, target);
	}
	else
	{
		UpdateMask mask;
		mask.SetCount(m_valuesCount);
		_SetVisibleBits(&mask, target);

		for(uint16 index = 0; index < m_valuesCount; index++)
		{
			if(GetUInt32Value(index) != 0 && mask.GetBit(index))
				updateMask->SetBit(index);
		}
	}
}

void Player::_SetUpdateBits(UpdateMask *updateMask, Player *target) const
{
	if(target == this)
	{
		Object::_SetUpdateBits(updateMask, target);
	}
	else
	{
		UpdateMask mask;
		mask.SetCount(m_valuesCount);
		_SetVisibleBits(&mask, target);

		Object::_SetUpdateBits(updateMask, target);
		*updateMask &= mask;
	}
}

void Player::_SetVisibleBits(UpdateMask *updateMask, Player *target) const
{
	updateMask->SetBit(OBJECT_FIELD_GUID);
	updateMask->SetBit(OBJECT_FIELD_TYPE);
	updateMask->SetBit(OBJECT_FIELD_SCALE_X);

	updateMask->SetBit(UNIT_FIELD_SUMMON);
	updateMask->SetBit(UNIT_FIELD_SUMMON+1);

	updateMask->SetBit(UNIT_FIELD_TARGET);
	updateMask->SetBit(UNIT_FIELD_TARGET+1);

	updateMask->SetBit(UNIT_FIELD_HEALTH);
	updateMask->SetBit(UNIT_FIELD_POWER1);
	updateMask->SetBit(UNIT_FIELD_POWER2);
	updateMask->SetBit(UNIT_FIELD_POWER3);
	updateMask->SetBit(UNIT_FIELD_POWER4);
	updateMask->SetBit(UNIT_FIELD_POWER5);

	updateMask->SetBit(UNIT_FIELD_MAXHEALTH);
	updateMask->SetBit(UNIT_FIELD_MAXPOWER1);
	updateMask->SetBit(UNIT_FIELD_MAXPOWER2);
	updateMask->SetBit(UNIT_FIELD_MAXPOWER3);
	updateMask->SetBit(UNIT_FIELD_MAXPOWER4);
	updateMask->SetBit(UNIT_FIELD_MAXPOWER5);

	updateMask->SetBit(UNIT_FIELD_LEVEL);
	updateMask->SetBit(UNIT_FIELD_FACTIONTEMPLATE);
	updateMask->SetBit(UNIT_FIELD_BYTES_0);
	updateMask->SetBit(UNIT_FIELD_FLAGS);
	for(uint16 i = UNIT_FIELD_AURA; i < UNIT_FIELD_AURASTATE; i ++)
		updateMask->SetBit(i);
	updateMask->SetBit(UNIT_FIELD_BASEATTACKTIME);
	updateMask->SetBit(UNIT_FIELD_BASEATTACKTIME+1);
	updateMask->SetBit(UNIT_FIELD_BOUNDINGRADIUS);
	updateMask->SetBit(UNIT_FIELD_COMBATREACH);
	updateMask->SetBit(UNIT_FIELD_DISPLAYID);
	updateMask->SetBit(UNIT_FIELD_NATIVEDISPLAYID);
	updateMask->SetBit(UNIT_FIELD_MOUNTDISPLAYID);
	updateMask->SetBit(UNIT_FIELD_BYTES_1);
	updateMask->SetBit(UNIT_FIELD_MOUNTDISPLAYID);
	updateMask->SetBit(UNIT_FIELD_PETNUMBER);
	updateMask->SetBit(UNIT_FIELD_PET_NAME_TIMESTAMP);
	updateMask->SetBit(UNIT_DYNAMIC_FLAGS);

	updateMask->SetBit(PLAYER_BYTES);
	updateMask->SetBit(PLAYER_BYTES_2);
	updateMask->SetBit(PLAYER_BYTES_3);
	updateMask->SetBit(PLAYER_GUILD_TIMESTAMP);

	for(uint16 i = 0; i < EQUIPMENT_SLOT_END; i++)
	{
															// lowguid
		updateMask->SetBit((uint16)(PLAYER_FIELD_INV_SLOT_HEAD + i*2));
															// highguid
		updateMask->SetBit((uint16)(PLAYER_FIELD_INV_SLOT_HEAD + (i*2) + 1));
	}
}

void Player::BuildCreateUpdateBlockForPlayer(UpdateData *data, Player *target ) const
{
	for(int i = 0; i < EQUIPMENT_SLOT_END; i++)
	{
		if(m_items[i] == NULL)
			continue;

		m_items[i]->BuildCreateUpdateBlockForPlayer(data, target);
	}

	if(target == this)
	{
		for(int i = EQUIPMENT_SLOT_END; i < INVENTORY_SLOT_ITEM_END; i++)
		{
			if(m_items[i] == NULL)
				continue;

			m_items[i]->BuildCreateUpdateBlockForPlayer(data, target);
		}
	}

	Unit::BuildCreateUpdateBlockForPlayer(data, target);
}

void Player::DestroyForPlayer(Player *target ) const
{
	Unit::DestroyForPlayer(target);

	for(int i = 0; i < EQUIPMENT_SLOT_END; i++)
	{
		if(m_items[i] == NULL)
			continue;

		m_items[i]->DestroyForPlayer(target);
	}

	if(target == this)
	{
		for(int i = EQUIPMENT_SLOT_END; i < INVENTORY_SLOT_ITEM_END; i++)
		{
			if(m_items[i] == NULL)
				continue;

			m_items[i]->DestroyForPlayer(target);
		}
	}
}
#endif

bool Player::SaveToDB ()
{
	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (!dbex)
		return false;

	if (DismountTimer.Enabled ())
	{
		Field.SetU32 (UNIT_FIELD_MOUNTDISPLAYID , 0);
		Field.SetBits (UNIT_FIELD_FLAGS, UFF_LOCKED_MOVE | UFF_MOUNTED, 0);
	}

	//	bool inworld = IsInWorld();
	//	if (inworld)
	//		RemoveFromWorld();

	ApplyAllItemMods (false);
	ApplyAllAffectMods (false);

	// Encode object fields
	char *fields = Field.EncodeSQL ();
	// Encode taxi mask
	char *taximask = EncodeSQL (TaxiMask, sizeof (TaxiMask));
	// Encode tutorial mask
	char *tutmask = EncodeSQL (TutorMask, sizeof (TutorMask));
	// Action buttons
	char *actions = EncodeSQL (Actions, sizeof (Actions));
	// Account data
	char *data0 = !AccountData [0] ? NULL :
	EncodeSQL (AccountData [0], sizeof (uint32) * 2 + 16 + GET_LE32 (AccountData [0] + 4));
	char *data1 = !AccountData [1] ? NULL :
	EncodeSQL (AccountData [1], sizeof (uint32) * 2 + 16 + GET_LE32 (AccountData [1] + 4));

	char *qlogin = QuoteSQL (Client->Login);

	bool rc = true;
	bool updateok = (dbex->ExecuteF (
		"UPDATE characters SET "
		"positionX=%g,positionY=%g,positionZ=%g,orientation=%g,mapId=%lu,zoneId=%lu,"
		"data='%s',taxiMask='%s',tutorialMask='%s',actions='%s',data0='%s',data1='%s' WHERE guid=%lu",
		PositionX, PositionY, PositionZ, Orientation, MapId, ZoneId, fields, taximask,
		tutmask, actions, NN_STR (data0), NN_STR (data1), GetLowGUID ()) == dbeOk)
		&& dbex->GetAffectedRows ();

	if (!updateok && (dbex->ExecuteF ("INSERT INTO characters "
		"(guid,login,data,name,positionX,positionY,positionZ,orientation,"
		"mapId,zoneId,taxiMask,tutorialMask,actions,data0,data1) VALUES "
		"(%lu,'%s','%s','%s',%g,%g,%g,%g,%lu,%lu,'%s','%s','%s','%s','%s')",
		GetLowGUID (), qlogin, fields, Name, PositionX, PositionY, PositionZ, Orientation,
		MapId, ZoneId, taximask, tutmask, actions, NN_STR (data0), NN_STR (data1)) != dbeOk))
	{
		LOG.Out (LOG_IMPORTANT, "Table `characters`: failed to store character %lu!\n",
			GetLowGUID ());
		rc = false;
	}

	delete [] data1;
	delete [] data0;

	if (qlogin != Client->Login)
		delete [] qlogin;
	delete [] actions;
	delete [] tutmask;
	delete [] taximask;
	delete [] fields;

	if (rc) rc = SaveInventory (dbex);
	if (rc) rc = SaveSpells (dbex);
	if (rc) rc = SaveQuestStatus (dbex);
	if (rc) rc = SaveMail (dbex);
	if (rc) rc = SaveAffects (dbex);

	World->db->PutExecutor (dbex);

	ApplyAllAffectMods (true);
	ApplyAllItemMods (true);

	//	if (inworld)
	//		AddToWorld ();

	return rc;
}

bool Player::LoadFromDB (uint32 iLowGuid)
{
	// The philosophy: try to load as much as possible despite errors
	// (but return error code anyway). This is required on char deletion.

	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (!dbex)
		return false;

	if ((dbex->ExecuteF ("SELECT name,data,positionX,positionY,positionZ,orientation,mapId,zoneId,"
		"taxiMask,tutorialMask,actions,data0,data1 FROM characters WHERE guid=%lu",
		iLowGuid) != dbeOk) || !dbex->NextRow ())
		return false;

	Field.SetU64 (OBJECT_FIELD_GUID, MAKEGUID (HIGHGUID_PLAYER, iLowGuid));

	Name = strnew (dbex->Get (0));

	bool rc = true;

	if (!Field.DecodeSQL (dbex->Get (1)))
		rc = false;

	PositionX = dbex->GetFloat (2);
	PositionY = dbex->GetFloat (3);
	PositionZ = dbex->GetFloat (4);
	Orientation = dbex->GetFloat (5);
	MapId = dbex->GetU32 (6);
	ZoneId = dbex->GetU32 (7);

	if (DecodeSQL (dbex->Get (8), &TaxiMask, sizeof (TaxiMask)) < sizeof (TaxiMask) ||
		DecodeSQL (dbex->Get (9), &TutorMask, sizeof (TutorMask)) < sizeof (TutorMask) ||
		DecodeSQL (dbex->Get (10), &Actions, sizeof (Actions)) < sizeof (Actions))
		rc = false;

	for (uint i = 0; i < 2; i++)
	{
		AccountData [i] = NULL;
		if (dbex->Get (11 + i))
		{
			uint sz = DecodeSQL (dbex->Get (11 + i), NULL, 0);
			if (sz)
			{
				AccountData [i] = new uint8 [sz];
				DecodeSQL (dbex->Get (11 + i), AccountData [i], sz);
			}
		}
	}

	if (Field.GetU32 (PLAYER_FLAGS) & PF_DEATHWORLD)
		DeathState = DEAD;

	// Try to load as much as possible
	if (!LoadInventory (dbex))   rc = false;
	if (!LoadSpells (dbex))      rc = false;
	if (!LoadQuestStatus (dbex)) rc = false;
	if (!LoadMail (dbex))        rc = false;
	if (!LoadAffects (dbex))     rc = false;

	World->db->PutExecutor (dbex);

	if (rc)
	{
		ApplyAllAffectMods (true);
		ApplyAllItemMods (true);
	}

	return rc;
}

bool Player::DeleteFromDB ()
{
	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (!dbex)
		return false;

	// We can't use one big IF because we must try hard to delete any traces
	// of this player, and if we'll have one big IF it will stop at first
	// SQL query that failed.
	bool rc = (dbex->ExecuteF ("DELETE FROM characters WHERE guid=%lu",
		GetLowGUID ()) == dbeOk);
	if (dbex->ExecuteF ("DELETE FROM inventory WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		rc = false;
	if (dbex->ExecuteF ("DELETE FROM quest_status WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		rc = false;
	if (dbex->ExecuteF ("DELETE FROM char_spells WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		rc = false;

	for (uint i = 0; i < ARRAY_LEN (Items); i++)
		if (Items [i] && !Items [i]->DeleteFromDB ())
			rc = false;

	World->db->PutExecutor (dbex);

	return rc;
}

bool Player::SaveQuestStatus (DatabaseExecutor *dbex)
{
	// We can't use the UPDATE/INSERT scheme here since some items
	// possibly disappeared from the Quests array and we won't delete
	// them if we would use this approach.

	if (dbex->ExecuteF ("DELETE FROM quest_status WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	for (int i = 0; i < Quests.Length (); i++)
	{
		QuestStatus *qs = Quests.Get (i);

		if (dbex->ExecuteF (
			"INSERT INTO quest_status (charGuid,questId,status,"
			"MobCount1,MobCount2,MobCount3,MobCount4,"
			"ItemCount1,ItemCount2,ItemCount3,ItemCount4) VALUES "
			"(%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu)",
			GetLowGUID (), qs->QuestId, qs->Status,
			qs->MobCount [0], qs->MobCount [1], qs->MobCount [2], qs->MobCount [3],
			qs->ItemCount [0], qs->ItemCount [1], qs->ItemCount [2], qs->ItemCount [3]) != dbeOk)
		{
			LOG.Out (LOG_IMPORTANT, "Table `quest_status`: failed to store quest %lu for player %lu!\n",
				qs->QuestId, GetLowGUID ());
			return false;
		}
	}
	return true;
}

bool Player::LoadQuestStatus (DatabaseExecutor *dbex)
{
	if (dbex->ExecuteF ("SELECT questId,status,MobCount1,MobCount2,MobCount3,MobCount4,"
		"ItemCount1,ItemCount2,ItemCount3,ItemCount4 FROM quest_status WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	Quests.DeleteAll ();
	while (dbex->NextRow ())
	{
		QuestStatus *qs = new QuestStatus ();
		qs->QuestId = dbex->GetU32 (0);
		qs->Status = dbex->GetU32 (1);
		qs->MobCount [0] = dbex->GetU32 (2);
		qs->MobCount [1] = dbex->GetU32 (3);
		qs->MobCount [2] = dbex->GetU32 (4);
		qs->MobCount [3] = dbex->GetU32 (5);
		qs->ItemCount [0] = dbex->GetU32 (6);
		qs->ItemCount [1] = dbex->GetU32 (7);
		qs->ItemCount [2] = dbex->GetU32 (8);
		qs->ItemCount [3] = dbex->GetU32 (9);
		//		if (LoadExistingQuest (qs))
		Quests.Push (qs);
		//		else
		//			delete qs;
	}
	return true;
}

bool Player::SaveInventory (DatabaseExecutor *dbex)
{
	if (dbex->ExecuteF ("DELETE FROM inventory WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	for (uint i = 0; i < ARRAY_LEN (Items); i++)
	{
		if (!Items [i])
			continue;
		Items [i]->SaveToDB ();

		if (dbex->ExecuteF (
			"INSERT INTO inventory (charGuid,slot,itemGuid) VALUES (%lu,%lu,%lu)",
			GetLowGUID (), i, Items [i]->GetLowGUID ()) != dbeOk)
		{
			LOG.Out (LOG_IMPORTANT, "Table `inventory`: failed to store inventory item %lu for player %lu!\n",
				Items [i]->GetLowGUID (), GetLowGUID ());
			return false;
		}
	}
	return true;
}

bool Player::LoadInventory (DatabaseExecutor *dbex)
{
	if (dbex->ExecuteF ("SELECT itemGuid,slot FROM inventory WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	// Clean current inventory
	for (uint i = 0; i < ARRAY_LEN (Items); i++)
		if (Items [i])
	{
		Items [i]->DecRef ();
		Items [i] = 0;
		Field.SetU64 (PLAYER_FIELD_INV_SLOT_HEAD + i * 2, 0);
	}

	while (dbex->NextRow ())
	{
		Item *item = new Item;
		if (item->LoadFromDB (dbex->GetU32 (0)))
			AddItemToSlot (dbex->GetU32 (1), item);
		item->DecRef ();
	}

	return true;
}

bool Player::SaveSpells (DatabaseExecutor *dbex)
{
	if (dbex->ExecuteF ("DELETE FROM char_spells WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	for (int i = 0; i < Spells.Length (); i++)
	{
		Spell *s = Spells.Get (i);
		if (dbex->ExecuteF ("INSERT INTO char_spells (charGuid,spellId,slotId) VALUES (%lu,%lu,%lu)",
			GetLowGUID (), s->SpellId, s->SlotId) != dbeOk)
		{
			LOG.Out (LOG_IMPORTANT, "Table `char_spells`: failed to store spell %lu for player %lu!\n",
				s->SpellId, GetLowGUID ());
			return false;
		}
	}
	return true;
}

bool Player::LoadSpells (DatabaseExecutor *dbex)
{
	if (dbex->ExecuteF ("SELECT spellId,slot FROM char_spells WHERE charGuid=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	// Clear spell list
	Spells.DeleteAll ();

	while (dbex->NextRow ())
		AddSpell (dbex->GetU32 (0), dbex->GetU32 (1));

	return true;
}

bool Player::SaveMail (DatabaseExecutor *dbex)
{
	if (dbex->ExecuteF ("DELETE FROM mail WHERE recipient=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	for (int i = 0; i < MailBox.Length (); i++)
	{
		Mail *m = MailBox.Get (i);
		char *qsubj = QuoteSQL (m->Subject);
		char *qbody = QuoteSQL (m->Body);

		if (dbex->ExecuteF ("INSERT INTO mail (mailId,sender,recipient,subject,body,item,time,money,COD,checked) "
			"VALUES (%lu,%lu,%lu,'%s','%s',%lu,%lu,%lu,%lu,%lu)",
			m->MessageId, m->SenderId, m->RecipientId, qsubj, qbody,
			m->ItemId, m->Time, m->Money, m->COD, m->Checked) != dbeOk)
			return false;;

		if (qsubj != m->Subject)
			delete [] qsubj;
		if (qbody != m->Body)
			delete [] qbody;
	}
	return true;
}

bool Player::LoadMail (DatabaseExecutor *dbex)
{
	if (dbex->ExecuteF ("SELECT mailId,sender,recipient,subject,body,item,time,"
		"money,COD,checked FROM mail WHERE recipient=%lu",
		GetLowGUID ()) != dbeOk)
		return false;

	// Clear message list -- just in case
	MailBox.DeleteAll ();

	while (dbex->NextRow ())
	{
		Mail *m = new Mail;
		m->MessageId = dbex->GetU32 (0);
		m->SenderId = dbex->GetU32 (1);
		m->RecipientId = dbex->GetU32 (2);
		m->Subject = strnew (dbex->Get (3));
		m->Body = strnew (dbex->Get (4));
		m->ItemId = dbex->GetU32 (5);
		m->Time = dbex->GetU32 (6);
		m->Money = dbex->GetU32 (7);
		m->COD = dbex->GetU32 (8);
		m->Checked = dbex->GetU32 (9);
		MailBox.Push (m);
	}

	return true;
}

bool Player::SaveAffects (DatabaseExecutor *dbex)
{
	return true;
}

bool Player::LoadAffects (DatabaseExecutor *dbex)
{
	return true;
}

//-------------------------// Item slot management //------------------------//

/**
 * This array defines which kinds of items in which equipment slots
 * can be equiped.
 */
static struct
{
	uint8 Slot;
	uint8 InvType;
} ItemSlotTypes [] =
{
	{ EQUIPMENT_SLOT_BACK, INVTYPE_CLOAK },
	{ EQUIPMENT_SLOT_BODY, INVTYPE_BODY },
	{ EQUIPMENT_SLOT_CHEST, INVTYPE_CHEST },
	{ EQUIPMENT_SLOT_CHEST, INVTYPE_ROBE },
	{ EQUIPMENT_SLOT_FEET, INVTYPE_FEET },
	{ EQUIPMENT_SLOT_FINGER1, INVTYPE_FINGER },
	{ EQUIPMENT_SLOT_FINGER2, INVTYPE_FINGER },
	{ EQUIPMENT_SLOT_HANDS, INVTYPE_HANDS },
	{ EQUIPMENT_SLOT_HEAD, INVTYPE_HEAD },
	{ EQUIPMENT_SLOT_LEGS, INVTYPE_LEGS },
	{ EQUIPMENT_SLOT_MAINHAND, INVTYPE_2HWEAPON },
	{ EQUIPMENT_SLOT_MAINHAND, INVTYPE_HOLDABLE },
	{ EQUIPMENT_SLOT_MAINHAND, INVTYPE_WEAPON },
	{ EQUIPMENT_SLOT_MAINHAND, INVTYPE_WEAPONMAINHAND },
	{ EQUIPMENT_SLOT_NECK, INVTYPE_NECK },
	{ EQUIPMENT_SLOT_OFFHAND, INVTYPE_SHIELD },
	{ EQUIPMENT_SLOT_OFFHAND, INVTYPE_WEAPONOFFHAND },
	{ EQUIPMENT_SLOT_RANGED, INVTYPE_RANGED },
	{ EQUIPMENT_SLOT_SHOULDERS, INVTYPE_SHOULDERS },
	{ EQUIPMENT_SLOT_TABARD, INVTYPE_TABARD },
	{ EQUIPMENT_SLOT_TRINKET1, INVTYPE_TRINKET },
	{ EQUIPMENT_SLOT_TRINKET2, INVTYPE_TRINKET },
	{ EQUIPMENT_SLOT_WAIST, INVTYPE_WAIST },
	{ EQUIPMENT_SLOT_WRISTS, INVTYPE_WRISTS },
	{ INVENTORY_SLOT_BAG_1, INVTYPE_BAG },
	{ INVENTORY_SLOT_BAG_2, INVTYPE_BAG },
	{ INVENTORY_SLOT_BAG_3, INVTYPE_BAG },
	{ INVENTORY_SLOT_BAG_4, INVTYPE_BAG },
};

int Player::FindFreeItemSlot (uint32 iInvType)
{
	// Special case for ammo (not sure its correct)
	if ((iInvType == INVTYPE_AMMO) ||
		(iInvType == INVTYPE_THROWN) ||
		(iInvType == INVTYPE_RANGEDRIGHT))
		return -2;

	for (uint i = 0; i < ARRAY_LEN (ItemSlotTypes); i++)
		if ((ItemSlotTypes [i].InvType == iInvType) &&
		!GetItem (ItemSlotTypes [i].Slot))
	{
		// Special case for 2H weapon
		if ((iInvType == INVTYPE_2HWEAPON) &&
			GetItem (EQUIPMENT_SLOT_OFFHAND))
			return -1;

		return ItemSlotTypes [i].Slot;
	}

	return -1;
}

bool Player::CanEquipItemInSlot (uint8 iSlot, uint32 iInvType)
{
	for (uint i = 0; i < ARRAY_LEN (ItemSlotTypes); i++)
		if ((ItemSlotTypes [i].InvType == iInvType) &&
		(ItemSlotTypes [i].Slot == iSlot))
	{
		// Special case for 2H weapon
		if ((iInvType == INVTYPE_2HWEAPON) &&
			GetItem (EQUIPMENT_SLOT_OFFHAND))
			return false;

		return true;
	}

	return false;
}

void Player::SwapItemSlots (uint8 iSrcSlot, uint8 iDstSlot)
{
	if ((iSrcSlot >= INVENTORY_SLOT_ITEM_END) ||
		(iDstSlot >= INVENTORY_SLOT_ITEM_END))
		return;

	if (iSrcSlot < EQUIPMENT_SLOT_END && iDstSlot >= EQUIPMENT_SLOT_END)
	{
		ApplyItemMods (Items [iSrcSlot], false);

		NetworkPacket *outpkt = Items [iSrcSlot]->BuildDestroyPacket ();
		SendToSet (outpkt, false);
	}

	Item *temp;
	temp = Items [iSrcSlot];
	Items [iSrcSlot] = Items [iDstSlot];
	Items [iDstSlot] = temp;

	if (iSrcSlot >= EQUIPMENT_SLOT_END && iDstSlot < EQUIPMENT_SLOT_END)
	{
		ApplyItemMods (Items [iDstSlot], true);

		NetworkPacket *outpkt = Items [iSrcSlot]->BuildCreatePacket ();
		SendToSet (outpkt, false);
	}

	Field.SetU64 (PLAYER_FIELD_INV_SLOT_HEAD + (iSrcSlot * 2),
		Items [iSrcSlot] ? Items [iSrcSlot]->GetGUID () : 0);
	Field.SetU64 (PLAYER_FIELD_INV_SLOT_HEAD + (iDstSlot * 2),
		Items [iDstSlot] ? Items [iDstSlot]->GetGUID () : 0);
}

int Player::GetSlotByItemID (uint32 iItemId)
{
	for (uint i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; i++)
		if (Items [i] && Items [i]->GetProto ()->ItemId == iItemId)
			return i;

	return 0;
}

int Player::GetSlotByItemGUID (uint64 guid)
{
	for (uint i = 0; i < INVENTORY_SLOT_ITEM_END; i++)
		if (Items [i] && Items [i]->GetGUID () == guid)
			return i;

	return -1;
}

void Player::AddItemToSlot (uint8 iSlot, Item *iItem)
{
	if ((iSlot >= INVENTORY_SLOT_ITEM_END) || Items [iSlot] || !iItem)
		return;

	if (IsInWorld)
	{
		NetworkPacket *outpkt = iItem->BuildCreatePacket ();
		if (iSlot < EQUIPMENT_SLOT_END)
			SendToSet (outpkt, true);
		else
			Client->Send (outpkt);
	}

	(Items [iSlot] = iItem)->IncRef ();
	Field.SetU64 (PLAYER_FIELD_INV_SLOT_HEAD + iSlot * 2, iItem->GetGUID ());

	iItem->Owner = this;
	//iItem->PlaceOnMap ();

	if (iSlot < EQUIPMENT_SLOT_END)
	{
		int VisibleBase = PLAYER_VISIBLE_ITEM_1_0 + (iSlot * 9);
		Field.SetU32 (VisibleBase + 0, iItem->Field.GetU32 (OBJECT_FIELD_ENTRY));
		Field.SetU32 (VisibleBase + 1, iItem->Field.GetU32 (ITEM_FIELD_ENCHANTMENT));
		Field.SetU32 (VisibleBase + 2, iItem->Field.GetU32 (ITEM_FIELD_ENCHANTMENT + 3));
		Field.SetU32 (VisibleBase + 3, iItem->Field.GetU32 (ITEM_FIELD_ENCHANTMENT + 6));
		Field.SetU32 (VisibleBase + 4, iItem->Field.GetU32 (ITEM_FIELD_ENCHANTMENT + 9));
		Field.SetU32 (VisibleBase + 5, iItem->Field.GetU32 (ITEM_FIELD_ENCHANTMENT + 12));
		Field.SetU32 (VisibleBase + 6, iItem->Field.GetU32 (ITEM_FIELD_ENCHANTMENT + 15));
		Field.SetU32 (VisibleBase + 7, iItem->Field.GetU32 (ITEM_FIELD_ENCHANTMENT + 18));
		Field.SetU32 (VisibleBase + 8, iItem->Field.GetU32 (ITEM_FIELD_RANDOM_PROPERTIES_ID));
		ApplyItemMods (iItem, true);
	}
}

Item *Player::RemoveItemFromSlot (uint8 iSlot)
{
	if (iSlot >= INVENTORY_SLOT_ITEM_END)
		return NULL;

	Item *item = Items [iSlot];
	Items [iSlot] = NULL;
	Field.SetU64 (PLAYER_FIELD_INV_SLOT_HEAD + iSlot * 2, 0);

	if (iSlot < EQUIPMENT_SLOT_END)
		ApplyItemMods (item, false);

	item->Owner = NULL;

	if (IsInWorld)
	{
		//item->RemoveFromMap ();

		NetworkPacket *outpkt = item->BuildDestroyPacket ();
		if (iSlot < EQUIPMENT_SLOT_END)
			SendToSet (outpkt, true);
		else
			Client->Send (outpkt);
	}

	return item;
}

#if 0

bool Player::HasSpell(uint32 spell)
{
	std::list<struct spells>::iterator itr;
	for (itr = m_spells.begin(); itr != m_spells.end(); ++itr)
	{
		if (itr->spellId == spell)
		{
			return true;
		}
	}
	return false;

}

void Player::AddToWorld()
{
	Object::AddToWorld();

	for(int i = 0; i < INVENTORY_SLOT_ITEM_END; i++)
	{
		if(m_items[i])
			m_items[i]->AddToWorld();
	}
}

void Player::RemoveFromWorld()
{
	for(int i = 0; i < INVENTORY_SLOT_ITEM_END; i++)
	{
		if(m_items[i])
			m_items[i]->RemoveFromWorld();
	}

	Object::RemoveFromWorld();
}

void Player::SetMovement(uint8 pType)
{
	WorldPacket data;

	switch(pType)
	{
		case MOVE_ROOT:
		{
			data.Initialize(SMSG_FORCE_MOVE_ROOT);
			data << GetGUID();
			GetSession()->SendPacket(&data);
		}break;
		case MOVE_UNROOT:
		{
			data.Initialize(SMSG_FORCE_MOVE_UNROOT);
			data << GetGUID();
			GetSession()->SendPacket(&data);
		}break;
		case MOVE_WATER_WALK:
		{
			data.Initialize(SMSG_MOVE_WATER_WALK);
			data << GetGUID();
			GetSession()->SendPacket(&data);
		}break;
		case MOVE_LAND_WALK:
		{
			data.Initialize(SMSG_MOVE_LAND_WALK);
			data << GetU32Value(OBJECT_FIELD_GUID);
			GetSession()->SendPacket(&data);
		}break;
		default:break;
	}
}

void Player::SetPlayerSpeed(uint8 SpeedType, float value, bool forced)
{
	WorldPacket data;

	switch(SpeedType)
	{
		case RUN:
		{
			if(forced) { data.Initialize(SMSG_FORCE_RUN_SPEED_CHANGE); }
			else { data.Initialize(MSG_MOVE_SET_RUN_SPEED); }
			data << GetGUID();
			data << float(value);
			GetSession()->SendPacket(&data);
		}break;
		case RUNBACK:
		{
			if(forced) { data.Initialize(SMSG_FORCE_RUN_BACK_SPEED_CHANGE); }
			else { data.Initialize(MSG_MOVE_SET_RUN_BACK_SPEED); }
			data << GetGUID();
			data << float(value);
			GetSession()->SendPacket(&data);
		}break;
		case SWIM:
		{
			if(forced) { data.Initialize(SMSG_FORCE_SWIM_SPEED_CHANGE); }
			else { data.Initialize(MSG_MOVE_SET_SWIM_SPEED); }
			data << GetGUID();
			data << float(value);
			GetSession()->SendPacket(&data);
		}break;
		case SWIMBACK:
		{
			data.Initialize(MSG_MOVE_SET_SWIM_BACK_SPEED);
			data << GetGUID();
			data << float(value);
			GetSession()->SendPacket(&data);
		}break;
		default:break;
	}
}

void Player::BuildPlayerRepop()
{
	WorldPacket data;
	//1.1.1
	Field.SetU32 (UNIT_FIELD_HEALTH, 1);

	SetMovement(MOVE_UNROOT);
	SetMovement(MOVE_WATER_WALK);

	SetPlayerSpeed(RUN, (float)8.5, true);
	SetPlayerSpeed(SWIM, (float)5.9, true);

	data.Initialize(SMSG_CORPSE_RECLAIM_DELAY);
	data << uint8(0x30) << uint8(0x75) << uint8(0x00) << uint8(0x00);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_SPELL_START);
	data << GetGUID() << GetGUID() << uint32(8326);
	data << uint16(0) << uint32(0) << uint16(0x02) << uint32(0) << uint32(0);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_UPDATE_AURA_DURATION);
	data << uint8(32);
	data << uint32(0);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_CAST_RESULT);
	data << uint32(8326);
	data << uint8(0x00);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_SPELL_GO);
	data << GetGUID() << GetGUID() << uint32(8326);
	data << uint16(01) << uint8(0) << uint8(0);
	data << uint16(0040);
	data << GetPositionX();
	data << GetPositionY();
	data << GetPositionZ();
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_SPELLLOGEXECUTE);
	data << (uint32)GetGUID() << (uint32)GetGUID();
	data << uint32(8326);
	data << uint32(1);
	data << uint32(0x24);
	data << uint32(1);
	data << GetGUID();
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_STOP_MIRROR_TIMER);
	data << uint8(0x00) << uint8(0x00) << uint8(0x00) << uint8(0x00);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_STOP_MIRROR_TIMER);
	data << uint8(0x01) << uint8(0x00) << uint8(0x00) << uint8(0x00);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_STOP_MIRROR_TIMER);
	data << uint8(0x02) << uint8(0x00) << uint8(0x00) << uint8(0x00);
	GetSession()->SendPacket(&data);

	Field.SetU32 (CONTAINER_FIELD_SLOT_1+29, 8326);
	Field.SetU32 (UNIT_FIELD_AURA+32, 8326);
	Field.SetU32 (UNIT_FIELD_AURALEVELS+8, 0xeeeeee00);
	Field.SetU32 (UNIT_FIELD_AURAAPPLICATIONS+8, 0xeeeeee00);
	Field.SetU32 (UNIT_FIELD_AURAFLAGS+4, 12);
	Field.SetU32 (UNIT_FIELD_AURASTATE, 2);

	SetFlag(PLAYER_FLAGS, 0x10);

	//spawn Corpse
	SpawnCorpseBody();
}

void Player::ResurrectPlayer()
{
	RemoveFlag(PLAYER_FLAGS, 0x10);
	setDeathState(ALIVE);
}

void Player::KillPlayer()
{
	WorldPacket data;

	SetMovement(MOVE_ROOT);

	data.Initialize(SMSG_STOP_MIRROR_TIMER);
	data << uint8(0x00) << uint8(0x00) << uint8(0x00) << uint8(0x00);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_STOP_MIRROR_TIMER);
	data << uint8(0x01) << uint8(0x00) << uint8(0x00) << uint8(0x00);
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_STOP_MIRROR_TIMER);
	data << uint8(0x02) << uint8(0x00) << uint8(0x00) << uint8(0x00);
	GetSession()->SendPacket(&data);

	setDeathState(CORPSE);
	SetFlag(UNIT_FIELD_FLAGS, 0x08);						//player death animation, also can be used with DYNAMIC_FLAGS
	SetFlag(UNIT_DYNAMIC_FLAGS, 0x00);
	CreateCorpse();
}

void Player::CreateCorpse()
{
	Corpse *pCorpse;
	uint32 _uf, _pb, _pb2, _cfb1, _cfb2;

	pCorpse = objmgr.GetCorpseByOwner(this);
	if(!pCorpse)
	{
		pCorpse = new Corpse();
		pCorpse->Create(objmgr.GenerateLowGuid(HIGHGUID_CORPSE), this, GetMapId(), GetPositionX(),
			GetPositionY(), GetPositionZ(), GetOrientation());

		_uf = GetU32Value(UNIT_FIELD_BYTES_0);
		_pb = GetU32Value(PLAYER_BYTES);
		_pb2 = GetU32Value(PLAYER_BYTES_2);

		uint8 race       = (uint8)(_uf);
		uint8 skin       = (uint8)(_pb);
		uint8 face       = (uint8)(_pb >> 8);
		uint8 hairstyle  = (uint8)(_pb >> 16);
		uint8 haircolor  = (uint8)(_pb >> 24);
		uint8 facialhair = (uint8)(_pb2);

		_cfb1 = ((0x00) | (race << 8) | (0x00 << 16) | (skin << 24));
		_cfb2 = ((face) | (hairstyle << 8) | (haircolor << 16) | (facialhair << 24));

		pCorpse->SetZoneId(GetZoneId());
		pCorpse->Field.SetU32 (CORPSE_FIELD_BYTES_1, _cfb1);
		pCorpse->Field.SetU32 (CORPSE_FIELD_BYTES_2, _cfb2);
		pCorpse->Field.SetU32 (CORPSE_FIELD_FLAGS, 4);
		pCorpse->Field.SetU32 (CORPSE_FIELD_DISPLAY_ID, GetU32Value(UNIT_FIELD_DISPLAYID));

		uint32 iDisplayID;
		uint16 iIventoryType;
		uint32 _cfi;
		for (int i = 0; i < EQUIPMENT_SLOT_END; i++)
		{
			if(m_items[i])
			{
				iDisplayID = m_items[i]->GetProto()->DisplayInfoID;
				iIventoryType = (uint16)m_items[i]->GetProto()->InventoryType;

				_cfi =  (uint16(iDisplayID)) | (iIventoryType)<< 24;
				pCorpse->Field.SetU32 (CORPSE_FIELD_ITEM + i,_cfi);
			}
		}
		//save corpse in db for future use
		pCorpse->SaveToDB();
		objmgr.AddObject(pCorpse);
	}
	else													//Corpse already exist in world, update it
	{
		pCorpse->SetPosition(GetPositionX(), GetPositionY(), GetPositionZ(), GetOrientation());
	}
}

void Player::SpawnCorpseBody()
{
	Corpse *pCorpse;

	pCorpse = objmgr.GetCorpseByOwner(this);
	if(pCorpse && !pCorpse->IsInWorld())
		pCorpse->PlaceOnMap();
}

void Player::SpawnCorpseBones()
{
	Corpse *pCorpse;
	pCorpse = objmgr.GetCorpseByOwner(this);
	if(pCorpse)
	{
		pCorpse->Field.SetU32 (CORPSE_FIELD_FLAGS, 5);
		pCorpse->SetUInt64Value(CORPSE_FIELD_OWNER, 0);		// remove corpse owner association
		//remove item association
		for (int i = 0; i < EQUIPMENT_SLOT_END; i++)
		{
			if(pCorpse->GetU32Value(CORPSE_FIELD_ITEM + i))
				pCorpse->Field.SetU32 (CORPSE_FIELD_ITEM + i, 0);
		}
		pCorpse->DeleteFromDB();
	}
}

void Player::DeathDurabilityLoss(double percent)
{
	uint32 pDurability, pNewDurability;

	for (int i = 0; i < EQUIPMENT_SLOT_END; i++)
	{
		if(m_items[i])
		{
			pDurability =  m_items[i]->GetU32Value(ITEM_FIELD_DURABILITY);
			if(pDurability)
			{
				pNewDurability = (uint32)(pDurability*percent);
				pNewDurability = (pDurability - pNewDurability);
				if(pNewDurability < 0) { pNewDurability = 0; }

				m_items[i]->Field.SetU32 (ITEM_FIELD_DURABILITY, pNewDurability);
			}
		}
	}
}

void Player::RepopAtGraveyard()
{
	float closestX, closestY, closestZ, closestO;
	float curX, curY, curZ;
	bool first = true;

	ObjectMgr::GraveyardMap::const_iterator itr;
	for (itr = objmgr.GetGraveyardListBegin(); itr != objmgr.GetGraveyardListEnd(); itr++)
	{
		GraveyardTeleport *pGrave = itr->second;
		if(pGrave->MapId == GetMapId())
		{
			curX = pGrave->X;
			curY = pGrave->Y;
			curZ = pGrave->Z;
			if(first || pow(m_positionX-curX,2) + pow(m_positionY-curY,2) <
				pow(m_positionX-closestX,2) + pow(m_positionY-closestY,2) )
			{
				first = false;

				closestX = curX;
				closestY = curY;
				closestZ = curZ;
				closestO = pGrave->O;
			}
		}
	}

	if(closestX && closestY && closestZ)
		SetPosition(closestX,closestY,closestZ,closestO, false);
}

void Player::JoinedChannel(Channel *c)
{
	m_channels.push_back(c);
}

void Player::LeftChannel(Channel *c)
{
	m_channels.remove(c);
}
#endif

void Player::ApplyModifierU32 (uint iFieldIndex, int iDelta, bool iApply)
{
	if (!iFieldIndex)
		return;

	int32 value = Field.GetU32 (iFieldIndex);
	if (iApply)
		value += iDelta;
	else
		value -= iDelta;

	Field.SetU32 (iFieldIndex, value);
}

void Player::ApplyModifierF32 (uint iFieldIndex, float iDelta, bool iApply)
{
	if (!iFieldIndex)
		return;

	float value = Field.GetF32 (iFieldIndex);
	if (iApply)
		value += iDelta;
	else
		value -= iDelta;

	Field.SetF32 (iFieldIndex, value);
}

void Player::ApplyItemMods (Item *iItem, bool iApply)
{
	if (!iItem)
		return;

	ItemPrototype *proto = iItem->GetProto ();
	if (!proto)
		return;

	ApplyModifierU32 (UNIT_FIELD_RESISTANCES + 0, proto->Armor, iApply);
	ApplyModifierU32 (UNIT_FIELD_RESISTANCES + 1, proto->FireRes, iApply);
	ApplyModifierU32 (UNIT_FIELD_RESISTANCES + 2, proto->NatureRes, iApply);
	ApplyModifierU32 (UNIT_FIELD_RESISTANCES + 3, proto->FrostRes, iApply);
	ApplyModifierU32 (UNIT_FIELD_RESISTANCES + 4, proto->ShadowRes, iApply);
	ApplyModifierU32 (UNIT_FIELD_RESISTANCES + 5, proto->ArcaneRes, iApply);

	ApplyModifierF32 (UNIT_FIELD_MINDAMAGE, proto->DamageMin [0], iApply);
	ApplyModifierF32 (UNIT_FIELD_MAXDAMAGE, proto->DamageMax [0], iApply);

	if (proto->Delay)
	{
		int idx = -1;
		if (iItem == Items [EQUIPMENT_SLOT_MAINHAND])
			idx = UNIT_FIELD_BASEATTACKTIME + 0;
		else if (iItem == Items [EQUIPMENT_SLOT_OFFHAND])
			idx = UNIT_FIELD_BASEATTACKTIME + 1;

		if (idx >= 0)
			Field.SetU32 (idx, iApply ? proto->Delay : 2000);
	}
}

void Player::ApplyAllItemMods (bool iApply)
{
	for (uint i = 0; i < ARRAY_LEN (Items); i++)
		if (Items [i])
			ApplyItemMods (Items [i], false);
}

void Player::CleanupChannels ()
{
	//	for (int i = Channels.Length () - 1; i >= 0; i--)
	//		Channels.Get (i)->Leave (this, false);
}

void Player::Update (uint32 iDeltaMs)
{
	Unit::Update (iDeltaMs);
	//@@anything to do here?
}

void Player::Login ()
{
	// Tutorial Flags
	SMSG_TUTORIAL_FLAGS_t *tutpkt = SMSG_TUTORIAL_FLAGS_t::Create ();
	memcpy (tutpkt->TutMask, TutorMask, sizeof (tutpkt->TutMask));
	Client->Send (tutpkt);

	// Initial Spells
	//smsg_InitialSpells ();

	// SMSG_ACTION_BUTTONS
	SMSG_ACTION_BUTTONS_t *butpkt = SMSG_ACTION_BUTTONS_t::Create ();
	memcpy (butpkt->Actions, Actions, sizeof (butpkt->Actions));
	Client->Send (butpkt);

	// SMSG_INITIALIZE_FACTIONS

	// SMSG_EXPLORATION_EXPERIENCE

	// SMSG_CAST_RESULT -- Spell_id = 836 (LOGINEFFECT (24347)) From spells.dbc.csv

	SMSG_LOGIN_SETTIMESPEED_t *timpkt = SMSG_LOGIN_SETTIMESPEED_t::Create ();
	time_t minutes = World->GetGameTime () / 60;
	time_t hours = minutes / 60; minutes %= 60;
	timpkt->Time = minutes + (hours << 6);
	timpkt->Speed = (float)0.017f;							// Normal Game Speed
	Client->Send (timpkt);

	// SMSG_UPDATE_AURA_DURATION -- if the player had an aura on when he logged out

	// Start the introduction movie if this is the first login
	PlayerCreateInfo *pci = FindCreateInfo (GetRace (), GetClass (), NULL);
	if ((GetLevel () == 1) && (PositionX == pci->PositionX) &&
		(PositionY = pci->PositionY) && (PositionZ == pci->PositionZ) &&
		(MapId == pci->MapId) && (ZoneId == pci->ZoneId))
	{
		static uint8 cinematics [] = { 81, 21, 41, 61, 2, 141, 101, 121 };
		SMSG_TRIGGER_CINEMATIC_t *cinpkt = SMSG_TRIGGER_CINEMATIC_t::Create ();
		cinpkt->Video = cinematics [GetRace () - 1];
		Client->Send (cinpkt);
	}
}

//------ dummy ---------

void Player::ReceiveDamage (Unit *iAttacker, uint32 iDamage) {}
void Player::AddSpell (uint iSpellId, uint iSlotId) {}
void Player::GiveXP (uint32 iXP, Unit *iVictim, bool iGroup) {}
void Player::ApplyModifier (Modifier *iMod, bool iApply, Affect *iParent) {}
