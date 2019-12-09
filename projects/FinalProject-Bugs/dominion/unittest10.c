#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest10()
{
    printf("--------------------- Project Bug #10 ------------------------\n");
    printf("Starting Unit Test 10 - Ambassador card - comparing position i with card choice \n\n");

    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, ambassador, smithy};

    initializeGame(2, k, 1234, &pre);

    printf("Game initialized \n\n");

    int bonus = 0,
        r = 11;

    pre.handCount[pre.whoseTurn] = r;

    // randomly assign cards to player and other player
    for (int i = 0; i < r - 1; i++)
    {
        pre.hand[pre.whoseTurn][i] = k[9 - i];
    }

    pre.hand[pre.whoseTurn][10] = ambassador;
    // set 3 duplicate copper cards in deck
    pre.hand[pre.whoseTurn][9] = copper;
    pre.hand[pre.whoseTurn][8] = copper;
    pre.hand[pre.whoseTurn][7] = copper;

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 1: Choose to discard 1 copper card. \n\n");

    int choice1 = 9,
        choice2 = 1;

    // for (int i = 0; i < r; i++)
    // {
    //     printf("Card %d, %d \n", i, post.hand[post.whoseTurn][i]);
    // }

    // call the cardEffect function
    cardEffect(ambassador, choice1, choice2, 0, &post, 10, &bonus);

    // for (int i = 0; i < r; i++)
    // {
    //     printf("Card %d, %d \n", i, post.hand[post.whoseTurn][i]);
    // }

    // assert the results
    int discard = 0;
    int copperCount = 0;
    int i = 0;

    while (i < r)
    {
        if (post.hand[post.whoseTurn][i] == -1)
        {
            discard++;
        }

        if (post.hand[post.whoseTurn][i] == copper)
        {
            copperCount++;
        }
        i++;
    }

    if (discard == choice2 + 1)
    {
        printf("Correct number of cards is discarded.\n");
        printf("Number of cards to be discarded: %d \n", choice2 + 1);
        printf("Number of cards discarded: %d \n\n", discard);
    }

    if (copperCount == 2)
    {
        printf("Correct number of copper cards is discarded.\n");
        printf("Number of copper cards that should remain: %d \n", 3 - choice2);
        printf("Number of copper cards remaining: %d \n\n", copperCount);
    }

    memcpy(&post, &pre, sizeof(struct gameState));
    printf("Test case 2: Choose to discard two copper cards. \n\n");

    choice1 = 9;
    choice2 = 2;

    // call the cardEffect function
    cardEffect(ambassador, choice1, choice2, 0, &post, 10, &bonus);

    // assert the results
    discard = 0;
    i = 0;
    copperCount = 0;

    while (i < r)
    {
        if (post.hand[post.whoseTurn][i] == -1)
        {
            discard++;
        }

        if (post.hand[post.whoseTurn][i] == copper)
        {
            copperCount++;
        }
        i++;
    }

    if (discard != choice2 + 1)
    {
        printf("Bug Found! Wrong number of cards discarded.\n");
        printf("Number of cards to be discarded: %d \n", choice2 + 1);
        printf("Number of cards discarded: %d \n\n", discard);
    }

    if (copperCount != 1)
    {
        printf("Bug Found! Wrong number of copper cards discarded.\n");
        printf("Number of copper cards that should remain: %d \n", 3 - choice2);
        printf("Number of copper cards remaining: %d \n\n", copperCount);
    }

    printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #10 <<<<<<<<<<<<<<<<<<< \n\n");
}

int main()
{
    unitTest10();
}