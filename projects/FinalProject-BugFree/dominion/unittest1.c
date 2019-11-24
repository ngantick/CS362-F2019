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
	int coppercount, silvercount, coppercount2, silvercount2, i, j;
	printf("Begin testing for 'Cards not trashed in Mine' bug.\n");
	fflush(stdout);
	memset(&G, 0, sizeof(struct gameState));
	initializeGame(2, k, time(0), &G);

	G.hand[G.whoseTurn][0] = mine;
	G.hand[G.whoseTurn][1] = copper;
	memcpy(&G2, &G, sizeof(struct gameState));//one game for each treasure card
	G2.hand[G2.whoseTurn][1] = silver;

	//Golds cannot be used for this test as there is no card that can be gained using them due to the bug "Mine improper cost handling"

	//Count the number of coppers in G and silvers in G2. no assumptions are made that discard piles are empty or players dont have other silvers etc


	coppercount = G.supplyCount[copper];
	silvercount = G2.supplyCount[silver];


	//COPPERS in G
	for (i = 0; i < G.numPlayers; i++)
	{
		for (j = 0; j < G.handCount[i]; j++)
		{
			if (G.hand[i][j] == copper)
			{
				coppercount++;
			}
		}
	}
	for (i = 0; i < G.numPlayers; i++)
	{
		for (j = 0; j < G.discardCount[i]; j++)
		{
			if (G.discard[i][j] == copper)
			{
				coppercount++;
			}
		}
	}
	for (i = 0; i < G.numPlayers; i++)
	{
		for (j = 0; j < G.deckCount[i]; j++)
		{
			if (G.deck[i][j] == copper)
			{
				coppercount++;
			}
		}
	}
	for (j = 0; j < G.playedCardCount; j++)
	{
		if (G.playedCards[j] == copper)
		{
			coppercount++;
		}
	}


	//SILVERS in G2
	for (i = 0; i < G2.numPlayers; i++)
	{
		for (j = 0; j < G2.handCount[i]; j++)
		{
			if (G2.hand[i][j] == silver)
			{
				silvercount++;
			}
		}
	}
	for (i = 0; i < G2.numPlayers; i++)
	{
		for (j = 0; j < G2.discardCount[i]; j++)
		{
			if (G2.discard[i][j] == silver)
			{
				silvercount++;
			}
		}
	}
	for (i = 0; i < G2.numPlayers; i++)
	{
		for (j = 0; j < G2.deckCount[i]; j++)
		{
			if (G2.deck[i][j] == silver)
			{
				silvercount++;
			}
		}
	}
	for (j = 0; j < G2.playedCardCount; j++)
	{
		if (G2.playedCards[j] == silver)
		{
			silvercount++;
		}
	}
	/*here cardeffect is called: 
	mine is the card we are testing, 
	1 represents the position in the hand of the treasure we put in, 
	province is the third argument because there is another bug in mine that causes any card higher than three cost more than the trash card to be gained and we must successfully gain a card to see if we successfully trashed a card
	0 is the useless choice 3
	G is gamestate
	0 for hand position of the mine card
	0 for bonus coins (not relevant)
	*/

	i=cardEffect(mine, 1, copper, 0, &G, 0, 0);
	j=cardEffect(mine, 1, copper, 0, &G2, 0, 0);
	

	//calculate the new card counts of copper and silver
	coppercount2 = G.supplyCount[copper];
	silvercount2 = G2.supplyCount[silver];


	//COPPERS in G
	for (i = 0; i < G.numPlayers; i++)
	{
		for (j = 0; j < G.handCount[i]; j++)
		{
			if (G.hand[i][j] == copper)
			{
				coppercount2++;
			}
		}
	}
	for (i = 0; i < G.numPlayers; i++)
	{
		for (j = 0; j < G.discardCount[i]; j++)
		{
			if (G.discard[i][j] == copper)
			{
				coppercount2++;
			}
		}
	}
	for (i = 0; i < G.numPlayers; i++)
	{
		for (j = 0; j < G.deckCount[i]; j++)
		{
			if (G.deck[i][j] == copper)
			{
				coppercount2++;
			}
		}
	}
	for (j = 0; j < G.playedCardCount; j++)
	{
		if (G.playedCards[j] == copper)
		{
			coppercount2++;
		}
	}

	//SILVERS in G2
	for (i = 0; i < G2.numPlayers; i++)
	{
		for (j = 0; j < G2.handCount[i]; j++)
		{
			if (G2.hand[i][j] == silver)
			{
				silvercount2++;
			}
		}
	}
	for (i = 0; i < G2.numPlayers; i++)
	{
		for (j = 0; j < G2.discardCount[i]; j++)
		{
			if (G2.discard[i][j] == silver)
			{
				silvercount2++;
			}
		}
	}
	for (i = 0; i < G2.numPlayers; i++)
	{
		for (j = 0; j < G2.deckCount[i]; j++)
		{
			if (G2.deck[i][j] == silver)
			{
				silvercount2++;
			}
		}
	}
	for (j = 0; j < G2.playedCardCount; j++)
	{
		if (G2.playedCards[j] == silver)
		{
			silvercount2++;
		}
	}

	my_assert(coppercount2 + 1 == coppercount, "coppers did not decrease by 1");
	my_assert(silvercount2 + 1 == silvercount, "silvers did not decrease by 1");

	printf("Testing complete for 'Cards not trashed in Mine' bug.\n\n");
	fflush(stdout);

}