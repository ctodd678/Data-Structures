#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>


//count_nodes.c

int main(int argc, char **argv){

    //INITIALIZE BOARDS AND JOIN GRAPHS
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);

    int count;

    for(int i = 0; i < HSIZE; i++){
        if(htable[i].init == 1){
            count++;
        }
    }
    
    printf("%d\n" , count);

    return 0;
}