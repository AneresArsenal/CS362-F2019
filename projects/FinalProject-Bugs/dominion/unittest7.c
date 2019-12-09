#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest7()
{
    printf("--------------------- Project Bug #7 ------------------------\n");
    char *messagePrefix = "UNIT TEST 7 - Tribute - Loop Overrun";
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    int nextPlayer = G.whoseTurn + 1;
    G.hand[G.whoseTurn][0] = tribute;

    //Set first card in next player's deck to the same action cards
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = baron;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = mine; //This card currently won't be hit because of bug in code decrementing the deckCount multiple times.
    //G.deck[nextPlayer][G.deckCount[nextPlayer] - 3] = mine; //This would address but is not accurate.

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    cardEffect(tribute, 1, 0, 0, &G, 0, &bonus);

    assert(G.numActions == (preG.numActions + 4), "%s - Ending Actions (%d) == Starting Actions + 4 (%d)\n", messagePrefix, G.numActions, (preG.numActions + 4));
    assert(G.coins == (preG.coins), "%s - Ending Coins (%d) == Starting Coins (%d)\n", messagePrefix, G.coins, (preG.coins));
    assert(G.handCount[G.whoseTurn] == (preG.handCount[G.whoseTurn]), "%s - Ending Cards (%d) == Starting Cards (%d)\n", messagePrefix, G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));

    printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #7 <<<<<<<<<<<<<<<<<<<\n\n");
}

int main()
{
    unitTest7();
}