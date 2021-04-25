CC = gcc
CFLAGS = -Wall -pedantic -std=c99


all: buildidx key2val val2key actors bacon1


util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o

hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o


buildidx: buildidx.o util.o hashfn.o
	$(CC) $(CFLAGS) buildidx.o util.o hashfn.o -o buildidx

buildidx.o: buildidx.c 
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o

key2val: key2val.o util.o hashfn.o
	$(CC) $(CFLAGS) key2val.o util.o hashfn.o -o key2val

key2val.o: key2val.c 
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o

val2key: val2key.o util.o hashfn.o
	$(CC) $(CFLAGS) val2key.o util.o hashfn.o -o val2key

val2key.o: val2key.c 
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o

actors: actors.o util.o hashfn.o
	$(CC) $(CFLAGS) actors.o util.o hashfn.o -o actors

actors.o: actors.c 
	$(CC) $(CFLAGS) -c actors.c -o actors.o

bacon1: bacon1.o util.o hashfn.o
	$(CC) $(CFLAGS) bacon1.o util.o hashfn.o -o bacon1

bacon1.o: bacon1.c 
	$(CC) $(CFLAGS) -c bacon1.c -o bacon1.o




clean:
	rm *.o
