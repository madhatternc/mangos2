/**
 *     \file  src/shared/CommandInterpreter.h
 *    \brief  Command line interpreter interface
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

#ifndef __COMMAND_INTERPRETER_H__
#define __COMMAND_INTERPRETER_H__

#include "Common.h"

/**
 *  \def MAX_COMMAND_ARGS
 *
 *  Maximum number of arguments to allow
 */
#define MAX_COMMAND_ARGS 4

/**
 *  \def ARG_STR
 *
 *  String arguments are passed as-is, with interpreted escape commands like \n\r\a\t etc
 */
#define ARG_STR     0

/**
 *  \def ARG_INT
 *
 *  Integer arguments
 */
#define ARG_INT     1

/**
 *  \def ARG_BOOL
 *
 *  Boolean arguments (on/off, yes/no, 1/0)
 */
#define ARG_BOOL    2

/**
 *  \def ARG_OPT
 *
 *  Missing optional strings are passed as NULLs, other types get NO_ARG
 */
#define ARG_OPT     0x80

/**
 *  \def ARG_OSTR
 *  \see ARG_STR
 *  Optional string arguments.
 */
#define ARG_OSTR    (ARG_OPT | ARG_STR)

/**
 *  \def ARG_OINT
 *  \see ARG_INT
 *  Optional integer arguments.
 */
#define ARG_OINT    (ARG_OPT | ARG_INT)

/**
 *  \def ARG_OBOOL
 *  \see ARG_BOOL
 *  Optional BOOL arguments.
 */
#define ARG_OBOOL   (ARG_OPT | ARG_BOOL)

/**
 *  \def NO_ARG
 *
 *  No argument used.
 */
#define NO_ARG      ((uintptr)-1)

/**
 *  \struct CommandDesc
 *  \brief This structure describes a server console command.
 */
struct CommandDesc
{
    /**
     *  \brief The command
     */
    const char *Name;

    /**
     *  \brief Number of command arguments
     */
    int NumArgs;

    /**
     *  \brief An array of command argument types (OPTional arguments may be missing)
     */
    uint8 Type [MAX_COMMAND_ARGS];

    /**
     *  \typedef typedef int (*ExecuteFunc)
     *  \brief The command callback
     *
     *  \details
     *  The command callback; if it returns non-zero, interpreter quits.
     *  Every parameter specified in the Type array is passed either
     *  as a char *pointer (ARG_STR) or a uintptr (ARG_INT and ARG_BOOL).
     */
    typedef int (*ExecuteFunc) (void *, ...);
    ExecuteFunc Execute;
    #define CMDFUNC(x) ((CommandDesc::ExecuteFunc)x)

    /**
     *  \brief Command description
     */
    const char *Description;
};

/**
 *  \brief Invoke an interactive command interpreter.
 *
 *  \arg \c  ConfigFile
 *    This is the 'autoexec' script to execute at startup.
 *  \arg \c  UserData
 *    A black box pointer to be passed to every Execute() function as first arg.
 *  \arg \c  Commands
 *    Pointer to array of structs describing the commands.
 *  \arg \c  NumCommands
 *    The number of elements in the Commands array.
 *  \arg \c  Prompt
 *    The prompt to display for command input.
 *  \arg \c  BadCommandHint
 *    The hint to display after "Bad command".
 *   \return Nothing
 */
extern void CommandInterpreter (const char *ConfigFile, void *UserData,
CommandDesc *Commands, int NumCommands,
const char *Prompt);
#endif                                                      // __COMMAND_INTERPRETER_H__
