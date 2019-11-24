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
	int  i, j;
	printf("Begin testing for 'Remodel improper cost handling' bug.\n");
	fflush(stdout);

	initializeGame(2, k, time(0), &G);
	
	for (i = curse; i <= treasure_map; i++)
	{
		
		for (j = curse; j <= treasure_map; j++)
		{
	
			memcpy(&G2, &G, sizeof(struct gameState));//start with fresh gamestate each time
			G2.hand[G.whoseTurn][0] = remodel;//prepare hand with remodel and a card
			G2.hand[G.whoseTurn][1] = i;

			if (getCost(i) + 2 >= getCost(j))//should cause cardEffect to succeed
			{
				my_assert(cardEffect(remodel, 1, j, 0, &G2, 0, 0) == 0, "CardEffect failed but should have succeeded");
			}
			else//should be cardEffect failing
			{
				my_assert(cardEffect(remodel, 1, j, 0, &G2, 0, 0) == -1, "CardEffect succeded but should have failed.");
			}
		}

	}
	printf("Testing complete for 'Remodel improper cost handling' bug.\n\n");
	fflush(stdout);
}
