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

GStatus Dynamic_AI(hashtable_t table, uint8_t Score, uint8_t *Advancement);

/************************** Function Definitions *****************************/

/**
 * @brief 
 * Initializes a Dynamic Programming controller Actor. Actors are the
 * name used for anything capable of making advancements in the game 
 * state (i.e. adding 1 or 2). This takes in the Actor who will use 
 * its Dynamic_Act function, the Dynamic type used to store a class-like 
 * object, and the hashtable to be used.
 * 
 * @param Actor The actor who will use Dynamic_Act to advance a game state. 
 * @param Dynamic The pointer to the dynamic struct, used as a class-like representation.
 * @param table The hashtable used by this dynamic programming instance.
 * @return GStatus The success of the initialization.
 */
GStatus Dynamic_Init(Actor_t Actor, dynamic_t Dynamic, hashtable_t table)
{
    // Set the action the passed in actor uses to Dynamic_Act
    Actor->Action = Dynamic_Act;

    // Initialize and store the hashtable to use
    Hashtable_Init(table);
    Dynamic->table = table;

    // Set the actors base structure to a Dynamic strucure
    Actor->ActorBase = Dynamic;

    return GST_SUCCESS;
};

/**
 * @brief 
 * Takes an action of behalf of the Actor that called it. 
 * This action will calculate the best next move, either 
 * adding 1 or 2, and take it.
 * 
 * @param game The game to take the action in.
 * @param ActorBase 
 * The Actors base structure, stores information Dynamic 
 * Programming instances need to take their actions.
 * @return GStatus The success of the action.
 */
GStatus Dynamic_Act(game_t game, void *ActorBase)
{
    // Recover the Dynamic structure from the Actors base structure
    dynamic_t Dynamic = (dynamic_t) ActorBase;

    // Variable to store the result of this action
    GStatus ActionState;

    // Set the default action to add 1, in case there is an error
    // and then calculate the actual action to take using the 
    // Dynamic_AI function (bottom of file)
    uint8_t Advancement = 1U;
    Dynamic_AI(Dynamic->table, game->State, &Advancement);

    #ifdef VERBOSE_OUTPUT
    printf("DynamicP AI Adds: %u\n", Advancement);
    #endif
    ActionState = Game_AdvanceState(game, Advancement);

    return ActionState;
};

/**
 * @brief Calculates the Reward for being in a state.
 * 
 * @param Score The current game score.
 * @param MyTurn 
 * Whether or not it is the Dynamic Programming instances turn. 
 * 1 = Yes, 0 = No.
 * @param Eval Pointer to an int. Dynamic_Evaluate stores its result here.
 * @return GStatus The success of the evaluation.
 */
