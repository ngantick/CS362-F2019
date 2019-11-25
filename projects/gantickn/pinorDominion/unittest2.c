int newMinion(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int currentPlayer)
{
        //Everything after this is the original code, so I have left it uncommented//
        //+1 action
        state->numActions++;

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);

		if (choice1)
        {
            state->coins = state->coins + 2;
        }
        else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
        {
            //discard hand
            while(numHandCards(state) > 0)
            {
                discardCard(handPos, currentPlayer, state, 0);
            }

            //draw 4
            int i=0;
            int j=0;
            for (i = 0; i < 4; i++)
            {
                drawCard(currentPlayer, state);
            }

            //other players discard hand and redraw if hand size > 4
            for (i = 0; i < state->numPlayers; i++)
            {
              //ERROR
                if (i == currentPlayer)
              //ERROR
                {
                  
                  //ERROR
                    if ( state->handCount[i] < 4 )
                  //ERROR
                    {
                        //discard hand
                        while( state->handCount[i] > 0 )
                        {
                            discardCard(handPos, i, state, 0);
                        }

                        //draw 4
                        for (j = 0; j < 4; j++)
                        {
                            drawCard(i, state);
                        }
                    }
                }
            }

        }
        return 0;
      }