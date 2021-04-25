#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS
struct Node{
    void *data;
    struct Node *next;
};

struct Performance{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};


//BASIC PROTOTYPES
struct Performance *newPerformance();

void push(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);

void readHead( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );

void pop( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );

struct Node **next( struct Performance *performance, struct Node **list_ptr);

int isEmpty( struct Performance *performance, struct Node **list_ptr);


//DERIVED PROTOTYPES

void freeList( struct Performance *performance, struct Node **list_ptr);

void readItem( struct Performance *performance, struct Node **list_ptr, int i, void *dest, unsigned int width);

void appendItem( struct Performance *performance, struct Node**list_ptr, void *src, int width);

void insertItem(struct Performance *performance, struct Node **list_ptr, int index, void *src, int width);

void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, int width);

void deleteItem(struct Performance *performance, struct Node **list_ptr, int index );

//LAST 20% PROTOTYPES

int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width);