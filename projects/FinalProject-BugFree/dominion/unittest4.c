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
    int seed = 1000;
    int numPlayers = 2;
    int output;
    struct gameState G, testG;
    int k[10] = {adventurer, baron, village, minion, remodel, cutpurse,
                 sea_hag, treasure_map, salvager, council_room};

    printf("--------------------- Project Bug #4 ------------------------\n");

    // ----------- TEST 1: --------------

    printf("TEST 1: isGameOver - Yes \n");

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //set supply count
    G.supplyCount[sea_hag] = 0;
    G.supplyCount[treasure_map] = 0;
    G.supplyCount[salvager] = 0;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    output = isGameOver(&testG);

    printf("return value = %d, expected = %d - ", output, 1);
    passFail(output == 1);

    printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #4 <<<<<<<<<<<<<<<<<<<\n\n");

    return 0;
}
