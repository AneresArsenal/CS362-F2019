/*
Assignment 3 - Learn how to create unit tests
Unit Test 2
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

    printf("Starting Unit Test 2 - playMinion function \n\n");

    initializeGame(2, k, 1234, &pre);
    printf("Game initialized \n\n");

    int handPos = 0,
        choice1 = 1,
        choice2 = 0,
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
    printf("Test case 1: Choice 1 Selected. \n\n");

    // call the refactored functions
    playMinion(choice1, choice2, &post, currentPlayer, handPos, bonus);

    // assert the results
    // added 1 action play
    if (post.numActions != pre.numActions + 1)
    {
        printf("Bug #1 found! Number of action plays not incremented by 1! \n");
        printf("Pre-call number of action plays: %d \n", pre.numActions);
        printf("Post-call number of action plays: %d \n\n", post.numActions);
    }

    printf("Test case 1: Choice 1 Selected. \n\n");

    // discard used minion card and + 4 cards hence 3 additional cards
    if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] + 3)
    {
        printf("Bug #2 found! Current hand not incremented accurately! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    if (post.coins == pre.coins)
    {
        printf("Bug found! Bonus of 2 coins not added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Choose to discard current hand and draw four cards. \n\n");

    // choose to discard hand
    choice1 = 0;
    choice2 = 1;

    // call the refactored functions
    playMinion(choice1, choice2, &post, currentPlayer, handPos, bonus);

    // assert the results
    // added 1 action play
    if (post.numActions != pre.numActions + 1)
    {
        printf("Bug #1 found! Number of action plays not incremented by 1! \n");
        printf("Pre-call number of action plays: %d \n", pre.numActions);
        printf("Post-call number of action plays: %d \n\n", post.numActions);
    }
    // bonus points should be added
    if (post.coins == pre.coins)
    {
        printf("Valid! Bonus not added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    printf("Test case 2: Choose to discard current hand and draw four cards. \n\n");

    if (post.handCount[currentPlayer] != 4)
    {
        printf("Bug #2 found! Drawn cards not equal to 4! \n\n");
    }

    printf("Unit Test 2 completed! \n\n");
    return 0;
}
