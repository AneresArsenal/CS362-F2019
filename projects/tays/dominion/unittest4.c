/*
Assignment 3 - Learn how to create unit tests
Unit Test 4 
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
    int tributeRevealedCards[2] = {-1, -1};

    printf("Starting Unit Test 4 \n\n");

    initializeGame(2, k, 1234, &pre);
    printf("Game initialized \n\n");

    int handPos = 0,
        currentPlayer = 0,
        bonus = 0,
        r = 10;

    int nextPlayer = currentPlayer + 1;

    pre.handCount[currentPlayer] = r;
    pre.deckCount[nextPlayer] = 11;

    // randomly assign cards to player and other player
    for (int i = 0; i < r; i++)
    {
        pre.hand[currentPlayer][i] = k[9 - i];
        pre.hand[nextPlayer][i] = k[9 - i];
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Reveal and discard top 2 cards from next player's hand. \n\n");

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

    // copper coins should increase coins by 2
    if (post.coins != pre.coins + 2)
    {
        printf("Bug #1 found! Wrong amount of bonus added! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    // village card should increase action plays by 2
    if (post.numActions != pre.numActions + 2)
    {
        printf("Bug #2 found! Number of action plays not incremented by 2! \n");
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
    // adds 4 cards to current player's deck and deduct 1 tribute card played
    if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] + 3)
    {
        printf("Bug found! Number of cards in player's hand is not accurate! \n");
        printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
        printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 3: Next player does not have sufficient cards to reveal \n\n");

    // call the refactored functions
    playTribute(&post, currentPlayer, handPos, &tributeRevealedCards[2], nextPlayer, bonus);

    pre.deckCount[nextPlayer] = 0;
    pre.discardCount[nextPlayer] = 0;

    // assert the results
    // adds 4 cards to current player's deck and deduct 1 tribute card played
    if (post.deckCount[currentPlayer] != pre.deckCount[currentPlayer] - 1)
    {
        printf("Bug found! Only one tribute card should be discarded.\n");
        printf("Pre-call deckCount: %d \n", pre.deckCount[currentPlayer]);
        printf("Post-call deckCount: %d \n\n", post.deckCount[currentPlayer]);
    }

    printf("Unit Test 4 completed! \n\n");
    return 0;
}
