/** @file dynamic.c
 * 
 * @brief 
 * An implementation of dynamic programming to play the game 
 * "Who Says 20 First". Assumes the other player also plays
 * optimally.
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

#include "dynamic.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Function Prototypes ******************************/

GStatus Dynamic_AI(uint8_t Score, uint8_t MyTurn, uint8_t *Advancement);

/************************** Function Definitions *****************************/

GStatus Dynamic_Init(Actor_t Actor, dynamic_t Dynamic)
{
    Actor->Action = Dynamic_Act;
    Actor->ActorBase = Dynamic;

    return GST_SUCCESS;
};

GStatus Dynamic_Act(game_t game, void *ActorBase)
{
    dynamic_t Dynamic = (dynamic_t) ActorBase;

    GStatus ActionState;

    uint8_t Advancement = 1U;
    Dynamic_AI(game->State, 1U, &Advancement);

    #ifdef VERBOSE_OUTPUT
    printf("DynamicP AI Adds: %u\n", Advancement);
    #endif
    ActionState = Game_AdvanceState(game, Advancement);

    return ActionState;
};

GStatus Dynamic_AI(uint8_t Score, uint8_t MyTurn, uint8_t *Advancement)
{
    *Advancement = 1U;

    return GST_SUCCESS;
};

/*** end of file ***/