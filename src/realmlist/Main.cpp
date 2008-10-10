/**
 *     \file  src/realmlist/Main.cpp
 *    \brief  Realm list server
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

#include <getopt.h>
#include "RealmListSrv.h"
#include "Database.h"
#include "Console.h"
#include "CommandInterpreter.h"
#include "version.h"

struct ServerOptions
{
    char *configFile;
    char *DbType;
    char *DbAddr;

    bool Running;
    RealmListSrv *rs;
    Database *db;

    ServerOptions ()
    {
        configFile = strnew (RL_CONFIG_FILE);
        DbType = strnew (DEFDBTYPE);
        DbAddr = strnew (DEFDBADDR);
        Running = false;
        rs = new RealmListSrv (3724, new Log ("realmlist.log"));
        db = NULL;
    }

    ~ServerOptions ()
    {
        StopServer ();
        rs->DecRef ();
        delete [] DbType;
        delete [] DbAddr;
        delete [] configFile;
    }

    bool CreateDatabase ()
    {
        if (!db)
        {
            CONSOLE.Out ("\axaOpening database\n");
            db = Database::Create (Database::ParseType (DbType), DbAddr);
            if (IS_ERR (db))
            {
                CONSOLE.Out ("\axcERROR: \axeFailed to open database: %s\n",
                    Database::ErrorString ((DatabaseError)PTR_ERR (db)));
                db = NULL;
                return false;
            }
        }
        return true;
    }

    void CloseDatabase ()
    {
        if (db)
        {
            CONSOLE.Out ("\axaClosing the database connection\n");
            db->DecRef ();
            db = NULL;
        }
    }

    void StartServer ()
    {
        if (!CreateDatabase ())
            return;

        if (!rs->IsRunning ())
        {
            CONSOLE.Out ("\axaStarting realm list server\n");
            rs->SetDatabase (db);
            if (rs->Start ())
                CONSOLE.Out ("\axeUp and running.\n");
        }
        else
            CONSOLE.Out ("\axeWARNING: \ax2Realm server already running\n");
    }

    void StopServer ()
    {
        if (!rs->IsRunning ())
            return;

        CONSOLE.Out ("\axaStopping realm list server\n");
        rs->Stop ();
        CloseDatabase ();
        CONSOLE.Out ("\axeServer down.\n");
    }
};

static void display_version ()
{
    CONSOLE.Out (
        "\ax9MaNGOS2 Realm List Server\ax2, version \axf%s\ax2\n"
        "Copyright \axf(C) \ax2%s\ax2\n",
        VERSION, COPYRIGHT);

    /// GPL notice
    CONSOLE.Out (
        "\n\ax2This is free software.  You may redistribute copies of it under the terms of\n"
        "\ax2the GNU General Public License <http://www.gnu.org/licenses/gpl.html>.\n"
        "\ax2There is NO WARRANTY, to the extent permitted by law.\ax2\n");

    /// SRP project notice
    CONSOLE.Out (
        "\n\ax2This product includes software developed by Tom Wu and Eugene\n"
        "\ax2Jhong for the SRP Distribution (http://srp.stanford.edu/).\n");

}

static void display_usage (const char *argv0, ServerOptions &srvopt)
{
    display_version ();

    CONSOLE.Out (
        "\n\ax2Usage: \axb%s [options]\ax2\n"
        "  \axa-c#\t--config=#\t\ax2Load an alternative config file (default: %s)\n"
        "  \axa-h\t--help\t\ax2Display program usage information\n"
        "  \axa-V\t--version\t\ax2Display program version information\n"
        , argv0, srvopt.configFile);
}

static int cmdVersion (ServerOptions *srvopt)
{
    CONSOLE.Out (
        "\ax2** Realm List Server **  \axa%s\ax2  for build \axa%d..%d\ax2 **\n",
        FULLVERSION, MIN_CLIENT_BUILD, MAX_CLIENT_BUILD);
    return 0;
}

static int cmdQuit (ServerOptions *srvopt)
{
    return 1;
}

static int cmdStart (ServerOptions *srvopt)
{
    srvopt->StartServer ();
    return 0;
}

static int cmdStop (ServerOptions *srvopt)
{
    srvopt->StopServer ();
    return 0;
}

static int cmdRealmList (ServerOptions *srvopt)
{
    RealmVector *rv = srvopt->rs->GetRealms ();
    if (!rv)
    {
        CONSOLE.Out ("\axeDatabase contains no realms");
        return 0;
    }
    CONSOLE.Out ("\axfRealm name\t\axeAddress\t\t    \axaPopulation\t\axbColor\t\axdType\t\ax9Language\n");
    for (int i = 0; i < rv->Length (); i++)
    {
        Realm *r = rv->Get (i);
        CONSOLE.Out ("\ax7%s\t%s\ax6%s\t\ax2%g\t\ax3%d\t\ax5%d\t\ax1%d\n",
            r->Name, strlen (r->Name) > 7 ? "" : "\t",
            r->Address, r->Population,
            r->Color, r->Type, r->Language);
    }
    return 0;
}

static int cmdLog (ServerOptions *srvopt, char *LogOpt)
{
    Log &Logger = *srvopt->rs->Logger;
    if (LogOpt)
        Logger.Logging (LogOpt);
    else
    {
        char buff [100];
        Logger.GetLogging (buff, sizeof (buff));
        CONSOLE.Out ("\ax3RealmList server logging: \axa%s\ax2\n", buff);
    }
    return 0;
}

static int cmdRealmDb (ServerOptions *srvopt, char *Type, char *Address)
{
    delete [] srvopt->DbType;
    srvopt->DbType = strnew (Type);
    delete [] srvopt->DbAddr;
    srvopt->DbAddr = strnew (Address);

    // Apply changes immediately if server is running
    if (srvopt->rs->IsRunning ())
    {
        if (srvopt->db)
        {
            srvopt->db->DecRef ();
            srvopt->db = NULL;
        }
        srvopt->CreateDatabase ();
        if (srvopt->db)
        {
            srvopt->rs->SetDatabase (srvopt->db);
            CONSOLE.Out ("\ax3Database successfully switched\n");
        }
    }
    return 0;
}

int main (int argc, char **argv)
{
    int c;
    static struct option long_options[] =
    {
        {"config", required_argument, NULL, 'c'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'V'},
        {0, 0, 0, 0}
    };

    // Initialize default server parameters
    ServerOptions srvopt;

    while ((c = getopt_long(argc, argv, "c:hv", long_options, NULL)) != EOF)
    {
        switch (c)
        {
            case 'c':
                delete [] srvopt.configFile;
                srvopt.configFile = strnew (optarg);
                break;
            case 'h':
                display_usage (argv[0], srvopt);
                return 0;
            case 'v':
                display_version ();
                return 0;
            default:
                abort ();
        }
    }

    static CommandDesc Commands [] =
    {
        {
            "start",     0,
            {
            }, CMDFUNC (cmdStart),
            "Starts the server"
        },
        {
            "stop",      0,
            {
            }, CMDFUNC (cmdStop),
            "Stop the server"
        },
        {
            "quit",      0,
            {
            }, CMDFUNC (cmdQuit),
            "Quit and shutdown server"
        },
        {
            "exit",      0,
            {
            }, CMDFUNC (cmdQuit),
            "Exit and shutdown server"
        },
        {
            "ver",       0,
            {
            }, CMDFUNC (cmdVersion),
            "Display server and expected client version"
        },
        {
            "realms",    0,
            {
            }, CMDFUNC (cmdRealmList),
            "Print the realmlist"
        },
        {
            "log",       1,
            {
                ARG_OSTR
            }, CMDFUNC (cmdLog),
            "Set/display logging options for Realm List server"
        },
        {
            "rdb",       2,
            {
                ARG_STR, ARG_STR
            }, CMDFUNC (cmdRealmDb),
            "Set up the SQL database"
        },
    };

    display_version ();

    CommandInterpreter (srvopt.configFile, &srvopt,
        Commands, ARRAY_LEN (Commands),
        "\ax1realm\ax9list\axf> \ax7");

    return 0;
}
