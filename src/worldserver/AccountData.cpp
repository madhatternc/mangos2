/**
 *     \file  src/worldserver/AccountData.cpp
 *    \brief  Receives all messages related to account and per character settings.
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

#include <openssl/md5.h>
#include <zlib.h>
#include "GameClient.h"
#include "Player.h"

void GameClient::SendAccountDataMD5 ()
{
    SMSG_ACCOUNT_DATA_MD5_t *outpkt = SMSG_ACCOUNT_DATA_MD5_t::Create ();
    for (uint i = 0; i < 5; i++)
    {
        uint8 *data;
        if (i <= 2)
            data = AccountData [i];
        else if (i <= 4)
            data = Character->AccountData [i - 3];

        if (data)
            memcpy (outpkt->MD5 + i * 16, data + 8, 16);
        else
            memset (outpkt->MD5 + i * 16, 0, 16);
    }
    Send (outpkt);
}

void GameClient::HandleRequestAccountData (CMSG_REQUEST_ACCOUNT_DATA_t &inpkt)
{
    if (!Character)
        return;

    uint8 *data;
    if (inpkt.FileIndex <= 2)
        data = AccountData [inpkt.FileIndex];
    else if (inpkt.FileIndex <= 4)
        data = Character->AccountData [inpkt.FileIndex - 3];
    else
        return;

    if (!data)
        return;

    SMSG_UPDATE_ACCOUNT_DATA_t *outpkt = SMSG_UPDATE_ACCOUNT_DATA_t::Create ();
    outpkt->FileIndex = inpkt.FileIndex;
    outpkt->UncompressedSize = GET_LE32 (data);
    outpkt->CompressedData_Size = GET_LE32 (data + 4);
    outpkt->CompressedData = data + 24;
    Send (outpkt);
}

void GameClient::HandleUpdateAccountData (CMSG_UPDATE_ACCOUNT_DATA_t &inpkt)
{
    if (!Character)
        return;

    uint8 **pdata;
    if (inpkt.FileIndex <= 2)
        pdata = &AccountData [inpkt.FileIndex];
    else if (inpkt.FileIndex <= 4)
        pdata = &Character->AccountData [inpkt.FileIndex - 3];
    else
        return;

    // Uncompress the data to check integrity and compute MD5
    uint8 *tmp = new uint8 [inpkt.UncompressedSize];
    uLongf tmplen = inpkt.UncompressedSize;
    if (tmplen &&
        uncompress (tmp, &tmplen, inpkt.CompressedData, inpkt.CompressedData_Size) != Z_OK)
    {
        delete [] tmp;
        return;
    }

    uint datasize = sizeof (uint32) * 2 + 16 + inpkt.CompressedData_Size;
    uint8 *data = new uint8 [datasize];

    delete [] *pdata;
    *pdata = data;

    PUT_LE32 (data, inpkt.UncompressedSize);
    PUT_LE32 (data + 4, inpkt.CompressedData_Size);
    MD5 (tmp, inpkt.UncompressedSize, data + 8);
    memcpy (data + 24, inpkt.CompressedData, inpkt.CompressedData_Size);

    delete [] tmp;
}
