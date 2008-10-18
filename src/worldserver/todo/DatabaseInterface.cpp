/**
 *     \file  src/worldserver/todo/DatabaseInterface.cpp
 *    \brief  Provides a basic interface to fixed SQL data.
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

//#include <mysql.h>
#include "DatabaseInterface.h"
#include "Sockets.h"
#include "Character.h"
#include "Log.h"
#include "Errors.h"
#include "Path.h"
#include "Quest.h"
#include "Gossip.h"
#include "UpdateFields.h"
#include "WorldServer.h"
#include "Item.h"
#include "Database.h"
#include "ChatHandler.h"

#include "Opcodes.h"                                        //added for new trainer code

DatabaseInterface::DatabaseInterface (Database *idb)
{
    (db = idb)->IncRef ();
}

DatabaseInterface::~DatabaseInterface ()
{
    db->DecRef ();
}

SpellInformation DatabaseInterface::GetSpellInformation (uint32 spellid)
{
    SpellInformation spellinfo;
    Get_Spell_Information (spellid, spellinfo);
    return spellinfo;
}

void DatabaseInterface::Get_Spell_Information (uint32 spellid, SpellInformation &SpellInfo)
{
    //let's go over how the method works:
    //  1) spellid is a numeric value of the spell the user wants
    //  2) SpellInfo is the info that is returned to the calling function
    //  3) We build up a SQL query:
    //  a) "SELECT * FROM spells s WHERE 'Spell Id' = spellid;"
    //  b) run query
    //  4) Store the result in the data structure from (2)
    //  5) Clean up used database resources
    DatabaseExecutor* dbex = db->GetExecutor();

    if (dbex->ExecuteF( "SELECT * FROM spells WHERE ID=%i", spellid ) != dbeOk)
        break;                                              // failure ...

    // Get the results of the query
    while (dbex->NextRow ())
    {
        //Storing data in struct (SpellInformation)

        SpellInfo.Id = NULLToNumeric (dbex->Get(0));
        SpellInfo.School = NULLToNumeric (dbex->Get(1));
        SpellInfo.C = NULLToNumeric (dbex->Get(2));
        SpellInfo.D = NULLToNumeric (dbex->Get(3));
        SpellInfo.E = NULLToNumeric (dbex->Get(4));
        SpellInfo.F = NULLToNumeric (dbex->Get(5));
        SpellInfo.G = NULLToNumeric (dbex->Get(6));
        SpellInfo.H = NULLToNumeric (dbex->Get(7));
        SpellInfo.I = NULLToNumeric (dbex->Get(8));
        SpellInfo.J = NULLToNumeric (dbex->Get(9));
        SpellInfo.K = NULLToNumeric (dbex->Get(10));

        // row 0 - 10 stored

        SpellInfo.L = NULLToNumeric (dbex->Get(11));
        SpellInfo.M = NULLToNumeric (dbex->Get(12));
        SpellInfo.N = NULLToNumeric (dbex->Get(13));
        SpellInfo.CastTime = NULLToNumeric (dbex->Get(14));
        SpellInfo.P = NULLToNumeric (dbex->Get(15));
        SpellInfo.CoolDown = NULLToNumeric (dbex->Get(16));
        SpellInfo.R = NULLToNumeric (dbex->Get(17));
        SpellInfo.S = NULLToNumeric (dbex->Get(18));
        SpellInfo.T = NULLToNumeric (dbex->Get(19));
        SpellInfo.U = NULLToNumeric (dbex->Get(20));

        // row 11 - 20 stored

        SpellInfo.V = NULLToNumeric (dbex->Get(21));
        SpellInfo.W = NULLToNumeric (dbex->Get(22));
        SpellInfo.X = NULLToNumeric (dbex->Get(23));
        SpellInfo.PlayerLevel = NULLToNumeric (dbex->Get(24));
        SpellInfo.MaxLevel = NULLToNumeric (dbex->Get(25));
        SpellInfo.Duration = NULLToNumeric (dbex->Get(26));
        SpellInfo.PowerType = NULLToNumeric (dbex->Get(27));
        SpellInfo.ManaCost = NULLToNumeric (dbex->Get(28));
        SpellInfo.ManaCostPerLevel = NULLToNumeric (dbex->Get(29));
        SpellInfo.AE = NULLToNumeric (dbex->Get(30));

        // row 21 - 30 stored

        SpellInfo.AF = NULLToNumeric (dbex->Get(31));
        SpellInfo.Range = NULLToNumeric (dbex->Get(32));
        SpellInfo.AH = NULLToNumeric (dbex->Get(33));
        SpellInfo.AI = NULLToNumeric (dbex->Get(34));
        SpellInfo.AJ = NULLToNumeric (dbex->Get(35));
        SpellInfo.AK = NULLToNumeric (dbex->Get(36));
        SpellInfo.AL = NULLToNumeric (dbex->Get(37));
        SpellInfo.AM = NULLToNumeric (dbex->Get(38));
        SpellInfo.AN = NULLToNumeric (dbex->Get(39));
        SpellInfo.AO = NULLToNumeric (dbex->Get(40));

        // row 31 - 40 stored

        SpellInfo.AP = NULLToNumeric (dbex->Get(41));
        SpellInfo.AQ = NULLToNumeric (dbex->Get(42));
        SpellInfo.AR = NULLToNumeric (dbex->Get(43));
        SpellInfo.AS = NULLToNumeric (dbex->Get(44));
        SpellInfo.AT = NULLToNumeric (dbex->Get(45));
        SpellInfo.AU = NULLToNumeric (dbex->Get(46));
        SpellInfo.AV = NULLToNumeric (dbex->Get(47));
        SpellInfo.AW = NULLToNumeric (dbex->Get(48));
        SpellInfo.AX = NULLToNumeric (dbex->Get(49));
        SpellInfo.AY = NULLToNumeric (dbex->Get(50));

        // row 41 - 50 stored

        SpellInfo.AZ = NULLToNumeric (dbex->Get(51));
        SpellInfo.BA = NULLToNumeric (dbex->Get(52));
        SpellInfo.BB = NULLToNumeric (dbex->Get(53));
        SpellInfo.BC = NULLToNumeric (dbex->Get(54));
        SpellInfo.BD = NULLToNumeric (dbex->Get(55));
        SpellInfo.BE = NULLToNumeric (dbex->Get(56));
        SpellInfo.BF = NULLToNumeric (dbex->Get(57));
        SpellInfo.BG = NULLToNumeric (dbex->Get(58));
        SpellInfo.RandomPercentDmg = NULLToNumeric (dbex->Get(59));
        SpellInfo.BI = NULLToNumeric (dbex->Get(60));

        // row 51 - 60 stored

        SpellInfo.BJ = NULLToNumeric (dbex->Get(61));
        SpellInfo.BK = NULLToNumeric (dbex->Get(62));
        SpellInfo.BL = NULLToNumeric (dbex->Get(63));
        SpellInfo.BM = NULLToNumeric (dbex->Get(64));
        SpellInfo.BN = NULLToNumeric (dbex->Get(65));
        SpellInfo.BO = NULLToNumeric (dbex->Get(66));
        SpellInfo.BP = NULLToNumeric (dbex->Get(67));
        SpellInfo.Speed = NULLToNumeric (dbex->Get(68));
        SpellInfo.BR = NULLToNumeric (dbex->Get(69));
        SpellInfo.BS = NULLToNumeric (dbex->Get(70));

        // row 61 - 70 stored

        SpellInfo.DmgPlus1 = NULLToNumeric (dbex->Get(71));
        SpellInfo.BU = NULLToNumeric (dbex->Get(72));
        SpellInfo.BV = NULLToNumeric (dbex->Get(73));
        SpellInfo.BW = NULLToNumeric (dbex->Get(74));
        SpellInfo.BX = NULLToNumeric (dbex->Get(75));
        SpellInfo.BY = NULLToNumeric (dbex->Get(76));
        SpellInfo.BZ = NULLToNumeric (dbex->Get(77));
        SpellInfo.CA = NULLToNumeric (dbex->Get(78));
        SpellInfo.CB = NULLToNumeric (dbex->Get(79));
        SpellInfo.CC = NULLToNumeric (dbex->Get(80));

        // row 71 - 80 stored

        SpellInfo.Radius = NULLToNumeric (dbex->Get(81));
        SpellInfo.CE = NULLToNumeric (dbex->Get(82));
        SpellInfo.CF = NULLToNumeric (dbex->Get(83));
        SpellInfo.CG = NULLToNumeric (dbex->Get(84));
        SpellInfo.CH = NULLToNumeric (dbex->Get(85));
        SpellInfo.CI = NULLToNumeric (dbex->Get(86));
        SpellInfo.CJ = NULLToNumeric (dbex->Get(87));
        SpellInfo.CK = NULLToNumeric (dbex->Get(88));
        SpellInfo.CL = NULLToNumeric (dbex->Get(89));
        SpellInfo.CM = NULLToNumeric (dbex->Get(90));

        // row 81 - 90 stored

        SpellInfo.CN = NULLToNumeric (dbex->Get(91));
        SpellInfo.CO = NULLToNumeric (dbex->Get(92));
        SpellInfo.CP = NULLToNumeric (dbex->Get(93));
        SpellInfo.CQ = NULLToNumeric (dbex->Get(94));
        SpellInfo.CR = NULLToNumeric (dbex->Get(95));
        SpellInfo.CS = NULLToNumeric (dbex->Get(96));
        SpellInfo.CT = NULLToNumeric (dbex->Get(97));
        SpellInfo.CU = NULLToNumeric (dbex->Get(98));
        SpellInfo.CV = NULLToNumeric (dbex->Get(99));
        SpellInfo.CW = NULLToNumeric (dbex->Get(100));

        // row 91 - 100 stored

        SpellInfo.CX = NULLToNumeric (dbex->Get(101));
        SpellInfo.CY = NULLToNumeric (dbex->Get(102));
        SpellInfo.CZ = NULLToNumeric (dbex->Get(103));
        SpellInfo.DA = NULLToNumeric (dbex->Get(104));
        SpellInfo.DB = NULLToNumeric (dbex->Get(105));
        SpellInfo.DC = NULLToNumeric (dbex->Get(106));
        SpellInfo.DD = NULLToNumeric (dbex->Get(107));
        SpellInfo.DE = NULLToNumeric (dbex->Get(108));
        SpellInfo.DF = NULLToNumeric (dbex->Get(109));
        SpellInfo.DG = NULLToNumeric (dbex->Get(110));

        // row 101 - 110 stored

        SpellInfo.Name = (char *) (dbex->Get(111));         //char *Name
        SpellInfo.DI = NULLToNumeric (dbex->Get(112));
        SpellInfo.DJ = NULLToNumeric (dbex->Get(113));
        SpellInfo.DK = NULLToNumeric (dbex->Get(114));
        SpellInfo.DL = NULLToNumeric (dbex->Get(115));
        SpellInfo.DM = NULLToNumeric (dbex->Get(116));
        SpellInfo.DN = NULLToNumeric (dbex->Get(117));
        SpellInfo.DO = NULLToNumeric (dbex->Get(118));
        SpellInfo.DP = NULLToNumeric (dbex->Get(119));
        SpellInfo.Rank = (char*) (dbex->Get(120));          //char *Rank

        // row 111 - 120 stored

        SpellInfo.DR = NULLToNumeric (dbex->Get(121));
        SpellInfo.DS = NULLToNumeric (dbex->Get(122));
        SpellInfo.DT = NULLToNumeric (dbex->Get(123));
        SpellInfo.DU = NULLToNumeric (dbex->Get(124));
        SpellInfo.DV = NULLToNumeric (dbex->Get(125));
        SpellInfo.DW = NULLToNumeric (dbex->Get(126));
        SpellInfo.DX = NULLToNumeric (dbex->Get(127));
        SpellInfo.DY = NULLToNumeric (dbex->Get(128));
        SpellInfo.Description = (char*) (dbex->Get(129));   //char *Description
        SpellInfo.EA = NULLToNumeric (dbex->Get(130));

        // row 121 - 130 stored

        SpellInfo.EB = NULLToNumeric (dbex->Get(131));
        SpellInfo.EC = NULLToNumeric (dbex->Get(132));
        SpellInfo.ED = NULLToNumeric (dbex->Get(133));
        SpellInfo.EE = NULLToNumeric (dbex->Get(134));
        SpellInfo.EF = NULLToNumeric (dbex->Get(135));
        SpellInfo.EG = NULLToNumeric (dbex->Get(136));
        SpellInfo.EH = NULLToNumeric (dbex->Get(137));
        SpellInfo.EI = (char*) (dbex->Get(138));
        SpellInfo.EJ = NULLToNumeric (dbex->Get(139));
        SpellInfo.EK = NULLToNumeric (dbex->Get(140));

        // row 131 - 140 stored

        SpellInfo.EL = NULLToNumeric (dbex->Get(141));
        SpellInfo.EM = NULLToNumeric (dbex->Get(142));
        SpellInfo.EN = NULLToNumeric (dbex->Get(143));
        SpellInfo.EO = NULLToNumeric (dbex->Get(144));
        SpellInfo.EP = NULLToNumeric (dbex->Get(145));
        SpellInfo.EQ = NULLToNumeric (dbex->Get(146));
        SpellInfo.ER = NULLToNumeric (dbex->Get(147));
        SpellInfo.ES = NULLToNumeric (dbex->Get(148));
        SpellInfo.SpellId = NULLToNumeric (dbex->Get(149));
        SpellInfo.spell_type = NULLToNumeric (dbex->Get(150));
        SpellInfo.replenish_type = NULLToNumeric (dbex->Get(151));
        SpellInfo.addDuration = NULLToNumeric (dbex->Get(152));
        SpellInfo.addDmg = NULLToNumeric (dbex->Get(153));
        SpellInfo.race = NULLToNumeric (dbex->Get(154));

        // row 141 - 154 stored
    }

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);
}

uint32 DatabaseInterface::NULLToNumeric (const char *input)
{
    uint32 result;
    result = uint32((uint32)atof (input));
    //OutputLog ("NULLToNumeric", (char *)input);
    for (int i=0;i<(int)strlen(input);i++)
    {
        if(input[i] == 0)
        {
            //OutputLog ("NULLToNumeric", "An empty value was found!");
            result = 0;
            break;
        }
    }
    return result;
}

void DatabaseInterface::spawnSpiritHealers ()
{
    //std::stringstream Q;
    Unit* pUnit;
    UpdateMask unitMask;
    NetworkPacket data;

    DatabaseExecutor* dbex = db->GetExecutor();

    if (dbex->Execute( "SELECT X,Y,Z,F,name_id,mapId,zoneId,faction_id FROM spirithealers" ) != dbeOk)
        break;                                              // failure ...

    //Q << "select X,Y,Z,F,name_id,mapId,zoneId,faction_id from spirithealers";
    //doQuery (Q.str ().c_str ());
    //MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
    //MYSQL_ROW row;
    //uint32 name;
    //while ((row = mysql_fetch_row (res)))

    // Get the results of the query
    while (dbex->NextRow ())
    {
        pUnit = new Unit();
        WorldServer::getSingletonPtr()->mObjectMgr.SetCreateUnitBits(unitMask);
        name = atoi(dbex->Get(4));
        //printf("%s name is %d\n",row[4],name);
        pUnit->setMapId(atoi(dbex->Get(5)));
        pUnit->setZone(atoi(dbex->Get(6)));
        //data.Clear();
        pUnit->setUpdateValue(OBJECT_FIELD_ENTRY, name);
        pUnit->setUpdateFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
        pUnit->setUpdateValue(UNIT_FIELD_DISPLAYID, 5233);
        pUnit->setUpdateValue(UNIT_NPC_FLAGS , 1);
        pUnit->setUpdateValue(UNIT_FIELD_FACTIONTEMPLATE , atoi(dbex->Get(7)));
        pUnit->setUpdateValue(UNIT_FIELD_HEALTH, 100 + 30*(60));
        pUnit->setUpdateValue(UNIT_FIELD_MAXHEALTH, 100 + 30*(60));
        pUnit->setUpdateValue(UNIT_FIELD_LEVEL , 60);
        pUnit->setUpdateFloatValue(UNIT_FIELD_COMBATREACH , 1.5f);
        pUnit->setUpdateFloatValue(UNIT_FIELD_MAXDAMAGE ,  5.0f);
        pUnit->setUpdateFloatValue(UNIT_FIELD_MINDAMAGE , 8.0f);
        pUnit->setUpdateValue(UNIT_FIELD_BASEATTACKTIME, 1900);
        pUnit->setUpdateValue(UNIT_FIELD_BASEATTACKTIME+1, 2000);
        pUnit->setUpdateFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 2.0f);

        uint8 *sname = WORLDSERVER.getCreatureName (name);
        if (!sname) sname = (uint8 *)"ERROR_NO_CREATURENAME_FOR_ENTRY";

        pUnit->Create(WorldServer::getSingletonPtr()->m_hiCreatureGuid++, sname,
            atof(dbex->Get(0)), atof(dbex->Get(1)), atof(dbex->Get(2)), atof(dbex->Get(3)));

        pUnit->CreateObject(&unitMask, &data, 0);

        // add to the world list of creatures
        WPAssert (pUnit->GetGUID ().Assigned ());
        WorldServer::getSingletonPtr()->addCreature(pUnit);

        // send create message to everyone
        WorldServer::getSingletonPtr()->SendGlobalMessage(&data);
        saveCreature(pUnit);
    }
    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);
}

uint32 DatabaseInterface::getGlobalTaxiNodeMask (uint32 curloc)
{

    DatabaseExecutor* dbex = db->GetExecutor();
    if (dbex->ExecuteF( "SELECT taxipath.destination FROM taxipath WHERE (taxipath.source = %s)", curloc ) != dbeOk)
        break;                                              // failure ...

    //std::stringstream TaxiMask;
    //TaxiMask << "SELECT taxipath.destination FROM taxipath WHERE ( (taxipath.source =" << curloc << "))";
    //doQuery (TaxiMask.str ().c_str ());
    //MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
    //MYSQL_ROW row;
    uint32 mask = 0;

    //while ((row = mysql_fetch_row (res)))

    // Get the results of the query
    while (dbex->NextRow ())
        mask |= 1 << (atoi(dbex->Get(0)) - 1);

    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);

    return mask;
}

AreaTrigger *DatabaseInterface::getAreaTriggerInformation(uint32 AreaTriggerID)
{

    DatabaseExecutor* dbex = db->GetExecutor();
    if (dbex->ExecuteF( "SELECT * FROM areatriggers WHERE AreaTriggerID= %s", AreaTriggerID ) != dbeOk)
        break;                                              // failure ...

    //std::stringstream areatrig;
    //areatrig << "SELECT * FROM areatriggers WHERE AreaTriggerID=" << AreaTriggerID ;
    //doQuery (areatrig.str ().c_str ());
    //MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
    //MYSQL_ROW row;

    AreaTrigger * tmpTrigger = new AreaTrigger;

    //while ((row = mysql_fetch_row (res)))

    // Get the results of the query
    while (dbex->NextRow ())
    {
        tmpTrigger->m_AreaTriggerID = atol(dbex->Get(0));
        tmpTrigger->m_MapID = atol(dbex->Get(1));
        tmpTrigger->m_X = atof(dbex->Get(2));
        tmpTrigger->m_Y = atof(dbex->Get(3));
        tmpTrigger->m_Z = atof(dbex->Get(4));
        tmpTrigger->m_O = atof(dbex->Get(5));
        tmpTrigger->m_TargetTriggerID = atol(dbex->Get(6));
    }
    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);

    return tmpTrigger;
}

uint32 DatabaseInterface::getNearestTaxiNode (float x, float y, float z, uint16 continent)
{

    DatabaseExecutor* dbex = db->GetExecutor();
    if (dbex->ExecuteF( "SELECT DISTINCT taxinodes.id, taxinodes.x, taxinodes.y, taxinodes.z FROM taxipath"
        "INNER JOIN taxinodes ON (taxipath.source = taxinodes.ID),  taxipathnodes WHERE"
        " ((taxipathnodes.continent = %i)AND (taxipathnodes.index = 0) AND (taxipathnodes.path"
        " = taxipath.id))", continent ) != dbeOk)
        break;                                              // failure ...

    //std::stringstream Q;
    //Q << " SELECT DISTINCT taxinodes.id, taxinodes.x, taxinodes.y, taxinodes.z FROM taxipath "
    //  " INNER JOIN taxinodes ON (taxipath.source = taxinodes.ID),  taxipathnodes "
    //  " WHERE       ((taxipathnodes.continent = "
    //  << continent << ")    and   (taxipathnodes.index = 0)    and    (taxipathnodes.path = taxipath.id)  ) ";
    //doQuery (Q.str ().c_str ());
    uint32 nearest = 0;
    float distance = -1;
    float nx, ny, nz, nd;
    //MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
    //MYSQL_ROW row;
    //while ((row = mysql_fetch_row (res)))
    // Get the results of the query
    while (dbex->NextRow ())
    {
        nx = float (atof(dbex->Get(1))) - x;
        ny = float (atof(dbex->Get(2))) - y;
        nz = float (atof(dbex->Get(3))) - z;
        nd = nx * nx + ny * ny + nz * nz;
        if (nd < distance || distance < 0)
        {
            distance = nd;
            nearest = atoi(dbex->Get(0));
        }
    }
    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);

    return nearest;
}

uint32 DatabaseInterface::getPath (uint32 source, uint32 destination)
{

    DatabaseExecutor* dbex = db->GetExecutor();
    if (dbex->ExecuteF( "SELECT ID FROM taxipath WHERE source = %i AND destination"
        " = %i", source, destination ) != dbeOk)
        break;                                              // failure ...

    /*std::stringstream ss;
    ss << " select ID from taxipath "
        << " where source = " << source
        << " and destination = " << destination;
    doQuery (ss.str ().c_str ());
    MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
    */

    // Get the results of the query
    while (dbex->NextRow ())
    {
        uint32 path = atoi(dbex->Get(0));
    }
    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);

    return path;
}

