/**
 *     \file  src/worldserver/todo/ChatHandler.cpp
 *    \brief  Receives all messages related to chat channels.
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

#include "ChatHandler.h"
#include "GameClient.h"
#include "Opcodes.h"
#include "Log.h"
#include "WorldServer.h"
#include "Character.h"
#include "UpdateFields.h"
#include "Database.h"
#include "Vectors.h"

ChatCommand *ChatCommandVector::Get (int iIndex)
{ return (ChatCommand *)Vector::Get (iIndex); }
/// Compare two array elements in given Mode
virtual int ChatCommandVector::Compare (Some Item1, Some Item2, int Mode) const
{ return strcmp (((ChatCommand *)Item1)->Name, ((ChatCommand *)Item2)->Name); }
/// Compare entry with a key
virtual int ChatCommandVector::CompareKey (Some Item, ConstSome Key, int Mode) const
{ return strcmp (((ChatCommand *)Item)->Name, (char *)Key); }

virtual bool ChatCommandVector::FreeItem (ChatCommand *Item)
{
    delete Item;
}

void ChatHandler::LoadCommands()                            /*FOLD00*/
{
    static bool first_call = true;

    if(first_call)
    {
        first_call = false;
        //ADMIN
        //      adminCommandTable[0].setValues("ban",         3, 0, &ChatHandler::HandleBanCommand,           "",   NULL);//LINA FEATURE
        //      adminCommandTable[1].setValues("unban",       3, 0, &ChatHandler::HandleUnBanCommand,         "",   NULL);//LINA FEATURE
        ChatCommand* usr = ChatCommand("usr",      AUTH_ADMIN,   1, NULL, "Change user attributes",   NULL);
        ChatCommand* gm = ChatCommand("gm",        AUTH_GM,      1, NULL, "Generel admin commands",   NULL);
        ChatCommand* move = ChatCommand("move",    AUTH_GM,      1, NULL, "Move commands",   NULL);
        ChatCommand* npc = ChatCommand("npc",      AUTH_SPAWNER, 1, NULL, "Spawner commands",   NULL);
        ChatCommand* admin = ChatCommand("admin",  AUTH_ADMIN,   1, NULL, "Admin commands",   NULL);

                                                            //LINA FEATUR
        ChatCommand("lvl",         AUTH_ADMIN, 1, &ChatHandler::HandleSecurityCommand,      "",   admin);
        ChatCommand("addspirit",   AUTH_ADMIN, 0, &ChatHandler::HandleAddSpiritCommand,     "",   admin);
        ChatCommand("die",         AUTH_ADMIN, 0, &ChatHandler::HandleDieCommand,           "",   admin);
        ChatCommand("update",      AUTH_ADMIN, 0, &ChatHandler::HandleUpdateCommand,        "",   admin);

        //CREATOR
        ChatCommand("info",        AUTH_GM, 0, &ChatHandler::HandleGUIDCommand,          "",   npc);
        ChatCommand("mobs",        AUTH_GM, 0, &ChatHandler::HandleSpawnCommand,         "",   npc);
        ChatCommand("taxi",        AUTH_GM, 0, &ChatHandler::HandleSpawnTaxiCommand,     "",   npc);
        ChatCommand("spell",       AUTH_GM, 0, &ChatHandler::HandleSpellCommand,         "",   npc);
        ChatCommand("rmvspell",    AUTH_GM, 0, &ChatHandler::HandleRemoveSpellCommand,   "",   npc);
        ChatCommand("item",        AUTH_GM, 0, &ChatHandler::HandleItemCommand,          "",   npc);
        ChatCommand("rmvitem",     AUTH_GM, 0, &ChatHandler::HandleRemoveItemCommand,    "",   npc);
        ChatCommand("itemmove",    AUTH_GM, 0, &ChatHandler::HandleItemMoveCommand,      "",   npc);
        ChatCommand("delete",      AUTH_GM, 0, &ChatHandler::HandleDeleteCommand,        "",   npc);
                                                            //LINA FEATURE
        ChatCommand("level",       AUTH_GM, 0, &ChatHandler::HandleChangeLevelCommand,   "",   npc);
        ChatCommand("skin",        AUTH_GM, 0, &ChatHandler::HandleDisplayIdCommand,     "",   npc);
        ChatCommand("faction",     AUTH_GM, 0, &ChatHandler::HandleFactionIdCommand,     "",   npc);
                                                            //LINA FEATURE
        ChatCommand("name",        AUTH_GM, 0, &ChatHandler::HandleNameCommand,          "",   npc);
        ChatCommand("flag",        AUTH_GM, 0, &ChatHandler::HandleNPCFlagCommand,       "",   npc);
        ChatCommand("animfreq", AUTH_ADMIN, 0, &ChatHandler::HandleAnimFreqCommand,      "",   npc);
        ChatCommand("random",      AUTH_GM, 0, &ChatHandler::HandleRandomCommand,        "",   npc);
        ChatCommand("addmove",     AUTH_GM, 0, &ChatHandler::HandleAddMoveCommand,       "",   npc);
        ChatCommand("run",         AUTH_GM, 0, &ChatHandler::HandleRunCommand,           "",   npc);
        ChatCommand("state",       AUTH_GM, 0, &ChatHandler::HandleAggressiveCommand,    "",   npc);

        //MOVE
        ChatCommand("where",       AUTH_GM, 0, &ChatHandler::HandleGPSCommand,           "",   move);
        ChatCommand("there",       AUTH_GM, 0, &ChatHandler::HandleAppearCommand,        "",   move);
        ChatCommand("here",        AUTH_GM, 0, &ChatHandler::HandleSummonCommand,        "",   move);
        ChatCommand("fast",   AUTH_SPAWNER, 0, &ChatHandler::HandleMoveCommand,          "",   move);
        ChatCommand("world",    AUTH_ADMIN, 0, &ChatHandler::HandleWorldPortCommand,     "",   move);
        ChatCommand("town",        AUTH_GM, 0, &ChatHandler::HandleRecallCommand,        "",   move);
        ChatCommand("prog",   AUTH_SPAWNER, 0, &ChatHandler::HandleProgCommand,          "",   move);
        ChatCommand("isle",        AUTH_GM, 0, &ChatHandler::HandleIsleCommand,          "",   move);

        //GM
                                                            //LINA FEATURE
        ChatCommand("pass",        AUTH_GM, 0, &ChatHandler::HandleGMPassCommand,        "",   gm);
        ChatCommand("off",         AUTH_GM, 0, &ChatHandler::HandleGMOffCommand,         "",   gm);
        ChatCommand("on",          AUTH_GM, 0, &ChatHandler::HandleGMOnCommand,          "",   gm);
        //ChatCommand("kick",        AUTH_GM, 0, &ChatHandler::HandleKickCommand,          "",   gm);//LINA FEATURE
                                                            //LINA FEATURE
        ChatCommand("save",        AUTH_GM, 0, &ChatHandler::HandleSaveAllCommand,       "",   gm);
        ChatCommand("announce",    AUTH_GM, 0, &ChatHandler::HandleAnnounceCommand,      "",   gm);

        //USR commands
        ChatCommand("hp",          AUTH_GM, 0, &ChatHandler::HandleModifyHPCommand,    "",   usr);
        ChatCommand("mana",        AUTH_GM, 0, &ChatHandler::HandleModifyManaCommand,      "",   usr);
        ChatCommand("gold",        AUTH_GM, 0, &ChatHandler::HandleModifyGoldCommand,      "",   usr);
        ChatCommand("lvl",         AUTH_GM, 0, &ChatHandler::HandleModifyLevelCommand,     "",   usr);
        ChatCommand("speed",       AUTH_GM, 0, &ChatHandler::HandleModifySpeedCommand,     "",   usr);
                                                            //LINA FEATURE
        ChatCommand("wspeed",      AUTH_GM, 0, &ChatHandler::HandleModifyWaterSpeedCommand,   "",   usr);
                                                            //LINA FEATURE
        ChatCommand("scale",       AUTH_GM, 0, &ChatHandler::HandleModifyScaleCommand,     "",   usr);
        ChatCommand("mount",       AUTH_GM, 0, &ChatHandler::HandleModifyMountCommand,     "",   usr);
        ChatCommand("exp",         AUTH_GM, 0, &ChatHandler::HandleModifyExpCommand,       "",   usr);
        ChatCommand("aura",     AUTH_ADMIN, 0, &ChatHandler::HandleAuraCommand,        "",   usr);
        ChatCommand("learn",    AUTH_ADMIN, 0, &ChatHandler::HandleLearnCommand,       "",   usr);
        ChatCommand("skin",     AUTH_ADMIN, 0, &ChatHandler::HandleMorphCommand,           "",   usr);

        //MAIN
        RegisterCommand(ChatCommand("help",        0, &ChatHandler::HandleHelpCommand,          "",   NULL));
        RegisterCommand(ChatCommand("commands",    0, &ChatHandler::HandleCommandsCommand,      "",   NULL));
        RegisterCommand(ChatCommand("info",        0, &ChatHandler::HandleInfoCommand,          "",   NULL));
        RegisterCommand(ChatCommand("dismount",    0, &ChatHandler::HandleDismountCommand,      "",   NULL));
        RegisterCommand(ChatCommand("mount",       0, &ChatHandler::HandleMountCommand,         "",   NULL));
                                                            //LINA FEATURE
        RegisterCommand(ChatCommand("save",        0, &ChatHandler::HandleSaveCommand,          "",   NULL));
        RegisterCommand(ChatCommand("start",       0, &ChatHandler::HandleStartCommand,         "",   NULL));
        RegisterCommand(ChatCommand("list",        0, &ChatHandler::HandleGMListCommand,        "",   NULL));
        RegisterCommand(ChatCommand("acct",        0, &ChatHandler::HandleAcctCommand,          "",   NULL));
        RegisterCommand(ChatCommand("login",       0, &ChatHandler::HandleGMLoginCommand,       "",   NULL));
        RegisterCommand(admin);
        RegisterCommand(usr);
        RegisterCommand(gm);
        RegisterCommand(move);
        RegisterCommand(npc);
    }
    /*
    if(load)
    {
        DatabaseInterface *dbi = DATABASE.createDatabaseInterface( );

        for(uint32 i = 0; commandTable[i].Name != NULL; i++)
        {
            dbi->loadChatCommand(commandTable[i].Name, &commandTable[i]);

            if(commandTable[i].ChildCommands != NULL)
            {
                ChatCommand *ptable = commandTable[i].ChildCommands;
                for(uint32 j = 0; ptable[j].Name != NULL; j++)
                {
                    std::string str = commandTable[i].Name;
                    str += " ";
                    str += ptable[j].Name;
                    dbi->loadChatCommand(str.c_str(), &ptable[j]);
                }
            }
        }

        DATABASE.removeDatabaseInterface(dbi);
    }
    */
}

