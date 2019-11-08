/*
Assignment 3
Unit Test 1
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // initialize variables
    struct gameState pre, post;
    int k[10] = {estate, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    printf("Starting Unit Test 1 \n");

    initializeGame(2, k, 9898, &pre);
    printf("Game initialized \n");

    int handPos = 1,
        choice1 = 1,
        bonus = 0;

    int currentPlayer = 1;

    // set some game state variables

    /* random int between 0 and 19 */
    int r = rand() % 5;

    pre.handCount[currentPlayer] = r;

    // randomly assign cards
    for (int i = 0; i < r; i++)
    {
        pre.hand[currentPlayer][i] = k[i];
    }

    // set one to be estate
    pre.hand[currentPlayer][3] = k[0];

    //added card for [whoseTurn] current player:
    // toFlag = 0 : add to discard
    // toFlag = 1 : add to deck
    // toFlag = 2 : add to hand

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Created a copy of the game state to compare before function call and after function call. \n");

    // call the refactored functions
    playBaron(handPos, choice1, &post, currentPlayer, bonus);

    // assert the results
    // bonus points should be added
    if (post.coins != pre.coins + 4)
    {
        printf("Bonus not added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n", post.coins);
    }

    if (post.handCount[currentPlayer] == pre.handCount[currentPlayer] - 1)
    {
        printf("Baron card discarded! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n", post.handCount[currentPlayer]);
    }

    if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 1)
    {
        printf("Baron card not discarded! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n", post.handCount[currentPlayer]);
    }

    return 0;
}
