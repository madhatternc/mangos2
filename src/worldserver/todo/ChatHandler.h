/**
 *     \file  src/worldserver/todo/ChatHandler.h
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

#ifndef __CHAT_HANDLER_H__
#define __CHAT_HANDLER_H__
#include "Vector.h"

class GameClient;
class Character;
class Unit;
class ChatHandler;
class ChatCommandVector;

enum CHAT_AUTH_LEVEL
{
    AUTH_USER = 0,
    AUTH_GM = 1,
    AUTH_SPAWNER = 2,
    AUTH_ADMIN = 3
};

class ChatCommandVector : public Vector
{
    public:
        ChatCommandVector () : Vector (0, 4) {}
        virtual ~ChatCommandVector ();
};

DECLARE_VECTOR(ChatArguments, char *,);
IMPLEMENT_VECTOR(,ChatArguments, char *);

class ChatCommand
{
    public:
        ChatCommandVector Subcommands;
        const char *Name;
        uint16 SecurityLevel;
        uint16 MinArgs;
        bool (ChatHandler::*Handler) (uint8* args);
        std::string Help;

        ChatCommand* Parent;

        ChatCommand ()
        {
            Subcommands = ChatCommandVector();
        }
        ChatCommand (const char * nme, uint16 sl, uint16 ma,
            bool (ChatHandler::*hnd) (uint8* args),
            std::string hlp, ChatCommand *parent)
        {
            Subcommands = ChatCommandVector();
            setValues(nme, sl, ma, hnd, hlp, parent);
        }
        ~ChatCommand ()
        {
            Subcommands.DeleteAll();
        }

        void setValues (const char * nme, uint16 sl, uint16 ma,
            bool (ChatHandler::*hnd) (uint8* args),
            std::string hlp, ChatCommand *parent)
        {
            Name = nme;
            SecurityLevel = sl;
            Handler = hnd;
            Help = hlp;
            MinArgs = ma;
            if(parent != NULL)
            {
                Parent = parent;
                parent->Subcommands.Push(this);
            }
        };
};

class ChatHandler
{
    public:
        ChatHandler() {}
        ~ChatHandler() {}

        void HandleMsg( NetworkPacket & recv_data, GameClient *pClient );

        void FillMessageData (NetworkPacket *data, uint8 type, GameClient *pClient, uint8 *text );
        void SpawnCreature (GameClient *pClient, char* pName, uint32 display_id, uint32 npcFlags, uint32 faction_id, uint32 level);
        void smsg_NewWorld (GameClient *pClient, uint16 c, float x, float y, float z);
        void MovePlayer (GameClient *pClient, float x, float y, float z);

        bool Execute(ChatArguments *args);
        void RegisterCommand(ChatCommand *cCommand);
        bool ParseCommands(uint8* text, uint16 text_length);
        void LoadCommands (bool load);

    protected:

        bool hasStringAbbr(const char* s1, const char* s2);
        void SendMultilineMessage(const char *str);

        bool ExecuteCommandInTable(ChatCommand *table, uint8* text);
        bool ShowHelpForCommand(ChatCommand *table, const char* cmd);

        // Level 0 commands
        bool HandleHelpCommand(ChatArguments* args);
        bool HandleCommandsCommand(ChatArguments* args);
        bool HandleNYICommand(ChatArguments* args);
        bool HandleAcctCommand(ChatArguments* args);
        bool HandleGMLoginCommand(ChatArguments* args);
        bool HandleStartCommand(ChatArguments* args);
        bool HandleInfoCommand(ChatArguments* args);
        bool HandleMountCommand(ChatArguments* args);
        bool HandleDismountCommand(ChatArguments* args);
        bool HandleSaveCommand(ChatArguments* args);
        bool HandleGMListCommand(ChatArguments* args);
        bool HandleGMPassCommand(ChatArguments* args);

        // Level 1 commands
        bool HandleSummonCommand(ChatArguments* args);
        bool HandleAppearCommand(ChatArguments* args);
        bool HandleRecallCommand(ChatArguments* args);
        bool HandleAnnounceCommand(ChatArguments* args);
        bool HandleKickCommand(ChatArguments* args);
        bool HandleGMOnCommand(ChatArguments* args);
        bool HandleGMOffCommand(ChatArguments* args);
        bool HandleGPSCommand(ChatArguments* args);
        bool HandleSaveAllCommand(ChatArguments* args);

        bool HandleModifyHPCommand(ChatArguments* args);
        bool HandleModifyManaCommand(ChatArguments* args);
        bool HandleModifyLevelCommand(ChatArguments* args);
        bool HandleModifyGoldCommand(ChatArguments* args);
        bool HandleModifySpeedCommand(ChatArguments* args);
        bool HandleModifyScaleCommand(ChatArguments* args);
        bool HandleModifyMountCommand(ChatArguments* args);
        bool HandleModifyExpCommand(ChatArguments* args);
        bool HandleModifyWaterSpeedCommand(ChatArguments* args);

        // Level 2 commands
        bool HandleGUIDCommand(ChatArguments* args);
        bool HandleNameCommand(ChatArguments* args);
        bool HandleProgCommand(ChatArguments* args);
        bool HandleItemMoveCommand(ChatArguments* args);
        bool HandleSpawnCommand(ChatArguments* args);
        bool HandleDeleteCommand(ChatArguments* args);
        bool HandleSpellCommand(ChatArguments* args);
        bool HandleSpawnTaxiCommand(ChatArguments* args);
        bool HandleItemCommand(ChatArguments* args);
        bool HandleAddMoveCommand(ChatArguments* args);
        bool HandleRandomCommand(ChatArguments* args);
        bool HandleRunCommand(ChatArguments* args);
        bool HandleChangeLevelCommand(ChatArguments* args);
        bool HandleNPCFlagCommand(ChatArguments* args);
        bool HandleDisplayIdCommand(ChatArguments* args);
        bool HandleFactionIdCommand(ChatArguments* args);
        bool HandleRemoveSpellCommand(ChatArguments* args);
        bool HandleRemoveItemCommand(ChatArguments* args);
        bool HandleAggressiveCommand(ChatArguments* args);

        // Level 3 commands
        bool HandleSecurityCommand(ChatArguments* args);
        bool HandleWorldPortCommand(ChatArguments* args);
        bool HandleAddSpiritCommand(ChatArguments* args);
        bool HandleMoveCommand(ChatArguments* args);
        bool HandleLearnCommand(ChatArguments* args);
        bool HandleAnimFreqCommand(ChatArguments* args);
        bool HandleStandStateCommand(ChatArguments* args);
        bool HandleDieCommand(ChatArguments* args);
        bool HandleMorphCommand(ChatArguments* args);
        bool HandleAuraCommand(ChatArguments* args);
        bool HandleUnBanCommand(ChatArguments* args);
        bool HandleBanCommand(ChatArguments* args);
        bool HandleUpdateCommand(ChatArguments* args);
        bool HandleIsleCommand(ChatArguments* args);

        int32 TestValue(const float Value, const float max, const float min);
        int32 TestValue(const uint32 Value, const uint32 max, const uint32 min);
        void ChangeSelectedChar(const uint16 &index, const uint32 Value, const uint32 max, const uint32 min, char * nom);
        void ChangeSelectedChar(const uint16 &index, const float Value, const float max, const float min, char * nom);
        void ChangeSelectedCharMsg(const uint16 &index, const float Value, const float max, const float min, char * nom);
        void ChangeSelectedCharMsg(const uint16 &index, const uint32 Value, const uint32 max, const uint32 min, char * nom);
        void Message(Character * pChar, char * nom, const float Value);
        void Message(Character * pChar, char * nom, const uint32 Value);
        void Message(Character * pChar, char * nom);

        Character * getCurrentCharByName(uint8 * pName);
        Character * getSelectedChar();

        Unit * getSelectedNPC();
        void ChangeSelectedNPC(const uint16 &index, const uint32 Value, const uint32 max, const uint32 min);

                                                            //ELECTRIX ADD
        void GenCreature (GameClient *pClient, uint32 StartId, uint32 EndId , uint32 StepId );
        GameClient *m_pClient;

        ChatCommandVector* ChatCommands;
};
#endif // __CHAT_HANDLER_H__
