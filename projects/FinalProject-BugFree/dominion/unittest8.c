#include "dominion.h"
#include "dominion_helpers.h"
#include "unit_test_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void unitTest8a()
{
    printf("--------------------- Project Bug #8 ------------------------\n");
    char *messagePrefix = "UNIT TEST 8A - playCard/cardEffect - Coin Tracking Issues For Baron";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = baron;
    G.hand[G.whoseTurn][1] = estate;
    G.hand[G.whoseTurn][2] = copper;
    G.handCount[G.whoseTurn] = 3;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    playCard(0, 1, 0, 0, &G);

    assert(G.coins == (preG.coins + 4), "%s - End Num Coins (%d) == Start Num Coins + 4 (%d)\n", messagePrefix, G.coins, (preG.coins + 4));
}

void unitTest8b()
{
    char *messagePrefix = "UNIT TEST 8B - playCard/cardEffect - Coin Tracking Issues For Cutpurse";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to cutpurse card
    G.hand[G.whoseTurn][0] = cutpurse;
    G.handCount[G.whoseTurn] = 1;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    playCard(0, 0, 0, 0, &G);

    assert(G.coins == (preG.coins + 2), "%s - End Num Coins (%d) == Start Num Coins + 2 (%d)\n", messagePrefix, G.coins, (preG.coins + 2));
}

void unitTest8c()
{
    char *messagePrefix = "UNIT TEST 8C - playCard/cardEffect - Coin Tracking Issues For Embargo";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to embargo card
    G.hand[G.whoseTurn][0] = embargo;
    G.handCount[G.whoseTurn] = 1;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    playCard(0, estate, 0, 0, &G);

    assert(G.coins == (preG.coins + 2), "%s - End Num Coins (%d) == Start Num Coins + 2 (%d)\n", messagePrefix, G.coins, (preG.coins + 2));
}

void unitTest8d()
{
    char *messagePrefix = "UNIT TEST 8D - playCard/cardEffect - Coin Tracking Issues For Minion";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to Minion card
    G.hand[G.whoseTurn][0] = minion;
    G.handCount[G.whoseTurn] = 1;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    playCard(0, 1, 0, 0, &G);

    assert(G.coins == (preG.coins + 2), "%s - End Num Coins (%d) == Start Num Coins + 2 (%d)\n", messagePrefix, G.coins, (preG.coins + 2));
}

void unitTest8e()
{
    char *messagePrefix = "UNIT TEST 8E - playCard/cardEffect - Coin Tracking Issues For Salvager";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to salvager and adventurer (cost is 6 for this card)
    G.hand[G.whoseTurn][0] = salvager;
    G.hand[G.whoseTurn][1] = adventurer;
    G.handCount[G.whoseTurn] = 2;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    playCard(0, 1, 0, 0, &G);

    assert(G.coins == (preG.coins + 6), "%s - End Num Coins (%d) == Start Num Coins + 6 (%d)\n", messagePrefix, G.coins, (preG.coins + 6));
}

void unitTest8f()
{
    char *messagePrefix = "UNIT TEST 8F - playCard/cardEffect - Coin Tracking Issues For Steward";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = steward;
    G.handCount[G.whoseTurn] = 1;

    G.coins = 10;

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    playCard(0, 2, 0, 0, &G);

    assert(G.coins == (preG.coins + 2), "%s - End Num Coins (%d) == Start Num Coins + 2 (%d)\n", messagePrefix, G.coins, (preG.coins + 2));
}

int main()
{
    unitTest8a();
    unitTest8b();
    unitTest8c();
    unitTest8d();
    unitTest8e();
    unitTest8f();

    printf("\n >>>>>>>>>>>>>> SUCCESS: Testing complete for Bug #8 <<<<<<<<<<<<<<<<<<<\n\n");
}