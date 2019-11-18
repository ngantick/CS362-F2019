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

void checkPlayMinion(int choice1, int choice2, struct gameState *post, int handPos, int currentPlayer)
{
	struct gameState pre;
	int i, flag;
	memcpy(&pre, post, sizeof(struct gameState));

	playMinion(choice1, choice2, post, handPos, currentPlayer);
	my_assert(post->numActions == pre.numActions + 1,"1 action was not gained");
	if (choice1)
	{
		my_assert(post->coins == pre.coins + 2, "Coins did not increase by 2");
	}
	else if (choice2)
	{
		for (i = 0; i < post->numPlayers; i++)
		{
			if (i == currentPlayer)
			{
				my_assert(post->handCount[i] == 4, "Player does not have 4 cards after playing Minion");
				if (pre.deckCount[i] < 4)
				{
					my_assert(post->discardCount[i] < 4, "More cards in the discard pile than there should be for the current player.");
					
				}
				else
				{
					my_assert(post->discardCount[i] == pre.discardCount[i] + pre.handCount[i] - 1, "Player did not discard all cards in hand after playing minion.");
					
				}
			}
			else 
			{
				if (pre.handCount[i] >= 5)
				{
					my_assert(post->handCount[i] == 4, "A player does not have 4 cards after minion was played");
					if (pre.deckCount[i] < 4)
					{
						my_assert(post->discardCount[i] < 4, "More cards in the discard pile than there should be for a player.");

					}
					else
					{
						my_assert(post->discardCount[i] = pre.discardCount[i] + pre.handCount[i], "Player did not discard all cards in hand after minion was played.");
						my_assert(post->deckCount[i] == pre.deckCount[i] - 4, "a player did not lose 4 cards from deck.");
					}
				}
			}
		}
	}

}

int main()
{

	struct gameState G;
	srand(time(0));
	int n, i, j, choice1, choice2, currentPlayer, handPos;
	for (j = 0; j < 2000; j++)
	{
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = rand() % 256;
		}
		G.numPlayers = rand() % (MAX_PLAYERS - 1) + 1;
		for (n = 0; n < G.numPlayers; n++)
		{
			G.deckCount[n] = rand() % MAX_DECK;
			G.discardCount[n] = rand() % MAX_DECK;
			
			G.handCount[n] = rand() % (MAX_HAND-101)+1;
			for (i = 0; i < G.handCount[n]; i++)
			{
				G.hand[n][i] = rand() % 27;
			}
			for (i = 0; i < G.discardCount[n]; i++)
			{
				G.discard[n][i] = rand() % 27;
			}
			

			for (i = 0; i < G.handCount[n]; i++)
			{
				G.deck[n][i] = rand() % 27;
			}
		}
		G.playedCardCount = rand() % 100;
		for (i = 0; i < G.playedCardCount; i++)
		{
			G.playedCards[i] = rand() % 27;
		}
		G.coins = rand() % 26;
		G.numActions = rand() % 10;
		choice1 = rand() % 2;
		choice2 = 1;
		if (choice1)
		{
			choice2 = 0;
		}
		currentPlayer = rand() % G.numPlayers;
		G.whoseTurn = currentPlayer;
		handPos = rand() % G.handCount[currentPlayer];
		checkPlayMinion(choice1,choice2, &G,handPos, currentPlayer);


	}
}