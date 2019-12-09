#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest9()
{
    printf("--------------------- Project Bug #9 ------------------------\n");
    printf("Starting Unit Test 9 - Tribute card - duplicate revealed cards \n\n");

    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 1234, &pre);

    printf("Game initialized \n\n");

    //Set discard pile to zero.
    pre.discardCount[pre.whoseTurn] = 0;
    pre.discard[pre.whoseTurn][0] = -1;

    int bonus = 0,
        r = 10;

    int nextPlayer = pre.whoseTurn + 1;

    //Set first cards in hand to feast and silver
    pre.deckCount[pre.whoseTurn] = r;
    pre.deckCount[nextPlayer] = r;
    // pre.deck[pre.whoseTurn][0] = tribute;

    // randomly assign cards to player and other player
    for (int i = 0; i < r; i++)
    {
        pre.deck[pre.whoseTurn][i] = k[9 - i];
        pre.deck[nextPlayer][i] = k[9 - i];
    }

    // set test variables
    pre.numActions = 0;
    pre.coins = 0;
    int pre_bonus = bonus;

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Reveal and discard top 2 cards (1 action card and 1 treasure card) from next player's hand. \n\n");

    // set top 2 cards
    post.deck[nextPlayer][9] = village;
    post.deck[nextPlayer][8] = copper;

    // call the cardEffect function
    cardEffect(tribute, 0, 0, 0, &post, 0, &bonus);

    // assert the results
    // copper coin (treasure card) should increase coins by 2
    if (bonus - pre_bonus != 2)
    {
        printf("Bug found! 2 bonus coins should be added! \n");
        printf("Pre-call bonus tally: %d \n", pre_bonus);
        printf("Post-call bonus tally: %d \n\n", bonus);
    }

    if (post.coins - pre.coins == 2)
    {
        printf("Bug found! 2 bonus coins should be added to bonus and not coins tally! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

    // village card (action card) should increase action plays by 2
    // if (post.numActions == pre.numActions + 2)
    // {
    //     printf("Valid! Number of action plays by 2! \n");
    //     printf("Pre-call number of action plays: %d \n", pre.numActions);
    //     printf("Post-call number of action plays: %d \n\n", post.numActions);
    // }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Reveal and discard top 2 cards from next player's hand with victory cards only. \n\n");

    // set top 2 cards
    post.deck[nextPlayer][9] = estate;
    post.deck[nextPlayer][8] = estate;

    // call the cardEffect function
    cardEffect(tribute, 0, 0, 0, &post, 0, &bonus);

    // assert the results
    // adds 2 cards to current player's deck and two action phases (bug error)
    // if (post.handCount[pre.whoseTurn] == pre.handCount[pre.whoseTurn] + 2)
    // {
    //     printf("Valid! Number of cards in player's hand is accurate! \n");
    //     printf("Pre-call handCount: %d \n", pre.handCount[pre.whoseTurn]);
    //     printf("Post-call handCount: %d \n\n", post.handCount[pre.whoseTurn]);
    // }

    if (post.numActions != pre.numActions)
    {
        printf("Bug found! Number of action plays should be unchanged! \n");
        printf("Pre-call number of action plays: %d \n", pre.numActions);
        printf("Post-call number of action plays: %d \n\n", post.numActions);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 3: Reveal and discard top 2 cards from next player's hand with action cards only. \n\n");

    // printf("Next player: %d \n", nextPlayer);

    // duplicate action cards on top deck
    post.deck[nextPlayer][9] = minion;
    post.deck[nextPlayer][8] = minion;

    // call the cardEffect function
    cardEffect(tribute, 0, 0, 0, &post, 0, &bonus);

    // assert the results
    // adds only 2 action phases to current player's deck
    if (post.numActions == pre.numActions + 4)
    {
        printf("Bug found! Number of action plays should be added by 2!  \n");
        printf("Pre-call numActions: %d \n", pre.numActions);
        printf("Post-call numActions: %d \n\n", post.numActions);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 4: Reveal and discard top 2 cards from next player's hand with treasure cards only. \n\n");

    // duplicate action cards on top deck
    post.deck[nextPlayer][9] = gold;
    post.deck[nextPlayer][8] = gold;

    bonus = 0;

    // call the cardEffect function
    cardEffect(tribute, 0, 0, 0, &post, 0, &bonus);

    // assert the results
    // adds only 2 action phases to current player's deck
    if (post.numActions != pre.numActions)
    {
        printf("Bug found! Number of action plays should be unchanged!  \n");
        printf("Pre-call numActions: %d \n", pre.numActions);
        printf("Post-call numActions: %d \n\n", post.numActions);
    }

    if (bonus - pre_bonus != 2)
    {
        printf("Bug found! 2 bonus coins should be added! \n");
        printf("Pre-call bonus tally: %d \n", pre_bonus);
        printf("Post-call bonus tally: %d \n\n", bonus);
    }

    if (post.coins - pre.coins == 2)
    {
        printf("Bug found! 2 bonus coins should be added to bonus and not coins tally! \n");
        printf("Pre-call coin tally: %d \n", pre.coins);
        printf("Post-call coin tally: %d \n\n", post.coins);
    }

printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #9 <<<<<<<<<<<<<<<<<<<\n\n");
}

int main()
{
    unitTest9();
}