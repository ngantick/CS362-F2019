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

void checkPlayTribute(struct gameState *post, int handPos, int currentPlayer, int nextPlayer)
{
	struct gameState pre;
	int i, flag, treasure, victory, action;
	memcpy(&pre, post, sizeof(struct gameState));
	int tributeRevealedCards[2] = { -1, -1 };
	playTribute(post, tributeRevealedCards, currentPlayer, nextPlayer);
	if (pre.deckCount[nextPlayer] >= 2)//this only will measure the outcomes of the gamestate when the nextplayer has two cards ready in their deck
	{
		tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		pre.deck[nextPlayer][pre.deckCount[nextPlayer]--] = -1;
		pre.deckCount[nextPlayer]--;
		tributeRevealedCards[1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		pre.deck[nextPlayer][pre.deckCount[nextPlayer]--] = -1;
		pre.deckCount[nextPlayer]--;

		if (tributeRevealedCards[0] == tributeRevealedCards[1])
		{
			tributeRevealedCards[1] = -1;
		}
		treasure = 0;
		victory = 0;
		action = 0;
		for (i = 0; i < 2; i++)
		{
			if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold)
			{
				treasure++;
			}
			else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall)
			{
				victory++;
			}
			else if (tributeRevealedCards[i] != -1)
			{
				action++;
			}
		}

		my_assert(post->coins == pre.coins + 2 * treasure,"Coins did not increase properly");
		printf("pre:%d\npost:%d\naction:%d\n", pre.numActions, post->numActions,action);
		my_assert(post->numActions == pre.numActions + 2 * action, "Actions did not increase properly");
		my_assert(post->handCount[currentPlayer] == pre.handCount[currentPlayer] + 2 * victory,"Did not draw cards properly");

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

			G.handCount[n] = rand() % (MAX_HAND - 1) + 1;
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
		G.playedCardCount = rand() % MAX_HAND;
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
		int nextPlayer;
		if (currentPlayer != G.numPlayers-1)
		{
			nextPlayer = currentPlayer + 1;
		}
		else
		{
			nextPlayer = 0;
		}
		handPos = rand() % G.handCount[currentPlayer];
		checkPlayTribute(&G, handPos,currentPlayer,nextPlayer);


	}
}