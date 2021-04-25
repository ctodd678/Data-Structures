#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

//ARRAY FUNCTIONS

struct Performance *newPerformance(){

    struct Performance *new_struct = malloc(sizeof(struct Performance)); //ALLOCATE MEMORY FOR PERFORMANCE STRUCT

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

struct Array *newArray(struct Performance *performance, unsigned int width, unsigned int capacity ){

    struct Array *new_struct = malloc(sizeof(struct Array)); //ALLOCATE MEMORY FOR ARRAY STRUCT

    //MALLOC ERROR MESSAGE
    if(new_struct == NULL){
        fprintf(stderr, "ERROR! Failed malloc in newArray (new_struct).\n");
        exit(0);
    }

    //DEFINE ELEMENTS OF ARRAY STRUCT
    new_struct->width = width;
    new_struct->nel = 0;
    new_struct->capacity = capacity;
    new_struct->data = malloc(width * capacity);

    //MALLOC ERROR MESSAGE
    if(new_struct->data == NULL){
        fprintf(stderr, "ERROR! Failed malloc in newArray (newstruct->data).\n");
        exit(0);
    }


    performance->mallocs = performance->mallocs + 1; //INCREMENT MALLOCS IN ARRAY

    return new_struct;

}

void readItem(struct Performance *performance, struct Array *array, unsigned int index, void *dest ){
    
    //ERROR MESSAGE
    if(index >= array->nel){
        fprintf(stderr, "ERROR! Index is >= array->nel in readItem.\n");
        exit(0);
    }
    
    char* tempDest = (char*)dest;
    char* tempData = (char*)array->data;

    int tempI = index * array->width;

    //TRAVERSES ARRAY AND READS ITEMS IN ARRAY
    for(int i = 0; i < array->width; i++){
        tempDest[i] = tempData[tempI];
        tempI++;
    }
    
    performance->reads = performance->reads + 1;

}

void writeItem(struct Performance *performance, struct Array *array, unsigned int index, void *src){

    //ERROR MESSAGE
    if(index > array->nel || index >=array->capacity){
        fprintf(stderr, "ERROR! Index is > array->nel OR index >=array->capacity in writeItem.\n");
        exit(0);
    }

    char* tempSrc = (char*)src;
    char* tempData = (char*)array->data;

    int tempI = index * array->width;

    for(int i = 0; i < array->width; i++){
        tempData[tempI] = tempSrc[i];
        tempI++;
    }

    if(array->nel == index){
        array->nel = array->nel + 1;
    }

     performance->writes = performance->writes + 1;

}

void contract(struct Performance *performance, struct Array *array){

    //ERROR MESSAGE
    if(array->nel == 0){
        fprintf(stderr, "ERROR! array-> nel == 0 in contract.\n");
        exit(0);
    }
    else{
        array->nel = array->nel - 1; //DECREASE ARRAY SIZE BY 1
    }
}

void freeArray( struct Performance *performance, struct Array *array ){

    //FREE ARRAY
    free(array->data);
    free(array);

    performance->frees = performance->frees + 1; //INCREMENT FREES IN ARRAY
}

//DELIVERED FUNCTIONS

void appendItem( struct Performance *performance, struct Array *array, void *src){

    //WRITES ITEM TO ARRAY
    writeItem(performance, array, array->nel, src);

}

void insertItem(struct Performance *performance, struct Array *array, unsigned int index, void *src){

    char* temp;
    int tempIndex = index;
    int i = array->nel;

    //TRAVERSES ARRAY FROM END TO START AND INSERTS VALUES
    for(i = i - 1; i > tempIndex - 1; i--){

        readItem(performance, array, i, &temp);
        writeItem(performance, array, i + 1, &temp);
    }
   
    writeItem(performance, array, index, src);

}

void prependItem(struct Performance *performance, struct Array *array, void *src){

    //INSERT VALUE AT INDEX 0 AT ARRAY
    insertItem(performance, array, 0, src);

}

void deleteItem(struct Performance *performance, struct Array *array, unsigned int index){

    char* temp;

    //TRAVERSES ARRAY STARTING AT INDEX AND OVERWRITE SPECIFIED INDEX WITH NEXT VALUE AND SO ON
    for(int i = index; i < array->nel - 1; i++){
        
        readItem(performance, array, i + 1, &temp);
        writeItem(performance, array, i, &temp);
    }
    
    contract(performance, array);
}


//FINAL 20%

int findItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){

    int i , compar_result = 0;
    unsigned char* c1 = target;
    unsigned char* c2[array->width];
    
    //TRAVERSE ENTIRE ARRAY, RETURN INDEX IF FOUND, -1 IF NOT FOUND
    for(i = 0; i < array->nel; i++){
        readItem(performance, array, i, c2);
        compar_result = compar(c1, c2);
        if(compar_result == 0){
            break;
        }
    }
    if(compar_result == 0){
        return i;
    }
    else{
        return -1;
    }
}

int searchItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){

    int high = (int) array->nel - 1, mid = 0, low = 0, compar_result = 5;
    unsigned char* c1 = target;
    unsigned char  c2[array->width];

    //BINARY SEARCH ALGORITHM IMPLEMENTED FROM Zybooks - > CIS 2520: Data Structures Unit 2, Chapter 2 "Binary Search"
    while(high >= low){
        mid = (high + low) / 2;
        readItem(performance, array, mid, c2);
        compar_result = compar(c1, c2);

        if(compar_result > 0){
            low = mid + 1;
        }
        else if(compar_result < 0){
            high = mid - 1;
        }
        else{
            return mid;
        }
    }
    
    return -1;
}