void DatabaseInterface::getPathNodes (uint32 path, Path *pathnodes)
{

    DatabaseExecutor* dbex = db->GetExecutor();
    if (dbex->ExecuteF ( "SELECT X,Y,Z FROM taxipathnodes WHERE path = %i ORDER BY 'index'", path ) != dbeOk)
        break;                                              // failure ...

    /*
    std::stringstream ss;
    ss << " SELECT X,Y,Z FROM taxipathnodes where path = "
        << path << " order by 'index' ";
    doQuery (ss.str ().c_str ());
    MYSQL_RES *res = mysql_store_result ((MYSQL *)mDatabaseConnection);

    uint16 numrows = (uint16)mysql_num_rows (res);
    */
    int NumRows = dbex->NumRows();
    pathnodes->setLength ((uint16)NumRows);
    //MYSQL_ROW row;
    //uint16 count = 0;
    while (dbex->NextRow ())
    {
        //for (uint32 a = 0; a < numrows; a++) {
        //  row = mysql_fetch_row (res);
        pathnodes->getNodes ()[ count ].x = (float)atof (dbex->Get(0));
        pathnodes->getNodes ()[ count ].y = (float)atof (dbex->Get(1));
        pathnodes->getNodes ()[ count ].z = (float)atof (dbex->Get(2));
        //count++

    }
    //pathnodes->setLength (NumRows);
    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);

}