void ChatHandler::RegisterCommand(ChatCommand *cCommand)    /*FOLD00*/
{
    ChatCommands->Push(cCommand);

}

bool ChatHandler::hasStringAbbr(const char* s1, const char* s2)
{
    for(;;)
    {
        if( !*s2 )
            return true;
        else if( !*s1 )
            return false;
        else if( tolower( *s1 ) != tolower( *s2 ) )
            return false;
        s1++; s2++;
    }
}

void ChatHandler::SendMultilineMessage(const char *str)
{
    char buf[256];
    NetworkPacket data;

    const char* line = str;
    const char* pos = line;
    while((pos = strchr(line, '\n')) != NULL)
    {
        strncpy(buf, line, pos-line);
        buf[pos-line]=0;

        SMSG_MESSAGECHAT_t *response = FillMessageData(0x09, m_pClient, (uint8*)buf);
        m_pClient->SendMsg(response);
        response.DecRef();

        line = pos+1;
    }

    SMSG_MESSAGECHAT_t *response = FillMessageData(0x09, m_pClient, (uint8*)line);
    m_pClient->SendMsg(response);
}

/*
bool ChatHandler::ExecuteCommandInTable(ChatCommand *table, uint8* text)
{
    char *cmd = (char*)text;
    uint32 AcctLvl = m_pClient->getAccountLvl();

    while (*text != ' ' && *text != '\0') text++; // skip command
    if(*text != '\0')
    {
        *text = '\0';
        text++;
    }

    while (*text == ' ') text++; // skip whitespace

    if(*cmd == '\0')
        return false;

    for(uint32 i = 0; table[i].Name != NULL; i++)
    {
        if(!hasStringAbbr(table[i].Name, cmd))
            continue;

        if(AcctLvl < table[i].SecurityLevel)
            continue;

        if(table[i].ChildCommands != NULL)
        {
            if(!ExecuteCommandInTable(table[i].ChildCommands, text))
            {
                if(table[i].Help != "")
                    SendMultilineMessage(table[i].Help.c_str());
                else
                {
                    NetworkPacket data;
                    FillMessageData(&data, 0x09, m_pClient, (uint8*)"There is no such subcommand.");
                    m_pClient->SendMsg(&data);
                }
            }
            return true;
        }

        if(!(this->*(table[i].Handler))(text))
        {
            if(table[i].Help != "")
                SendMultilineMessage(table[i].Help.c_str());
            else
            {
                NetworkPacket data;
                FillMessageData(&data, 0x09, m_pClient, (uint8*)"Incorrect syntax.");
                m_pClient->SendMsg(&data);
            }
        }
        return true;
    }

    return false;
}
*/

