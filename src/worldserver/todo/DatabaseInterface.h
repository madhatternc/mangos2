/**
 *     \file  src/worldserver/todo/DatabaseInterface.h
 *    \brief  Provides a basic interface to fixed SQL data.
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

#ifndef __DATABASE_INTERFACE_H__
#define __DATABASE_INTERFACE_H__

#include "Common.h"
#include "Spell.h"
#include "AreaTrigger.h"
#include "MiscHandler.h"

class Database;
class Unit;
class Character;
class Path;
class ChatCommand;
class NetworkPacket;

class DatabaseInterface
{
    /// The database object
    Database *db;

    public:
        DatabaseInterface (Database *idb);
        ~DatabaseInterface ();

        int doQuery (const char * query);
        uint64 doQueryId (const char * query);
        int IsNameTaken(char * charname);
        int GetNameGUID(char * charname);
        bool GetPlayerNameFromGUID(uint32 guid, uint8 *name);
        void addCharacter (Character * newChar);
        std::set< Character * > enumCharacters (int account_id);
        void removeCharacter (Character * newChar);
        void setCharacter (Character * diffChar);
        void setHighestGuids();

        uint32 getGlobalTaxiNodeMask (uint32 curloc);

        uint32 getPath (uint32 source, uint32 destination);
        void getPathNodes (uint32 path, Path *pathnodes);
        uint32 getNearestTaxiNode (float x, float y, float z, uint16 continent);

                                                            //Area Trigger stuff
        AreaTrigger *getAreaTriggerInformation(uint32 AreaTriggerID);

                                                            //load spells for this Trainer
        void getTrainerSpells (Character * pChar, guid trainer, NetworkPacket & data);
        //int getTrainerSpellsCount (guid Trainer); //count how many spells a given trainer has
                                                            //get the price for a specific spell
        int getTrainerSpellsPrice (guid Spell, guid trainer);
                                                            //add spells to trainer
        int addTrainerSpell (guid Trainer, guid Spell, uint32 SpellPrice);

        void updateCreature(Unit *pUnit);
        void saveCreature(Unit *pUnit);
        std::set< Unit * > loadCreatures();
        void loadCreatureNames(std::map< uint32, uint8*> & p_names);
        void saveCreatureNames(std::map< uint32, uint8*> p_names);
        void spawnSpiritHealers ();
        bool isSpiritHealer(uint32 guid);
        void getClosestSpiritHealer(float &x, float &y, float &z, uint16 &mapID);

        void loadItems();

        void loadQuests();                                  // load the quests into QuestHandler
        void loadQuestStatus(Character *pChar);             // load quest progress for this character
        void saveQuestStatus(Character *pChar);             // save quest progress for this character

        //gossip stuff//////
        void loadTextRelation();
        void loadNPCText();
        void loadTextOptions();
        ////////////////////

        int Login(char* username, char* ip);
        int getAccountLvl(int account_id);
        char * getAccountPass(int account_id);

        int IsCharMoveExist(uint32 guid);
        /*
         ///////////////////////////// NIMROD //////////////////////////////////////
         int addUserGuild(char *member, char *leader); // adds a user to a clan -- agrega a un wn al clan
         int addNewGuild(char *lider, char *nombre, char *motd); // agrega un clan // adds a guild
         char* getGuildMotd(char* usuario); //get motd -- saca el mensaje del dia
         int setGuildMotd(char *lider, char *mensaje); // set new guild motd -- pone nuevo motd
         int removeUserGuild(char *member, char *leader); // remove an user from the guild -- saca a 1 user del clan
         int disbandGuild(char *leader); // disband the guild -- desarma el clan
         int setGuildRank(char *leader, char *member, int rank); // gives a rank to a user -- da ranking a un wn
         /////////////////////////////// END NIMROD /////////////////////////////////////////
         */

        void Get_Spell_Information (uint32 spellid, SpellInformation &SpellInfo);
        SpellInformation GetSpellInformation (uint32 spellid);
        void OutputLog (char *fCaller, char *fInformation);
        uint32 NULLToNumeric (const char *input);

        SocialData* getFriendList(uint32 guid);
        void AddFriend(uint32 guid, uint32 friendid, char *charname);
        void RemoveFriend(uint32 guid, uint32 friendid);

        void loadTalents();

        void loadChatCommand(const char *name, ChatCommand * cmd);

};
#endif                                                      // __DATABASE_INTERFACE_H__
