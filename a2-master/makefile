CC = gcc
CFLAGS = -Wall -pedantic -std=c99


all: test1 test2 test3 test4 test5 test6 test7 test8


test1: test1.c array.c
	$(CC) -o test1 test1.c array.c

test2: test2.c array.c
	$(CC) -o test2 test2.c array.c  

test3: test3.c array.c
	$(CC) -o test3 test3.c array.c  

test4: test4.c array.c
	$(CC) -o test4 test4.c array.c  

test5: test5.c array.c
	$(CC) -o test5 test5.c array.c 

test6: test6.c array.c
	$(CC) -o test6 test6.c array.c 

test7: test7.c array.c
	$(CC) -o test7 test7.c array.c 

test8: test8.c array.c
	$(CC) -o test8 test8.c array.c 



test1.o: test1.c
	$(CC) $(CFLAGS) -c test1.c -o test1.o

test2.o: test2.c
	$(CC) $(CFLAGS) -c test2.c -o test2.o

test3.o: test3.c
	$(CC) $(CFLAGS) -c test3.c -o test3.o

test4.o: test4.c
	$(CC) $(CFLAGS) -c test4.c -o test4.o

test5.o: test5.c
	$(CC) $(CFLAGS) -c test5v.c -o test5.o

test6.o: test6.c
	$(CC) $(CFLAGS) -c test6.c -o test6.o

test7.o: test7.c
	$(CC) $(CFLAGS) -c test7.c -o test7.o

test8.o: test8.c
	$(CC) $(CFLAGS) -c test8.c -o test8.o


array.o: array.c
	$(CC) $(CFLAGS) -c array.c -o array.o

clean:
	rm *.o *.out
