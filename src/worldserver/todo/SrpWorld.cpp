/**
 *     \file  src/worldserver/todo/SrpWorld.cpp
 *    \brief  Provides basic functions for World Server SRP authentication.
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

#include "SrpWorld.h"

void SrpWorld::decode( unsigned char *data )
{
    if(firstRecv && encrypt)
    {
        unsigned char* K = (unsigned char*)SS_Hash;
        for(int i = 0; i < 6; i++ )
        {
            unsigned char a = prevbyte;
            prevbyte = data[i];
            data[i] = K[keypos] ^ (data[i] - a);
            keypos++;
            keypos %= 40;
        }
    }
    else
        firstRecv = true;
}

void SrpWorld::encode( unsigned char *data )
{
    if(firstSent && encrypt)
    {
        unsigned char* K = (unsigned char*)SS_Hash;
        for(int i = 0;i < 4; i++ )
        {
            data[i] = (K[keypos2] ^ data[i]) + prevbyte2;
            prevbyte2 = data[i];
            keypos2++;
            keypos2 %= 40;
        }
    }
    else
        firstSent = true;
}