/* //no longer needed was using way to much cpu time for my likeing - gb
int DatabaseInterface::getTrainerSpellsCount (guid Trainer)
{
    int answer;
    std::stringstream ss;
    ss << " select COUNT(*) as spellcount from trainers t INNER JOIN spells s ON t.spellGuid = s.ID where t.trainerGuid = "
        << Trainer.sno << " order by t.spellGuid ";
    doQuery (ss.str ().c_str ());
    MYSQL_RES *res = mysql_store_result ((MYSQL *)mDatabaseConnection);
    MYSQL_ROW row;
    row = mysql_fetch_row (res);
    if (row == NULL)
        answer = 0;
    else
    {
        answer = (int)atof (row[0]);
        //answer = 1;
    }
    mysql_free_result (res);
    return answer;
}
*/

int DatabaseInterface::getTrainerSpellsPrice (guid Spell, guid Trainer)
{
    int answer = 99999;
    DatabaseExecutor* dbex = db->GetExecutor();
    if (dbex->ExecuteF( "SELECT t.price FROM trainers t WHERE t.trainerGuid = %i"
        "AND t.spellGuid = %i ORDER BY t.spellGuid", Trainer.sno, Spell.sno) != dbeOk)
        break;                                              // failure ...

    //std::stringstream ss;
    //ss << " select t.price from trainers t where t.trainerGuid = "
    //  << Trainer.sno << " and t.spellGuid = "
    //  << Spell.sno << " order by t.spellGuid ";
    // select t.price from trainers where t.trainerGuid = <trainerGuid> and t.spellGuid = <spellGuid>
    //doQuery (ss.str ().c_str ());
    //MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
    //uint16 numrows = (uint16)mysql_num_rows (res);
    //MYSQL_ROW row;
    while (dbex->NextRow ())
    {
        //for (uint32 a = 0; a < numrows; a++)
        //{
        //row = mysql_fetch_row (res);
        answer = int (atol(dbex->Get(0));                   //set price
    }
    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);

        return answer;
}

int DatabaseInterface::addTrainerSpell (guid Trainer, guid Spell, uint32 iSpellPrice)
{
    DatabaseExecutor* dbex = db->GetExecutor();
        if (dbex->ExecuteF( "INSERT INTO trainers (`trainerGuid`, `spellGuid`, `price`) VALUES ('%u', '%u', '%u');",
        Trainer.sno, Spell.sno, iSpellPrice) != dbeOk)
        break;                                              // failure ...

    //char sql[512];
    //sprintf (sql, "INSERT INTO trainers (`trainerGuid`, `spellGuid`, `price`) VALUES ('%u', '%u', '%u');",
    //   Trainer.sno, Spell.sno, iSpellPrice);
    //doQuery (sql);
    //MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
    /*MYSQL_ROW row;
     row = mysql_fetch_row (res);
     if (row == NULL) {
     answer = 0;
     }
     else {
     answer = 1;
     }*/
    //mysql_free_result (res);

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
        db->PutExecutor (dbex);
        return 0;                                           //answer;
}