GStatus Dynamic_Evaluate(uint8_t Score, uint8_t MyTurn, int *Eval)
{
    // Status returns GST_SUCCESS if we have just evaluated the last
    // possible state in the game, GST_FAILURE otherwise
    GStatus FoundEndGame;
    if (Score > MAX_STATE) // Make sure no one tries to make illegal moves (i.e. add beyond 20)
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

/**
 * @brief 
 * Recursively calculates the expected reward for being in this state. 
 * Given as a sum of discounted rewards of this state and all future 
 * possible states.
 * 
 * @param table The hashtable used to store previously calculated rewards.
 * @param Score The score of the current game.
 * @param Depth How many actions ahead we are currently looking.
 * @param MyTurn 
 * Whether or not it is the Dynamic Programming instances turn. 
 * 1 = Yes, 0 = No.
 * @param Reward Pointer to a float. Dynamic_Reward stores its result here.
 * @return GStatus Status of the reward calculation.
 */
GStatus Dynamic_Reward(hashtable_t table, uint8_t Score, uint8_t Depth, uint8_t MyTurn, float *Reward)
{
    // Evaluates the score in the current state
    int score = 0;
    GStatus EvalResult = Dynamic_Evaluate(Score, MyTurn, &score);

    // If the current state is the last state in the game, return the result directly
    if (EvalResult == GST_SUCCESS)
    {
        *Reward = score;
        return GST_SUCCESS;
    }

    // Variables to store intermediate calculations, the max found reward, and the gamma value.
    float tmp;
    float max;
    float gamma = pow(0.5, Depth);

    // Use the Hashtable stored value, if it exists
    GStatus Hashtable_Valid = Hashtable_Get(table, Score, MyTurn, Reward);
    if (Hashtable_Valid == GST_SUCCESS)
    {
        #ifdef TRACE_CALCS
        printf("Reward Score (%.5e) -- Using Hashtable Stored Value!\n", *Reward);
        #endif
        return GST_SUCCESS;
    }

    if (MyTurn) // Calculate the Reward obtained by us, the Dynamic AI Player
    {
        max = -100000;
        // Calculate for a move of add 1
        Dynamic_Reward(table, Score+1, Depth+1, 0, &tmp);
        if (tmp > max)
        {
            max = tmp;
        }
        // Calculate for a move of add 2
        Dynamic_Reward(table, Score+2, Depth+1, 0, &tmp);
        if (tmp > max)
        {
            max = tmp;
        }
    }
    else // Calculate the Reward obtained by our Opponent
    {
        max = 100000;
        // Calculate for a move of add 1
        Dynamic_Reward(table, Score+1, Depth+1, 1, &tmp);
        if (tmp < max) // Here we want the smallest reward, since a good reward for our opponent is bad for us
        {
            max = tmp;
        }
        // Calculate for a move of add 2
        Dynamic_Reward(table, Score+2, Depth+1, 1, &tmp);
        if (tmp < max) // Here we want the smallest reward, since a good reward for our opponent is bad for us
        {
            max = tmp;
        }
    }

    // Calculate the reward contribution in this state
    *Reward = (gamma*max);

    // Store the reward in the Hashtable
    Hashtable_Put(table, Score, MyTurn, *Reward);

    #ifdef TRACE_CALCS
    int i;
    for (i = 0; i < Depth; i++){printf("\t");}
    printf("Reward Score(%u), Depth(%u), MyTurn(%u), Gamma(%.5e), Max(%.5e), Reward(%.5e)\n", Score, Depth, MyTurn, gamma, max, *Reward);
    #endif

    return GST_SUCCESS;
}

/**
 * @brief 
 * Calculates the best possible move to make, given the current 
 * score of the game. Done assuming the other player will also 
 * play optimally.
 * 
 * @param table The hashtable used to store previously calculated rewards.
 * @param Score The score of the current game.
 * @param Advancement Pointer to a uint. Dynamic_AI stores the action to take here.
 * @return GStatus The Status of the action calculation.
 */
GStatus Dynamic_AI(hashtable_t table, uint8_t Score, uint8_t *Advancement)
{
    // Set the default advancement to 1, just in case an error occurs
    *Advancement = 1U;
    float bestMove = -10000;
    float tmp;

    // Check if advancing by 1 is the best move
    #ifdef TRACE_CALCS
    printf("Calculate Add One Reward...\n");
    #endif

    // Calculate the reward that would be obtained if we added 1
    Dynamic_Reward(table, Score+1, 0, 0, &tmp);

    #ifdef TRACE_CALCS
    printf("Add One Reward: %.5e\n", tmp);
    #endif

    // If adding one gives us the highest rewards, choose to add 1
    if (tmp > bestMove)
    {
        bestMove = tmp;
        *Advancement = 1U;
    }

    // Check if advancing by 2 is the best move
    #ifdef TRACE_CALCS
    printf("Calculate Add Two Score...\n");
    #endif

    // Calculate the reward that would be obtained if we added 2
    Dynamic_Reward(table, Score+2, 0, 0, &tmp);

    #ifdef TRACE_CALCS
    printf("Add Two Reward: %.5e\n", tmp);
    #endif

    // If adding two gives us the highest rewards, choose to add 2
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