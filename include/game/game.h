/** @file game.h
 * 
 * @brief The game state of "Who Say's 20 First". 
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

#ifndef GNP_GAME_H		/* prevent circular inclusions */
#define GNP_GAME_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include <stdint.h>
#include <stdio.h>

#include "status.h"

/************************** Constant Definitions *****************************/

#define GAME_NOT_WON   0U
#define GAME_WON       1U

#define MAX_STATE               20U
#define MAX_STATE_ADVANCEMENT   2U

#define TURN_PLAYER1    1U
#define TURN_PLAYER2    2U

/**************************** Type Definitions *******************************/

typedef struct game *game_t;
typedef struct Actor *Actor_t;

struct game
{
    uint8_t State;
    uint8_t Won; 
    Actor_t Player1;
    Actor_t Player2;
    uint8_t PlayerTurn;
};

struct Actor {
    GStatus (*Action)(game_t, void *Actor);
    void* ActorBase;   
};

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

GStatus Game_Init (game_t game, Actor_t player1, Actor_t player2);
GStatus Game_SpinOnce(game_t game);
GStatus Game_AdvanceState(game_t game, uint8_t advancement);
GStatus Game_GetState(game_t game, uint8_t *state);
GStatus Game_IsWon(game_t game, uint8_t *isWon);
GStatus Game_PrintScore(game_t game);

#ifdef __cplusplus
}
#endif

#endif /* GNP_GAME_H */

/*** end of file ***/