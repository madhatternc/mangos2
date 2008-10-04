/**
 *     \file  src/worldserver/Player.h
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

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Opcodes.h"
#include "Timer.h"
#include "Unit.h"
#include "Item.h"

#define EQUIPMENT_SLOT_START         0
#define EQUIPMENT_SLOT_HEAD          0
#define EQUIPMENT_SLOT_NECK          1
#define EQUIPMENT_SLOT_SHOULDERS     2
#define EQUIPMENT_SLOT_BODY          3
#define EQUIPMENT_SLOT_CHEST         4
#define EQUIPMENT_SLOT_WAIST         5
#define EQUIPMENT_SLOT_LEGS          6
#define EQUIPMENT_SLOT_FEET          7
#define EQUIPMENT_SLOT_WRISTS        8
#define EQUIPMENT_SLOT_HANDS         9
#define EQUIPMENT_SLOT_FINGER1       10
#define EQUIPMENT_SLOT_FINGER2       11
#define EQUIPMENT_SLOT_TRINKET1      12
#define EQUIPMENT_SLOT_TRINKET2      13
#define EQUIPMENT_SLOT_BACK          14
#define EQUIPMENT_SLOT_MAINHAND      15
#define EQUIPMENT_SLOT_OFFHAND       16
#define EQUIPMENT_SLOT_RANGED        17
#define EQUIPMENT_SLOT_TABARD        18
#define EQUIPMENT_SLOT_END           19

#define INVENTORY_SLOT_BAG_START     19
#define INVENTORY_SLOT_BAG_1         19
#define INVENTORY_SLOT_BAG_2         20
#define INVENTORY_SLOT_BAG_3         21
#define INVENTORY_SLOT_BAG_4         22
#define INVENTORY_SLOT_BAG_END       23

#define INVENTORY_SLOT_ITEM_START    23
#define INVENTORY_SLOT_ITEM_1        23
#define INVENTORY_SLOT_ITEM_2        24
#define INVENTORY_SLOT_ITEM_3        25
#define INVENTORY_SLOT_ITEM_4        26
#define INVENTORY_SLOT_ITEM_5        27
#define INVENTORY_SLOT_ITEM_6        28
#define INVENTORY_SLOT_ITEM_7        29
#define INVENTORY_SLOT_ITEM_8        30
#define INVENTORY_SLOT_ITEM_9        31
#define INVENTORY_SLOT_ITEM_10       32
#define INVENTORY_SLOT_ITEM_11       33
#define INVENTORY_SLOT_ITEM_12       34
#define INVENTORY_SLOT_ITEM_13       35
#define INVENTORY_SLOT_ITEM_14       36
#define INVENTORY_SLOT_ITEM_15       37
#define INVENTORY_SLOT_ITEM_16       38
#define INVENTORY_SLOT_ITEM_END      39

enum
{
	RACE_HUMAN      = 1,
	RACE_ORC        = 2,
	RACE_DWARF      = 3,
	RACE_NIGHTELF   = 4,
	RACE_UNDEAD     = 5,
	RACE_TAUREN     = 6,
	RACE_GNOME      = 7,
	RACE_TROLL      = 8,
	RACE_GOBLIN     = 9,
	RACE_BLOODELF   = 10,
	RACE_DRAENEI    = 11
};

enum
{
	CLASS_WARRIOR   = 1,
	CLASS_PALADIN   = 2,
	CLASS_HUNTER    = 3,
	CLASS_ROGUE     = 4,
	CLASS_PRIEST    = 5,
	CLASS_SHAMAN    = 7,
	CLASS_MAGE      = 8,
	CLASS_WARLOCK   = 9,
	CLASS_DRUID     = 11
};

/// Bitfields for PLAYER_FLAGS
enum
{
	/// Deathworld (players only)
	PF_DEATHWORLD           = 0x00000010,
	/// Player is sleeping
	PF_SLEEPING             = 0x00000020,
	/// Free for all PvP
	PF_FREE_FOR_PVP         = 0x00000080
};

class Item;
class Channel;
struct Spell;
class Mail;
class Database;

struct QuestStatus
{
	uint32 QuestId;
	uint32 Status;
	/// number of items collected
	uint32 ItemCount [4];
	/// number of monsters slain
	uint32 MobCount [4];

	QuestStatus ()
	{
		memset (ItemCount, 0, sizeof (ItemCount));
		memset (MobCount, 0, sizeof (MobCount));
	}
};

struct Spell
{
	uint32 SpellId;
	uint32 SlotId;
};

struct PlayerCreateInfo
{
	uint8 Race;
	uint8 Class;
	uint32 MapId;
	uint32 ZoneId;
	float PositionX;
	float PositionY;
	float PositionZ;
	float Orientation;
	uint16 DisplayId;
	uint8 Strength;
	uint8 Ability;
	uint8 Stamina;
	uint8 Intellect;
	uint8 Spirit;
	uint32 Health;
	uint32 Mana;
	uint32 Rage;
	uint32 Focus;
	uint32 Energy;
	uint32 AttackPower;
	float MinDmg;
	float MaxDmg;
	uint32 Item [10];
	uint8 ItemSlot [10];
	uint16 Spell [10];
};

enum PlayerMovementType
{
	MOVE_ROOT       = 1,
	MOVE_UNROOT     = 2,
	MOVE_WATER_WALK = 3,
	MOVE_LAND_WALK  = 4,
};

enum PlayerSpeedType
{
	RUN      = 1,
	RUNBACK  = 2,
	SWIM     = 3,
	SWIMBACK = 4,
	WALK     = 5,
};

/**
 * This class represents a player character.
 */
