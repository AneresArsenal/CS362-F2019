#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest6()
{

    printf("--------------------- Project Bug #6 ------------------------\n");
    char *messagePrefix = "UNIT TEST 6 - Feast - Coin Management Issues";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to feast
    G.handCount[G.whoseTurn] = 1;
    G.hand[G.whoseTurn][0] = feast;

    int choice1 = silver; //Card to gain (worth 3, allowed)

    //Set discard pile to zero.
    G.discardCount[G.whoseTurn] = 0;
    G.discard[G.whoseTurn][0] = -1;

    //Coins should not reset between playing cards as bonus coins could be granted.
    G.coins = 6;

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    cardEffect(feast, choice1, 0, 0, &G, 0, &bonus);

    assert(G.coins == preG.coins, "%s - Ending Coins (%d) == Starting Coins (%d)\n", messagePrefix, G.coins, preG.coins);
    assert(G.handCount[G.whoseTurn] == 0, "%s - Hand Count == 0 (%d) \n", messagePrefix, G.handCount[G.whoseTurn]);

    printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #6 <<<<<<<<<<<<<<<<<<<\n\n");
}

int main()
{
    unitTest6();
}