/**
 *     \file  src/worldserver/Main.cpp
 *    \brief  The one, true World server.
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

#include <getopt.h>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
}

#include "WorldServer.h"
#include "Database.h"
#include "Console.h"
#include "CommandInterpreter.h"
#include "StringFun.h"
#include "version.h"

struct ServerOptions
{
    bool Running;
    /// World database
    Database *wdb;
    /// World database host/login/password/database
    char *wDbType, *wDbAddr;
    /// Realm database (can be same as world database for small installations)
    Database *rdb;
    /// Realm database host/login/password/database
    char *rDbType, *rDbAddr;
    /// Config file (startup script)
    char *ConfigFile;
    /// The world server
    WorldServer *ws;

    ServerOptions ()
    {
        Running = false;
        wDbType = strnew (DEFDBTYPE);
        wDbAddr = strnew (DEFDBADDR);
        rDbType = strnew (DEFDBTYPE);
        rDbAddr = strnew (DEFDBADDR);
        ConfigFile = strnew (WS_CONFIG_FILE);
        wdb = rdb = NULL;
        ws = new WorldServer (8129, new Log ("worldserv.log"));
    }

    ~ServerOptions ()
    {
        StopServer ();
        CloseDatabase ();
        ws->DecRef ();
        delete [] wDbType;
        delete [] wDbAddr;
        delete [] rDbType;
        delete [] rDbAddr;
        delete [] ConfigFile;
    }

    bool CreateDatabase ()
    {
        if (!wdb)
        {
            CONSOLE.Out ("\axaOpening world database\n");
            wdb = Database::Create (Database::ParseType (wDbType), wDbAddr);
            if (IS_ERR (wdb))
            {
                CONSOLE.Out ("\axcERROR: \axeFailed to open database: %s\n",
                                    Database::ErrorString ((DatabaseError)PTR_ERR (wdb)));
                wdb = NULL;
                return false;
            }
        }
        if (!rdb)
        {
            CONSOLE.Out ("\axaOpening realm database\n");
            rdb = Database::Create (Database::ParseType (rDbType), rDbAddr);
            if (IS_ERR (rdb))
            {
                CONSOLE.Out ("\axcERROR: \axeFailed to open database: %s\n",
                                    Database::ErrorString ((DatabaseError)PTR_ERR (rdb)));
                rdb = NULL;
                return false;
            }
        }
        return true;
    }

    void CloseDatabase ()
    {
        if (wdb)
        {
            CONSOLE.Out ("\axaClosing world database connection\n");
            wdb->DecRef ();
            wdb = NULL;
        }
        if (rdb)
        {
            CONSOLE.Out ("\axaClosing realm database connection\n");
            rdb->DecRef ();
            rdb = NULL;
        }
    }

    void StartServer ()
    {
        if (!CreateDatabase ())
            return;

        if (!ws->IsRunning ())
        {
            CONSOLE.Out ("\axaStarting world server\n");
            ws->SetDatabase (wdb, rdb);
            if (ws->Start ())
                CONSOLE.Out ("\axeUp and running.\n");
        }
        else
            CONSOLE.Out ("\axeWARNING: \ax2World server already running\n");
    }

    void StopServer ()
    {
        if (ws->IsRunning ())
        {
            CONSOLE.Out ("\axaStopping world server\n");
            ws->Stop ();
            CONSOLE.Out ("\axeServer down.\n");
        }
    }
};

static void display_version ()
{
    CONSOLE.Out (
        "\ax9World Server\ax2, version \axf%s\ax2\n"
        "Copyright \axf(C) \ax2%s\ax2\n",
        VERSION, COPYRIGHT);

    /// GPL v3 notice
    CONSOLE.Out (
        "\n\ax2This is free software.  You may redistribute copies of it under the terms of\n"
        "\ax2the GNU General Public License <http://www.gnu.org/licenses/gpl.html>.\n"
        "\ax2There is NO WARRANTY, to the extent permitted by law.\ax2\n");

    /// SRP notice
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
        , argv0, srvopt.ConfigFile);
}

static int cmdVersion (ServerOptions *srvopt)
{
    (void)srvopt;
    CONSOLE.Out (
        "\ax2** OpenWoW World Server **    \axa%s\ax2    for clients \axa%d..%d\ax2 **\n",
        FULLVERSION, MIN_CLIENT_BUILD, MAX_CLIENT_BUILD);
    return 0;
}

static int cmdQuit (ServerOptions *srvopt)
{
    (void)srvopt;
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

static int cmdRealm (ServerOptions *srvopt, char *Name)
{
    if (Name)
        srvopt->ws->SetRealmName (Name);
    else
        CONSOLE.Out (
            "\ax3Server realm is now: \axa%s\ax2\n",
            srvopt->ws->GetRealmName ());
    return 0;
}

static int cmdRealmDB (ServerOptions *srvopt, char *DbType, char *DbAddr)
{
    if (DbType)
    {
        delete [] srvopt->rDbType;
        srvopt->rDbType = strnew (DbType);
        delete [] srvopt->rDbAddr;
        srvopt->rDbAddr = strnew (DbAddr);
        if (srvopt->rdb)
            CONSOLE.Out (
                "\axeServer is running, changes will take place after restart\ax2\n");
    }
    return 0;
}

static int cmdWorldDB (ServerOptions *srvopt, char *DbType, char *DbAddr)
{
    delete [] srvopt->wDbType;
    srvopt->wDbType = strnew (DbType);
    delete [] srvopt->wDbAddr;
    srvopt->wDbAddr = strnew (DbAddr);
    if (srvopt->wdb)
        CONSOLE.Out (
            "\axeServer is running, changes will take place after restart\ax2\n");
    return 0;
}

static int cmdBroadcast (ServerOptions *srvopt, const char *Text)
{
    (void)srvopt;
    srvopt->ws->SendGlobalMessage (Text, NULL);
    CONSOLE.Out (
        "\ax3Message sent to all players: \axa%s\ax2\n", Text);
    return 0;
}

static int cmdInfo (ServerOptions *srvopt)
{
    time_t time = srvopt->ws->GetGameTime ();
    int hour = time / 3600; time %= 3600;
    int mins = time / 60; time %= 60;
    int secs = time;
    CONSOLE.Out (
        "\ax3Users connected:  \axa%d\ax2\n"
        "\ax3Game time is now: \axa%d:%d:%d\ax2\n",
        srvopt->ws->GetClientsConnected (),
        hour, mins, secs);
    return 0;
}

static int cmdMotd (ServerOptions *srvopt, char *Motd)
{
    (void)srvopt;
    if (Motd)
        srvopt->ws->SetMotd (Motd);
    else
        CONSOLE.Out (
            "\ax3Current MOTD is: \axa%s\ax2\n",
            srvopt->ws->GetMotd ());
    return 0;
}

static int cmdLog (ServerOptions *srvopt, char *LogOpt)
{
    Log &Logger = *srvopt->ws->Logger;
    if (LogOpt)
        Logger.Logging (LogOpt);
    else
    {
        char buff [100];
        Logger.GetLogging (buff, sizeof (buff));
        CONSOLE.Out ("\ax3World server logging: \axa%s\ax2\n", buff);
    }
    return 0;
}

static int cmdCinematics (ServerOptions *srvopt, uintptr Enable)
{
    (void)srvopt;
    if (Enable != NO_ARG)
                srvopt->ws->SetCinematics (Enable != 0);
    CONSOLE.Out (
        "\ax3Server Cinematics are currently: \axa%s\ax2\n",
        srvopt->ws->GetCinematics () ? "on" : "off");
    return 0;
}

static int cmdStartZone (ServerOptions *srvopt, uintptr Zone)
{
    (void)srvopt;
    if (Zone != NO_ARG)
        srvopt->ws->SetStartZone (Zone);
    else
        CONSOLE.Out (
            "\ax3Server start zone set to: \axa%s\ax2\n",
            srvopt->ws->GetStartZone () ?
            "Human Zone" : "Normal Race Zone");
    return 0;
}

static int cmdLimit (ServerOptions *srvopt, uintptr Limit)
{
    (void)srvopt;
    if (Limit != NO_ARG)
        srvopt->ws->SetClientLimit (Limit);
    else
        CONSOLE.Out (
            "\ax3Current player limit set to: \axa%u\ax2\n",
                    srvopt->ws->GetClientLimit ());
    return 0;
}

static int cmdLoad (ServerOptions *srvopt, char *File)
{
    int s = luaL_loadfile (srvopt->ws->Lua, File);

    if (s == 0)
        // execute Lua program
        s = lua_pcall (srvopt->ws->Lua, 0, LUA_MULTRET, 0);

    if (s != 0)
    {
        CONSOLE.Out ("\ax6WARNING: \axe%s\n",
                     lua_tostring (srvopt->ws->Lua, -1));
        lua_pop (srvopt->ws->Lua, 1);  // remove error message
    }
    else
        CONSOLE.Out ("\axa%s\ax2 loaded\n", File);

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

    while ((c = getopt_long(argc, argv, "c:hv", long_options, NULL)) != EOF) {
        switch (c) {
        case 'c':
            delete [] srvopt.ConfigFile;
            srvopt.ConfigFile = strnew (optarg);
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
        { "start",     0, {}, CMDFUNC (cmdStart),
          "Start the server" },
        { "stop",      0, {}, CMDFUNC (cmdStop),
          "Stop and shutdown server" },
        { "exit",      0, {}, CMDFUNC (cmdQuit),
          "Exit and shutdown server" },
        { "quit",      0, {}, CMDFUNC (cmdQuit),
          "Quit and shutdown server" },
        { "ver",       0, {}, CMDFUNC (cmdVersion),
          "Display server and expected client version" },
        { "realm",     1, { ARG_OSTR }, CMDFUNC (cmdRealm),
          "Set the World Server realm name" },
        { "rdb",       2, { ARG_OSTR, ARG_STR }, CMDFUNC (cmdRealmDB),
          "Set the realm database type and address" },
        { "wdb",       2, { ARG_OSTR, ARG_STR }, CMDFUNC (cmdWorldDB),
          "Set the world database type and address" },
        { "bcast",     1, { ARG_OSTR }, CMDFUNC (cmdBroadcast),
          "Send a system message to all the players in the world" },
        { "info",      0, {}, CMDFUNC (cmdInfo),
          "Show miscelaneous information about current state of the server" },
        { "motd",      1, { ARG_OSTR }, CMDFUNC (cmdMotd),
          "Set/display the current MOTD" },
        { "log",       1, { ARG_OSTR }, CMDFUNC (cmdLog),
          "Set world server logging flags" },
        { "cinematics",1, { ARG_OBOOL }, CMDFUNC (cmdCinematics),
          "Set/display server cinematics" },
        { "stzone",    1, { ARG_OINT }, CMDFUNC (cmdStartZone),
          "Set/display the default start zone (0-Normal, 1-Human)" },
        { "limit",     1, { ARG_OINT }, CMDFUNC (cmdLimit),
          "Set/display the player limit" },
        { "load",     1, { ARG_STR }, CMDFUNC (cmdLoad),
          "Load a Lua script file" },
    };

    display_version ();

    CommandInterpreter (srvopt.ConfigFile, &srvopt,
                Commands, ARRAY_LEN (Commands),
                "\ax1world\ax9srv\axf> \ax7");

    return 0;
}
