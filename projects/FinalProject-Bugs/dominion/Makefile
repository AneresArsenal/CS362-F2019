CFLAGS= -Wall -fpic -coverage -lm -std=c99

UTSOURCES = $(wildcard unittest*.c)
UTOUTPUT = $(patsubst %.c, %, $(UTSOURCES))

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.ut *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

unit_test_helpers.o: unit_test_helpers.h unit_test_helpers.c
	gcc -c unit_test_helpers.c -g  $(CFLAGS)

unittestresults: clean dominion.o unit_test_helpers.o rngs.o $(UTOUTPUT)
	gcov -f -b dominion.c >> unittestresults.out
	# cat dominion.c.gcov

$(UTOUTPUT): %: %.c
	$(CC) -o $@.ut -g $@.c dominion.o unit_test_helpers.o rngs.o $(CFLAGS)
	./$@.ut >> unittestresults.out