void DatabaseInterface::getTrainerSpells (Character * pChar, guid Trainer, NetworkPacket & data)
{
    //the whole packets built in here now :D
    uint32 Price;

        uint32 player_level, player_gold, count;

    //get Players level and gold
        player_level = pChar->getUpdateValue( UNIT_FIELD_LEVEL );
        player_gold = pChar->getUpdateValue( PLAYER_FIELD_COINAGE );

    //Get the list of spells
        DatabaseExecutor* dbex = db->GetExecutor();
        if (dbex->ExecuteF( "SELECT * FROM trainers t INNER JOIN spells s ON t.spellGuid = s.ID"
        "WHERE t.trainerGuid = %i ORDER BY t.spellGuid",Trainer.sno ) != dbeOk)
        break;                                              // failure ...

    //std::stringstream spellslist;
    //spellslist << "SELECT * FROM trainers t INNER JOIN spells s ON t.spellGuid = s.ID WHERE t.trainerGuid = " << Trainer.sno << " ORDER BY t.spellGuid ";
    //doQuery( spellslist.str( ).c_str( ) );

    //MYSQL_RES *result = mysql_store_result( (MYSQL *)mDatabaseConnection );
    //uint32 numrows = (uint32)mysql_num_rows( result );
    //MYSQL_ROW row;
        int NumRows = dbex->NumRows();

        data.Initialize( (38*NumRows)+48, SMSG_TRAINER_LIST );//set packet size
        data << Trainer.sno << Trainer.type;
        data << uint32(0);
        data << ((uint32)NumRows);                          //Count of all spells
    //for( count = 0; count < NumRows; count++ ) // go through every Spell
        while (dbex->NextRow ())                            // go through every Spell
    {
        //row = mysql_fetch_row( result ); // get current spell
        data << ((uint32)(atof(dbex->Get(1))));             //spell id

        /*
        //needs to change but will do for now
        Price = (100*((uint32)(atof(row[ 27 ])))) + ((uint32)(atof(row[ 2 ]))); //+ price
        if(Price < 100)
        Price += 100;
        */
            Price = 0;                                      // Temp Price Fix while we don't have money

            if( (pChar->isAllreadyLearned( (uint32 (atof(dbex->Get(1))) ) )) == 0 )
        {
            //player hasn't learn't spell
                                                            //check if player is right level
            if(player_level >= ((uint32)(atof(dbex->Get(27)))) )
            {
                if(player_gold >= ((uint32)Price))          //check if player has money enough
                {
                    data << uint8(0);                       //ok (non zero = not ok)
                }
                else
                {
                    data << uint8(1);                       //not ok
                }
            }
            else
            {
                data << uint8(1);                           //not ok
            }
        }
        else
        {
            data << uint8(2);                               //used by character
        }

        data << uint32( ((uint32)Price));                   //set Spell Cost
            data << uint32(0) << uint32(0);
            data << uint32( ((uint32)(atof(dbex->Get(27)))) );//set Required level
            data << uint32(0) << uint32(0) << uint32(0) << uint32(0) << uint8(0);
    }

    // and finally you must return the database executor back to the pool
    // so that it can be recycled
    db->PutExecutor (dbex);
    //mysql_free_result( result ); //Clean Up

    //add the text at the top
    //H  e  l  l  o  !     R  e  a  d  y     f  o  r     s  o  m  e     t  r  a  i  n  i  n  g  ?
        data << uint32(0x6c6c6548) << uint32(0x5220216f) << uint32(0x79646165);
        data << uint32(0x726f6620) << uint32(0x6d6f7320) << uint32(0x72742065);
        data << uint32(0x696e6961) << uint32(0x003f676e);
}

void DatabaseInterface::setCharacter (Character * diffChar)
{
    int i;
        char invtemp[30];
        WPAssert (diffChar);

    //LINA STAT
        diffChar->setUpdateValue(UNIT_FIELD_STAT0, diffChar->m_stat0);
        diffChar->setUpdateValue(UNIT_FIELD_STAT1, diffChar->m_stat1);
        diffChar->setUpdateValue(UNIT_FIELD_STAT2, diffChar->m_stat2);
        diffChar->setUpdateValue(UNIT_FIELD_STAT3, diffChar->m_stat3);
        diffChar->setUpdateValue(UNIT_FIELD_STAT4, diffChar->m_stat4);
    //diffChar->setUpdateValue(UNIT_FIELD_HEALTH, diffChar->m_health);
        diffChar->setUpdateValue(UNIT_FIELD_MAXHEALTH, diffChar->m_health);
    //diffChar->setUpdateValue(UNIT_FIELD_POWER1, diffChar->m_mana);
        diffChar->setUpdateValue(UNIT_FIELD_MAXPOWER1, diffChar->m_mana);
    //LINA STAT

        std::stringstream ss;
        std::string invstr;
        ss << "update characters set"
        " positionX = " << diffChar->m_positionX << ", "
        " positionY = " << diffChar->m_positionY << ", "
        " positionZ = " << diffChar->m_positionZ << ", "
        " orientation= " << diffChar->m_orientation << ", "
        " data = '";
        for (uint16 index = 0; index < UPDATE_BLOCKS; index ++)
    {
        ss << diffChar->getUpdateValue(index) << " ";
    }
    ss << "', " <<
        " zoneId= " << diffChar->m_zoneId << ", "
        " mapId= " << diffChar->m_mapId
        << " where guid = " << diffChar->m_guid->sno;
        doQuery (ss.str ().c_str ());
        invstr.empty();
        invstr = "delete from inventory where charGuid = ";
        sprintf (invtemp, "%d", diffChar->GetGUID ().sno);
        invstr += invtemp;
        doQuery (invstr.c_str ());

        for(i = 0; i<39; i++)
    {
        if (diffChar->m_items[i].guid != 0)
        {
            invstr.empty();
                invstr = "INSERT INTO inventory (charGuid,inventorySlot,itemGuid,itemId) VALUES (";
                sprintf(invtemp, "%d", diffChar->GetGUID().sno);
                invstr += invtemp;
                invstr += ", ";
                sprintf(invtemp, "%d", i);
                invstr += invtemp;
                invstr += ", ";
                sprintf(invtemp, "%d", diffChar->m_items[i].guid);
                invstr += invtemp;
                invstr += ", ";
                sprintf(invtemp, "%d", diffChar->m_items[i].itemid);
                invstr += invtemp;
                invstr += ")";
                doQuery (invstr.c_str ());
        }
    }
    // save quest progress
    saveQuestStatus(diffChar);

    // Spells
        std::stringstream spellstr;
        spellstr << "DELETE FROM char_spells where charId=" << diffChar->GetGUID().sno;
        doQuery(spellstr.str().c_str());

        std::list<struct spells> spells = diffChar->getSpellList();
        std::list<struct spells>::iterator itr;
        for (itr = spells.begin(); itr != spells.end(); ++itr)
    {
        std::stringstream spellstr2;
            spellstr2 << "INSERT INTO char_spells (charId,spellId,slotId) VALUES "
            << "(" << diffChar->GetGUID ().sno << ", " << itr->spellId << ", " << itr->slotId << ")";
            doQuery(spellstr2.str().c_str());
    }

    //START OF LINA ACTION BAR
    std::stringstream actionstr;
        actionstr << "DELETE FROM char_actions where charId=" << diffChar->GetGUID ().sno;
        doQuery(actionstr.str().c_str());

        std::list<struct actions> actions = diffChar->getActionList();
        std::list<struct actions>::iterator itr2;
        for (itr2 = actions.begin(); itr2 != actions.end(); ++itr2)
    {
        char sql[256];
            sprintf(sql,"INSERT INTO char_actions (charId, button, action, type, misc) VALUES ('%u', '%u', '%u', '%u', '%u')\n",
            diffChar->GetGUID ().sno, itr2->button, itr2->action, itr2->type, itr2->misc);
            doQuery(sql);
    }
    //END OF LINA ACTION BAR
}

void DatabaseInterface::removeCharacter (Character * newChar)
{
    if (strcmp ((char *) newChar->m_name, "RandomGuy"))
    {
        std::stringstream a; a << "delete from characters where guid = " << newChar->m_guid->sno;
            doQuery (a.str ().c_str ());

            std::stringstream b; b << "delete from char_spells where charid = " << newChar->m_guid->sno;
            doQuery (b.str ().c_str ());

            std::stringstream c; c << "delete from inventory where charGuid = " << newChar->m_guid->sno;
            doQuery (c.str ().c_str ());

            std::stringstream d; d << "delete from queststatus where playerId = " << newChar->m_guid->sno;
            doQuery (d.str ().c_str ());

            std::stringstream actions;
            actions << "delete from char_actions where charid = " << newChar->m_guid->sno;
            doQuery (actions.str ().c_str ());
    }
}

