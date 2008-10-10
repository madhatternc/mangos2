/**
 *     \file  src/worldserver/todo/GossipHandler.h
 *    \brief  Receives all messages related to NPC gossip.
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

#ifndef __GOSSIP_HANDLER_H__
#define __GOSSIP_HANDLER_H__

#include "MsgHandler.h"

class TextRelation;
class TextOption;
class NPCText;
class GossipHandler : public MsgHandler
{
    public:
        GossipHandler();
        ~GossipHandler();

        void HandleMsg( NetworkPacket & recv_data, GameClient *pClient );
        void addTextRelation( TextRelation *pTextRelation );
        void addNPCText( NPCText * pNPCText );
        void addTextOption( TextOption * pTextOption );
        TextRelation * getTextRelation( uint32 NPCID );
        uint32 getTextID(uint32 NPCID);
        NPCText * getNPCText( uint32 NPCTextID );
        TextOption * getTextOption( uint32 OptionID );

    protected:
        // Gossip data
        //NPC Text RelationShip
        typedef std::map<uint32, TextRelation*> TextRelationMap;
        TextRelationMap mTextRelations;

        //Text Options
        typedef std::map<uint32, TextOption*> TextOptionMap;
        TextOptionMap mTextOptions;

        //NPC Texts
        typedef std::map<uint32, NPCText*> NPCTextMap;
        NPCTextMap mNPCTexts;
};
#endif                                                      // __GOSSIP_HANDLER_H__
