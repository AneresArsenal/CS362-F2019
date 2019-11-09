/*
Assignment 3 - Learn how to create unit tests
Unit Test 5 
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
    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    printf("Starting Unit Test 5 \n\n");

    initializeGame(2, k, 1234, &pre);
    printf("Game initialized \n\n");

    int handPos = 0,
        currentPlayer = 0,
        r = 10;

    pre.handCount[currentPlayer] = r;

    // randomly assign cards to player and other player
    for (int i = 0; i < r; i++)
    {
        pre.hand[currentPlayer][i] = k[9 - i];
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Choose to discard copper card and gain gold.\n\n");

    int choice1 = 0,
        choice2 = gold;

    post.hand[currentPlayer][choice1] = copper;

    // call the refactored functions
    playMine(choice1, choice2, &post, currentPlayer, handPos);

    // assert the results
    printf("Cost of card requested: %d \n", getCost(choice2));
        printf("Cost of card discarded: %d \n\n", getCost(pre.hand[currentPlayer][choice1]));
        
    if (getCost(choice2) - getCost(pre.hand[currentPlayer][choice1]) > 3)
    {
        printf("Bug #1 found! Gold is too expensive! \n");
        printf("Cost of card requested: %d \n", getCost(choice2));
        printf("Cost of card discarded: %d \n\n", getCost(pre.hand[currentPlayer][choice1]));
    }

    if (post.thrashPileCount != pre.thrashPileCount + 1)
    {
        printf("Bug #2 found! Discarded card not thrashed! \n");
        printf("Pre-call thrash pile count: %d \n", pre.thrashPileCount);
        printf("Post-call thrash pile count: %d \n\n", post.thrashPileCount);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Valid choices made.\n\n");

    choice2 = gold;

    post.hand[currentPlayer][choice1] = silver;

    // call the refactored functions
    playMine(choice1, choice2, &post, currentPlayer, handPos);

    // assert the results
    if (getCost(choice2) - getCost(pre.hand[currentPlayer][choice1]) > 3)
    {
        printf("Valid! Discard silver for gold is allowed. \n");
        printf("Cost of card requested: %d \n", getCost(choice2));
        printf("Cost of card discarded: %d \n\n", getCost(pre.hand[currentPlayer][choice1]));
    }

    if (post.thrashPileCount != pre.thrashPileCount + 1)
    {
        printf("Bug #2 found! Discarded card not thrashed! \n");
        printf("Pre-call thrash pile count: %d \n", pre.thrashPileCount);
        printf("Post-call thrash pile count: %d \n\n", post.thrashPileCount);
    }

    printf("Unit Test 5 completed! \n\n");
    return 0;
}