std::set< Character *> DatabaseInterface::enumCharacters (int account_id)
{
    std::string invstr;
        char invtemp[20];

        std::set< Character *> temp;
        std::stringstream ss;
        ss << "select * from characters where acct=" << (int)account_id << "";
        doQuery (ss.str ().c_str ());

        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (!res) return temp;
        MYSQL_ROW row;
        MYSQL_RES *invres;
        MYSQL_ROW invrow;
        Character * tempchar;

        while ((row = mysql_fetch_row (res)))
    {
        tempchar = new Character ();
            strcpy ((char *)tempchar->m_name, row[ 3 ]);

            uint16 length = strlen(row[2])+1;
            uint8 *data = new uint8[length];
            memcpy(data, row[2], length);

            tempchar->LoadUpdateValues(data);
            tempchar->m_zoneId = atoi (row[ 8 ]);
            tempchar->m_mapId = atoi (row[ 7 ]);
            tempchar->m_positionX = (float)atof (row[ 4 ]);
            tempchar->m_positionY = (float)atof (row[ 5 ]);
            tempchar->m_positionZ = (float)atof (row[ 6 ]);
            tempchar->m_orientation = (float)atof (row[9]);

        /*
         tempchar->m_outfitId = atoi (row[ 11 ]);
         tempchar->m_guildId = atoi (row[ 17 ]);
         tempchar->m_petInfoId = atoi (row[ 18 ]);
         tempchar->m_petLevel = atoi (row[ 19 ]);
         tempchar->m_petFamilyId = atoi (row[ 20 ]);
         */

        // Inventory
            invstr = "select * from inventory where charGuid=";
            sprintf(invtemp, "%d", (int)tempchar->m_guid->sno);
            invstr += invtemp;
            invstr += "";
            doQuery (invstr.c_str ());
            invres = mysql_store_result ((MYSQL *)mDatabaseConnection);
            while ((invrow = mysql_fetch_row (invres)))
        {
            if (atol(invrow[2]) == 0 || atol(invrow[3]) == 0)
            {
                continue;
            }
            tempchar->m_items[(int)atoi(invrow[1])].guid = (uint32)atol(invrow[2]);
                tempchar->m_items[(int)atoi(invrow[1])].itemid = (uint32)atol(invrow[3]);
        }

        // Spells
        std::stringstream spellstr;
            spellstr << "SELECT * FROM char_spells WHERE charId=" << tempchar->m_guid->sno;
            doQuery(spellstr.str().c_str());
            MYSQL_RES *spellres = mysql_store_result ((MYSQL *)mDatabaseConnection);
            MYSQL_ROW spellrow;
            while ((spellrow = mysql_fetch_row (spellres)))
            tempchar->addSpell(atoi(spellrow[2]), atoi(spellrow[3]));

        //START OF LINA ACTION BAR
            std::stringstream actionstr;

            actionstr << "SELECT * FROM char_actions WHERE charId=" << tempchar->m_guid->sno << " ORDER BY button";
            doQuery(actionstr.str().c_str());
            MYSQL_RES *actionres = mysql_store_result ((MYSQL *)mDatabaseConnection);
            MYSQL_ROW actionrow;
            while ((actionrow = mysql_fetch_row (actionres)))
            tempchar->addAction(atoi(actionrow[1]), atoi(actionrow[2]), atoi(actionrow[3]), atoi(actionrow[4]));
            mysql_free_result (actionres);
        //END OF LINA ACTION BAR

            mysql_free_result (spellres);
            mysql_free_result (invres);

            temp.insert (tempchar);
    }
    mysql_free_result (res);
        return temp;
}

// <WoW Chile Dev Team> Start Change
int DatabaseInterface::IsCharMoveExist(uint32 guid)
{
    char query[300];
        strcpy(query,"");
        sprintf(query, "SELECT COUNT(*) FROM creatures_mov WHERE creatureId = '%u'", guid);
        doQuery(query);
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        row = mysql_fetch_row (res);
        if (atoi(row[0]) > 0)                               //if not cero then mob can move
        return atoi(row[0]);
        else
        return 0;
        mysql_free_result (res);
}

// <WoW Chile Dev Team> Stop Change

int DatabaseInterface::IsNameTaken(char * charname)
{
    int answer;
        char query[300];
        strcpy(query,"");
        sprintf(query, "SELECT guid FROM characters WHERE name = '%s'", charname);
        doQuery(query);
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        row = mysql_fetch_row (res);
        if (row == NULL)
    {
        answer = 0;
    }
    else
    {
        answer = 1;
    }
    mysql_free_result (res);
        return answer;
}

int DatabaseInterface::GetNameGUID(char * charname)
{
    int Guid=-1;
        char query[300];
        strcpy(query,"");
        sprintf(query, "SELECT guid FROM characters WHERE name = '%s'", charname);
        doQuery(query);
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        row = mysql_fetch_row (res);
        if (row != NULL)
    {
        Guid = atoi(row[0]);
    }
    mysql_free_result (res);
        return Guid;
}

// NOTE: not used anymore, but may be useful later
bool DatabaseInterface::GetPlayerNameFromGUID(uint32 guid, uint8 *name)
{
    std::stringstream ss;
        ss << "SELECT name FROM characters WHERE guid=" << guid;
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (!res)
        return false;

        MYSQL_ROW row = mysql_fetch_row (res);
        if(!row)
        return false;

        strcpy((char*)name, row[0]);

        return true;
}

void DatabaseInterface::addCharacter (Character *newChar)
{
    std::stringstream ss;
        ss << "INSERT INTO characters "
        << "(data,name,acct,positionX,positionY,positionZ,orientation, zoneId, mapId,guid) "
        << "VALUES ('";

        for (uint16 index = 0; index < UPDATE_BLOCKS; index ++)
    {
        ss << newChar->getUpdateValue(index) << " ";
    }

    ss << "', "
        << "'" << newChar->m_name << "', "
        << newChar->m_accountId << ", "
        << (float)newChar->m_positionX << ", "
        << (float)newChar->m_positionY << ", "
        << (float)newChar->m_positionZ << ", "
        << (float)newChar->m_orientation << ", "
        << newChar->m_zoneId << ", "
        << newChar->m_mapId << ", "
        << newChar->GetGUID ().sno << " "
        << ")";

        doQuery (ss.str ().c_str ());
}

int DatabaseInterface::doQuery (const char * query)
{
    LOG.outString ((std::string("SQL: ") + query).c_str ());
        mysql_query ((MYSQL *)mDatabaseConnection, query);

        const char *err = mysql_error((MYSQL*)mDatabaseConnection);
        if (err && *err)
        LOG.outString ("SQL ERROR: %s", err);

        return mysql_field_count ((MYSQL *)mDatabaseConnection);
}

// Logs in a client with username and password, or creates new account is username doesnt exist
int DatabaseInterface::Login(char* username, char* ip)
{
    LOG.outString ("DB: Checking username...");
        char query[300];
        strcpy(query, "");
        sprintf(query, "SELECT * FROM accounts WHERE login='%s'", username);
        doQuery(query);
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;

        if (!res)
        return -2;

        if (res->row_count == 1)
    {                                                       // Match!
        row = mysql_fetch_row (res);
            int ret=atoi(row[0]);

            if(atoi(row[3]) > 0)                            //TEST GM
        {
            if(row[5]!=NULL)                                //if ip, check to be sure
            {
                if(strcmp(ip,row[5])!=0) ret=-2;            //not set return to 2
                    printf("DBI: Login %s, Connect IP: %s, DB IP: %s\n", username, ip, row[5]);
            }
            else                                            //else no ip found
            {
                printf("DBI: Login %s, Connect IP: %s, No DB IP\n", username, ip);
                    ret=-1;                                 //set return to 1
            }
            if (!DATABASE.GetTestIP ())                     //if test ip/login off
            {
                printf("DBI: WARNING *** TestIP OFF *** WARNING\n");
                    ret=atoi(row[0]);                       //force return to row
            }
        }
        return ret;
    }
    else
    {
        // Check the config if we should auto create accounts
        if (!DATABASE.GetAutoCreateAcct ())
            return -3;

        // create new account withusername and password
            sprintf(query, "INSERT INTO accounts (login, password, realpassword) VALUES ('%s', '%s', '%s')", username, "none", "none");
            doQuery(query);

        // select the new account to get its ID #
            sprintf(query, "SELECT * FROM accounts WHERE login='%s'", username);
            doQuery(query);

            MYSQL_RES *login_res = mysql_store_result ((MYSQL *)mDatabaseConnection);
            row = mysql_fetch_row (login_res);

            return atoi(row[0]);
    }
    return -1;
}

uint64 DatabaseInterface::doQueryId (const char * query)
{
    LOG.outString ((std::string("SQL: ") + query).c_str ());
        mysql_query ((MYSQL *)mDatabaseConnection, query);

        const char *err = mysql_error((MYSQL*)mDatabaseConnection);
        if (err && *err)
        LOG.outString ("SQL ERROR: %s", err);

        return mysql_insert_id ((MYSQL *)mDatabaseConnection);
}

int DatabaseInterface::getAccountLvl(int account_id)
{
    std::stringstream ss;
        ss << "SELECT gm FROM accounts WHERE acct=" << account_id;
        doQuery(ss.str().c_str());
        MYSQL_RES *res = mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        if (res->row_count >= 1)
    {
        row = mysql_fetch_row(res);
            return atoi(row[0]);
    }

    // account id not found, default to 0
    return 0;
}

void DatabaseInterface::updateCreature(Unit *pUnit)
{
    std::stringstream ss;

        ss << "UPDATE creatures SET" << ""
        << " name_id=" << pUnit->getUpdateValue(OBJECT_FIELD_ENTRY) << ","
        << " positionX=" << pUnit->m_positionX << ","
        << " positionY=" << pUnit->m_positionY << ","
        << " positionZ=" << pUnit->m_positionZ << ","
        << " orientation=" << pUnit->m_orientation << ","
        << " mapId=" << pUnit->m_mapId << ","
        << " zoneId=" << pUnit->m_zoneId << ","
        << " data='";

        for (uint16 index = 0; index < UNIT_END; index++)
    {
        ss << pUnit->getUpdateValue(index) << " ";
    }

    ss <<"' WHERE id=" << pUnit->m_guid->sno << "";

        doQuery (ss.str ().c_str ());

        const char *err = mysql_error((MYSQL*)mDatabaseConnection);
        if (err && *err)
        LOG.outString ("SQL ERROR: %s", err);
}

