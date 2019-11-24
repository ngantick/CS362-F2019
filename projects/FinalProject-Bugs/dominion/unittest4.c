#include "dominion.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void my_assert(int statement, char* message)
{
	if (!statement)
	{
		printf("%s\n", message);
		fflush(stdout);
	}
}

int main()
{
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	struct gameState G, G2;
	int  i, j, x;
	printf("Begin testing for 'isGameOver fails to check all of the supply' bug.\n");
	fflush(stdout);

	initializeGame(2, k, time(0), &G);

	for (i = curse; i <= treasure_map; i++)
	{

		for (j = curse; j <= treasure_map; j++)
		{
			for (x = curse; x <= treasure_map; x++)
			{
				if (i == province || j == province || x == province)//the game will be over regardless of the bug if province is set to 0
				{
					break;
				}
				if (i == j || i == x || j == x)
				{
					break;
				}

				memcpy(&G2, &G, sizeof(struct gameState));//start with fresh gamestate each time

				G2.supplyCount[i] = 0;//set three piles to 0, this should work even if the cards are not in k as piles not in the game are set to -1 and all cards should be checked
				G2.supplyCount[j] = 0;
				G2.supplyCount[x] = 0;
				
				my_assert(isGameOver(&G2) == 1, "isGameOver returned 0 when it should return 1");
			}
		}

	}
}