/**
 *     \file  src/worldserver/Mail.h
 *    \brief  Provides basic Mail functions.
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

#ifndef __MAIL_H__
#define __MAIL_H__

class Mail
{
    public:
        uint32 MessageId;
        uint32 SenderId;
        uint32 RecipientId;
        char *Subject;
        char *Body;
        uint32 ItemId;
        uint32 Time;
        uint32 Money;
        uint32 COD;
        uint32 Checked;

        ~Mail ()
        {
            delete [] Subject;
            delete [] Body;
        }
};
#endif // __MAIL_H__
