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

    printf("Starting Unit Test 5 - playMine function \n\n");

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
    int checkCost = post.hand[currentPlayer][choice1];

    // call the refactored functions
    mineCard(choice1, choice2, &post, handPos);

    // assert the results
    //make sure difference of cost is 3 or less (cheaper is fine)
    if (getCost(choice2) - getCost(checkCost) > 3)
    {
        printf("Bug #1 found! Gold is too expensive! \n");
        printf("Cost of card requested: %d \n", getCost(choice2));
        printf("Cost of card discarded: %d \n\n", getCost(checkCost));
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Valid choices made.\n\n");
    choice1 = 0,
    choice2 = gold;

    post.hand[currentPlayer][choice1] = silver;
    checkCost = post.hand[currentPlayer][choice1];

    // call the refactored functions
    mineCard(choice1, choice2, &post, currentPlayer);

    // assert the results
    //make sure difference of cost is 3 or less (cheaper is fine)
    if (getCost(choice2) - getCost(checkCost) <= 3)
    {
        printf("Valid! Swap is allowed! \n");
        printf("Cost of card requested: %d \n", getCost(choice2));
        printf("Cost of card discarded: %d \n\n", getCost(checkCost));
    }

    printf("Unit Test 5 completed! \n\n");
    return 0;
}