class Player : public Unit
{
	friend class WorldServer;
	friend class GameClient;

	/**
	 * Regenerate given field
	 * @arg iValueIndex
	 *   The index of the value to regenerate.
	 * @arg iMaxValueIndex
	 *   The index of the maximum for the value.
	 * @arg iRise
	 *   true if the value should rise by time, false if should decrease
	 */
	void Regenerate (uint iValueIndex, uint iMaxValueIndex, bool iRise);

	/**
	 * Sets bits required for creating a player in the updateMask.
	 * Note:  Doesn't set Quest or Inventory bits
	 * updateMask - the updatemask to hold the set bits
	 */
	void SetCreateBits (BitVector &Bits, Player *iTarget) const;
	void SetUpdateBits (BitVector &Bits, Player *iTarget) const;
	void SetVisibleBits (BitVector &Bits, Player *iTarget) const;

	bool LoadMail (DatabaseExecutor *dbex);
	bool SaveMail (DatabaseExecutor *dbex);
	bool LoadInventory (DatabaseExecutor *dbex);
	bool SaveInventory (DatabaseExecutor *dbex);
	bool LoadSpells (DatabaseExecutor *dbex);
	bool SaveSpells (DatabaseExecutor *dbex);
	bool LoadQuestStatus (DatabaseExecutor *dbex);
	bool SaveQuestStatus (DatabaseExecutor *dbex);
	bool LoadAffects (DatabaseExecutor *dbex);
	bool SaveAffects (DatabaseExecutor *dbex);

	/// Apply or unapply one modifier to a specific parameter.
	void ApplyModifierU32 (uint iFieldIndex, int iDelta, bool iApply);
	/// Same but for float parameters and modifiers
	void ApplyModifierF32 (uint iFieldIndex, float iDelta, bool iApply);

	/**
	 * Apply all modificators from a item to the character.
	 * @arg iItem
	 *   The item to apply modificators from
	 * @arg iApply
	 *   true to apply, false to unapply
	 */
	void ApplyItemMods (Item *iItem, bool iApply);

	/**
	 * Apply or remove modificators from all dressed items
	 * @arg iApply
	 *   true to apply modificators, false to remove them
	 */
	void ApplyAllItemMods (bool iApply);

	/// Regeneration timer
	Timer RegenTimer;
	/// The dismount timer
	Timer DismountTimer;
	/// The cost to be charged after dismount (taxi)
	uint32 DismountCost;
	/// The target position for taxi route
	float DismountPosX, DismountPosY, DismountPosZ;
	/// Account data; same format as in GameClient class
	uint8 *AccountData [2];

	/// AFK status
	bool AFK;

	/// Inventory and equipment
	Item *Items [INVENTORY_SLOT_ITEM_END];

	/// Player creation data
	static DECLARE_VECTOR_SORTED (PlayerCreateInfoVector, PlayerCreateInfo *, ) PlayerCreateData;

	/// Preload all static data from database
	static bool PreloadStaticData ();
	/// Unload any static data we loaded before
	static void UnloadStaticData ();
	/// Find the structure for the speciefied race/class
	PlayerCreateInfo *FindCreateInfo (int iRace, int iClass, uint32 *err);

	/// Destroy the object -- use DecRef
	virtual ~Player ();

