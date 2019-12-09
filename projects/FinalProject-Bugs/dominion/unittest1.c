#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void passFail(int result)
{
    if (result == 1)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
}

int main()
{
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int output;
    int pass = -1;
    struct gameState G, testG;
    int k[10] = {adventurer, baron, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    printf("--------------------- Project Bug #1 ------------------------\n");

    // ----------- TEST 1: --------------

    printf("TEST 1: choice1 = silver, choice2 = copper \n");

    pass = -1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //set players hand
    G.hand[thisPlayer][0] = silver;
    G.hand[thisPlayer][1] = silver;
    G.hand[thisPlayer][2] = mine;
    G.handCount[thisPlayer] = 3;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    choice1 = 0;
    choice2 = copper;
    handpos = 2;
    output = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("return value = %d, expected = %d - ", output, 0);
    passFail(output == 0);
    printf("current players discardCount = %d, expected = %d - ", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
    passFail(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);
    printf("current players discard pile contains = %d, expected = %d - ", testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1], mine);
    passFail(testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1] == mine);
    printf("current players hand count = %d, expected = %d - ", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
    passFail(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);
    printf("Player's hand contains copper piece - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        if (testG.hand[thisPlayer][i] == copper)
        {
            pass = 1;
            break;
        }
    }
    passFail(pass == 1);

    // ----------- TEST 2:  --------------

    printf("TEST 2: choice1 = copper, choice2 = silver \n");

    pass = -1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //set players hand
    G.hand[thisPlayer][0] = copper;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = mine;
    G.handCount[thisPlayer] = 3;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    choice1 = 0;
    choice2 = silver;
    handpos = 2;
    output = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("return value = %d, expected = %d - ", output, 0);
    passFail(output == 0);
    printf("current players discardCount = %d, expected = %d - ", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
    passFail(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);
    printf("current players discard pile contains = %d, expected = %d - ", testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1], mine);
    passFail(testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1] == mine);
    printf("current players hand count = %d, expected = %d - ", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
    passFail(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);
    printf("Player's hand contains silver piece - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        if (testG.hand[thisPlayer][i] == silver)
        {
            pass = 1;
            break;
        }
    }
    passFail(pass == 1);

    printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #1 <<<<<<<<<<<<<<<<<<< \n\n");

    return 0;
}
