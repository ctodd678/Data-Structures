#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

//actors.c

int main(int argc, char *argv[]){

    FILE *fp_movieNames, *fp_movieActors, *fp_actorNames;
    int key_i = 0;
    char *actorName;
    char val[STRLEN] = "";
    char key[STRLEN] = "";

    //CHECK CMD LINE ARGS
    if (argc == 2){
        actorName = malloc(sizeof(char) * strlen(argv[1]) + 1);
        strcpy(actorName, argv[1]);
    }
    else{
        fprintf(stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);  //error message for more than 2 args
        exit(0);
    }

    if(strcmp(actorName, "Kevin Bacon") == 0){
        fprintf(stderr, "You entered %s! Please enter a different actor's name.\n", actorName);
        exit(0);
    }
    
    //OPEN FILES
    fp_movieNames = fopen("title.basics.kv", "rb");
    fp_movieActors = fopen("title.principals.kv", "rb");
    fp_actorNames = fopen("name.basics.kv", "rb");

    char *actorKey = NULL;
    char baconKey[256];
    
    //GET ACTOR KEY
    key_i = read_keyval(fp_actorNames, key, val);
    while(key_i == 2){
        if(strcmp(val, actorName) == 0){
            actorKey = malloc(sizeof(char) * strlen(key) + 1);
            strcpy(actorKey, key);
            break;
        }
        key_i = read_keyval(fp_actorNames, key, val);
    }

    if(actorKey == NULL){
        fprintf(stderr, "Actor %s not found! Please enter a different actor's name.\n", actorName);
        exit(0);
    }

    //RESET FILE POINTER
    fclose(fp_actorNames);
    fp_actorNames = fopen("name.basics.kv", "rb");

    //GET BACON KEY
    key_i = read_keyval(fp_actorNames, key, val);
    while(key_i == 2){
        if(strcmp(val, "Kevin Bacon") == 0){
            strcpy(baconKey, key);
            break;
        }
        key_i = read_keyval(fp_actorNames, key, val);
    }

    //RESET FILE POINTER
    fclose(fp_actorNames);
    fp_actorNames = fopen("name.basics.kv", "rb");

    char *actorMovies[256];
    
    int i = 0;
    //GET MOVIE KEYS FROM ACTOR KEYS
    key_i = read_keyval(fp_movieActors, key, val);
    while(key_i == 2){
        if(strcmp(val, actorKey) == 0){
            actorMovies[i] = malloc(sizeof(char) * strlen(key) + 1);
            strcpy(actorMovies[i], key);
            i++;
        }
        key_i = read_keyval(fp_movieActors, key, val);
    }
    int actorMovieCount = i;

    fclose(fp_movieActors);
    fp_movieActors = fopen("title.principals.kv", "rb");

    char *movie;
    i = 0;
    int foundMovie = 0;
    //GET MOVIE KEYS FROM KEVIN BACON KEY
    key_i = read_keyval(fp_movieActors, key, val);
    while(key_i == 2){
        if(foundMovie == 1){
            break;
        }
        if((strcmp(val, baconKey) == 0)){
            for(i = 0; i < actorMovieCount; i++){
                if(strcmp(actorMovies[i], key) == 0){
                    movie = malloc(sizeof(char) * strlen(actorMovies[i]) + 1);
                    strcpy(movie, actorMovies[i]);
                    foundMovie = 1;
                    break;
                }
            }
        }
        key_i = read_keyval(fp_movieActors, key, val);
    }
    
    //IF A MOVIE WAS FOUND, GET MOVIE KEY AND PRINT MOVIE TITLE
    if(foundMovie == 1){
        char *movieName;
        //GET MOVIE KEY
        key_i = read_keyval(fp_movieNames, key, val);
        while(key_i == 2){
            if(strcmp(key, movie) == 0){
                movieName = malloc(sizeof(char) * strlen(val) + 1);
                strcpy(movieName, val);
                break;
            }
            key_i = read_keyval(fp_movieNames, key, val);
        }
        printf("%s\n" , movieName);
        free(movieName);
    }
    
    //FREE EVERYTHING AND QUIT
    for(i = actorMovieCount - 1; i >= 0; i--){
        free(actorMovies[i]);
    }
    free(actorKey);
    free(actorName);
    free(movie);
    fclose(fp_movieNames);
    fclose(fp_movieActors);
    fclose(fp_actorNames);
    
    return 0;
}