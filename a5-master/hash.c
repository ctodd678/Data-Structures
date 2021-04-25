#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

//hash.c

//BASIC FUNCTIONS

struct Performance *newPerformance(){

    struct Performance *new_struct = malloc(sizeof(struct Performance)); //create new performance struct

    //MALLOC ERROR MESSAGE
    if(new_struct == NULL){
        fprintf(stderr, "ERROR! Failed malloc in newPerformance (new_struct).\n");
        exit(0);
    }

    //DEFINE ELEMENTS OF PERFORMANCE STRUCT
    new_struct->reads = 0;
    new_struct->writes = 0;
    new_struct->mallocs = 0;
    new_struct->frees = 0;

    return new_struct;
}

struct HashTable *createTable(struct Performance *performance, unsigned int capacity, int (*hash)(void *, int ), int (*compar)(const void *, const void *)){
    
    struct HashTable *new_table = (struct HashTable*) malloc(sizeof(struct HashTable)); //create new HashTable struct

    //MALLOC ERROR MESSAGE
    if(new_table == NULL){
        fprintf(stderr, "ERROR! Failed malloc in createTable (new_table).\n");
        exit(0);
    }
    

    //SET ELEMENTS OF HashTable
    new_table->capacity = capacity;
    new_table->nel = 0;
    new_table->hash = hash;
    new_table->compar = compar;


    new_table->data = malloc(sizeof(void*) * capacity);
    
    //MALLOC ERROR MESSAGE
    if(new_table->data == NULL){
        fprintf(stderr, "ERROR! Failed malloc in createTable (new_table->data).\n");
        exit(0);
    }

    //printf("\n\nTEST hash");
    for(int i = 0; i < capacity; i++){
        new_table->data[i] = NULL;  //set pointers to null  
        performance->reads++;       //increment reads
    }

    performance->mallocs++;      //increment mallocs

    return new_table;
}

void addElement(struct Performance *performance, struct HashTable *table, void *src){

    int bucket;

    //nel == capacity ERROR MESSAGE
    if(table->nel == table->capacity){
        fprintf(stderr, "ERROR! table->nel == table->capacity in addElement.\n");
        exit(0);
    }

    bucket = table->hash(src, table->capacity);

    while(table->data[bucket] != NULL){
        bucket++;               //increment bucket
        performance->reads++;   //increment reads
        
        if(bucket == table->capacity){
            bucket = 0;                 //set bucket to 0 if bucket is at capacity
        }
    }

    table->data[bucket] = src;      //copy data
    performance->writes++;          //increment writes
}

int getIdx(struct Performance *performance, struct HashTable *table, void *src){

    int bucket, originalBucket, cmpBucket;

    bucket = table->hash(src, table->capacity);             //get initial bucket
    originalBucket = bucket;                                //set original bucket

    cmpBucket = table->compar(src, table->data[bucket]);    //get initial compar value
    performance->reads++;                                   //increment reads

    //loop until cmpBucket == 0
    while(cmpBucket != 0){
        bucket++;   

        if(bucket == table->capacity){
            bucket = 0;                 //set bucket to 0 if bucket is at capacity
        }
        if(bucket == originalBucket){   //return -1 if bucket == initial bucket
            return -1;
        }
        
        if(table->data[bucket] != NULL){
            cmpBucket = table->compar(table->data[bucket], src);    //set compar value
            performance->reads++;                                   //increment reads         
        }
    }

    return bucket;
}

void freeTable(struct Performance *performance, struct HashTable *table){

    //FREE POINTER ARRAY
    free(table->data);
    free(table);
    performance->frees++;   //increment frees
}

//DERIVED FUNCTIONS

void *getElement(struct Performance *performance, struct HashTable *table, void *src){

    int id = getIdx(performance, table, src);   //get id of element

    if(id == -1){                               //returns null if element not found
        return NULL;
    }
    else{
        return table->data[id];                 //return element
    }
}

void removeElement(struct Performance *performance, struct HashTable *table, void *target){

    int id = getIdx(performance, table, target);    //get id of element

    if(id != - 1){
        table->data[id] = NULL;
        performance->writes++;                      //increment writes
        table->nel--;                               //decrement nel         

    }
    else{
        fprintf(stderr, "ERROR! Element not found in removeElement.");
    }
}

//20% FUNCTIONS

int hashAccuracy(struct HashTable *table){

    int i = 0, hashI = 0, hashDifference = 0, hashAcc = 0;

    //ITERATE THROUGH HASH TABLE AND CALCULATE DIFFERENCES 
    for(; i < table->capacity; i++){
        if(table->data[i] != NULL){
            hashI = table->hash(table->data[i], table->capacity);
            hashDifference = i - hashI;

            if(i > hashI){
                hashAcc = hashAcc + hashDifference;
            } 
            else if(i < hashI){
                hashAcc = hashAcc + (table->capacity - (hashI + i));
            }
        }
    }
    return hashAcc;
}

void rehash(struct HashTable *table){

    int i = 0, hashI = 0, hashDifference = 0, hashAcc = 0, newHashAcc = 0;

    int emptyIndex = 0;
    int moved = 0;

    while(moved < 10){
        for(; i < table->capacity; i++){
            if(table->data[i] == NULL){
                //find next index with data
                emptyIndex = i;
                while(table->data[i] == NULL){
                    i++;
                }
                table->data[emptyIndex] = table->data[i];   //set data
                moved++;                                    //increment moved
            }
        }
    }
}
