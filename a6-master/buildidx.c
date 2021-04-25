#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

//buildidx.c

void changeExt(char*, char*, char*);

int main(int argc, char *argv[]){

    FILE    *fp_i;
    FILE    *fp_o1;
    FILE    *fp_o2;
    long    capacity;
    int     hash_key = 0, hash_val = 0, key_i = 0, i = 0, readIndex;
    char    key[STRLEN];
    char    val[STRLEN];
    char    *inputFile, *file1, *file2;

    //CHECK CMD LINE ARGS
    if (argc == 3){
        fp_i = fopen(argv[1], "rb");
        capacity = strtol(argv[2], NULL, 10);
        inputFile = malloc(sizeof(char) * strlen(argv[1]) + 1);
        strcpy(inputFile, argv[1]);
    }
    else{
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]);  //error message for more than 2 args
        exit(0);
    }
    file1 = malloc(sizeof(char) * (strlen(inputFile) + 3));
    file2 = malloc(sizeof(char) * (strlen(inputFile) + 3));

    
    //GET EXTENSIONS FOR OUTPUT FILES
    changeExt(inputFile, file1, file2);
    fp_o1 = fopen(file1, "w+b");
    fp_o2 = fopen(file2, "w+b");
    write_empty(fp_o1, capacity);
    write_empty(fp_o2, capacity);

    //ITERATE THROUGH FIRST FILE AND WRITE TO OTHER FILES
    key_i = read_keyval(fp_i, key, val);
    while(key_i == 2){
        hash_key = hashfn(key, capacity);

        readIndex = 0;
        read_index(fp_o1, hash_key, &readIndex);
        while(readIndex != -1){
            if(hash_key == capacity - 1){
                hash_key = 0;
            }
            hash_key++;
            read_index(fp_o1, hash_key, &readIndex);
        }
        write_index(fp_o1, i, hash_key);
    
        hash_val = hashfn(val, capacity);
        readIndex = 0;
        read_index(fp_o2, hash_val, &readIndex);
        while(readIndex != -1){
            if(hash_val == capacity - 1){
                hash_val = 0;
            }
            hash_val++;
            read_index(fp_o2, hash_val, &readIndex);
        }
        write_index(fp_o2, i, hash_val);
        
        key_i = read_keyval(fp_i, key, val);
        i++;
    }

    //FREE EVERYTHING AND QUIT
    free(file1);
    free(file2);
    free(inputFile);
    fclose(fp_i);
    fclose(fp_o1);
    fclose(fp_o2);

    return 0;
}

void changeExt(char *in, char *f1, char *f2) {
    in[strlen(in) - 2] = '\0';
    strcpy(f1, in);
    strcpy(f2, in);
    strcat(f1, "khs");
    strcat(f2, "vhs");
}