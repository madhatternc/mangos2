/**
 *     \file  src/worldserver/ProtocolVectors.cpp
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

#include "ProtocolVectors.h"
#include "Object.h"
#include "Database.h"
#include "StringFun.h"
#include "UpdateFields.h"
#include "Player.h"

IMPLEMENT_VECTOR (, LootResponseVector, LootItem *);
IMPLEMENT_VECTOR (, FriendsVector, FriendStr *);
IMPLEMENT_VECTOR (, MembersVector, Member *);

IMPLEMENT_VECTOR (, CharsVector, CharacterData *);
IMPLEMENT_VECTOR (CharacterData::, SlotItemsVector, SlotItemData *);

IMPLEMENT_VECTOR (, DamageVector, DamageInfo *);

bool CharacterData::Load (DatabaseExecutor *dbex, uint32 iLowGuid)
{
    // We can safely ignore top 32 bits of the GUID since HIGHGUID_PLAYER == 0
    if ((dbex->ExecuteF ("SELECT name,PositionX,PositionY,PositionZ,mapId,zoneId,data "
                         "FROM characters WHERE guid=%d", iLowGuid) != dbeOk)
     || !dbex->NextRow ())
        return false;

    GUID = MAKEGUID (HIGHGUID_PLAYER, iLowGuid);
    Name = strnew (dbex->Get (0));
    PositionX = dbex->GetFloat (1);
    PositionY = dbex->GetFloat (2);
    PositionZ = dbex->GetFloat (3);
    MapId = dbex->GetU32 (4);
    ZoneId = dbex->GetU32 (5);

    uint32 data [PLAYER_END];
    if (DecodeSQL (dbex->Get (6), &data, sizeof (data)) < sizeof (data))
        return false;

    uint32 bytes = data [UNIT_FIELD_BYTES_0];
    Race = bytes;
    Class = bytes >> 8;
    Gender = bytes >> 16;

    bytes = data [PLAYER_BYTES];
    Skin = bytes;
    Face = bytes >> 8;
    HairStyle = bytes >> 16;
    HairColor = bytes >> 24;

    bytes = data [PLAYER_BYTES_2];
    FacialHair = bytes;

    Level = data [UNIT_FIELD_LEVEL];

    //Guild;
    //Unknown;
    //RestState;
    PetInfoId = 0;
    PetLevel = 0;
    PetFamilyId = 0;

    // Now handle the inventory: I don't know what last slot is for (???)
    for (int i = 0; i <= EQUIPMENT_SLOT_END; i++)
    {
        SlotItemData *sid = new SlotItemData;
        memset (sid, 0, sizeof (SlotItemData));
        SlotItems.Push (sid);
    }

    if (dbex->ExecuteF ("SELECT itemGuid,slot FROM inventory WHERE charGuid=%d "
                        "AND slot<" STRINGIZE(EQUIPMENT_SLOT_END), iLowGuid) != dbeOk)
        return true;

    while (dbex->NextRow ())
    {
        uint32 item_guid = dbex->GetU32 (0);
        int slot = dbex->GetU32 (1);
        DEBUG_BREAK_IF (slot >= EQUIPMENT_SLOT_END);

        // Load just the first few fields of the item so that
        DatabaseExecutor *ndbex = dbex->GetParent ()->GetExecutor ();
        if ((ndbex->ExecuteF ("SELECT data FROM items WHERE guid=%lu", item_guid) != dbeOk)
         || !ndbex->NextRow ())
        {
            dbex->GetParent ()->PutExecutor (ndbex);
            continue;
        }

        uint32 part_fields [OBJECT_FIELD_ENTRY + 1];
        DecodeSQL (ndbex->Get (0), &part_fields, sizeof (part_fields));
        dbex->GetParent ()->PutExecutor (ndbex);

        // Find out the prototype of this item
        ItemPrototype *ip = Item::FindProto (part_fields [OBJECT_FIELD_ENTRY]);
        if (!ip)
            continue;

        SlotItemData *sid = SlotItems [slot];
        sid->DisplayId = ip->DisplayId;
        sid->InventoryType = ip->InventoryType;
    }

    return true;
}
