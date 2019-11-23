/*
Assignment 4 - Learn how to create a Random Tester
Random Test 1 
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

    //reference https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/

    // initialize and set variables
    struct gameState pre, post;
    int k[10] = {feast, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    int bug1_found_count = 0,
        bug2_found_count = 0;

    printf("Starting Random Test 1 - playBaron function \n\n");

    initializeGame(2, k, 1234, &pre);
    printf("Game initialized \n\n");

    for (int i = 0; i < 100; i++)
    {
        // reset game whenever a test is completed
        memcpy(&post, &pre, sizeof(struct gameState));

        printf("Random Test # %d \n", i);

        int choice1 = 1,
            currentPlayer = 1,
            r = rand() % (10 + 1); //number of cards in hand

        pre.handCount[currentPlayer] = r;

        //randomize state variables
        pre.coins = rand() % (20);
        pre.numActions = rand() % (20);

        // randomly assign cards
        for (int j = 0; j < r; j++)
        {
            int card = rand() % (10);
            pre.hand[currentPlayer][j] = k[card];
        }

        printf("Test case 1: Estate card exist in hand and player choose to discard estate. \n\n");

        // set one to be estate
        post.hand[currentPlayer][4] = estate;

        // call the refactored functions
        baronCard(choice1, &post);

        // assert the results
        // bonus points should be added
        if (post.coins != pre.coins + 4)
        {
            printf("Bug found! Bonus not added properly! \n");
            printf("Pre-call coin tally: %d \n", pre.coins);
            printf("Post-call coin tally: %d \n\n", post.coins);
        }

        if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 2)
        {
            printf("Bug #1 Found! Baron card and estate card found should both be discarded! \n");
            bug1_found_count++;
            printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
            printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
        }

        int j = post.discardCount[currentPlayer];
        int countEstate = 0;

        for (int i = 0; i < j; i++)
        {
            if (post.discard[currentPlayer][i] == estate)
            {
                countEstate++;
            }
        }

        // only one estate card should be in the discard pile (the one that is discarded)
        if (countEstate != 1)
        {
            printf("Bug #2 Found!Only one Estate card should exist in discard pile! \n");
            bug2_found_count++;
            printf("Pre-call Estate discardCount: %d \n", 0);
            printf("Post-call Estate discardCount: %d \n\n", countEstate);
        }

        memcpy(&post, &pre, sizeof(struct gameState));
        printf("Test case 2: Estate card do not exist in hand and player choose to discard estate. \n\n");

        // call the refactored functions
        baronCard(choice1, &post);

        // assert the results
        // bonus points should not be added
        if (post.coins == pre.coins)
        {
            printf("Valid! Bonus not added! \n");
            printf("Pre-call coin tally: %d \n", pre.coins);
            printf("Post-call coin tally: %d \n\n", post.coins);
        }

        if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 1)
        {
            printf("Error!  Baron card not discarded! \n");
            printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
            printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
        }

        memcpy(&pre, &post, sizeof(struct gameState));
        printf("Test case 3: Estate card do not exist in hand and player choose not to discard estate. \n\n");

        // call the refactored functions
        baronCard(choice1, &post);

        // assert the results
        // bonus points should be added
        if (post.coins == pre.coins)
        {
            printf("Valid! Bonus not added! \n");
            printf("Pre-call coin tally: %d \n", pre.coins);
            printf("Post-call coin tally: %d \n\n", post.coins);
        }

        if (post.handCount[currentPlayer] == pre.handCount[currentPlayer] - 1)
        {
            printf("Valid! Only Baron card discarded! \n");
            printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
            printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
        }

        if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 1)
        {
            printf("Error! Baron card not discarded! \n");
            printf("Pre-call handCount: %d \n", pre.handCount[currentPlayer]);
            printf("Post-call handCount: %d \n\n", post.handCount[currentPlayer]);
        }

        memcpy(&post, &pre, sizeof(struct gameState));
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Number of times Bug #1 was discovered in random testing >>> %d \n\n", bug1_found_count);
    printf("Number of times Bug #2 was discovered in random testing >>> %d \n\n", bug2_found_count);
    printf("Time elapsed >>> %f \n\n", time_spent);
    printf("Random Test 1 completed! \n\n");
    return 0;
}
