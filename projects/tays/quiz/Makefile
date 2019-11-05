CFLAGS= -Wall -fpic -coverage -lm -std=c99

make:
	gcc  -o testme -g  testme.c $(CFLAGS)

run:
	./testme

coverage:
	gcov testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme
