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

GStatus Dynamic_AI(uint8_t Score, uint8_t *Advancement);

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
    Dynamic_AI(game->State, &Advancement);

    #ifdef VERBOSE_OUTPUT
    printf("DynamicP AI Adds: %u\n", Advancement);
    #endif
    ActionState = Game_AdvanceState(game, Advancement);

    return ActionState;
};

GStatus Dynamic_Evaluate(uint8_t Score, uint8_t MyTurn, int *Eval)
{
    // printf("Debug evl - s, mt: %u, %u\n", Score, MyTurn);
    GStatus FoundEndGame;
    if (Score > MAX_STATE) // Make sure no one tries to make illegal moves
    {
        *Eval = -100;
        FoundEndGame = GST_SUCCESS;
    }
    else if (Score == MAX_STATE && MyTurn == 1) // Score is already 20 on my turn, other player won
    {
        *Eval = -10;
        FoundEndGame = GST_SUCCESS;
    }
    else if (Score == MAX_STATE && MyTurn == 0) // Score is already 20 on other players turn, I won
    {
        *Eval = 10;
        FoundEndGame = GST_SUCCESS;
    }
    else // Score is not 20, nobody won
    {
        *Eval = 0;
        FoundEndGame = GST_FAILURE;
    }

    return FoundEndGame;
}

GStatus Dynamic_Reward(uint8_t Score, uint8_t Depth, uint8_t MyTurn, float *Reward)
{
    int score = 0;
    GStatus EvalResult = Dynamic_Evaluate(Score, MyTurn, &score);
    // printf("Debug evl_r st, sc: %u , %d\n", EvalResult, score);
    if (EvalResult == GST_SUCCESS)
    {
        *Reward = score;
        return GST_SUCCESS;
    }

    float tmp;
    float max;
    float gamma = pow(0.5, Depth);

    if (MyTurn) // Dynamic AI Player
    {
        max = -100000;
        // Calculate for a move of add 1
        Dynamic_Reward(Score+1, Depth+1, 0, &tmp);
        if (tmp > max)
        {
            max = tmp;
        }
        // Calculate for a move of add 2
        Dynamic_Reward(Score+2, Depth+1, 0, &tmp);
        if (tmp > max)
        {
            max = tmp;
        }
    }
    else // Opponent
    {
        max = 100000;
        // Calculate for a move of add 1
        Dynamic_Reward(Score+1, Depth+1, 1, &tmp);
        if (tmp < max)
        {
            max = tmp;
        }
        // Calculate for a move of add 2
        Dynamic_Reward(Score+2, Depth+1, 1, &tmp);
        if (tmp < max)
        {
            max = tmp;
        }
    }

    *Reward = (gamma*max);

    #ifdef TRACE_CALCS
    int i;
    for (i = 0; i < Depth; i++){printf("\t");}
    printf("Reward Score(%u), Depth(%u), MyTurn(%u), Gamma(%.5e), Max(%.5e), Reward(%.5e)\n", Score, Depth, MyTurn, gamma, max, *Reward);
    #endif

    return GST_SUCCESS;
}


// Done assuming the other player will also play optimally
GStatus Dynamic_AI(uint8_t Score, uint8_t *Advancement)
{
    // Set the default advancement to 1, just in case an error occurs
    *Advancement = 1U;
    float bestMove = -10000;
    float tmp;

    // Check if advancing by 1 is the best move
    #ifdef TRACE_CALCS
    printf("Calculate Add One Reward...\n");
    #endif

    Dynamic_Reward(Score+1, 0, 0, &tmp);

    #ifdef TRACE_CALCS
    printf("Add One Reward: %.5e\n", tmp);
    #endif

    if (tmp > bestMove)
    {
        bestMove = tmp;
        *Advancement = 1U;
    }

    // Check if advancing by 2 is the best move
    #ifdef TRACE_CALCS
    printf("Calculate Add Two Score...\n");
    #endif

    Dynamic_Reward(Score+2, 0, 0, &tmp);

    #ifdef TRACE_CALCS
    printf("Add Two Reward: %.5e\n", tmp);
    #endif

    if (tmp > bestMove)
    {
        bestMove = tmp;
        *Advancement = 2U;
    }

    #ifdef TRACE_CALCS
    printf("Best Move Is Add %u\n", *Advancement);
    #endif

    return GST_SUCCESS;
};

/*** end of file ***/