bool ChatHandler::Execute(ChatArguments *args)
{
    ChatCommand *cur = NULL;
    ChatCommandVector *vec = ChatCommands;
    int depth = 0;
    int ind = 0;

    if(!args->Length())
        return false;

    while(true)
    {
        ind = vec->Find(args->Get(depth));
        if(ind != -1)
        {
            cur = vec->Get(ind);
            // execute
            if(cur->Handler)
            {
                if(cur->Minargs + depth <= args.Length())
                    return cur.Handler(args);
                else
                {
                    SMSG_MESSAGECHAT_t *response = FillMessageData(0x09, m_pClient, (uint8*)"Not enough arguments.");
                    m_pClient->SendMsg(response);
                    response.Decref();
                    // not enough arguments
                    // FIXME error message
                    return 0;
                }
            }
        }

        if(ind != 1 && cur)
        {
            // search for subcommands
            depth++;
            vec = cur->Subcommands;
        }

    }

}

ChatArguments* ChatHander::ParseLine(uint8* text, uint32 length)
{
    ChatArguments ret = ChatArguments();
    uint8* cur = text;                                      // Current position
    uint8* last = cur;                                      // Position of the last token
    uint quotes = 0;                                        // Count which quotes exist
    uint8* nword;

    if(!length)
        length = strlen(text);

    #define PUSHARG()\
        nword = (uint8 *)malloc(cur - last +1);\
        memcpy(last, &nword, cur-last); \
        nword[cur-last+1] = 0; \
        ret.Push(nword); \

    while(cur)
    {
        switch(cur)
        {
            case '\'':
                // Token ends here
                if (quotes & 1)
                    PUSHARG();
                else
                    // start quote
                    quotes = quotes | 1;
                break;
            case '"':
                if (quotes & 2)
                    PUSHARG();
                else
                    quotes = quotes | 2;
                break;
            case ' ':
            case '\t':
                if (quotes || ((cur > text) && cur-1 != '\\'))
                    break;
                else
                    PUSHARG();
        }
        cur++;
        if(cur-text > end)
        {
            // if we have a last token left, add him even when we are in brackets. it becomes one large argument then
            if(last != cur-1)
            {
                cur--;
                PUSHARG();
                break;
            }
        }
    }
    #undef PUSHARG
    return ret;

}

bool ChatHandler::ParseCommands(uint8* text, uint16 text_length)
{
    (void)text_length;
    assert(text);
    //    assert(*text);

    if(text[0] != '!' && text[0] != '.')                    // let's not confuse users
        return false;
    text++;

    ChatArguments* args = ParseLine(text);

    if(!Execute(args))
    {
        SMSG_MESSAGECHAT_t *response = FillMessageData(0x09, m_pClient, (uint8*)"There is no such command.");
        m_pClient->SendMsg(response);
        response.Decref();
        return false;
    }

    return true;
}

