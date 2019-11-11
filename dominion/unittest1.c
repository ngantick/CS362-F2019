#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

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
	
	int seed = 30;
	int preNumBuys = 0;
	int handCount = 2;
	int r = 0;
	
	
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	
	// declare the game state
	struct gameState G;
	// declare the arrays
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	

	printf("Begin Testing someFunction():\n");
	//
	// set the state of your variables
	 // comment on what this is going to test
	//
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game
	G.handCount[p] = handCount; // set any other variables
	memcpy(G.hand[p], coppers, sizeof(int) * handCount);	//fill hand with coppers
	
	/*This section is where the requirements are set, and pre-variables are saved*/
	r = addCardToHand(g->whoseTurn, baron, G);		//ADD - put Baron in the hand
	if( r == 1) {
		printf("Error adding baron to hand\n");
	}
	r = addCardToHand(g->whoseTurn, estate, G);		//ADD - put an Estate in hand
	if( r == 1) {
		printf("Error adding estate to hand\n");
	}
	preNumBuys = G.numBuys;							//save the prefuction buys value
	
	r = playCard(4, 1, 0, 0, G);					//play the baron, which is hand position 4
	
	int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state);
/* Play card with index handPos from current player's hand */
	
	
	
	
	
	
	

	// call the refactored function
	myrefactoredfunction(p, &G, bonus);

	// verify that your asserts pass, for the bugs your asserts may fail
	assert(G.coins == something); // check a condition
	assert(some condition);
	assert(some condition);

	//
	// adjust the state of your variables to continue testing the function
	 // comment on what this is going to test
	//
	memset(&G, 0, sizeof(struct gameState)); // set the game state
	r = initializeGame(3, k, seed, &G); // initialize a new game
	G.handCount[p] = handCount; // set any other variables
	memcpy(G.hand[p], silvers, sizeof(int) * handCount);

	// call the refactored function again
	myrefactoredfunction(p, &G, bonus);

	// verify that your asserts pass, for the bugs your asserts may fail
	assert(G.coins == something); // check a condition
	assert(some condition);
	assert(some condition);
	printf("Test completed!\n");
	
	
}










