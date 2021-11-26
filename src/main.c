/** @file main.c
 * 
 * @brief Main source file for the "Who Say's 20 First" game. 
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

/***************************** Include Files *********************************/

#include <stdio.h>

#include "status.h"

#include "game.h"
#include "player.h"

/************************** Constant Definitions *****************************/

#define VERBOSE_OUTPUT

/**************************** Type Definitions *******************************/

struct Actor player1_s;
Actor_t player1 = &player1_s;

struct Actor player2_s;
Actor_t player2 = &player2_s;

struct game game_s;
game_t game = &game_s;

/************************** Function Prototypes ******************************/

/************************** Function Definitions *****************************/

int main()
{
	Player_Init(player1);
	Player_Init(player2);

	Game_Init(game, player1, player2);

	Game_SpinOnce(game);

	printf("Hello World!\n");

	if (GST_SUCCESS == 0L) {
		printf("Status Here!\n");
	}

	return (0);
}