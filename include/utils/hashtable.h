/** @file hashtable.h
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

#ifndef GNP_HASHT_H		/* prevent circular inclusions */
#define GNP_HASHT_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "status.h"

#include <stdint.h>

/************************** Constant Definitions *****************************/

#define HASH_MAX_CAPACITY   50U

/**************************** Type Definitions *******************************/

struct hashtable
{
    float hash_map[HASH_MAX_CAPACITY];
    uint8_t hash_used[HASH_MAX_CAPACITY];
};
typedef struct hashtable *hashtable_t;

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

GStatus Hashtable_Init(hashtable_t table);
GStatus Hashtable_Put(hashtable_t table, uint8_t Score, uint8_t MyTurn, float Reward);
GStatus Hashtable_Get(hashtable_t table, uint8_t Score, uint8_t MyTurn, float *Reward);

#ifdef __cplusplus
}
#endif

#endif /* GNP_HASHT_H */

/*** end of file ***/