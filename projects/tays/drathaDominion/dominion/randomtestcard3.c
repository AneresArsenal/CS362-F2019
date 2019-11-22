/*
Assignment 4 - Learn how to create a Random Tester
Random Test 3
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    // Use current time as seed for random generator
    srand(time(0));
    clock_t begin = clock();

    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int tributeRevealedCards[2] = {-1, -1};

    int bug1_found_count = 0,
        bug2_found_count = 0;

    for (int i = 0; i < 100; i++)
    {
        // reset game whenever a test is completed
        memcpy(&post, &pre, sizeof(struct gameState));

        printf("Random Test # %d \n", i);

        printf("Starting Random Test 3 - playTribute function \n\n");

        initializeGame(2, k, 1234, &pre);
        printf("Game initialized \n\n");

        int handPos = 0,
            currentPlayer = 0,
            bonus = 0,
            r = rand() % (10 + 1); //number of cards in hand

        int nextPlayer = 1;

        pre.handCount[currentPlayer] = r;
        pre.deckCount[nextPlayer] = 11;

        // randomly assign cards to player and other player
        // randomly assign cards
        for (int j = 0; j < r; j++)
        {
            int card = rand() % (10);
            pre.hand[currentPlayer][j] = k[card];
            card = rand() % (10);
            pre.hand[nextPlayer][j] = k[card];
        }

        //randomize state variables
        pre.coins = rand() % (20);
        pre.numActions = rand() % (20);

        memcpy(&post, &pre, sizeof(struct gameState));
        printf("Test case 1: Reveal and discard top 2 cards (1 action card and 1 treasure card) from next player's hand. \n\n");

        // set top 2 cards
        post.hand[nextPlayer][10] = village;
        post.hand[nextPlayer][9] = copper;

        // call the refactored functions
        playTribute(&post, currentPlayer, handPos, &tributeRevealedCards[2], nextPlayer, bonus);

        // assert the results
        // discard 2 cards from other player's deck
        if (post.deckCount[nextPlayer] != pre.deckCount[nextPlayer] - 2)
        {
            printf("Bug found! Number of discarded cards from other player's deck is not 2! \n");
            printf("Pre-call deckCount: %d \n", pre.deckCount[nextPlayer]);
            printf("Post-call deckCount: %d \n\n", post.deckCount[nextPlayer]);
        }

        // copper coin (treasure card) should increase coins by 2
        if (post.coins != pre.coins + 2)
        {
            printf("Bug #1 found! Wrong amount of bonus added! \n");
            bug1_found_count++;
            printf("Pre-call coin tally: %d \n", pre.coins);
            printf("Post-call coin tally: %d \n\n", post.coins);
        }

        // village card (action card) should increase action plays by 1 (
        //deduct one for current phase and + 2 action phases)
        if (post.numActions != pre.numActions + 1)
        {
            printf("Bug #2 found! Number of action plays not incremented by 1! \n");
            bug2_found_count++;
            printf("Pre-call number of action plays: %d \n", pre.numActions);
            printf("Post-call number of action plays: %d \n\n", post.numActions);
        }

        memcpy(&post, &pre, sizeof(struct gameState));
        printf("Test case 2: Reveal and discard top 2 cards from next player's hand with victory cards only. \n\n");

        // call the refactored functions
        playTribute(&post, currentPlayer, handPos, &tributeRevealedCards[2], nextPlayer, bonus);

        post.hand[nextPlayer][10] = estate;
        post.hand[nextPlayer][9] = estate;

        // assert the results
        // adds only 2 cards to current player's deck and deduct 1 tribute card played
        // (net 1 additional card)
        if (post.handCount[currentPlayer] == pre.handCount[currentPlayer] + 1)
        {
            printf("Valid! Number of cards in player's hand is accurate! \n");
            printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
            printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
        }

        memcpy(&post, &pre, sizeof(struct gameState));
        printf("Test case 3: Next player does not have sufficient cards to reveal \n\n");

        post.deckCount[nextPlayer] = 0;
        post.discardCount[nextPlayer] = 0;
        // call the refactored functions
        playTribute(&post, currentPlayer, handPos, &tributeRevealedCards[2], nextPlayer, bonus);

        // assert the results
        // no actions taken and deduct 1 tribute card played
        if (post.deckCount[currentPlayer] != pre.deckCount[currentPlayer] - 1)
        {
            printf("Bug found! Only one tribute card should be discarded.\n");
            printf("Pre-call deckCount: %d \n", pre.deckCount[currentPlayer]);
            printf("Post-call deckCount: %d \n\n", post.deckCount[currentPlayer]);
        }

        memcpy(&post, &pre, sizeof(struct gameState));
        printf("Test case 4: Next player only have 1 card to reveal \n\n");

        post.deckCount[nextPlayer] = 1;
        post.hand[nextPlayer][1] = village;
        post.discardCount[nextPlayer] = 0;
        // call the refactored functions
        playTribute(&post, currentPlayer, handPos, &tributeRevealedCards[2], nextPlayer, bonus);

        // village card (action card) should increase action plays by 1 (
        //deduct one for current phase and + 2 action phases)
        if (post.numActions != pre.numActions + 1)
        {
            printf("Bug #2 found! Number of action plays not incremented by 1! \n");
            bug2_found_count++;
            printf("Pre-call number of action plays: %d \n", pre.numActions);
            printf("Post-call number of action plays: %d \n\n", post.numActions);
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Number of times Bug #1 was discovered in random testing >>> %d \n\n", bug1_found_count);
    printf("Number of times Bug #2 was discovered in random testing >>> %d \n\n", bug2_found_count);
    printf("Time elapsed >>> %f \n\n", time_spent);
    printf("Random Test 3 completed! \n\n");
    return 0;
}
