/** @file parameters.h
 * 
 * @brief A collection of parameters used to determine how the game functions. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2021 Graham Power.  All rights reserved.
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */ 

#ifndef GNP_PARAMS_H		/* prevent circular inclusions */
#define GNP_PARAMS_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include <stdint.h>

/************************** Constant Definitions *****************************/

// Enables game state and non-player state updates in the terminal.
// Uncomment to remove.
#define VERBOSE_OUTPUT

// Enables detailed output about the calculations preformed by non-user players.
// Uncomment to enable. This will make the terminal output very messy.
#define TRACE_CALCS

// Types of players.
// Don't change these!
#define USER    0U      // A manual player, who will interact with the terminal.
#define DYNAMIC 1U      // An ai player, who will use dynamic programming to play.

// Sets the type of player 1 and 2.
// Can be any of 'USER', 'DYNAMIC'.
#define PLAYER1     USER
#define PLAYER2     DYNAMIC

#ifdef __cplusplus
}
#endif

#endif /* GNP_PARAMS_H */

/*** end of file ***/