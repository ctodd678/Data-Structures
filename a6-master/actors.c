#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

//actors.c

int main(int argc, char *argv[]){

    FILE *fp_movieNames, *fp_movieActors, *fp_actorNames;
    int key_i = 0;
    char *movieName;
    char val[STRLEN] = "";
    char key[STRLEN] = "";

    //CHECK CMD LINE ARGS
    if (argc == 2){
        movieName = malloc(sizeof(char) * strlen(argv[1]) + 1);
        strcpy(movieName, argv[1]);
    }
    else{
        fprintf(stderr, "Usage: %s ‘movie name’\n", argv[0]);  //error message for more than 2 args
        exit(0);
    }
    
    //OPEN FILES
    fp_movieNames = fopen("title.basics.kv", "rb");
    fp_movieActors = fopen("title.principals.kv", "rb");
    fp_actorNames = fopen("name.basics.kv", "rb");

    char *actorKeys[256];

    char movieKey[256];
    int i = 0;
    //GET MOVIE KEY
    key_i = read_keyval(fp_movieNames, key, val);
    while(key_i == 2){
        if(strcmp(val, movieName) == 0){
            strcpy(movieKey, key);
            break;
        }
        key_i = read_keyval(fp_movieNames, key, val);
    }


    fclose(fp_movieActors);
    fp_movieActors = fopen("title.principals.kv", "rb");
    
    //GET ACTOR KEYS FOR MOVIE
    key_i = read_keyval(fp_movieActors, key, val);
    while(key_i == 2){
        if(strcmp(key, movieKey) == 0){
            actorKeys[i] = malloc(strlen(val) + 1);
            strcpy(actorKeys[i], val);
            i++;
        }
        key_i = read_keyval(fp_movieActors, key, val);
    }
    int actorCount = i;
 
    //GET ACTOR NAMES FROM ACTORS KEYS
    key_i = read_keyval(fp_actorNames, key, val);
    while(key_i == 2){
        for(i = 0; i < actorCount; i++){
            if(strcmp(actorKeys[i], key) == 0){
                printf("%s\n" , val);
            }
        }
        key_i = read_keyval(fp_actorNames, key, val);
    }
    
    //FREE EVERYTHING AND QUIT
    for(i = actorCount - 1; i >= 0; i--){
        free(actorKeys[i]);
    }
    
    free(movieName);
    fclose(fp_movieNames);
    fclose(fp_movieActors);
    fclose(fp_actorNames);
    
    return 0;
}