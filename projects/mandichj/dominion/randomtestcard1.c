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

void checkPlayBaron(int choice1, struct gameState *post, int currentPlayer)
{
	struct gameState pre;
	int i,flag;

	memcpy(&pre, post, sizeof(struct gameState));

	playBaron(choice1, post, currentPlayer);

	my_assert(post->numBuys == pre.numBuys + 1,"Number of buys did not increase");

	if (choice1 == 0)//checks for decrease in estate supply and that there is an estate on top of the discard pile
	{
		

		my_assert(supplyCount(estate, post) == supplyCount(estate, &pre)-1,"Supplycount of estates did not decrease");

		my_assert(post->discard[currentPlayer][post->discardCount[currentPlayer] - 1] == estate,"Estate is not on top of discard pile");

	}
	else
	{
		flag = 0;
		for (i = 0; i < pre.handCount[currentPlayer]; i++)//checks if a card was able to be discarded and the choice was made
		{
			if (pre.hand[currentPlayer][i] == estate)
			{
				flag = 1;
				
			}
		}
		if (flag == 0)//same as above choice1==0
		{

			my_assert(supplyCount(estate, post) == supplyCount(estate, &pre) - 1, "Supplycount of estates did not decrease");

			my_assert(post->discard[currentPlayer][post->discardCount[currentPlayer] - 1] == estate, "Estate is not on top of discard pile");

		}
		else//checks that gold increased by 4 and there is an estate on top of the discard pile and that handCount decreased by 1
		{
	
			my_assert(post->coins == pre.coins + 4,"Coins did not increase by 4");
			my_assert(post->discard[currentPlayer][post->discardCount[currentPlayer] - 1] == estate, "Estate is not on top of discard pile");
			my_assert(post->handCount[currentPlayer] == pre.handCount[currentPlayer] - 1,"Hand Count did not decrease by 1");
		}
	}
}

int main() {

	struct gameState G;
	srand(time(0));
	int n, i, j, choice1, currentPlayer;
	for (j = 0; j < 2000; j++)
	{
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = rand() % 256;
		}
		G.numPlayers = rand() % (MAX_PLAYERS - 1) + 1;
		for (n = 0; n <G.numPlayers; n++)
		{
			G.deckCount[n] = rand() % MAX_DECK;
			G.discardCount[n] = rand() % MAX_DECK;
		
			G.handCount[n] = rand() % MAX_HAND;
			for (i = 0; i < G.handCount[n]; i++)
			{
				G.hand[n][i] = rand() % 27;
			}
			for (i = 0; i < G.discardCount[n]; i++)
			{
				G.discard[n][i] = rand() % 27;
			}
		}
	
	G.coins = rand() % 26;
	G.supplyCount[estate] = rand() % 20;
	G.numBuys = rand() % 10;
	choice1 = rand() % 2;

	
	currentPlayer = rand() % G.numPlayers;
	checkPlayBaron(choice1, &G, currentPlayer);

	
	}
}