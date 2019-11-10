
#Makefile for CS362 Quiz 2
#Nick Gantick
#11/10/2019


CFLAGS= -Wall -fpic -coverage -lm -std=c99


default: testme

testme:
	gcc -o testme testme.c $(CFLAGS)

clean:
	rm testme

cleanall:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme

	
#an example execution would be to navigate to the diretory where this makefile is located
#command[1]: make
#command[2]: ./testme