void ChatHandler::MessageChat(CMSG_MESSAGECHAT_t *rcv_data, GameClient *pClient)
{
    //uint16 text_length = strlen((char*)recv_data.data+8)+1;
    // we don't trust the Msglength attribute
    //uint16 text_length = strlen(rcvdata->Msg)+1;

    m_pClient = pClient;

    uint8 text_mode = recv_data.data[0];
    SMSG_MESSAGECHAT* response = FillMessageData(recvdata.Type, pClient, recvdata.Msg );

    switch(rcv_data.Type)
    {
        case CHAT_MSG_SAY:
            if (ParseCommands(recv_data.Msg, 0) > 0)
                break;
            WORLDSERVER.SendGlobalMessage(&response, pClient);
            break;
        case CHAT_MSG_WHISPER:
            if(!recv_data.Whisperto)
            {
                LOG.Out("Can't find whisper target");
            }
            else
            {
                if(!WORLDSERVER.SendMessageToPlayer(response, rcv_data.Whisperto))
                {
                    //FIXME Send msg that player is not online
                }
            }
            break;
        case CHAT_MSG_CHANNEL:
            //@@@FIXME
            //Guess we need special handlers for guild etc, too
        default:
            // Send msg as it is
            //pClient->SendMsg( &response);
            WORLDSERVER.SendGlobalMessage(&response, pClient);
    }

    response.DecRef();
}

void ChatHandler::TextEmote(CMSG_TEXT_EMOTE_t *rcv_data, GameClient *pClient)
{
    uint32 text_emote, guid1, guid2;
    char *nam=0; uint16 namlen=0;
    //@@@FIXEME review packets

    WorldServer::CharacterMap::iterator chariter;
    WorldServer::CreatureMap::iterator npciter;
    // FIXME, we really need better lookups here
    if( ( npciter = WORLDSERVER.mCreatures.find( rcv_data->Guid ) ) != WORLDSERVER.mCreatures.end( ) )
    {
        nam = npciter->second->getCreatureName( );
        namlen = strlen( nam ) + 1;
    }
    else if( ( chariter = WORLDSERVER.mCharacters.find( rcv_data->Guid ) ) != WORLDSERVER.mCharacters.end( ) )
    {
        nam = chariter->second->getName( );
        namlen = strlen( nam ) + 1;
    }

    data.Clear();
    SMSG_EMOTE_t* response = SMSG_EMOTE_t::Create();

    uint8 emote_anim = WORLDSERVER.mEmotes[uint8(rcv_data.Emote&0xff)];

    response->Emote = emote_anim;
    respone->.Guid =  pClient->getCurrentChar()->GetGUID();
    response->Assemble();
    WORLDSERVER.SendGlobalMessage (&response);
    response->DecRef();

    SMSG_TEXT_EMOTE_t* response2 = SMSG_TEXT_EMOTE_t::Create();

    response2->Guid = rcv_data->Guid;
    response2->Emote = emote_anim;
    response2->Name = nam;

    response2.Assemble();

    data.Clear ();
    data.SetLength (12 + namlen);
    data.opcode = SMSG_TEXT_EMOTE;

    pClient->SendMsg( &response2 );
    WORLDSERVER.SendGlobalMessage(&response2, pClient);

}

SMSG_MESSAGECHAT_t ChatHandler::FillMessageData(uint8 type, GameClient* pClient, uint8 *text )
{

    // !!!! Be careful using strlen to determine the size of the chat message.
    // A CHAT_MSG_WHISPER sends TWO null terminated  strings(first the name of
    // the whisper target, then the message) and doing strlen only finds the
    // length of the first string.  -- DeathCheese

    SMSG_MESSAGECHAT_t *response = SMSG_MESSAGECHAT_t::Create();

    if (pClient)
        response->Guid = pClient->getCurrentChar()->GetGUID();
    else
        response->Guid = guid(0, 0);
    response->Type = type;

    response->Msg = strnew(text);
    response->Msglength = strlen(text)+1;

    /*if (type == CHAT_MSG_WHISPER){
    //FIXME didn't capturea Sendername anymore. maybe lookedup by guid
    response->Sendername = strnew();
    response->Msglength += 1;
    }
    */
    if( pClient )
    {
        logoutput += pClient->getCurrentChar( )->getName( );
        logoutput += ": ";
    }

    if(type == CHAT_MSG_AFK && pClient!=0)                  // toggle AFK
    {
        response->Afktoggle = pClient->getCurrentChar()->ToggleAFK();
    }
    response->Assemble();
    //FIXME output
    //response->DecRef();
    return response;

    /* Vote for ugliest code ever ;)
    const uint8 msgchat_header_size=13;
    uint8 msgchat_header[msgchat_header_size] = {type,
            0x00, 0x00, 0x00, 0x00}; //no idea what are those bytes for

    // add guid to message header
    guid mguid;
    if (pClient)
            mguid = pClient->getCurrentChar()->GetGUID();
    else
            mguid.Set (0, 0);
    memcpy (msgchat_header + 5, &mguid.sno, 4);
    msgchat_header[9] = 0x00;
    msgchat_header[10] = 0x00;
    msgchat_header[11] = 0x00;
    msgchat_header[12] = 0x00;

    data->Clear();

    std::string logoutput = "CHAT: ";
    if( pClient ) {
            logoutput += pClient->getCurrentChar( )->getName( );
            logoutput += ": ";
    }

    uint32 length = strlen((char*)text) + 1;
    //  data.Initialize(length+msgchat_header_size+5 , SMSG_MESSAGECHAT);
    if (type == CHAT_MSG_WHISPER){
            // Whisper Chat:  Server receives two strings.  First is the target of whisper, second is the message.
            uint16 msg_length = strlen((char*)text+length) + 1;

            data->SetLength(msgchat_header_size + msg_length + 1);
            data->opcode = SMSG_MESSAGECHAT;
            memcpy(data->data, msgchat_header, msgchat_header_size);
            memcpy(data->data+msgchat_header_size, text+length, msg_length);
            data->data[msgchat_header_size+msg_length] = 0; //NULL terminated string
            logoutput += "->";
            logoutput += (char *)text;
            logoutput += "<- ";
            logoutput += (char *)(text + length);
    }
    else{

            data->SetLength(msgchat_header_size + length + 5);
            data->opcode = SMSG_MESSAGECHAT;

            memcpy(data->data,msgchat_header,msgchat_header_size);
            memcpy(data->data+13, &length, 4);
            memcpy(data->data+17, text, length);
            data->data[msgchat_header_size+length+4] = 0; //NULL terminated string
            logoutput += (char *)text;
    }

    LOG.outString( logoutput.c_str( ) );

    // The last byte is most likely a flag, 0 or 1, denoting on or off
    uint8 byte = 0x00;
    if(type == CHAT_MSG_AFK && pClient!=0) { // toggle AFK
            byte = pClient->getCurrentChar()->ToggleAFK();
    }

    data->data[data->length-1] = byte;

    if (type == CHAT_MSG_WHISPER){
            // save the whisper TO name
            char name[22];
            memcpy(name, text, length);
            WORLDSERVER.SendMessageToPlayer(data, (char*)name); // slightly hackish I guess
            }
    */
}

