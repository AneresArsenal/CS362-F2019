/*
Assignment 3 - Learn how to create unit tests
Unit Test 3 
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

    printf("Starting Unit Test 3 - playAmbassador function \n\n");

    initializeGame(2, k, 1234, &pre);
    printf("Game initialized \n\n");

    int handPos = 0,
        choice1 = 4,
        choice2 = 3,
        currentPlayer = 1,
        r = 10;

    pre.handCount[currentPlayer] = r;

    // randomly assign cards
    for (int i = 0; i < r; i++)
    {
        pre.hand[currentPlayer][i] = k[9 - i];
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Player choose to discard 3 cards (invalid). \n\n");

    // set three village cards
    post.hand[currentPlayer][5] = village;
    post.hand[currentPlayer][6] = village;
    post.hand[currentPlayer][7] = village;

    // call the refactored functions
    ambassadorCard(choice1, choice2, &post, handPos);

    // assert the results
    // discard max 2 cards i.e. discard Ambassador card + 2 cards max
    if (post.handCount[currentPlayer] < pre.handCount[currentPlayer] - 3)
    {
        printf("Bug #1 found! Return more than 2 cards to supply! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    // supply count change should be add choice 2 deduct 2 * # of player (1)
    if (post.supplyCount[village] != pre.supplyCount[village] + choice2 - 2)
    {
        printf("Bug #2 found! Card not added into and deducted from supply correctly! \n");
        printf("Pre-call suuply count: %d \n", pre.supplyCount[village]);
        printf("Post-call suuply count: %d \n\n", post.supplyCount[village]);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Player choose not to discard revealed card.\n\n");

    choice2 = 0;

    // call the refactored functions
    ambassadorCard(choice1, choice2, &post, handPos);

    // assert the results
    // discard only Ambassador card
    if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 1)
    {
        printf("Bug found! Card not discarded properly from hand! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    printf("Unit Test 3 completed! \n\n");
    return 0;
}
