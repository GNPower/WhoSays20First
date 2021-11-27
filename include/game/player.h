/** @file PLAYER.h
 * 
 * @brief A manual player for the game. 
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

#ifndef GNP_PLAYER_H		/* prevent circular inclusions */
#define GNP_PLAYER_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "status.h"
#include "game.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

GStatus Player_Init(Actor_t Actor);
GStatus Player_Act(game_t game, void* ActorBase);


#ifdef __cplusplus
}
#endif

#endif /* GNP_PLAYER_H */

/*** end of file ***/