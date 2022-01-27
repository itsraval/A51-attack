#include <stdio.h>
#include <stdlib.h>
#include "headers/constant.h"
#include "headers/A51LIB.h"
#include "headers/treeState.h"
#include "headers/retriveKey.h"
#include <time.h>

int isCorrectState(int* r1, int* r2, int* r3, int* outputStream, int pos){
    int o1, o2, o3;

    while(pos<OUTPUTLENGTH){
        int majBit = majorityBit(r1, r2, r3);

        if(majBit == r1[R1MAJ]){
            o1 = clockRegister(r1, R1LENGTH);
        }else{
            o1 = r1[R1LENGTH-1];
        }

        if(majBit == r2[R2MAJ]){
            o2 = clockRegister(r2, R2LENGTH);
        }else{
            o2 = r2[R2LENGTH-1];
        }

        if(majBit == r3[R3MAJ]){
            o3 = clockRegister(r3, R3LENGTH);
        }else{
            o3 = r3[R3LENGTH-1];
        }

        if(outputStream[pos] != o1 ^ o2 ^ o3){
            return 0;
        }
        pos++;
    }
    return 1;
}

int findR3_clock(int* r1, int* r2, int* r3, int* outputStream){
    int* r1c = makeCopyRegister(r1, R1LENGTH);
    int* r2c = makeCopyRegister(r2, R2LENGTH);
    int* r3c = makeCopyRegister(r3, R3LENGTH);

    int pos = 0;
    int posR3 = 21;
    while(1){
        int majBit = majorityBit(r1c, r2c, r3c);
        pos++;

        if(majBit == r1c[R1MAJ]){
            clockRegister(r1c, R1LENGTH);
        }

        if(majBit == r2c[R2MAJ]){
            clockRegister(r2c, R2LENGTH);
        }

        if(majBit == r3c[R3MAJ]){
            r3c[21] = outputStream[pos]^ r1c[18] ^ r2c[21];
            clockRegister(r3c, R3LENGTH);
            r3[posR3] = outputStream[pos]^ r1c[18] ^ r2c[21];
            posR3--;
            if(posR3==10){
                break;
            }
        }

    }

    int correctState = isCorrectState(r1c, r2c, r3c, outputStream, pos);
    free(r1c);
    free(r2c);
    free(r3c);
    return correctState;
} 

void fase3Recursive(int* r1, int* r2, int* r3, int* outputStream, int pos, int value, int* frame){
    r3[pos] = value;
    if(pos==0){
        int correctState = findR3_clock(r1, r2, r3, outputStream);

        if(correctState){
            State root = newNode(r1, r2, r3);
            reverse100Clock(root, frame); 
        }     
    }else{
        fase3Recursive(r1, r2, r3, outputStream, pos-1, 0, frame);
        fase3Recursive(r1, r2, r3, outputStream, pos-1, 1, frame);
    }
}


void fase3(int* r1, int* r2, int* r3, int* outputStream, int* frame){
    fase3Recursive(r1, r2, r3, outputStream, 9, 0, frame);
    fase3Recursive(r1, r2, r3, outputStream, 9, 1, frame);
}

int findR3_21(int* r1, int* r2, int* r3, int* outputStream){
    int* r1c = makeCopyRegister(r1, R1LENGTH);
    int* r2c = makeCopyRegister(r2, R2LENGTH);
    int* r3c = makeCopyRegister(r3, R3LENGTH);

    int pos = 0;
    while(1){
        int majBit = majorityBit(r1c, r2c, r3c);
        pos++;

        if(majBit == r1c[R1MAJ]){
            clockRegister(r1c, R1LENGTH);
        }

        if(majBit == r2c[R2MAJ]){
            clockRegister(r2c, R2LENGTH);
        }

        if(majBit == r3c[R3MAJ]){
            break;
        }
    }
    int value = outputStream[pos]^ r1c[18] ^ r2c[21];
    free(r1c);
    free(r2c);
    free(r3c);
    return value;
}

void fase2Recursive(int* r1, int* r2, int* r3, int* r1XORr2, int* outputStream, int pos, int value, int* frame){
    if(pos==13) pos--;
    r1[pos] = value;
    r2[pos+3] = r1[pos] ^ r1XORr2[18-pos];
    if(pos==9){
        for(int r200=0; r200<2; r200++){
            r2[0] = r200; 
            r3[21] = findR3_21(r1, r2, r3, outputStream);
            fase3(r1, r2, r3, outputStream, frame);                            
        }
    }else{
        if(pos==16){
            r1[13] = r1[0] ^ r1[18] ^ r1[17] ^ r1[16];
            r2[13+3] = r1[13] ^ r1XORr2[18-13];
        }
        fase2Recursive(r1, r2, r3, r1XORr2, outputStream, pos-1, 0, frame);
        fase2Recursive(r1, r2, r3, r1XORr2, outputStream, pos-1, 1, frame);
    }
}

void fase2(int* r1, int* r2, int* r3, int* r1XORr2, int* outputStream, int* frame){
    r2[11] = r1[8] ^ r1XORr2[10];
    fase2Recursive(r1, r2, r3, r1XORr2, outputStream, 18, 0, frame);
    fase2Recursive(r1, r2, r3, r1XORr2, outputStream, 18, 1, frame);
    return;
}

int* fase1(int* r1, int* r2, int* r3, int* outputStream, int r3Control, int r3Output){
    r3[10] = r3Control;
    r3[22] = r3Output;
    int compR3 = complementary(r3Control);
    for(int i=0; i<9; i++){
        r1[i] = compR3;
        r2[i+1] = compR3;
    }
    r2[10] = compR3;
    int* r1XORr2 = malloc(R1XORR2LENGTH * sizeof(int));
    initializeRegister(r1XORr2, R1XORR2LENGTH);
    for (int i=0; i<R1XORR2LENGTH; i++){
        r1XORr2[i] = r3[22] ^ outputStream[i];
    }
    return r1XORr2;
}

void attack(int* r1, int* r2, int* r3, int* outputStream, int* frame){
    for(int r3Control=0; r3Control<2; r3Control++){
        for(int r3Output=0; r3Output<2; r3Output++){
            int* r1XORr2 = fase1(r1, r2, r3, outputStream, r3Control, r3Output);
            fase2(r1, r2, r3, r1XORr2, outputStream, frame);
        }
    }
}

int main(){
    time_t rawtime;
  struct tm * timeinfo;

time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "Current local time and date: %s\n", asctime (timeinfo) );


    int* r1 = malloc(R1LENGTH * sizeof(int));
    int* r2 = malloc(R2LENGTH * sizeof(int));
    int* r3 = malloc(R3LENGTH * sizeof(int));
    int outputStream[OUTPUTLENGTH] = {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    // int outputStream[OUTPUTLENGTH] = {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0};
    int frame[FRAMELENGTH] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0};

    initializeRegister(r1, R1LENGTH);
    initializeRegister(r2, R2LENGTH);
    initializeRegister(r3, R3LENGTH);

    attack(r1, r2, r3, outputStream, frame);


    time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "Current local time and date: %s\n", asctime (timeinfo) );
}