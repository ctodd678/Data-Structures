#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

//key2val.c
void changeExt(char*, char*);

int val2key(FILE*, FILE*, char*, char*);

int main(int argc, char *argv[]){

    FILE *fp_i, *fp_i2;
    char *inputFile, *file1, *searchTerm;
    char val[STRLEN];

    //CHECK CMD LINE ARGS
    if (argc == 3){
        fp_i = fopen(argv[1], "rb");
        inputFile = malloc(sizeof(char) * strlen(argv[1]) + 1);
        searchTerm = malloc(sizeof(char) * strlen(argv[2]) + 1);
        strcpy(inputFile, argv[1]);
        strcpy(searchTerm, argv[2]);
    }
    else{
        fprintf(stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);  //error message for more than 2 args
        exit(0);
    }

    file1 = malloc(sizeof(char) * (strlen(inputFile) + 3));

    //GET EXTENSIONS FOR OTHER FILE
    changeExt(inputFile, file1);
    //OPEN KHS FILE
    fp_i2 = fopen(file1, "rb");

    //IF VAL2KEY RETURNS 1, PRINT FOUND 0, ELSE PRINT NOT FOUND
    if(val2key(fp_i, fp_i2, searchTerm, val)){
        printf("%s\n" , val);
    }
    else{
        printf("NOT FOUND\n");
    }

    //FREE AND CLOSE EVERYTHING
    free(inputFile);
    free(searchTerm);
    free(file1);
    fclose(fp_i);
    fclose(fp_i2);

    return 0;
}

//CHANGES FILE EXTENSIONS
void changeExt(char *in, char *f1) {
    in[strlen(in) - 2] = '\0';
    strcpy(f1, in);
    strcat(f1, "vhs");
}

//RETURNS 1 OR 0 IF VALUE FOUND, RETURNS FOUND VALUE THROW k POINTER
int val2key(FILE* fpI, FILE* fpI_2, char* search, char* v){
    int i, hash, initialHash;

    hash = hashfn(search, get_capacity(fpI_2));
    initialHash = hash;

    //LOOPS UNTIL VALUE IS RETURNED OR BREAKS
    while(1){
        read_index(fpI_2, hash, &i);
        read_val(fpI, i, v);
        hash++;

        if(strcmp(v, search) == 0){
            read_key(fpI, i, v);
            return 1;
        }
        if(hash == (get_capacity(fpI_2) - 1)){
            hash = 0;
        }
        if(hash == initialHash){
            break;
        }
    }
    return 0;
}