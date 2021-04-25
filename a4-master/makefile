CC = gcc
CFLAGS = -Wall -pedantic -std=c99


all: ttest


tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o


ttest: ttest.o tree.o
	$(CC) $(CFLAGS) ttest.o tree.o -o ttest


ttest.o: ttest.c 
	$(CC) $(CFLAGS) -c ttest.c -o ttest.o



clean:
	rm *.o *.out
