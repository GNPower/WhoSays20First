/** @file player.c
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

#include "player.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Function Prototypes ******************************/

/************************** Function Definitions *****************************/

GStatus Player_Init(Actor_t Actor)
{
    Actor->Action = Player_Act;

    return GST_SUCCESS;
};

GStatus Player_Act(game_t game, void* Actor)
{
    GStatus ActionState = GST_INVALID_STATE;    
    int score = 0;
    while(ActionState == GST_INVALID_STATE)
    {
        printf("Add 1 or 2? : ");
        fflush(stdout);
        scanf("%d", &score);
        ActionState = Game_AdvanceState(game, (uint8_t) score);
        if (ActionState == GST_INVALID_STATE)
        {
            printf("Input Not Allowed, Can Only Be 1 or 2!\n");
        }
    }

    return ActionState;
};

/*** end of file ***/