#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//BANDB HEADER FILE


//FUNCTION DEFINITIONS
void getbytes(unsigned char * , int, void * , int);

void getbits(char *, int , void * , int  , int);

unsigned long long bits2ull(char *);

long long bits2ll(char *);

unsigned long long pow_unsigned(unsigned long long, unsigned long long);

long long pow_signed(long long , long long);

void spff( char *, char *, char *, float *);

void dpff( char *, char *, char *, double *);