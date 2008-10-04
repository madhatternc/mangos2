/**
 *     \file  src/worldserver/Item.cpp
 *    \brief  Provides basic Item functions.
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

#include "Item.h"
#include "Unit.h"
#include "Database.h"
#include "WorldServer.h"

IMPLEMENT_VECTOR_SORTED (Item::, ItemProtoVector, ItemPrototype *, ItemId, uint32)

Item::ItemProtoVector Item::ItemPrototypes;

Item::Item ()
{
	ItemProto = NULL;
	Owner = NULL;

	Field.SetLength (ITEM_END);
	Field.Clear (OBJECT_END, ITEM_END - ITEM_START);
	Field.SetBits (OBJECT_FIELD_TYPE, TYPE_ITEM, TYPE_ITEM);
}

Item::~Item ()
{
}

bool Item::PreloadStaticData ()
{
	LOG.Out (LOG_COMMON, "Loading item prototype table ...\n");

	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (dbex->Execute ("SELECT * FROM protoitem") != dbeOk)
	{
		LOG.Out (LOG_IMPORTANT, "Failed to load item prototypes from database!\n");
		World->db->PutExecutor (dbex);
		return false;
	}

	if (dbex->NumFields () != 113)
	{
		LOG.Out (LOG_IMPORTANT, "Table `protoitem`: wrong number of fields!\n");
		World->db->PutExecutor (dbex);
		return false;
	}

	ItemPrototypes.DeleteAll ();

	while (dbex->NextRow ())
	{
		if (!dbex->GetU32 (0))
		{
			LOG.Out (LOG_IMPORTANT, "Table `protoitem`: wrong item identifier: 0\n");
			continue;
		}

		ItemPrototype *ip = new ItemPrototype;

		ip->ItemId = dbex->GetU32 (0);
		ip->Class = dbex->GetU32 (2);
		ip->SubClass = dbex->GetU32 (3);
		ip->Name1 = strnew (dbex->Get (4));
		ip->Name2 = strnew (dbex->Get (5));
		ip->Name3 = strnew (dbex->Get (6));
		ip->Name4 = strnew (dbex->Get (7));
		ip->DisplayId = dbex->GetU32 (8);
		ip->Quality = dbex->GetU32 (9);
		ip->Flags = dbex->GetU32 (10);
		ip->BuyPrice = dbex->GetU32 (11);
		ip->SellPrice = dbex->GetU32 (12);
		ip->InventoryType = dbex->GetU32 (13);
		ip->AllowableClass = dbex->GetU32 (14);
		ip->AllowableRace = dbex->GetU32 (15);
		ip->ItemLevel = dbex->GetU32 (16);
		ip->RequiredLevel = dbex->GetU32 (17);
		ip->RequiredSkill = dbex->GetU32 (18);
		ip->RequiredSkillRank = dbex->GetU32 (19);
		ip->Field20 = dbex->GetU32 (20);
		ip->Field21 = dbex->GetU32 (21);
		ip->Field22 = dbex->GetU32 (22);
		ip->Field23 = dbex->GetU32 (23);
		ip->MaxCount = dbex->GetU32 (24);
		ip->Field25 = dbex->GetU32 (25);

		int idx = 26;
		for (uint i = 0; i < ARRAY_LEN (ip->ItemStatType); i++)
		{
			ip->ItemStatType [i] = dbex->GetU32 (idx++);
			ip->ItemStatValue [i] = dbex->GetU32 (idx++);
		}

		for (uint i = 0; i < ARRAY_LEN (ip->DamageMin); i++)
		{
			ip->DamageMin [i] = dbex->GetFloat (idx++);
			ip->DamageMax [i] = dbex->GetFloat (idx++);
			ip->DamageType [i] = dbex->GetU32 (idx++);
		}

		ip->Armor = dbex->GetU32 (61);
		ip->Field62 = dbex->GetU32 (62);
		ip->FireRes = dbex->GetU32 (63);
		ip->NatureRes = dbex->GetU32 (64);
		ip->FrostRes = dbex->GetU32 (65);
		ip->ShadowRes = dbex->GetU32 (66);
		ip->ArcaneRes = dbex->GetU32 (67);
		ip->Delay = dbex->GetU32 (68);
		ip->Field69 = dbex->GetU32 (69);

		idx = 70;
		for (uint i = 0; i < ARRAY_LEN (ip->SpellId); i++)
		{
			ip->SpellId [i] = dbex->GetU32 (idx++);
			ip->SpellTrigger [i] = dbex->GetU32 (idx++);
			ip->SpellCharges [i] = dbex->GetU32 (idx++);
			ip->SpellCooldown [i] = dbex->GetU32 (idx++);
			ip->SpellCategory [i] = dbex->GetU32 (idx++);
			ip->SpellCategoryCooldown [i] = dbex->GetU32 (idx++);
		}

		ip->Bonding = dbex->GetU32 (100);
		ip->Description = strnew (dbex->Get (101));
		ip->Field102 = dbex->GetU32 (102);
		ip->Field103 = dbex->GetU32 (103);
		ip->Field104 = dbex->GetU32 (104);
		ip->Field105 = dbex->GetU32 (105);
		ip->Field106 = dbex->GetU32 (106);
		ip->Field107 = dbex->GetU32 (107);
		ip->Field108 = dbex->GetU32 (108);
		ip->Field109 = dbex->GetU32 (109);
		ip->Field110 = dbex->GetU32 (110);
		ip->Field111 = dbex->GetU32 (111);
		ip->MaxDurability = dbex->GetU32 (112);

		ItemPrototypes.Push (ip);
	}

	ItemPrototypes.QuickSort ();

	World->db->PutExecutor (dbex);
	return true;
}

void Item::UnloadStaticData ()
{
	ItemPrototypes.DeleteAll ();
}

bool Item::Create (uint32 iItemId, Unit *iOwner)
{
	return Create (World->GenerateGUID (HIGHGUID_THING), iItemId, iOwner);
}

bool Item::Create (uint32 iLowGuid, uint32 iItemId, Unit *iOwner)
{
	Field.SetU64 (OBJECT_FIELD_GUID, MAKEGUID (HIGHGUID_THING, iLowGuid));

	Field.SetU32 (OBJECT_FIELD_ENTRY, iItemId);
	Field.SetF32 (OBJECT_FIELD_SCALE_X, 1.0f);

	uint64 owner_guid = iOwner ? iOwner->GetGUID () : 0;

	Field.SetU64 (ITEM_FIELD_OWNER, owner_guid);
	Field.SetU64 (ITEM_FIELD_CONTAINED, owner_guid);
	Field.SetU32 (ITEM_FIELD_STACK_COUNT, 1);

	ItemProto = ItemPrototypes.GetByKey (Some (iItemId));
	if (!ItemProto)
		return false;

	Field.SetU32 (ITEM_FIELD_MAXDURABILITY, ItemProto->MaxDurability);
	Field.SetU32 (ITEM_FIELD_DURABILITY, ItemProto->MaxDurability);

	Owner = iOwner;
	return true;
}

ItemPrototype *Item::FindProto (uint iItemId)
{
	return ItemPrototypes.GetByKey (Some (iItemId));
}

bool Item::SaveToDB ()
{
	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (!dbex)
		return false;

	char *fields = Field.EncodeSQL ();
	bool rc = true;

	// Most of the time the item will be already in database, so
	// try UPDATE first, and if it fails, try INSERT
	bool updateok = (dbex->ExecuteF ("UPDATE items SET data='%s' WHERE guid=%lu",
		fields, GetLowGUID ()) == dbeOk)
		&& dbex->GetAffectedRows ();
	if (!updateok && ((dbex->ExecuteF ("INSERT INTO items VALUES (%lu, '%s')",
		GetLowGUID (), fields) != dbeOk)
		|| !dbex->GetAffectedRows ()))
	{
		LOG.Out (LOG_IMPORTANT, "Table `items`: failed to store item %lu!\n",
			GetLowGUID ());
		rc = false;
	}

	delete [] fields;
	World->db->PutExecutor (dbex);
	return rc;
}

bool Item::LoadFromDB (uint32 iLowGuid)
{
	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (!dbex)
		return false;

	if ((dbex->ExecuteF ("SELECT data FROM items WHERE guid=%lu", iLowGuid) != dbeOk) ||
		!dbex->NextRow ())
	{
		error:  World->db->PutExecutor (dbex);
		return false;
	}

	if (!Field.DecodeSQL (dbex->Get (0)))
		goto error;

	ItemProto = FindProto (Field.GetU32 (OBJECT_FIELD_ENTRY));
	if (!ItemProto)
		goto error;

	World->db->PutExecutor (dbex);
	return true;
}

bool Item::DeleteFromDB ()
{
	DatabaseExecutor *dbex = World->db->GetExecutor ();
	if (!dbex)
		return false;

	bool rc = (dbex->ExecuteF ("DELETE FROM items WHERE guid=%lu", GetLowGUID ()) == dbeOk);
	World->db->PutExecutor (dbex);
	return rc;
}