	public:
		/// Current quest statuses
		DECLARE_VECTOR_SORTED (QuestStatusVector, QuestStatus *, ) Quests;
		/// Channels
		DECLARE_VECTOR_SORTED (ChannelsVector, Channel *, ) Channels;
		/// Player's mailbox
		DECLARE_VECTOR_SORTED (MailVector, Mail *, ) MailBox;
		/// Player spells
		DECLARE_VECTOR (SpellsVector, Spell *, ) Spells;

		/// max 12 characters name (24 bytes for UTF-8)
		char *Name;
		/// The client object associated with this character
		GameClient *Client;
		/// Currently selected object
		uint64 CurSelection;
		/// Current target
		uint64 CurTarget;
		/// The group leader
		uint64 GroupLeader;
		/// True if player is already a member of a group
		bool IsInGroup;
		/// True if player is invited into a group
		bool IsInvited;
		/// The GUID of the (presumably dead :) creature we're looting
		uint64 LootGuid;
		/// Which taxi nodes we can use
		uint8 TaxiMask [32];
		/// Initially all zeros, it gets filled with ones as tutorials are passed
		uint8 TutorMask [32];
		/// Action buttons
		uint32 Actions [120];

		/// Create a (mostly) uninitialized player object
		Player ();

		/**
		 * Handle the CHAR_CREATE message. Creates a new player object
		 * and initialize all fields to values appropiate for the corresponding
		 * race, class etc.
		 * @arg inpkt
		 *   The parset network data in a structure
		 * @return
		 *   One of WSE_XXX codes
		 */
		uint32 Create (CMSG_CHAR_CREATE_t &inpkt, GameClient *iClient);

		/// Start the session
		void Login ();

		/**
		 * This is a no-op for Player since a) we can't be looted and
		 * b) we already have all the loot in our pockets.
		 */
		virtual void GenerateLoot () {}

		/// Update unit state depending on time passed
		virtual void Update (uint32 iDeltaMs);

		/// Player should override it to use POS/NEG fields
		virtual void ApplyModifier (Modifier *iMod, bool iApply, Affect *iParent);

		/**
		 * Receive damage from another unit. This is a important function
		 * which is overrided by most children classes because different
		 * creatures react differently to the damage they take. Also note
		 * that this is the ULTIMATE damage, e.g. all resistances, parry
		 * etc is already subtracted from the attack power. Also this function
		 * is responsible to call GiveXP() on the respective attacker unit
		 * after this unit is killed (and it is NOT neccessary that this is
		 * the iAttacker unit).
		 *
		 * @arg iAttacker
		 *   The attacker unit.
		 * @arg iDamage
		 *   The damage caused by the attacker unit.
		 */
		virtual void ReceiveDamage (Unit *iAttacker, uint32 iDamage);

		/**
		 * Give experience points to player
		 * @arg iXP
		 *   Amount of experience points to give.
		 * @arg iVictim
		 *   The creature that has been killed.
		 * @arg iGroup
		 *   true if XP should be distributed amongst all group members
		 *   (if player is part of group, otherwise this is ignored).
		 *   If this is false, the whole XP is given only to this player.
		 */
		virtual void GiveXP (uint32 iXP, Unit *iVictim, bool iGroup = true);

		//----------------// Player saving & loading //----------------//

		/// Save this object to database
		virtual bool SaveToDB ();
		/// Load this object from database
		bool LoadFromDB (uint32 iLowGuid);
		/// Delete this object from database
		virtual bool DeleteFromDB ();

		void AddToWorld ();
		void RemoveFromWorld ();

		/// Toggle Away-From-Keyboard flag and return the new state.
		bool ToggleAFK ()
			{ return (AFK = !AFK); };
		/// Get character name
		const char *GetName ()
			{ return Name; };

		/// Notification of monster kill: update quest flags, if needed
		void KilledMonster (uint32 iEntry, const uint64 &iGuid);

		/**
		 * Give some XP points to this character for killing the creature
		 * with given GUID; if it is is 0, experience comes from another
		 * source (e.g. quest completion) and no purple XP message is printed.
		 * @arg iXP
		 *   Amount of eXperience Points to give
		 * @arg iGuid
		 *   The identifier of killed creature
		 */
		void GiveXP (uint32 iXP, uint64 iGuid);

		/// These functions build a specific type of A9 packet
		//virtual void BuildCreateUpdateBlockForPlayer (BitVector *Bits, Player *target) const;
		/// Destroy this player and all items in inventory for other player
		//virtual void DestroyForPlayer (Player *target) const;

		//----------// Taxi handling //----------//

