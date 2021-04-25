#include <stdio.h>
#include "tree.h"

//tree.c

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

void attachNode(struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width ){

    struct Node *new_node = malloc(sizeof(struct Node));    //create new Node struct

    //MALLOC ERROR MESSAGE
    if(new_node == NULL){
        fprintf(stderr, "ERROR! Failed malloc in attachNode (new_node).\n");
        exit(0);
    }

    //DEFINE NODE ELEMENTS
    new_node->data = malloc(width);
    new_node->lt = NULL;
    new_node->gte = NULL;

    memcpy(new_node->data, src, width);     //copy memory into new_node->data

    *node_ptr = new_node;

    performance->mallocs++;     //increment mallocs
    performance->writes++;      //increment writes
}

int comparNode(struct Performance *performance, struct Node**node_ptr, int (*compar)(const void *, const void *), void *target){

    struct Node *tempNode = *node_ptr;

    performance->reads++;       //increment reads

    return compar(target, tempNode->data);      //return compar result
    
    //ERROR MESSAGE
    fprintf(stderr, "ERROR! Something wrong happened in  comparNode.\n");
    exit(0);
}

struct Node**next(struct Performance *performance, struct Node**node_ptr, int direction){

    struct Node *tempNode = *node_ptr;

    //TREE EMPTY ERROR MESSAGE
    if(isEmpty(performance, node_ptr) == 1){
        fprintf(stderr, "ERROR! Tree is empty. (next).\n");
        exit(0);
    }

    //return lower tree if direction < 0 or return higher try if direction >= 0
    if(direction < 0){
        performance->reads++; 
        return &tempNode->lt;
    }
    else if(direction >= 0){
        performance->reads++; 
        return &tempNode->gte;
    }
   
    //ERROR MESSAGE
    fprintf(stderr, "ERROR! Something went wrong in next.\n");
    exit(0);

    return NULL;  
}

void readNode(struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width ){

    struct Node *tempNode = *node_ptr;

    //TREE EMPTY ERROR MESSAGE
    if(isEmpty(performance, node_ptr) == 1){
        return;
    }

    memcpy(dest, tempNode->data, width);        //copy data 

    performance->reads++;                       //increment reads
}

void detachNode(struct Performance *performance, struct Node**node_ptr){

    struct Node *tempNode = *node_ptr;

    //TREE EMPTY ERROR MESSAGE
    if(isEmpty(performance, node_ptr) == 1){
        fprintf(stderr, "ERROR! Tree is empty. (readNode).\n");
        exit(0);
    }

    free(tempNode->data);
    tempNode->data = NULL;
    free(tempNode);
    tempNode = NULL;

    performance->frees++;       //increment frees
}

int isEmpty(struct Performance *performance, struct Node**node_ptr){

    //IF node_ptr is NULL return 1 else return 0
    if(*node_ptr == NULL){
        return 1; 
    } 
    else{
        return 0;
    }
}

//DERIVED FUNCTIONS

void addItem(struct Performance *performance, struct Node**node_ptr, int(*compar)(const void*, const void*), void *src, unsigned int width){

    struct Node **currentNode = node_ptr;
    int tempCompar = 0;

    //iterate while tree is not empty 
    while(isEmpty(performance, currentNode) == 0){

        tempCompar = comparNode(performance, currentNode, compar, src);
        currentNode = next(performance, currentNode, tempCompar);
    }

    //add item using attachNode
    attachNode(performance, currentNode, src, width);
}

void freeTree(struct Performance *performance, struct Node**node_ptr){

    struct Node **currentNode = node_ptr;
    
    //recursively free tree by calling freeTree while tree is not empty
    if(isEmpty(performance, currentNode) == 0){
        freeTree(performance, next(performance, currentNode, -1));
        freeTree(performance, next(performance, currentNode, 1));

        detachNode(performance, currentNode);   //use detach node to remove and free node
    }
}


//20% FUNCTIONS

int searchItem(struct Performance *performance, struct Node **node_ptr, int(*compar)(const void*, const void*), void *target, unsigned int width){

    struct Node **currentNode = node_ptr;
    int tempCompar = 10;

     //TREE EMPTY ERROR MESSAGE
    if(isEmpty(performance, node_ptr) == 1){
        fprintf(stderr, "ERROR! Tree is empty. (searchItem).\n");
        exit(0);
    }

    //iterate through tree while not 
    while(isEmpty(performance, currentNode) == 0){

        tempCompar = comparNode(performance, currentNode, compar, target); 

        //if match found read node and return 1
        if(tempCompar == 0){
            readNode(performance, currentNode, target, width);
            return 1;
            break;
        }

        
        currentNode = next(performance, currentNode, tempCompar);
    }

    return 0;   //return 0 if item not found
}