void DatabaseInterface::saveCreature(Unit *pUnit)
{
    // then save all creatures
    std::stringstream ss;
        std::stringstream temp;
        ss << "INSERT INTO creatures "
        "(name_id,positionX,positionY,positionZ,orientation,id,mapId,zoneId,data) "
        "VALUES ("
        "" << pUnit->getUpdateValue(OBJECT_FIELD_ENTRY) << ", "
        << pUnit->m_positionX << ", "
        << pUnit->m_positionY << ", "
        << pUnit->m_positionZ << ", "
        << pUnit->m_orientation << ", "
        << pUnit->m_guid->sno << ", "
        << pUnit->m_mapId << ", "
        << pUnit->m_zoneId << ", "
        << "'";

        for (uint16 index = 0; index < UNIT_END; index ++)
    {
        ss << pUnit->getUpdateValue(index) << " ";
    }

    ss << "') ";

        doQuery (ss.str ().c_str ());

    /*temp << "INSERT INTO creatures_attr (id, displayid, level) VALUES ("
    << pUnit->m_guid->sno << ", "
    << pUnit->getUpdateValue(UNIT_FIELD_DISPLAYID) << ", "
    << pUnit->getUpdateValue(UNIT_FIELD_LEVEL) << ")";
    doQuery (temp.str ().c_str ());
    printf("%s", mysql_error((MYSQL*)mDatabaseConnection));*/
}

void DatabaseInterface::loadCreatureNames(std::map< uint32, uint8*> & m_names)
{
    std::stringstream ss;
        ss << "SELECT * FROM creature_names";
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;

        char *name;
        while ((row = mysql_fetch_row (res)))
    {
        name = new char[strlen(row[1])+1];
            strcpy(name, row[1]);
            m_names[ atol(row[0]) ] = (uint8*)name;
    }
}

void DatabaseInterface::saveCreatureNames(std::map< uint32, uint8*> p_names)
{
    std::stringstream ss2;
        ss2 << "DELETE FROM creature_names";
        doQuery (ss2.str ().c_str ());
        for (std::map< uint32, uint8*>::iterator itr = p_names.begin (); itr != p_names.end (); ++ itr)
    {
        std::stringstream ss;
            ss << "INSERT INTO creature_names (name_id,creature_name) VALUES (" << itr->first << ", '" << itr->second << "')";
            doQuery (ss.str ().c_str ());
    }
}

std::set<Unit*> DatabaseInterface::loadCreatures()
{
    std::set< Unit *> temp;
        MYSQL_RES *res, *res2;
        MYSQL_ROW row, row2;
        Unit *tempunit;
        int32 maxhealth;

        doQuery ("SELECT * FROM creatures");
        res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if(!res)
        return temp;

        while ((row = mysql_fetch_row (res)))
    {
        uint16 length = strlen(row[7])+1;
            uint8 *data = new uint8[length];
        //char str[100];
            memcpy(data, row[7], length);

            #if 0
            char str [100];
            sprintf(str, "SELECT displayid, level FROM creatures_attr WHERE id = '%d'", atoi(row[0]));
            doQuery (str);
            res2 =  mysql_store_result ((MYSQL *)mDatabaseConnection);
            row2 = mysql_fetch_row (res2);
        //uint8 * name = row2[0];
            #endif

            uint8 * name = WORLDSERVER.getCreatureName(atol(row[8]));
            if (!name)
            name = (uint8 *)"ERROR_NO_CREATURENAME_FOR_ENTRY";

            tempunit = new Unit();
            tempunit->Create(atol(row[0]), name, (float)atof(row[1]), (float)atof(row[2]), (float)atof(row[3]), (float)atof(row[4]));
            tempunit->setZone((uint16)atol(row[5]));
            tempunit->setMapId((uint16)atol(row[6]));
            tempunit->m_moveRandom = atoi(row[9]) > 0;
            tempunit->m_moveRun = atoi(row[10]) > 0;
            tempunit->m_aggressive = (uint8)atoi(row[11]);  //LINA
            tempunit->LoadUpdateValues(data);

            #if 0
        // Use new table for certain bitmask values instead of "Data"
            tempunit->setUpdateValue(UNIT_FIELD_LEVEL, atoi(row2[1]));
            tempunit->setUpdateValue(UNIT_FIELD_DISPLAYID, atoi(row2[0]));
            #endif

        /*
         // BEGIN FIX MONSTER STATS - NISHAVEN
         float fLevel = (float) tempunit->getUpdateValue(UNIT_FIELD_LEVEL);
         tempunit->setUpdateValue(UNIT_FIELD_HEALTH, (uint32)((1.24*fLevel*fLevel)+(1.79*fLevel)+40.64));
         tempunit->setUpdateValue(UNIT_FIELD_MAXHEALTH, (uint32)((1.24*fLevel*fLevel)+(1.79*fLevel)+40.64));
         tempunit->setUpdateFloatValue(UNIT_FIELD_MINDAMAGE, 4.0f+fLevel);
         tempunit->setUpdateFloatValue(UNIT_FIELD_MAXDAMAGE, 4.0f+fLevel+fLevel);

         updateCreature(tempunit);
         // END FIX MONSTER STATS
         */

            if (tempunit->getUpdateValue (UNIT_NPC_FLAGS) & 4)// vendor
        {
            // load his goods

            std::stringstream query;
                query << "SELECT * FROM vendors WHERE vendorGuid=" << tempunit->GetGUID().sno;

                doQuery (query.str().c_str ());
                res2 = mysql_store_result ((MYSQL *)mDatabaseConnection);
                if(res2)
            {
                while ((row2 = mysql_fetch_row (res2)))
                {
                    if (tempunit->getItemCount() >= 128)
                    {
                        // this should never happen unless someone has been fucking with the dbs
                        // complain and break :P
                        LOG.outString ("Vendor has too many items. Check the DB!");
                            break;
                    }

                    tempunit->setItemId(tempunit->getItemCount() , (uint32)atol(row2[1]));
                        tempunit->setItemAmount(tempunit->getItemCount() , (uint32)atoi(row2[2]));
                        tempunit->increaseItemCount();
                }

                mysql_free_result (res2);
            }
        }

        if (tempunit->getUpdateValue (UNIT_NPC_FLAGS) & 2)  // questmaster
        {
            // load assigned quests

            std::stringstream query;
                query << "SELECT * FROM creaturequestrelation WHERE creatureId=" <<
                tempunit->GetGUID().sno << " ORDER BY questId";
                doQuery (query.str ().c_str ());

                res2 =  mysql_store_result ((MYSQL *)mDatabaseConnection);
                if(res2)
            {
                while ((row2 = mysql_fetch_row (res2)))
                    tempunit->addQuest(atol(row2[1]));

                    mysql_free_result (res2);
            }
        }

        std::stringstream query;
            query << "SELECT X,Y,Z FROM creatures_mov WHERE creatureId=" <<
            tempunit->GetGUID().sno;
            doQuery (query.str().c_str ());

        //Added unit Waypoint load during World Server creature load
            if(!tempunit->hasWaypoints())
        {
            tempunit->getPositionX(),
                tempunit->getPositionY(),
                tempunit->getPositionZ();
                tempunit->addWaypoint(tempunit->getPositionX(), tempunit->getPositionY(), tempunit->getPositionZ());
        }

        res2 = mysql_store_result ((MYSQL *)mDatabaseConnection);
            if(res2)
        {
            while ((row2 = mysql_fetch_row (res2)))
                tempunit->addWaypoint(atof(row2[0]), atof(row2[1]), atof(row2[2]));

                mysql_free_result (res2);
        }

        temp.insert(tempunit);

            if((tempunit->getDeathState() == CORPSE) || tempunit->getUpdateValue(UNIT_FIELD_HEALTH) <= 0)
        {
            LOG.outString("Reviving NPC in dead state");
                maxhealth = tempunit->getUpdateValue(UNIT_FIELD_MAXHEALTH);
                tempunit->setDeathState(ALIVE);
                tempunit->setUpdateValue(UNIT_FIELD_HEALTH,maxhealth);
                updateCreature(tempunit);
        }
    }

    mysql_free_result (res);

        return temp;
}

void DatabaseInterface::setHighestGuids()
{
    doQuery ("SELECT MAX(guid) FROM characters");
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (res)
    {
        MYSQL_ROW row;
            row = mysql_fetch_row (res);
            if (row[0])
            WORLDSERVER.m_hiCharGuid = atol(row[0])+1;
    }

    mysql_free_result (res);

        doQuery ("SELECT MAX(id) FROM creatures");
        res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (res)
    {
        MYSQL_ROW row;
            row = mysql_fetch_row (res);
            if (row[0])
            WORLDSERVER.m_hiCreatureGuid = atol(row[0])+1;
    }
    mysql_free_result (res);
        doQuery ("SELECT MAX(itemGuid) FROM inventory");
        res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (res)
    {
        MYSQL_ROW row1;
            row1 = mysql_fetch_row (res);
            if (row1[0])
        {
            WORLDSERVER.m_hiItemGuid = atol(row1[0])+1;
        }
    }
    mysql_free_result (res);
}

