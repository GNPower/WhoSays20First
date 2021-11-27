/** @file game.c
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

#include "game.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Function Prototypes ******************************/

/************************** Function Definitions *****************************/

GStatus Game_Init (game_t game, Actor_t player1, Actor_t player2)
{
    game->State = 0;
    game->Won = GAME_NOT_WON;
    game->Player1 = player1;
    game->Player2 = player2;
    game->PlayerTurn = TURN_PLAYER1;

    #ifdef VERBOSE_OUTPUT

    printf("===== WHO SAY'S 20 FIRST =====\n");

    #endif

    return GST_SUCCESS;
};

GStatus Game_SpinOnce(game_t game)
{
    GStatus ActionStatus = GST_FAILURE;
    Game_PrintTurn(game);
    if (game->State == GAME_WON)
    {
        return GST_SUCCESS;
    }
    if (game->PlayerTurn == TURN_PLAYER1)
    {
        ActionStatus = game->Player1->Action(game, game->Player1->ActorBase);
        game->PlayerTurn = TURN_PLAYER2;
    }
    else if (game->PlayerTurn == TURN_PLAYER2)
    {
        ActionStatus = game->Player2->Action(game, game->Player2->ActorBase);
        game->PlayerTurn = TURN_PLAYER1;
    }
    Game_PrintScore(game);

    return ActionStatus;
};

GStatus Game_Spin(game_t game)
{
    GStatus ActionStatus = Game_SpinOnce(game);
    while (ActionStatus == GST_SUCCESS)
    {
        ActionStatus = Game_SpinOnce(game);
    }

    #ifdef VERBOSE_OUTPUT
    if (ActionStatus == GST_GAME_WON)
    {
        printf("\n\nGame Over!\n");
        if (game->PlayerTurn == TURN_PLAYER1)
        {
            printf("Player 2 Wins!\n");
        }
        else
        {
            printf("Player 1 Wins!\n");
        }
    }
    #endif

    return ActionStatus;
};

GStatus Game_AdvanceState(game_t game, uint8_t advancement)
{
    if (advancement <= 0 || advancement > MAX_STATE_ADVANCEMENT || game->State + advancement > MAX_STATE)
    {
        return GST_INVALID_STATE;
    }
    if (game->Won == GAME_WON)
    {
        return GST_GAME_WON;
    }

    game->State += advancement;

    if (game->State == MAX_STATE)
    {
        game->Won = GAME_WON;
        return GST_GAME_WON;
    }
    else
    {
        return GST_SUCCESS;
    }    
};

GStatus Game_GetState(game_t game, uint8_t *state)
{
    *state = game->State;

    return GST_SUCCESS;
};

GStatus Game_IsWon(game_t game, uint8_t *isWon)
{
    *isWon = game->Won;

    return GST_SUCCESS;
};

GStatus Game_PrintTurn(game_t game)
{
    #ifdef VERBOSE_OUTPUT
    if (game->PlayerTurn == TURN_PLAYER1)
    {
        printf("\n\nTurn: Player 1\n");
    }
    else
    {
        printf("\n\nTurn: Player 2\n");
    }
    #endif

    return GST_SUCCESS;
};

GStatus Game_PrintScore(game_t game)
{
    #ifdef VERBOSE_OUTPUT
    printf("\nCurrent Score: %u\n", game->State);
    #endif

    return GST_SUCCESS;
};

/*** end of file ***/