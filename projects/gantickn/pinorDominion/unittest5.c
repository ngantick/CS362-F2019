int newMine(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int currentPlayer)
{
int i=0; //initialize later loop variable

int j = state->hand[currentPlayer][choice1];  //store card we will trash

        if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
        {
            printf("These are not treasures. Error.\n");
            return -1;
        }

        if (choice2 > treasure_map || choice2 < curse)
        {
            printf("These are not treasures. Error.\n");
            return -1;
        }

//ERROR START!
        if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
        {   
            printf("Cost is too large. Error.\n");
            return -1;
        }

        gainCard(choice2, state, 2, currentPlayer);

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
//ERROR END!

        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(i, currentPlayer, state, 1);
                break;
            }
        }
  return 0;
}