void ChatHandler::SpawnCreature(GameClient *pClient, char* pName, uint32 display_id, uint32 npcFlags, uint32 faction_id, uint32 level)
{
    NetworkPacket data;

    // Create the requested monster
    Character *chr = pClient->getCurrentChar();
    float x = chr->getPositionX();
    float y = chr->getPositionY();
    float z = chr->getPositionZ();
    float o = chr->getOrientation();

    Unit* pUnit = new Unit();
    UpdateMask unitMask;
    WorldServer::getSingletonPtr()->mObjectMgr.SetCreateUnitBits(unitMask);

    pUnit->Create(WORLDSERVER.m_hiCreatureGuid++, (uint8*)pName, x, y, z, o);
    pUnit->setMapId(chr->getMapId());
    pUnit->setZone(chr->getZone());
    data.Clear();
    pUnit->setUpdateValue(OBJECT_FIELD_ENTRY, WORLDSERVER.addCreatureName((uint8*)pUnit->getCreatureName()));
    pUnit->setUpdateFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
    pUnit->setUpdateValue(UNIT_FIELD_DISPLAYID, display_id);
    pUnit->setUpdateValue(UNIT_NPC_FLAGS , npcFlags);
    pUnit->setUpdateValue(UNIT_FIELD_FACTIONTEMPLATE , faction_id);
    float fLevel = (float) level;                           // avoid casting all over the place
    pUnit->setUpdateValue(UNIT_FIELD_HEALTH, (uint32)((1.24*fLevel*fLevel)+(1.79*fLevel)+40.64) );
    pUnit->setUpdateValue(UNIT_FIELD_MAXHEALTH, (uint32)((1.24*fLevel*fLevel)+(1.79*fLevel)+40.64) );
    pUnit->setUpdateValue(UNIT_FIELD_LEVEL , level);

    pUnit->setUpdateFloatValue(UNIT_FIELD_COMBATREACH , 1.5f);
                                                            // 5,6, 7, 8, 9,10
    pUnit->setUpdateFloatValue(UNIT_FIELD_MINDAMAGE ,  4.0f+fLevel);
                                                            // 6,8,10,12,14,16
    pUnit->setUpdateFloatValue(UNIT_FIELD_MAXDAMAGE , 4.0f+fLevel+fLevel);
    pUnit->setUpdateValue(UNIT_FIELD_BASEATTACKTIME, 1900);
    pUnit->setUpdateValue(UNIT_FIELD_BASEATTACKTIME+1, 2000);
    pUnit->setUpdateFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 2.0f);

    pUnit->CreateObject(&unitMask, &data, 0);

    // add to the world list of creatures
    WPAssert (pUnit->GetGUID().Assigned ());
    WORLDSERVER.mCreatures [pUnit->GetGUID().sno] = pUnit;

    // send create message to everyone
    WORLDSERVER.SendGlobalMessage(&data);

    DatabaseInterface *dbi = DATABASE.createDatabaseInterface( );
    dbi->saveCreature(pUnit);
    DATABASE.removeDatabaseInterface(dbi);
}

