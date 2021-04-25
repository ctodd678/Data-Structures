CC = gcc
CFLAGS = -Wall -pedantic -std=c99


all: test_getbytes test_getbits test_bits2ull test_bits2ll test_spff test_dpff


test_getbytes: test_getbytes.c bandb.c
	$(CC) -o test_getbytes test_getbytes.c bandb.c

test_getbits: test_getbits.c bandb.c
	$(CC) -o test_getbits test_getbits.c bandb.c

test_bits2ull: test_bits2ull.c bandb.c
	$(CC) -o test_bits2ull test_bits2ull.c bandb.c

test_bits2ll: test_bits2ll.c bandb.c
	$(CC) -o test_bits2ll test_bits2ll.c bandb.c

test_spff: test_spff.c bandb.c
	$(CC) -o test_spff test_spff.c bandb.c

test_dpff: test_dpff.c bandb.c
	$(CC) -o test_dpff test_dpff.c bandb.c



test_getbytes.o: test_getbytes.c
	$(CC) $(CFLAGS) -c test_getbytes.c -o test_getbytes.o

test_getbits.o: test_getbits.c
	$(CC) $(CFLAGS) -c test_getbits.c -o test_getbits.o

test_bits2ull.o: test_bits2ull.c
	$(CC) $(CFLAGS) -c test_bits2ull.c -o test_bits2ull.o 

test_bits2ll.o: test_bits2ll.c
	$(CC) $(CFLAGS) -c test_bits2ll.c -o test_bits2ll.o 

test_spff.o: test_spff.c
	$(CC) $(CFLAGS) -c test_spff.c -o test_spff.o 

test_dpff.o: test_dpff.c
	$(CC) $(CFLAGS) -c test_dpff.c -o test_dpff.o

bandb.o: bandb.c
	$(CC) $(CFLAGS) -c bandb.c -o bandb.o  


clean:
	rm *.o *.out
