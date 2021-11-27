/** @file status.h
 * 
 * @brief A collection of return status used throughout the source code. 
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

#ifndef GNP_STATUS_H		/* prevent circular inclusions */
#define GNP_STATUS_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include <stdint.h>

/************************** Constant Definitions *****************************/

/*********************** Common statuses 0 - 500 *****************************/
#define GST_SUCCESS             0L
#define GST_FAILURE             1L

/***************** Common Components statuses 501 - 1000 *********************/

/********************** Hash Table statuses 501 - 510 ************************/
#define GST_HASH_EXISTS         501L

/********************* Game State statuses 511 - 530 *************************/

#define GST_INVALID_STATE       511L
#define GST_GAME_WON            512L

/**************************** Type Definitions *******************************/

typedef uint16_t GStatus;

/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* GNP_STATUS_H */

/*** end of file ***/