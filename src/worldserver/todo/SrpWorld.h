/**
 *     \file  src/worldserver/todo/SrpWorld.h
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

#ifndef __SRP_WORLD_H__
#define __SRP_WORLD_H__

class SrpWorld
{
    public:
        char user[1024];
        char SS_Hash[40];
        unsigned char keypos, prevbyte;
        unsigned char keypos2, prevbyte2;
        bool firstSent;
        bool firstRecv;
        bool encrypt;

        SrpWorld()
        {
            firstSent = false;
            firstRecv = false;
            keypos = 0; prevbyte = 0;
            keypos2 = 0; prevbyte2 = 0;
            encrypt = true;
        }

        ~SrpWorld() {}

        void decode(unsigned char *data);
        void encode(unsigned char *data);
};
#endif // __SRP_WORLD_H__
