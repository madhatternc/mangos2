/**
 *     \file  src/shared/Console.h
 *    \brief  Functions for cross-platform console handling
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

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Common.h"
#include "Singleton.h"

/**
 *  \def CONSOLE
 *
 *  Handy shortcut
 */
#define CONSOLE (Console::getSingleton ())

/**
 *  \class Console
 *  \brief A class for interacting with the console.
 *
 *  \details
 *  Why a class?... hard to say, mostly to keep hardcore C++ guys happy.
 *  For now uses STDIN/STDOUT handles; no initialization parameters are
 *  allowed due to the Singleton architecture.
 */
class Console : public Singleton <Console>
{
    public:
        /**
         *  \enum KeyCodes
         *  \brief Key codes as returned by ReadKey ().
         *
         *  \details
         *  \li \c 1-31     special keys like backspace, enter etc
         *  \li \c 32..255  ASCII extended codes
         *  \li \c 256..511 Functional keys, arrows, ins/del etc.
         *
         *  \par
         *  Also if a key has been pressed together with a modifier like Ctrl
         *  or Alt, it is added 512 and/or 1024 respectively.
         *
         *  \par
         *  For example, Alt-A would return 1024+65 = 1089, Ctrl-A would return
         *  512 + 65 = 577, Ctrl-Alt-A would return 512 + 1024 + 65 = 1601 and so on.
         */
        enum KeyCodes
        {
            /**
             *  \brief Use this mask to extract just the base key code
             */
            MASK_KEY = 511,

            /**
             *  \brief This mask denotes that a key was pressed together with CTRL
             */
            MASK_CTRL = 512,

            /**
             *  \brief This mask denotes that a key was pressed together with ALT
             */
            MASK_ALT = 1024,

            /**
             *  \brief Key was pressed together with SHIFT (ONLY for functional keys)
             */
            MASK_SHIFT = 2048,

            // Special keys
            KEY_BACKSP = 8,
            KEY_ENTER = 13,
            KEY_ESC = 27,
            KEY_TAB = 9,

            // Extended function keys
            KEY_F1 = 256,
            KEY_F2,
            KEY_F3,
            KEY_F4,
            KEY_F5,
            KEY_F6,
            KEY_F7,
            KEY_F8,
            KEY_F9,
            KEY_F10,
            KEY_F11,
            KEY_F12,
            KEY_UP,
            KEY_DOWN,
            KEY_LEFT,
            KEY_RIGHT,
            KEY_HOME,
            KEY_END,
            KEY_INS,
            KEY_DEL,
            KEY_PGUP,
            KEY_PGDN
        };

        /**
         *  \enum ConsoleTextColor
         *  \brief Console text color constants.
         *
         *  \details
         *  Console text color constants (used as values 0 to 0xf in
         *  Out ()). Foreground colors are allowed in the 0..15 range,
         *  background in 0..7 range.
         */
        enum ConsoleTextColor
        {
            BLACK = 0,
            DBLUE,
            DGREEN,
            DCYAN,
            DRED,
            DMAGENTA,
            BROWN,
            GRAY,
            LGRAY,
            LBLUE,
            LGREEN,
            LCYAN,
            LRED,
            LMAGENTA,
            YELLOW,
            WHITE
        };

        /**
         *  \brief Set this to false to disable colored text output
         */
        static bool UseColoredText;

        //-------------------------------------------------------------------//

        /**
         *  \brief Initialize the object
         */
        Console ();

        /**
         *  \brief Destroy the object
         */
        ~Console ();

        /**
         *  \brief Get terminal size.
         */
        static void GetSize (int *Columns, int *Rows);

        /**
         *  \brief Clear the whole screen. This resets textcolor to the defaults.
         */
        static void Clear ();

        /**
         *  \brief Change console text color to given Foreground/Background colors.
         *
         *  \note
         *  If either fg and/or bg is -1, that one does not change.
         */
        static void SetTextColor (int fg, int bg);

        /**
         *  \brief Get current text color.
         */
        static void GetTextColor (uint8 *fg, uint8 *bg);

        /**
         *  \brief The most basic console output routine.
         *
         *  \details
         *  The most basic console output routine. Usually not used,
         *  provided just for implementing more advanced functions like
         *  operator <<
         *
         *  \return Number of characters successfuly output.
         */
        static int RawOutput (const void *String, size_t Length);

        /**
         *  \brief Emit a string to console.
         *
         *  \details
         *  "\a1fBlah \axaYeah \a3xIndeed" would produce "Blah" as white
         *  letters on blue background, then "Yeah" as bright green letters
         *  on same background (any chars except 0-9 a-f A-F stay for
         *  "don't change"), and, finally, "Indeed" would be printed
         *  as bright green letters on cyan background.
         *
         *  \par
         *  If the two characters after \a are 'pu', the current color is
         *  pushed into a 32-element-deep stack, and there is the 'po' command
         *  for popping the text color from that stack. Make sure those always
         *  comes in pairs.
         */
        int operator << (const char *string);

        /**
         *  \brief Just like printf, but supports additional control codes
         *  \see operator <<
         *
         *  \return Number of actual characters displayed.
         */
        static int Out (const char *format, ...);

        /**
         *  \brief Check if a key was pressed.
         */
        static bool KeyPressed ();

        /**
         *  \brief Read a keycode from standard input.
         *
         *  \details
         *  Read (and wait for, if not available) a keycode from standard input.
         *  See the comments before the definition of the KeyCodes enum.
         *
         *  \par
         *  Also it has support for some control keys, defined by the KEY_XXX
         *  constants. Not that we write a game engine, but it supports at least
         *  the basic text editing keys.
         *
         *  \return -1 on errors or for unknown key pressed.
         */
        static int GetKey ();

        /**
         *  \brief Read a line from terminal, implementing minimal line editing capabilities.
         *
         *  \return Number of characters entered.
         */
        static int ReadLine (const char *Prompt, char *Buffer, size_t BufferSize);

        /**
         *  \brief Push a string into the readline's history buffer.
         */
        static void ReadLineHistoryPush (const char *String);

    private:
        /**
         *  \brief Readline history
         */
        static char *ReadlineHistory [32];
        static int ReadlineHistoryLen;

        /**
         *  \brief Current foreground color
         */
        static uint8 CurrentFG;

        /**
         *  \brief Current background color
         */
        static uint8 CurrentBG;

        /**
         *  \brief The stack for \aPU and \aPO ops
         */
        static uint8 ColorStack [64];
        static int ColorStackDepth;

        static void PushColor ();
        static void PopColor ();
};
#endif                                                      // __CONSOLE_H__