void DatabaseInterface::loadItems()
{
    std::stringstream ss;
        ss << "SELECT * FROM items";
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        Item *pItem;
        int i;
        while ((row = mysql_fetch_row (res)))
    {
        if (atol(row[0]))
        {
            pItem = new Item;
                pItem->Create(0, atol(row[0]));
                pItem->Class = atol(row[1]);
                pItem->SubClass = atol(row[2]);
                pItem->name1 = row[3];
                pItem->name2 = row[4];
                pItem->name3 = row[5];
                pItem->name4 = row[6];
                pItem->DisplayInfoID = atol(row[7]);
                pItem->OverallQualityID = atol(row[8]);
                pItem->Flags = atol(row[9]);
                pItem->Buyprice = atol(row[10]);
                pItem->Sellprice = atol(row[11]);
                pItem->Inventorytype = atol(row[12]);
                pItem->AllowableClass = atol(row[13]);
                pItem->AllowableRace = atol(row[14]);
                pItem->ItemLevel = atol(row[15]);
                pItem->RequiredLevel = atol(row[16]);
                pItem->RequiredSkill = atol(row[17]);
                pItem->RequiredSkillRank = atol(row[18]);
                pItem->MaxCount = atol(row[19]);
                pItem->Stackable = atol(row[20]);
                pItem->ContainerSlots = atol(row[21]);
                for(i = 0; i < 20; i+=2)
            {
                pItem->BonusStat[i/2] = atol(row[22 + i]);
                    pItem->BonusAmount[i/2] = atol(row[23 + i]);
            }
            for(i = 0; i < 15; i+=3)
            {
                pItem->MinimumDamage[i/3] = atol(row[42 + +i]);
                    pItem->MaximumDamage[i/3] = atol(row[43 +i]);
                    pItem->DamageType[i/3] = atol(row[44 + i]);
            }
            for(i = 0; i < 6; i++)
            {
                pItem->Resistances[i] = atol(row[57 + i]);
            }
            pItem->Delay = atol(row[63]);
                pItem->AmmunitionType = atol(row[64]);
                pItem->MaxDurability = atol(row[65]);
                for(i = 0; i < 30; i+=6)
            {
                pItem->SpellID[i/6] = atol(row[66+i]);
                    pItem->SpellTrigger[i/6] = atol(row[67+i]);
                    pItem->SpellCharges[i/6] = atol(row[68+i]);
                    pItem->SpellCooldown[i/6] = atol(row[69+i]);
                    pItem->SpellCategory[i/6] = atol(row[70+i]);
                    pItem->SpellCategoryCooldown[i/6] = atol(row[71+i]);
            }
            pItem->Bonding = atol(row[96]);
                pItem->Description = row[97];
                pItem->Pagetext = atol(row[98]);
                pItem->LanguageID = atol(row[99]);
                pItem->PageMaterial = atol(row[100]);
                pItem->StartQuestID = atol(row[101]);
                pItem->LockID = atol(row[102]);
                pItem->Material = atol(row[103]);
                pItem->Sheathetype = atol(row[104]);
                pItem->Unknown1 = atol(row[105]);
                pItem->Unknown2 = 0;
                WORLDSERVER.AddItem(pItem);
        }
    }
}

void DatabaseInterface::loadQuests()
{
    std::stringstream ss;
        ss << "SELECT * FROM quests";
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row (res)))
    {
        Quest *pQuest = new Quest;
            pQuest->m_questId = atol(row[0]);
            pQuest->m_zone = atol(row[1]);
            pQuest->m_title = row[2];
            pQuest->m_details = row[3];
            pQuest->m_objectives = row[4];
            pQuest->m_completedText = row[5];
            pQuest->m_incompleteText = row[6];
            pQuest->m_targetGuid = atol(row[7]);
            pQuest->m_questItemId[0] = atol(row[8]);
            pQuest->m_questItemId[1] = atol(row[9]);
            pQuest->m_questItemId[2] = atol(row[10]);
            pQuest->m_questItemId[3] = atol(row[11]);
            pQuest->m_questItemCount[0] = atol(row[12]);
            pQuest->m_questItemCount[1] = atol(row[13]);
            pQuest->m_questItemCount[2] = atol(row[14]);
            pQuest->m_questItemCount[3] = atol(row[15]);
            pQuest->m_questMobId[0] = atol(row[16]);
            pQuest->m_questMobId[1] = atol(row[17]);
            pQuest->m_questMobId[2] = atol(row[18]);
            pQuest->m_questMobId[3] = atol(row[19]);
            pQuest->m_questMobCount[0] = atol(row[20]);
            pQuest->m_questMobCount[1] = atol(row[21]);
            pQuest->m_questMobCount[2] = atol(row[22]);
            pQuest->m_questMobCount[3] = atol(row[23]);
            pQuest->m_choiceRewards = atoi(row[24]);
            pQuest->m_choiceItemId[0] = atol(row[25]);
            pQuest->m_choiceItemId[1] = atol(row[26]);
            pQuest->m_choiceItemId[2] = atol(row[27]);
            pQuest->m_choiceItemId[3] = atol(row[28]);
            pQuest->m_choiceItemId[4] = atol(row[29]);
            pQuest->m_choiceItemCount[0] = atol(row[30]);
            pQuest->m_choiceItemCount[1] = atol(row[31]);
            pQuest->m_choiceItemCount[2] = atol(row[32]);
            pQuest->m_choiceItemCount[3] = atol(row[33]);
            pQuest->m_choiceItemCount[4] = atol(row[34]);
            pQuest->m_itemRewards = atoi(row[35]);
            pQuest->m_rewardItemId[0] = atol(row[36]);
            pQuest->m_rewardItemId[1] = atol(row[37]);
            pQuest->m_rewardItemId[2] = atol(row[38]);
            pQuest->m_rewardItemId[3] = atol(row[39]);
            pQuest->m_rewardItemId[4] = atol(row[40]);
            pQuest->m_rewardItemCount[0] = atol(row[41]);
            pQuest->m_rewardItemCount[1] = atol(row[42]);
            pQuest->m_rewardItemCount[2] = atol(row[43]);
            pQuest->m_rewardItemCount[3] = atol(row[44]);
            pQuest->m_rewardItemCount[4] = atol(row[45]);
            pQuest->m_rewardGold = atol(row[46]);
            pQuest->m_questXp = atol(row[47]);
            pQuest->m_originalGuid = atol(row[48]);
            pQuest->m_requiredLevel = atol(row[49]);
            pQuest->m_previousQuest = atol(row[50]);
            WORLDSERVER.addQuest(pQuest);
    }

    mysql_free_result(res);
}

void DatabaseInterface::loadTextRelation()
{
    std::stringstream ss;
        ss << "SELECT * FROM npctextrelationship";
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res = mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (!res)
        return;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row (res)))
    {
        TextRelation *pRelation = new TextRelation;
            pRelation->m_TextID = atol(row[0]);
            pRelation->m_NPCGUID = atol(row[1]);
            WorldServer::getSingleton().addTextRelation(pRelation);
    }

    mysql_free_result(res);
}

void DatabaseInterface::loadNPCText()
{
    std::stringstream ss;
        ss << "SELECT * FROM npc_text";
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (!res)
        return;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row (res)))
    {
        NPCText *pNPCText = new NPCText;
            pNPCText->m_TextID = atol(row[0]);
            pNPCText->m_Text = row[1];
            pNPCText->m_OptionCount = atol(row[2]);
            pNPCText->m_OptionID[1] = atol(row[3]);
            pNPCText->m_OptionID[2] = atol(row[4]);
            pNPCText->m_OptionID[3] = atol(row[5]);
            pNPCText->m_OptionID[4] = atol(row[6]);
            pNPCText->m_OptionID[5] = atol(row[7]);
            pNPCText->m_OptionID[6] = atol(row[8]);
            pNPCText->m_OptionID[7] = atol(row[9]);
            pNPCText->m_OptionID[8] = atol(row[10]);
            pNPCText->m_OptionID[9] = atol(row[11]);
            pNPCText->m_OptionID[10] = atol(row[12]);
            pNPCText->m_OptionID[11] = atol(row[13]);
            pNPCText->m_OptionID[12] = atol(row[14]);
            pNPCText->m_OptionID[13] = atol(row[15]);
            pNPCText->m_OptionID[14] = atol(row[16]);
            pNPCText->m_OptionID[15] = atol(row[17]);

            WorldServer::getSingleton().addNPCText(pNPCText);
    }

    mysql_free_result(res);
}

void DatabaseInterface::loadTextOptions()
{
    std::stringstream ss;
        ss << "SELECT * FROM text_options";
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (!res)
        return;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row (res)))
    {
        TextOption *pTextOption = new TextOption;
            pTextOption->m_OptionID = atol(row[0]);
            pTextOption->m_OptionText = row[1];
            pTextOption->m_OptionIconID = atol(row[2]);
            pTextOption->m_TextID = atol(row[3]);
            WorldServer::getSingleton().addTextOption(pTextOption);
    }

    mysql_free_result(res);
}