void ChatHandler::smsg_NewWorld(GameClient *pClient, uint16 c, float x, float y, float z)
{
    WorldServer::CreatureMap creatures = WORLDSERVER.getCreatureMap();
    WorldServer::CharacterMap characters = WORLDSERVER.getCharacterMap();

    data.Initialize(4, SMSG_TRANSFER_PENDING);
    SMSG_TRANSFER_PENDING_t* response = SMSG_TRANSFER_PENDING_t::Create();
    SMSG_NEW_WORLD_t* response2 = SMSG_NEW_WORLD_t::Create();
    response->Type = 0;
    response->Assemble();

    pClient->SendMsg(&response);
    response->DecRef();

    // Build a NEW WORLD packet
    data.Initialize(20, SMSG_NEW_WORLD);
    response2->C = c;
    response2->X = x;
    response2->Y = y;
    response2->Z = z;
    response2->O = 0.0f;
    response2->Assemble();

    pClient->SendMsg( &response2 );
    response2->DecRef();

    /*
    // Destroy this client's player from all clients (including self)
    uint32 guid = pClient->getCurrentChar()->GetGUID();
    data.Initialize(SMSG_DESTROY_OBJECT);
    data << (uint32)guid << (uint8)0x00 << (uint8)0x00 << (uint8)0x00 << (uint8)0x00;
    WPAssert(data.getLength() == 8);
    pClient->SendMsg(&data);

    for( WorldServer::CreatureMap::iterator i = creatures.begin( ); i != creatures.end( ); ++ i )
    {
    uint32 guid = i->second->GetGUID();
    data.Initialize(SMSG_DESTROY_OBJECT);
    data << (uint32)guid << i->second->getGUIDHigh();
    WPAssert(data.getLength() == 8);
    pClient->SendMsg(&data);
    }
    */

    // Destroy ourselves from other clients
    SMSG_DESTROY_OBJECT_t* response3 = SMSG_NEW_WORLD_t::Create();
    response3->Guid = pClient->getCurrentChar()->GetGUID();
    response3->Assemble();
    pClient->getCurrentChar()->SendMessageToSet(&response3, true);

    // Remove ourselves from inrange lists
    for( WorldServer::CharacterMap::iterator iter = characters.begin( ); iter != characters.end( ); ++ iter )
        iter->second->RemoveInRangeObject( pClient->getCurrentChar() );

    for( WorldServer::CreatureMap::iterator iter = creatures.begin( ); iter != creatures.end( ); ++ iter )
        iter->second->RemoveInRangeObject( pClient->getCurrentChar() );

    pClient->getCurrentChar()->ClearInRangeSet();

    pClient->getCurrentChar()->setMapId(c);

    pClient->getCurrentChar()->setNewPosition(x,y,z);
    // FIXME ???
    pClient->getCurrentChar()->setPosition(8000,8000,0,0,true);
}

void ChatHandler::MovePlayer(GameClient *pClient, float x, float y, float z)
{

    //Output new position to the console
    uint8 txtBuffer[512];
    sprintf((char*)txtBuffer,"WORLD: Moved player to (%f, %f, %f)",x,y,z );
    LOG.outString( (char*)txtBuffer );

    sprintf((char*)txtBuffer,"You have been moved to (%f, %f, %f)",x,y,z );
    SMSG_MESSAGECHAT_t data =  FillMessageData(0x09, pClient, txtBuffer);
    pClient->SendMsg( &data );
    data->DecRef();

    ////////////////////////////////////////
    //Set the new position of the character
    Character *chr = pClient->getCurrentChar();

    //Send new position to client via MSG_MOVE_TELEPORT_ACK
    chr->TeleportAck(&data, x,y,z);
    pClient->SendMsg(&data);

    //////////////////////////////////
    //Now send new position of this player to all clients using MSG_MOVE_HEARTBEAT
    chr->BuildHeartBeat(&data);
    WORLDSERVER.SendGlobalMessage(&data, pClient);
}

Character * ChatHandler::getCurrentCharByName(uint8 * pName)
{
    WorldServer::ClientSet::iterator itr;
    for (itr = WORLDSERVER.mClients.begin(); itr != WORLDSERVER.mClients.end(); itr++)
    {
        if( strcmp(((GameClient*)(*itr))->getCharacterName(), (char*)pName) == 0 )
        {
            return ((GameClient*)(*itr))->getCurrentChar();
        }
    }
    NetworkPacket data;
    uint8 buf[256];
    sprintf((char*)buf,"Character (%s) does not exist or is not logged in.", (char*)pName);
    SMSG_MESSAGECHAT_t data = FillMessageData(0x09, m_pClient, buf);
    m_pClient->SendMsg( & );
    data->DecRef();
    return NULL;
}

Character *ChatHandler::getSelectedChar()
{
    guid mguid;
    SMSG_MESSAGECHAT_t* data;

    Character *chr = m_pClient->getCurrentChar();
    mguid = chr->getSelection ();
    if (mguid.Assigned ())
    {
        if (mguid.type == 0)
            chr = WORLDSERVER.GetCharacter (mguid.sno);
        else
        {
            data = FillMessageData(0x09, m_pClient,(uint8*) "Please select a User.");
            m_pClient->SendMsg( &data );
            data.DecRef();
        }
    }
    else
    {
        data = FillMessageData (0x09, m_pClient,(uint8*) "AutoSelection.");
        m_pClient->SendMsg (&data);
        data->DecRef();
    }
    return chr;
}

//UINT32
int32 ChatHandler::TestValue(const float Value, const float max, const float min)
{
    if(Value<min || Value>max)
    {
        SMSG_MESSAGECHAT_t data = FillMessageData(0x09, m_pClient,(uint8*)"Invalid Value.");
        m_pClient->SendMsg( &data );
        data->DecRef();
        return 0;
    }
    return 1;
}

