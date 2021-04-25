#include <stdio.h>
#include "bandb.h"


//CIS 2520 ASSIGMENT 1 - Connor Todd (1039174)

//BANDB FUNCTIONS

void getbytes(unsigned char dest[] , int bytes , void *src , int reverse){
    int i;

    unsigned char *temp = (unsigned char*)src;

    //COPY MEMORY IN ORDER
    if (reverse == 0){
        memcpy(dest, temp, bytes);
    }
    //COPY MEMORY AND REVERSE STRING
    else if(reverse == 1){
        memcpy(dest, temp, bytes);
        for(i = 0; i < bytes; i++){
            dest[i] = temp[(bytes - 1) - i];
        }
    }
}

void getbits(char dest[] , int bytes , void *src , int start , int end){

    //VARIABLES
    char *binaryNumber = (char*)src;

    int i = 0, j = 0, k = start, startBitPos, endBitPos, startBytePos, endBytePos; 

    startBitPos = start % 8;                  //CALCULATE POSITION OF START BIT
    endBitPos = (end % 8) + 1;                //CALCULATE POSITION OF END BIT

    startBytePos = (bytes - (start / 8) - 1); //CALCULATE POSITION OF START BYTE
    endBytePos = (bytes - (end / 8) - 1);     //CALCULATE POSITION OF END BIT

    i = endBytePos; //SET INDEX TO VALUE OF STARTBYTE
    do{
        if(i == startBytePos){                  //CASE FOR STARTBYTE BEING THE INDEX

            for(j = startBitPos; j >= 0; j--){
                if((binaryNumber[i] >> (7 - j)) & 1){
                    dest[k] = '1';
                }
                else{
                    dest[k] = '0';
                }
                k--;
            }
        }
        else if(startBytePos == endBytePos){    //CASE FOR STARTBYTE AND ENDBYTE BEING THE SAME
  
            for(j = startBitPos; j >= endBitPos; j--){
                if((binaryNumber[i] >> (7 - j)) & 1){
                    dest[k] = '1';
                }
                else{
                    dest[k] = '0';
                }
                k--;
            }
        }
        else if(i == endBytePos){               //CASE FOR EDNBYTE BEING THE INDEX

            for(j = 7; j >= endBitPos; j--){
                if((binaryNumber[i] >> (7 - j)) & 1){
                    dest[k] = '1';
                }
                else{
                    dest[k] = '0';
                }
                k--;
            }
        }
        else{   
                                                //CASE FOR STARTBYTE AND/OR ENDBYTE NOT BEING THE SAME OR THE SAME AS INDEX
            for(j = 7; j >= 0; j--){
                if((binaryNumber[i] >> (7 - j)) & 1){
                    dest[k] = '1';
                }
                else{
                    dest[k] = '0';
                }
                k--;
            }
        }
        i--;

    }while(i >= startBytePos); //LOOP UNTIL INDEX IS EQUAL TO START BYTE
    
    dest[start - end] = '\0';
}

unsigned long long pow_unsigned(unsigned long long inputNum, unsigned long long e){
    //HELPER FUNCTION TO FIND POWER

    unsigned long long outputNum = 1;

    //FIND THE PRODUCT OF THE BASE AND EXPONENT
    for(; e > 0; e--){
        outputNum = outputNum * inputNum;
    }

    return outputNum;
}

long long pow_signed(long long inputNum, long long e){
    //HELPER FUNCTION TO FIND POWER

    long long outputNum = 1;

    //FIND THE PRODUCT OF THE BASE AND EXPONENT
    for(; e > 0; e--){
        outputNum = outputNum * inputNum;
    }

    return outputNum;
}

unsigned long long bits2ull(char *bits ){

    int i, j = strlen(bits) - 1;
    unsigned long long num = 0;

    //Iterate through the string to write binary number to unsigned long long
    for(i = 0; i < strlen(bits); i++){
        if(bits[i] == '1'){
            num = num + (pow_unsigned(2 , j)); //Calcualtes binaray value using seperate power function and adds to num
        }
        j--;
    }
    return num;
}

long long bits2ll(char *bits ){

    int i, j = strlen(bits) - 1;
    long long num = 0;

    //Iterate through the string to write binary number to long long 
    for(i = 0; i < strlen(bits); i++){
        if(i == 0){
            if(bits[i] == '1'){
                num = num - (pow_signed(2 , j)); //Subtracts to get 2's complement at index i = 0
            } 
        }
        else{
            if(bits[i] == '1'){
                num = num + (pow_signed(2 , j)); //Calcualtes binaray value using seperate power function and adds to num
            }
        }
        j--;
    }
    return num;
}

void spff( char *sign, char *exponent, char *significand, float*src ){

    getbits(sign, 4, src, 0, 1);            //GET SIGN VALUES
    getbits(exponent, 4, src, 2, 9);        //GET EXPONENT VALUES
    getbits(significand, 4, src, 10, 23);   //GET SIGNIFICAND VALUES
}

void dpff( char *sign, char *exponent, char *significand, double *src ){

    getbits(sign, 4, src, 0, 1);            //GET SIGN VALUES
    getbits(exponent, 4, src, 1, 12);       //GET EXPONENT VALUES
    getbits(significand, 4, src, 12, 64);   //GET SIGNIFICAND VALUES
}