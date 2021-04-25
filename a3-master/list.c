#include "list.h"


//BASIC PROTOTYPES
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

void push(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){

    struct Node *new_node = malloc(sizeof(struct Node)); //create new Node struct

    //MALLOC ERROR MESSAGE
    if(new_node == NULL){
        fprintf(stderr, "ERROR! Failed malloc in push (new_node).\n");
        exit(0);
    }

    new_node->data = malloc(width);
    new_node->next = NULL;

    memcpy(new_node->data, src, width);

    new_node->next = *list_ptr;
    *list_ptr = new_node;


    //INCREMENT MALLCOS AND WRITES
    performance->mallocs++;
    performance->writes++;
}

void readHead( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ){

    struct Node *tempList = *list_ptr;

    //LIST EMPTY ERROR MESSAGE
    if(isEmpty(performance, list_ptr)){
        fprintf(stderr, "ERROR! List empty in readHead.\n");
        exit(0);
    }

    memcpy(dest, tempList->data, width);


    //INCREMENT READS
    performance->reads++;

}

void pop( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ){

    struct Node *tempList = *list_ptr;

    //LIST EMPTY ERROR MESSAGE
    if(isEmpty(performance, list_ptr)){
        fprintf(stderr, "ERROR! List empty in pop.\n");
        exit(0);
    }

    memcpy(&dest, tempList->data, width);

    *list_ptr = tempList->next;

    free(tempList->data);
    free(tempList);

    //INCREMENT FREES AND READS
    performance->frees++;
    performance->reads++;
}

struct Node **next( struct Performance *performance, struct Node **list_ptr){

    struct Node *tempList = *list_ptr;

    //LIST EMPTY ERROR MESSAGE
    if(isEmpty(performance, list_ptr)){
        fprintf(stderr, "ERROR! List empty in next.\n");
        exit(0);
    } 

    performance->reads++;

    return &tempList->next;
}

int isEmpty( struct Performance *performance, struct Node **list_ptr){

    //IF LIST EMPTY
    if(*list_ptr == NULL){
        return 1; 
    } 
    else{
        return 0;
    }
}


//DERIVED PROTOTYPES

void freeList( struct Performance *performance, struct Node **list_ptr){

    struct Node *tempList = *list_ptr;
    void *temp_dest = tempList->data;
    unsigned int temp_width = sizeof(tempList->data);

    //TRAVERSE LIST UNTIL EMPTY
    while(isEmpty(performance, list_ptr) == 0){
        pop(performance, list_ptr, temp_dest, temp_width);
    }
}

void readItem( struct Performance *performance, struct Node **list_ptr, int i, void *dest, unsigned int width){

    struct Node **currentNode = list_ptr;

    //TRAVERSE LIST UNTIL INDEX
    for(int j = 0; j < i; j++){
        currentNode = next(performance, currentNode);
    }
    readHead(performance, currentNode, dest, width);

}

void appendItem(struct Performance *performance, struct Node **list_ptr, void *src, int width){

    struct Node **currentNode = list_ptr;

    //TRAVERSE LIST UNTIL EMPTY
    while(isEmpty(performance, currentNode) == 0){
        currentNode = next(performance, currentNode);
    }

    push(performance, currentNode, src, width);
    
}

void insertItem(struct Performance *performance, struct Node **list_ptr, int index, void *src, int width){

    struct Node **currentNode = list_ptr;

    //TRAVERSE LIST UNTIL INDEX
    for(int i = 0; i < index; i++){
        currentNode = next(performance, currentNode);
    }

    push(performance, currentNode, src, width);

}

void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, int width){

    //CALL INSERT ITEM WITH INDEX 0
    insertItem(performance, list_ptr, 0, src, width);
}

void deleteItem(struct Performance *performance, struct Node **list_ptr, int index ){

    struct Node **currentNode = list_ptr;
    void *temp_dest;
    unsigned int temp_width;

    //TRAVERSE LIST UNTIL INDEX
    for(int i = 0; i < index; i++){
        currentNode = next(performance, currentNode);
    }

    struct Node *tempNode = *currentNode;

    temp_width = sizeof(tempNode->data);
    temp_dest = tempNode->data;

    pop(performance, currentNode, temp_dest, temp_width);
}


//LAST 20% PROTOTYPES

int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width){

    struct Node *tempList = *list_ptr;
    int i = 0;

    //TRAVERSE LIST UNTIL EMPTY
    while(isEmpty(performance, &tempList) == 0){

        readHead(performance, &tempList, tempList->data, width); //READ HEAD OF CURRENT LIST

        if(compar(target, tempList->data) == 0){
            return i; //RETURN INDEX IF MATCH
        }

        tempList = *next(performance, &tempList);
        i++;
    }

    return -1; //RETURN -1 IF NO MATCH FOUND
}