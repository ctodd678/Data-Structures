#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//hash.h

//STRUCTS

struct HashTable{
    unsigned int capacity;
    unsigned int nel;
    void **data;
    int (*hash)(void *, int );
    int (*compar)(const void *, const void *);
};

struct Performance{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};

//BASIC PROTOYPES

struct Performance *newPerformance();

struct HashTable *createTable(struct Performance *performance, unsigned int capacity, int (*hash)(void *, int ), int (*compar)(const void *, const void *));

void addElement(struct Performance *performance, struct HashTable *table, void *src);

int getIdx(struct Performance *performance, struct HashTable *table, void *src);

void freeTable(struct Performance *performance, struct HashTable *table);

//DERIVED PROTOYPES

void *getElement(struct Performance *performance, struct HashTable *table, void *src);

void removeElement(struct Performance *performance, struct HashTable *table, void *target);

//20% PROTOYPES

int hashAccuracy(struct HashTable *table);

void rehash(struct HashTable *table);
