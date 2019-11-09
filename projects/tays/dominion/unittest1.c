/*
Assignment 3 - Learn how to create unit tests
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
    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    printf("Starting Unit Test 2 \n\n");

    initializeGame(2, k, 1234, &pre);
    printf("Game initialized \n\n");

    int handPos = 0,
        choice1 = 1,
        bonus = 0, 
        currentPlayer = 1,
        r = 10;

    pre.handCount[currentPlayer] = r;

    // randomly assign cards
    for (int i = 0; i < r; i++)
    {
        pre.hand[currentPlayer][i] = k[9 - i];
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Estate card exist in hand and player choose to discard estate. \n\n");
    // set one to be estate
    post.hand[currentPlayer][4] = estate;

    // call the refactored functions
    playBaron(handPos, choice1, &post, currentPlayer, bonus);

    // assert the results
    // bonus points should be added
    if (post.coins != pre.coins + 4)
    {
        printf("Bug found! Bonus not added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 2)
    {
        printf("Bug #1 Found! Baron card and estate card found should both be discarded! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    int j = post.discardCount[currentPlayer];
    for (int i = 0; i < j; i++)
    {
        if (post.discard[currentPlayer][i] == estate)
        {
            printf("Bug #2 Found! Estate card found in discard pile, player should not have gained one! \n");
        }
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Estate card do not exist in hand and player choose to discard estate. \n\n");

    // call the refactored functions
    playBaron(handPos, choice1, &post, currentPlayer, bonus);

    // assert the results
    // bonus points should be added
    if (post.coins == pre.coins)
    {
        printf("Valid! Bonus not added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 1)
    {
        printf("Error!  Baron card not discarded! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    memcpy(&pre, &post, sizeof(struct gameState));
    printf("Test case 3: Estate card do not exist in hand and player choose not to discard estate. \n\n");

    // call the refactored functions
    playBaron(handPos, 0, &post, currentPlayer, bonus);

    // assert the results
    // bonus points should be added
    if (post.coins == pre.coins)
    {
        printf("Valid! Bonus not added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    if (post.handCount[currentPlayer] == pre.handCount[currentPlayer] - 1)
    {
        printf("Valid! Only Baron card discarded! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 1)
    {
        printf("Error!  Baron card not discarded! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    printf("Unit Test 1 completed! \n\n");
    return 0;
}
