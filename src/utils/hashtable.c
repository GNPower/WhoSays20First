/** @file hashtable.c
 * 
 * @brief 
 * A hashtable to store the results of AI actions. So trees don't
 * have to be explored more than once
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

#include "hashtable.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Function Prototypes ******************************/

/************************** Function Definitions *****************************/

GStatus Hashtable_Init(hashtable_t table)
{
    unsigned int i;
    for (i = 0U; i < HASH_MAX_CAPACITY; i++)
    {
        table->hash_used[i] = 0U;
    }

    return GST_SUCCESS;
};

GStatus Hashtable_Put(hashtable_t table, uint8_t Score, uint8_t MyTurn, float Reward)
{
    unsigned long hash = (1U + MyTurn)*Score;
    if (hash >= HASH_MAX_CAPACITY)
    {
        return GST_FAILURE;
    }

    table->hash_map[hash] = Reward;

    return GST_SUCCESS;
};

GStatus Hashtable_Get(hashtable_t table, uint8_t Score, uint8_t MyTurn, float *Reward)
{
    unsigned long hash = (1U + MyTurn)*Score;
    if (hash >= HASH_MAX_CAPACITY)
    {
        return GST_FAILURE;
    }
    if (table->hash_used[hash] == 0U)
    {
        return GST_FAILURE;
    }

    *Reward = table->hash_map[hash];

    return GST_SUCCESS;
};

/*** end of file ***/