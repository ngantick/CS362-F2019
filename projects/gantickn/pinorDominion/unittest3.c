int newAmbassador(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int currentPlayer)
{
//Everything after this is the original code, so I have left it uncommented//
int i = 0;
int j = 0;		//used to check if player has enough cards to discard


        if (choice2 > 2 || choice2 < 0)
        {
            printf("You cannot return less than 0 or more than 2 copies. Error.\n");
            return -1;
        }

        if (choice1 == handPos)
        {

            printf("Error\n");
            return -1;
        }

        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (i != handPos && state->hand[currentPlayer][i]  == state->hand[currentPlayer][choice1] && i != choice1)
            {
                j++;
            }
        }
        if (j < choice2)
        {
          printf("You do not have enough cards to discard. Error.\n");
            return -1;
        }

        if (DEBUG)
            printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

        //increase supply count for choosen card by amount being discarded
        state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

        //each other player gains a copy of revealed card
        for (i = 0; i < state->numPlayers; i++)
        {
          //ERROR
            if (i == currentPlayer)
          //ERROR
            {
                gainCard(state->hand[currentPlayer][choice1], state, 0, i);
            }
        }

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);

        //trash copies of cards returned to supply
        for (j = 0; j < choice2; j++)
        {
            for (i = 0; i < state->handCount[currentPlayer]; i++)
            {
                if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
                {
                    discardCard(i, currentPlayer, state, 1);
                    //ERROR WHEN REMOVED break; //ERROR WHEN REMOVED
                }
            }
        }
  return 0;
}