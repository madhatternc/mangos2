/**
 *     \file  src/worldserver/todo/MovementHandler.cpp
 *    \brief  Receives all messages related to movement of objects.
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

#include <math.h>
#include <time.h>
#include "MovementHandler.h"
#include "Opcodes.h"
#include "Log.h"
#include "Character.h"
#include "WorldServer.h"
#include "UpdateFields.h"

MovementHandler::MovementHandler()
{

}

MovementHandler::~MovementHandler()
{

}

void MovementHandler::HandleMsg( NetworkPacket & recv_data, GameClient *pClient )
{
    NetworkPacket data;

    // Was getting crashes receiving heartbeats from players that had logged out
    // So dont go any further if they have no current character
    if (!pClient->IsInWorld())  return;

    // This does not need to be verbose :) - Joker
    //printf("WORLD: Movement Opcode 0x%.4X\n", recv_data.opcode );
    switch (recv_data.opcode)
    {
        case MSG_MOVE_HEARTBEAT:
        {
            data.Clear();
            data.Initialize( recv_data.length+8, MSG_MOVE_HEARTBEAT);

            if( pClient->getCurrentChar() && !pClient->getCurrentChar( )->setPosition( recv_data.data+8 ) )
            {
                NetworkPacket movedata;
                pClient->getCurrentChar( )->TeleportAck( &movedata, pClient->getCurrentChar( )->getPositionX( ), pClient->getCurrentChar( )->getPositionY( ), pClient->getCurrentChar( )->getPositionZ( ) );
                pClient->getNetwork( )->sendWData(&movedata, (SrpWorld*)(pClient));
            }

            // GUID of player who sent heartbeat
            guid cguid = pClient->getCurrentChar()->GetGUID();
            memcpy (data.data + 0, &cguid.sno, 4);
            memcpy (data.data + 4, &cguid.type, 4);

            memcpy (data.data + 8, recv_data.data, recv_data.length);
            //memcpy(data.data+8, recv_data.data+8, recv_data.length-8);
            //WORLDSERVER.SendAreaMessage(&data, pClient, 0);
            pClient->getCurrentChar ()->SendMessageToSet (&data, false);
            break;
        }

        case MSG_MOVE_JUMP: case MSG_MOVE_START_FORWARD : case MSG_MOVE_START_BACKWARD: case MSG_MOVE_SET_FACING:
        case MSG_MOVE_STOP: case MSG_MOVE_START_STRAFE_LEFT: case MSG_MOVE_START_STRAFE_RIGHT: case MSG_MOVE_STOP_STRAFE:
        case MSG_MOVE_START_TURN_LEFT: case MSG_MOVE_START_TURN_RIGHT:  case MSG_MOVE_STOP_TURN: case MSG_MOVE_START_PITCH_UP :
        case MSG_MOVE_START_PITCH_DOWN: case MSG_MOVE_STOP_PITCH : case MSG_MOVE_SET_RUN_MODE: case MSG_MOVE_SET_WALK_MODE:
        case MSG_MOVE_SET_PITCH: case MSG_MOVE_START_SWIM:
        case MSG_MOVE_STOP_SWIM:
        {
            if( !pClient->getCurrentChar( )->setPosition( recv_data.data+8 ) )
            {
                NetworkPacket movedata;
                pClient->getCurrentChar( )->TeleportAck( &movedata, pClient->getCurrentChar( )->getPositionX( ), pClient->getCurrentChar( )->getPositionY( ), pClient->getCurrentChar( )->getPositionZ( ) );
                pClient->getNetwork( )->sendWData(&movedata, (SrpWorld*)(pClient));
                pClient->getCurrentChar( )->getPosition( recv_data.data+8 );
            }

            // GUID of player who sent the message
            guid cguid = pClient->getCurrentChar ()->GetGUID ();

            data.Clear();
            data.Initialize (8 + recv_data.length, recv_data.opcode);
            //data.Initialize( recv_data.length, recv_data.opcode);

            memcpy (data.data + 0, &cguid.sno, 4);
            memcpy (data.data + 4, &cguid.type, 4);

            memcpy(data.data + 8, recv_data.data, recv_data.length);
            //memcpy(data.data+8, recv_data.data+8, recv_data.length-8);
            //            WORLDSERVER.SendAreaMessage(&data, pClient, 0);
            pClient->getCurrentChar ()->SendMessageToSet(&data, false);
            break;
        }
        case MSG_MOVE_WORLDPORT_ACK:
        {
            LOG.outString( "WORLD: got MSG_MOVE_WORLDPORT_ACK." );

            // Create myself for other clients
            pClient->getCurrentChar()->SetPosToNewPos();

            // Create Player Character
            WORLDSERVER.mObjectMgr.BuildAndSendCreatePlayer( pClient->getCurrentChar(), 1, NULL );

            // Build the in-range set
            WORLDSERVER.CheckForInRangeObjects( pClient->getCurrentChar() );

            // Send a message to other Clients that a new player has entered the WORLDSERVER
            std::list<NetworkPacket*> msglist;
            WORLDSERVER.mObjectMgr.BuildCreatePlayerMsg( pClient->getCurrentChar(), &msglist, 0 );

            std::list<NetworkPacket*>::iterator msgitr;
            for (msgitr = msglist.begin(); msgitr != msglist.end(); )
            {
                NetworkPacket *msg = (*msgitr);
                pClient->getCurrentChar()->SendMessageToSet(msg, false);
                delete msg;
                msgitr = msglist.erase(msgitr);
            }
            break;
        }

        default:
            break;
    }

}