		void SetDismountTimer (uint32 time)
			{ DismountTimer = time; };
		void SetDismountCost (uint32 money)
			{ DismountCost = money; };
		void SetDismountPos (float x, float y, float z)
			{ DismountPosX = x; DismountPosY = y; DismountPosZ = z; }

		//----------// Quest handling //----------//

		uint32 GetQuestStatus (uint32 iQuestId);
		uint32 AddNewQuest (uint32 iQuestId, uint32 iStatus = 4);
		void LoadExistingQuest (QuestStatus &iQS);
		void SetQuestStatus (uint32 iQuestId, uint32 iNewStatus);
		bool CheckQuestStatus (uint32 iQuestId);
		uint16 GetOpenQuestSlot ();
		uint16 GetQuestSlot (uint32 iQuestId);

		//----------// Mail handling //----------//

		/// Add a message to player's mailbox
		void AddMail (Mail *m);
		/// Get number of messages in the mailbox
		uint32 GetMailSize ()
			{ return MailBox.Length (); }
		/// Get a specific message by identifier
		Mail *GetMail (uint32 iId)
			{ return MailBox.GetByKey (ConstSome (iId)); }
		/// Remove a message by its identifier
		void RemoveMail (uint32 iId)
		{
			int idx = MailBox.FindSortedKey (ConstSome (iId));
			if (idx >= 0) MailBox.Delete (idx);
		}

		//----------// Handle spells //----------//

		bool HasSpell (uint32 iSpell);
		void InitialSpells ();
		void AddSpell (uint iSpellId, uint iSlotId = 0xffff);

		//----------// Handle equipment & inventory //----------//

		/// Get the item placed in the given character slot
		Item *GetItem (uint iSlot)
		{
			DEBUG_BREAK_IF (iSlot >= INVENTORY_SLOT_ITEM_END);
			return Items [iSlot];
		}

		/// Swap two items and send notifications to anyone worth it
		void SwapItemSlots (uint8 iSrcSlot, uint8 iDstSlot);

		/**
		 * Find the slot where the item with given identifier is placed.
		 * Does not look in equipment and bag slots.
		 * @return
		 *   Item slot number or -1 on error.
		 */
		int GetSlotByItemID (uint32 iId);

		/**
		 * Find the slot where the item with given GUID is placed.
		 * The search includes all slots (equipment, bag slots and inventory).
		 */
		int GetSlotByItemGUID (uint64 iGuid);

		/**
		 * Insert a item into the specified slot.
		 * @arg iSlot
		 *   Slot number to place item into
		 * @arg iItem
		 *   The item to place into the slot
		 */
		void AddItemToSlot (uint8 iSlot, Item *iItem);

		/**
		 * Remove a item from indicated slot.
		 * Does NOT decrement reference counter on the item,
		 * so if you don't need the item anymore you must
		 * DecRef() it yourself.
		 */
		Item *RemoveItemFromSlot (uint8 iSlot);

		/**
		 * Find a free equipment slot for an item of the specified type.
		 * @iInvType
		 *   Inventory type (see INVTYPE_XXX constants).
		 * @return
		 *   This function returns the target slot number, or -1 if there
		 *   are no free equipment slots for this type of items. Also the
		 *   function returns -2 if item is of the 'ammo' type (e.g. bullets,
		 *   arrows, thrown and such).
		 */
		int FindFreeItemSlot (uint32 iInvType);

		/**
		 * Check if it is possible to place an item of given type
		 * into the indicated slot.
		 * @arg iSlot
		 *   Target slot number
		 * @arg iInvType
		 *   Inventory type (see INVTYPE_XXX constants).
		 * @return
		 *   true if item can be placed into the indicated slot.
		 */
		bool CanEquipItemInSlot (uint8 iSlot, uint32 iInvType);

		//----------// Death Stuff //----------//

		void SpawnCorpseBody ();
		void SpawnCorpseBones ();
		void CreateCorpse ();
		void KillPlayer ();
		void ResurrectPlayer ();
		void BuildPlayerRepop ();
		/// iPercent = 24.8 fixed-point (256 = 1, 128 = 0.5 etc)
		void DeathDurabilityLoss (uint iPercent);
		void RepopAtGraveyard ();

		//----------// Movement stuff //----------//

		void SetMovement (uint8 pType);
		void SetPlayerSpeed (uint8 SpeedType, float value, bool forced = false);

		//----------// Channel stuff //----------//

		void JoinedChannel (Channel *iChan);
		void LeftChannel (Channel *iChan);
		void CleanupChannels ();
};
#endif														// __PLAYER_H__
