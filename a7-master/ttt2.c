#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>


//ttt2.c

void init_boards(){
    //SET INIT VALUES IN ALL BOARDS
    for(int i = 0; i < HSIZE; i++){
        htable[i].init = 0;
    }
}

int depth(Board board){
    int d = 0;

    //TRAVERSE STRING AND COUNT ALL Xs and Os
    for(int i = 0; i < BSIZE; i++){
        if(board[i] == 'X' || board[i] == 'O'){
            d++;
        }
    }
    return d;
}

char winner(Board board){

    int i = 0, j = 0;
    int xC = 0, oC = 0;

    //IF DEPTH LESS THAN 5 RETURN ?
    if(depth(board) < 5){
        return '?';
    }
 
    //CHECK FOR X OR O WIN
    for(i = 0; i < 8; i++){
        xC = 0;
        oC = 0;

        //ITERATES THROW EVERY POSSIBLE WIN CHECKING 3 OCURRANCES OF X OR O IN A ROW
        for(j = 0; j < 3; j++){
            if(board[pos2idx[WINS[i][j]]] == 'X'){
                xC++;
            }
            else if(board[pos2idx[WINS[i][j]]] == 'O'){
                oC++;
            }
        }
        if(xC == 3){
            return 'X';
        }
        else if (oC == 3){
            return 'O';
        }
    }

    //IF BOARD FULL RETURN -
    if(depth(board) == 9){
        return '-';
    }

    //RETURN ? IF ALL OTHER CASES ARE FALSE
    return '?';
}

char turn(Board board){
    
    if (depth(board) == 9 || winner(board) == 'X' || winner(board) == 'O'){
        return '-';
    }
    else if(depth(board) % 2 == 0){
        return 'X';
    }

    return 'O';
}

void init_board(Board board){
    int hash = board_hash(board);       //get board hash

    //INITIALIZE BOARD STRUCTURE
    htable[hash].init = 1;
    htable[hash].turn = turn(board);
    htable[hash].depth = depth(board);
    htable[hash].winner = winner(board);
    strcpy(htable[hash].board, board);
}

void join_graph(Board board){
    
    int hash = board_hash(board);   //get board hash

    for(int i = 0; i < 9; i++){
        if(board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O'){   //set all non valid moves to -1
            htable[hash].move[i] = -1;
        } 
        else{
            //COPY BOARD
            Board cpy;
            strcpy(cpy, board);
            cpy[pos2idx[i]] = turn(board);
            int hashCpy = board_hash(cpy);  //calculate hash for new board
            htable[hash].move[i] = hashCpy; //set hash

            //CREATE NEW BOARD 
            if(htable[hashCpy].init == 0){
                init_board(cpy);            //initialize board copy
                join_graph(cpy);            //recursively call join_graph
            }
        }
    }
}


//20% Functions

void compute_score(){
    
    int max = 0, min = 0;
    int i = 0, j = 0, k = 0;
    int currentScore = 0, foundN = 0;

    for(i = 9; i >= 0; i--){                                        //start at largest depth
        for(j = 0; j < HSIZE; j++){
            if((htable[j].init == 1) && (i == htable[j].depth)){    //check if i == depth and struct is initialized
                if(htable[j].winner == 'X'){                        //check if X wins in struct
                    htable[j].score = 1;
                }
                else if(htable[j].winner == 'O'){                   //check if O wins in struct
                    htable[j].score = -1;
                }
                else if(htable[j].winner == '-'){                   //check if tie in struct
                    htable[j].score = 0;
                }
                else{
                    foundN = 0;
                    for(k = 0; k < 9; k++){                                 //loop throw child nodes
                        currentScore = htable[htable[j].move[k]].score;     //set current score
                        if(htable[j].move[k] != -1){
                            if(!foundN){                                    //find the first score of a playable position
                                max = min = currentScore;                   //set inital max and min
                                foundN = 1;                                 //set found to 1
                            }
                            if(currentScore > max){                         //find actual max
                                max = currentScore;                         //set actual max
                            }
                            else if(currentScore < min){                    //find actual min 
                                min = currentScore;                         //set actual min
                            }
                        }
                    }
                    if(htable[j].turn == 'X'){                              //if X's turn set score to max
                        htable[j].score = max; 
                    }
                    else if(htable[j].turn == 'O'){                         //if O's turn set score to min
                        htable[j].score = min;
                    }
                }
            }
        }
    }
}

int best_move(int board){
    int i = 0;
    int move = -5;
    int currentMove;

    //POSSIBLE WIN MOVE
    for(i = 0; i < 9; i++){
        currentMove = htable[board].move[i];
        if(currentMove != -1){
            if(htable[currentMove].score == 1 && htable[board].turn == 'X'){        //set best move for X
                move = i;
                goto end;
            }
            else if(htable[currentMove].score == -1 && htable[board].turn == 'O'){  //set best move for O
                move = i;
                goto end;
            }
        }
    }

    //POSSSIBLE TIE MOVE
    for(i = 0; i < 9; i++){
        currentMove = htable[board].move[i];
        if(currentMove != -1){
            if(htable[currentMove].score == 0 && htable[board].turn == 'X'){        //set best move for X
                move = i;
                goto end;
            }
            else if(htable[currentMove].score == 0 && htable[board].turn == 'O'){   //set best move for O
                move = i;
                goto end;
            }
        }
    }

    //FIRST AVAILABLE MOVE
    for(i = 0; i < 9; i++){
        currentMove = htable[board].move[i];
        if(currentMove != -1){                  //set the first possible valid move
           move = i;
           goto end;
        }
    }

    //USE OF LABELS FOR EASIER ERROR TESTING
    end:
    //printf("\nRETURNING: %d\n\n" , move);
    return move;
}

