//Write automated test generator for the Baron, req 90% statement and branch coverage
//use -b and -f options when generating coverage, target <5min for coverage

//timing provided by https://www.techiedelight.com/find-execution-time-c-program/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
	/*
	struct gameState {
		int numPlayers; //number of players
		int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
		int embargoTokens[treasure_map+1];
		int outpostPlayed;
		int outpostTurn;
		int whoseTurn;
		int phase;
		int numActions; 	// Starts at 1 each turn
		int coins; 			// Use as you see fit!
		int numBuys; 		// Starts at 1 each turn
		int hand[MAX_PLAYERS][MAX_HAND];
		int handCount[MAX_PLAYERS];
		int deck[MAX_PLAYERS][MAX_DECK];
		int deckCount[MAX_PLAYERS];
		int discard[MAX_PLAYERS][MAX_DECK];
		int discardCount[MAX_PLAYERS];
		int playedCards[MAX_DECK];
		int playedCardCount;
	};*/		
	
	double execTime = 0.0;
	clock_t begin = clock();
	
	int seed = 30;
//	int preNumBuys = 0;
//	int handCount = 2;
	int r = 0;
	int iter = 0;
	
	// set your card array
	int k[10] = { minion, council_room, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };
	
	// declare the game state
	struct gameState G;
	
	printf("randomtestcard1 Testing Begin:\n");
	
	SelectStream(2);
    PutSeed(3);

	srand(time(0));

	do	{

		iter++;
		//Initilize the game struct
		//Initilize the game struct
		int y = rand() % ((MAX_PLAYERS - 2 + 1)) + 2;
		G.whoseTurn = rand() % y;
//		printf("num players: %i\t turn: %i \n", y, G.whoseTurn);
		r = initializeGame(y, k, seed, &G); // initialize a new game
		
		if( rand() % 20 == 0)	{
			int currentPlayer = G.whoseTurn;
			int nextPlayer = currentPlayer + 1;
			if (nextPlayer > (G.numPlayers - 1)) {
				nextPlayer = 0;		
			}
			G.deckCount[nextPlayer] = 0;
			G.handCount[nextPlayer] = 1;
		}


		
		/*This section is where the requirements are set*/
			//	int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)   //Note: supplyPos is enum of choosen card 	//toFlag = 2 is to hand
		int q = G.whoseTurn;
		int s = rand() % 2;
		r = gainCard(baron, &G, 2, q);		//Adds the baron to the current player's hand
		if( r == 1) {
			printf("Error adding baron to hand\n");
		}
		if( s == 1)	{
			r = gainCard(estate, &G, 2, q);		//Adds an estate to the current player's hand
			if( r == 1) {
				printf("Error adding estate to hand\n");
			}
		}
		
		/*This section is resposible for generating a random play for the required card*/
			//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
//		float temp = floor(Random() + 0.5);		//construct a rondom boolean value
		int m = rand() % 2;		//(int) temp;
		int n = G.handCount[G.whoseTurn];
//		printf("temp: %f\tm: %i\n", temp, m);
//		printf("calling playCard with parameters, %i, %i, 0, gamestate struct\n", n-2, m);
		r = playCard(n-1-s, m, 0, 0, &G);					//play the baron, which is second from end, randomly choose to discard the estate or not
	
	}while(iter < 1000);
	
	clock_t end = clock();
	
	execTime += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("randomtestcard1 Testing End - time elapsed is %f seconds\n", execTime);
	
	
}










