CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

randomtestcard1: dominion.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	
randomtestcard3: dominion.o randomtestcard3.c
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS)
	
randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
	@echo "--randomtestcard1 results--\n" &> randomtestresults.out
	./randomtestcard1 &> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	@echo "\n\n--randomtestcard2 results--\n" &> randomtestresults.out
	./randomtestcard2 &> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	@echo "\n\n--randomtestcard3 results--\n" &> randomtestresults.out
	./randomtestcard3 &> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out


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
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