//FLOAT
int32 ChatHandler::TestValue(const uint32 Value, const uint32 max, const uint32 min)
{
    if(Value<min || Value>max)
    {
        SMSG_MESSAGECHAT_t data =  FillMessageData(0x09, m_pClient,(uint8*)"Invalid Value.");
        m_pClient->SendMsg( &data );
        data->DecRef();
        return 0;
    }
    return 1;
}

//FLOAT
void ChatHandler::ChangeSelectedCharMsg(const uint16 &index, const float Value, const float max, const float min, char * nom)
{
    NetworkPacket data;

    if(!TestValue(Value, max, min)) return;

    Character * pChar = getSelectedChar();
    if(pChar!=NULL)
    {
        data.Initialize( 12, index );
        data << pChar->getUpdateValue( OBJECT_FIELD_GUID );
        data << pChar->getUpdateValue( OBJECT_FIELD_GUID + 1 );
        data << Value;
        pChar->SendMessageToSet( &data, true );
        Message(pChar, nom, Value);
    }
    return;
}

//UINT32
void ChatHandler::ChangeSelectedCharMsg(const uint16 &index, const uint32 Value, const uint32 max, const uint32 min, char * nom)
{
    NetworkPacket data;

    if(!TestValue(Value, max, min)) return;

    Character * pChar = getSelectedChar();
    if(pChar!=NULL)
    {
        data.Initialize( 12, index );
        data << pChar->getUpdateValue( OBJECT_FIELD_GUID );
        data << pChar->getUpdateValue( OBJECT_FIELD_GUID + 1 );
        data << Value;
        pChar->SendMessageToSet( data, true );
        Message(pChar, nom, Value);
    }
    return;
}

//FLOAT
void ChatHandler::ChangeSelectedChar(const uint16 &index, const float Value, const float max, const float min, char * nom)
{
    if(!TestValue(Value, max, min)) return;

    Character * pChar = getSelectedChar();
    if(pChar!=NULL)
    {
        pChar->setUpdateFloatValue(index , Value);
        Message(pChar, nom, Value);
    }
    return;
}

//UINT32
void ChatHandler::ChangeSelectedChar(const uint16 &index, const uint32 Value, const uint32 max, const uint32 min, char * nom)
{
    if(!TestValue(Value, max, min)) return;

    Character * pChar = getSelectedChar();
    if(pChar!=NULL)
    {
        pChar->setUpdateValue(index , Value);
        Message(pChar, nom, Value);
    }
    return;
}

//FLOAT
void ChatHandler::Message(Character * pChar, char * nom, const float Value)
{
    SMSG_MESSAGECHAT_t* data;
    uint8 buf[256];

    if(strcmp(pChar->getName(),m_pClient->getCurrentChar()->getName())!=0)
    {
        // send message to user
        sprintf((char*)buf,"You change the %s to %2.2f of %s.", nom, Value, pChar->getName());
        data = FillMessageData(0x09, m_pClient, buf);
        m_pClient->SendMsg( data );
        data->DecRef();

        // send message to player
        sprintf((char*)buf,"%s changed your %s to %2.2f.", m_pClient->getCurrentChar()->getName(), nom, Value);
        data = FillMessageData(0x09, pChar->pClient, buf);
        pChar->pClient->SendMsg( data );
        data->DecRef();
    }
    else
    {
        // send message to user
        sprintf((char*)buf,"You change your %s to %2.2f.", nom, Value);
        data = FillMessageData(0x09, m_pClient, buf);
        m_pClient->SendMsg( data );
        data->DecRef();
    }
}

//UINT32
void ChatHandler::Message(Character * pChar, char * nom, const uint32 Value)
{
    SMSG_MESSAGECHAT_t* data;
    uint8 buf[256];

    if(strcmp(pChar->getName(),m_pClient->getCurrentChar()->getName())!=0)
    {
        // send message to user
        sprintf((char*)buf,"You change the %s to %i of %s.", nom, Value, pChar->getName());
        data = FillMessageData(0x09, m_pClient, buf);
        m_pClient->SendMsg( data );
        data->DecRef();

        // send message to player
        sprintf((char*)buf,"%s changed your %s to %i.", m_pClient->getCurrentChar()->getName(), nom, Value);
        data = FillMessageData(0x09, pChar->pClient, buf);
        pChar->pClient->SendMsg( data );
        data->DecRef();
    }
    else
    {
        // send message to user
        sprintf((char*)buf,"You change your %s to %i.", nom, Value);
        data = FillMessageData(0x09, m_pClient, buf);
        m_pClient->SendMsg( &data );
        data->DecRef();
    }
}

void ChatHandler::Message(Character * pChar, char * nom)
{
    NetworkPacket data;
    uint8 buf[256];

    if(strcmp(pChar->getName(),m_pClient->getCurrentChar()->getName())!=0)
    {
        // send message to user
        sprintf((char*)buf,"You %s %s.", nom, pChar->getName());
        data = FillMessageData(0x09, m_pClient, buf);
        m_pClient->SendMsg( data );
        data->DecRef();

        // send message to player
        sprintf((char*)buf,"%s %s you.", m_pClient->getCurrentChar()->getName(), nom);
        data = FillMessageData(0x09, pChar->pClient, buf);
        pChar->pClient->SendMsg( data );
        data->DecRef();
    }
    else
    {
        // send message to user
        sprintf((char*)buf,"You %s to you.", nom);
        data = FillMessageData(0x09, m_pClient, buf);
        m_pClient->SendMsg( data );
        data->DecRef();
    }
}

Unit * ChatHandler::getSelectedNPC()
{
    guid mguid;

    mguid = m_pClient->getCurrentChar()->getSelection ();
    if (mguid.Assigned ())
    {
        if (mguid.type == 0xF0001000)
            return WORLDSERVER.GetCreature (mguid.sno);
    }

    SMSG_MESSAGECHAT_t* data =  FillMessageData(0x09, m_pClient,(uint8*) "Please select a NPC");
    m_pClient->SendMsg( &data );
    data->DecRef();

    return NULL;
}

void ChatHandler::ChangeSelectedNPC(const uint16 &index, const uint32 Value, const uint32 max, const uint32 min)
{
    SMSG_MESSAGECHAT_t* data;

    if(!TestValue(Value, max, min)) return;

    Unit * pUnit = getSelectedNPC();
    if(pUnit!=NULL)
    {
        pUnit->setUpdateValue(index , Value);

        DatabaseInterface *dbi = DATABASE.createDatabaseInterface( );
        /*
           sprintf((char*)buf, "DELETE FROM creatures WHERE id=%u", pUnit->GetGUID());
           dbi->doQuery((char*)buf);
           dbi->saveCreature(pUnit);
           */
        dbi->updateCreature(pUnit);
        DATABASE.removeDatabaseInterface(dbi);
        pUnit->UpdateObject();

        data = FillMessageData(&data, 0x09, m_pClient,(uint8*)"NPC updated.");
        m_pClient->SendMsg( data );
    }
    return;
}

void ChatHandler::GenCreature(GameClient *pClient, uint32 StartId, uint32 EndId ,uint32 StepId )
{
    char* pName= "Def Name ";
    uint32 CurrentId=1;
    uint16 ModuloId=0;
    uint32 npcFlags=0;
    uint32 faction_id=0;
    uint32 level=10;
    NetworkPacket data;

    // Create the requested monster

    Character *chr = pClient->getCurrentChar();
    float x = chr->getPositionX();
    float y = chr->getPositionY();
    float z = chr->getPositionZ();
    float o = chr->getOrientation();

    for (CurrentId=StartId;CurrentId<=EndId;CurrentId++)
    {
        x+= (float) 5.0f;
        ModuloId++;
        if ( ModuloId>=StepId)
        {
            x-= (float) 5.0f *(float) ModuloId;
            ModuloId=0;
            y+= (float) 10.0f;
        }

        sprintf(pName,"Id:%i",CurrentId);

        Unit* pUnit = new Unit();
        UpdateMask unitMask;
        WorldServer::getSingletonPtr()->mObjectMgr.SetCreateUnitBits(unitMask);

        pUnit->Create(WORLDSERVER.m_hiCreatureGuid++, (uint8*)pName, x, y, z, o);
        pUnit->setMapId(chr->getMapId());
        pUnit->setZone(chr->getZone());
        data.Clear();
        pUnit->setUpdateValue(OBJECT_FIELD_ENTRY, WORLDSERVER.addCreatureName((uint8*)pUnit->getCreatureName()));
        pUnit->setUpdateFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
        pUnit->setUpdateValue(UNIT_FIELD_DISPLAYID, CurrentId);
        pUnit->setUpdateValue(UNIT_NPC_FLAGS , npcFlags);
        pUnit->setUpdateValue(UNIT_FIELD_FACTIONTEMPLATE , faction_id);
        //pUnit->setUpdateValue(UNIT_FIELD_HEALTH, 100 + 30*level);
        //pUnit->setUpdateValue(UNIT_FIELD_MAXHEALTH, 100 + 30*level);
        pUnit->setUpdateValue(UNIT_FIELD_HEALTH, (uint32)((1.24*(float)level*(float)level)+(1.79*(float)level)+40.64) );
        pUnit->setUpdateValue(UNIT_FIELD_MAXHEALTH, (uint32)((1.24*(float)level*(float)level)+(1.79*(float)level)+40.64) );

        pUnit->setUpdateValue(UNIT_FIELD_LEVEL , level);

        pUnit->setUpdateFloatValue(UNIT_FIELD_COMBATREACH , 1.5f);
        pUnit->setUpdateFloatValue(UNIT_FIELD_MAXDAMAGE ,  5.0f);
        pUnit->setUpdateFloatValue(UNIT_FIELD_MINDAMAGE , 8.0f);
        pUnit->setUpdateValue(UNIT_FIELD_BASEATTACKTIME, 1900);
        pUnit->setUpdateValue(UNIT_FIELD_BASEATTACKTIME+1, 2000);
        pUnit->setUpdateFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 2.0f);

        pUnit->CreateObject(&unitMask, &data, 0);

        //  add to the world list of creatures
        WPAssert (pUnit->GetGUID ().Assigned ());
        WORLDSERVER.mCreatures[pUnit->GetGUID().sno] = pUnit;

        // send create message to everyone
        WORLDSERVER.SendGlobalMessage(&data);

        DatabaseInterface *dbi = DATABASE.createDatabaseInterface( );
        char sql[512];
        sprintf(sql, "insert into skin set id_skin='%i',name='%s',type='0',race='0', gender='0'", CurrentId,pName);
        dbi->doQuery(sql);
        //dbi->saveCreature(pUnit);
        DATABASE.removeDatabaseInterface(dbi);
    }
}

ChatHandler* ChatHandler::ChatHandler()
{
    ChatCommands = ChatCommandsVector();
    LoadCommands();

}

// }ELECTRIX ADD END