void DatabaseInterface::loadQuestStatus(Character *pChar)
{
    std::stringstream ss;
        ss << "SELECT * FROM queststatus WHERE playerId=" << pChar->GetGUID().sno;
        doQuery (ss.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if (!res)
        return;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row (res)))
    {
        uint32 status = atol(row[2]);
            quest_status qs;
            qs.status = status;
            qs.quest_id = atol(row[1]);
            qs.m_questMobCount[0] = atol(row[3]);
            qs.m_questMobCount[1] = atol(row[4]);
            qs.m_questMobCount[2] = atol(row[5]);
            qs.m_questMobCount[3] = atol(row[6]);
            qs.m_questItemCount[0] = atol(row[7]);
            qs.m_questItemCount[1] = atol(row[8]);
            qs.m_questItemCount[2] = atol(row[9]);
            qs.m_questItemCount[3] = atol(row[10]);

            pChar->loadExistingQuest(qs);
    }

    mysql_free_result (res);
}

void DatabaseInterface::saveQuestStatus(Character *pChar)
{
    std::stringstream ss;
        ss << "DELETE FROM queststatus WHERE playerId=" << pChar->GetGUID().sno;
        doQuery (ss.str ().c_str ());

        std::map<uint32, struct quest_status> temp = pChar->getQuestStatusMap();
        for (std::map<uint32, struct quest_status>::iterator i = temp.begin (); i != temp.end (); ++ i)
    {
        std::stringstream ss2;
            ss2 << "INSERT INTO queststatus (playerId,questId,status,questMobCount1,questMobCount2,questMobCount3,questMobCount4,"
            << "questItemCount1,questItemCount2,questItemCount3,questItemCount4) VALUES "
            << "(" << pChar->GetGUID ().sno << ", "
            << i->first << ", "
            << i->second.status << ", "
            << i->second.m_questMobCount[0] << ", "
            << i->second.m_questMobCount[1] << ", "
            << i->second.m_questMobCount[2] << ", "
            << i->second.m_questMobCount[3] << ", "
            << i->second.m_questItemCount[0] << ", "
            << i->second.m_questItemCount[1] << ", "
            << i->second.m_questItemCount[2] << ", "
            << i->second.m_questItemCount[3]
            << ")";
            doQuery(ss2.str ().c_str ());

            const char *err = mysql_error((MYSQL*)mDatabaseConnection);
            if (err && *err)
            LOG.outString ("SQL ERROR: %s", err);
    }
}

bool DatabaseInterface::isSpiritHealer(uint32 guid)
{
    std::stringstream Q;
        Q << "SELECT X,Y,Z FROM spirithealers";
        doQuery (Q.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;

        while ((row = mysql_fetch_row (res)))
    {
        Unit* pCreature = WorldServer::getSingletonPtr()->GetCreature(guid);
            if(floorf(pCreature->getPositionX()) == floorf(atof(row[0])) &&
            floorf(pCreature->getPositionY()) == floorf(atof(row[1])) &&
            floorf(pCreature->getPositionZ()) == floorf(atof(row[2])))
        {
            mysql_free_result (res);
                return true;
        }

    }
    mysql_free_result (res);
        return false;
}

void DatabaseInterface::getClosestSpiritHealer(float &x, float &y, float &z, uint16 &mapID)
{
    std::stringstream Q;
        float cx,cy,cz;
        cx = x; cy = y; cz = z;
        Q << "SELECT X,Y,Z FROM spirithealers WHERE mapID=" << mapID;
        doQuery (Q.str ().c_str ());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        if ((row = mysql_fetch_row (res)))
    {
        x = (float)atof(row[0]);
            y = (float)atof(row[1]);
            z = (float)atof(row[2]);
    }
    while ((row = mysql_fetch_row (res)))
    {
        if(sqrt (pow(cx-atof(row[0]),2) + pow(cy-atof(row[1]),2))< sqrt (pow(cx-x,2) + pow(cy-y,2)))
        {
            x = (float)atof(row[0]);
                y = (float)atof(row[1]);
                z = (float)atof(row[2]);
        }

    }
    mysql_free_result (res);
}

void DatabaseInterface::loadChatCommand(const char *name, ChatCommand * cmd)
{
    std::stringstream s;
        s << "SELECT security, help FROM commands WHERE name = '" << name  << "'";
        doQuery(s.str().c_str());
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        if(!res)
        return;

        MYSQL_ROW row;
        row = mysql_fetch_row (res);
        if (row != NULL)
    {
        cmd->SecurityLevel = atoi(row[0]);
            cmd->Help = row[1];
    }
    mysql_free_result (res);
}

char * DatabaseInterface::getAccountPass(int account_id)
{
    std::stringstream ss;
        ss << "SELECT realpassword FROM accounts WHERE acct=" << account_id;
        doQuery(ss.str().c_str());
        MYSQL_RES *res = mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        if (res->row_count >= 1)
    {
        row = mysql_fetch_row(res);
            return row[0];
    }

    // account id not found, default to 0
    return 0;
}

void DatabaseInterface::AddFriend(uint32 guid, uint32 friendid, char *charname)
{
    char query[300];
        char output[300];

        sprintf(output, "Adding friend to database Guid %i Friend %i Char %s\n", guid, friendid, charname);
        LOG.outString (output);

        sprintf(query, "INSERT INTO social (charname, guid, friendid, flags) VALUES('%s', '%i','%i', 'FRIEND')", charname, guid, friendid);
        doQuery(query);
        mysql_store_result ((MYSQL *)mDatabaseConnection);
}

void DatabaseInterface::RemoveFriend(uint32 guid, uint32 friendid)
{
    char query[300];
        char output[300];

        sprintf(output, "Removing friend from database Guid %i Friend %i\n", guid, friendid);
        LOG.outString (output);

        sprintf(query, "DELETE FROM social Where guid = '%i' AND friendid = '%i'", guid, friendid);
        doQuery(query);
        mysql_store_result ((MYSQL *)mDatabaseConnection);
}

SocialData* DatabaseInterface::getFriendList(uint32 guid)
{
    SocialData *pSdata;
        char query[300];

        strcpy(query, "");
        sprintf(query, "SELECT COUNT(*) FROM social where guid='%i'",guid);
        doQuery(query);
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;
        row = mysql_fetch_row (res);
        int Counter = atoi(row[0]);

        strcpy(query, "");

        pSdata = new SocialData;
        pSdata->pSudata = new SocialUserData[Counter];
        pSdata->pArraySize = Counter;

        sprintf(query, "SELECT * FROM social where guid='%i'",guid);
        doQuery(query);
        MYSQL_RES *res2 =  mysql_store_result ((MYSQL *)mDatabaseConnection);

        int i=0;
        while ((row = mysql_fetch_row (res2)))
    {
        pSdata->pSudata[i].guid = atoi(row[2]);
            pSdata->pSudata[i].charname = row[0];
        //printf("DEBUG: Added Guid %i Char %s to pSdata\n", pSdata->pSudata[i].guid, pSdata->pSudata[i].charname);
            i++;
    }
    strcpy(query, "");
        return pSdata;
}

void DatabaseInterface::loadTalents()
{
    char query[300];
        int maxrank;
        uint32 t_id, Class;
        TALENT **Talents;

        Talents = new TALENT*[255];

        for(int i=0; i < 255; i++)
    {
        Talents[i] = new TALENT[8];
    }

    strcpy(query, "");
        sprintf(query, "SELECT * FROM talents");
        doQuery(query);
        MYSQL_RES *res =  mysql_store_result ((MYSQL *)mDatabaseConnection);
        MYSQL_ROW row;

        while ((row = mysql_fetch_row(res)))
    {
        t_id = atoi(row[1]);
            Class = atoi(row[3]);
            maxrank = atoi(row[2]);

            uint16 length = strlen(row[4])+1;
            uint8 *data = new uint8[length];
            memcpy(data, row[4], length);

            Talents[t_id][Class].Class = Class;
            Talents[t_id][Class].MaxRank = maxrank;
            Talents[t_id][Class].TalentId = t_id;

            char* next = strtok((char*)data, " ");
            Talents[t_id][Class].Ranks[0].Byte1 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[0].Byte2 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[0].Byte3 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[0].Byte4 = atol(next);

            length = strlen(row[5])+1;
            data = new uint8[length];
            memcpy(data, row[5], length);

            next = strtok((char*)data, " ");
            Talents[t_id][Class].Ranks[1].Byte1 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[1].Byte2 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[1].Byte3 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[1].Byte4 = atol(next);

            length = strlen(row[6])+1;
            data = new uint8[length];
            memcpy(data, row[6], length);

            next = strtok((char*)data, " ");
            Talents[t_id][Class].Ranks[2].Byte1 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[2].Byte2 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[2].Byte3 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[2].Byte4 = atol(next);

            length = strlen(row[7])+1;
            data = new uint8[length];
            memcpy(data, row[7], length);

            next = strtok((char*)data, " ");
            Talents[t_id][Class].Ranks[3].Byte1 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[3].Byte2 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[3].Byte3 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[3].Byte4 = atol(next);

            length = strlen(row[8])+1;
            data = new uint8[length];
            memcpy(data, row[8], length);

            next = strtok((char*)data, " ");
            Talents[t_id][Class].Ranks[4].Byte1 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[4].Byte2 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[4].Byte3 = atol(next);

            next = strtok(NULL, " ");
            Talents[t_id][Class].Ranks[4].Byte4 = atol(next);
    }
    strcpy(query, "");
        mysql_free_result (res);
        WORLDSERVER.SetTalentDatabase(Talents);

        for(int i=0; i < 255; i++) delete [] Talents[i];
        delete [] Talents;

}
