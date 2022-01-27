#include "A51LIB.h"
#include "constant.h"
#include <stdio.h>
#include <stdlib.h>

int* makeCopyRegister(int* r, int len){
    int* rc = malloc(len * sizeof(int));
    for(int i=0; i<len; i++){
        rc[i] = r[i];
    }
    return rc;
}

int complementary(int x){
    // ritorna il valore complementare
    if(x == 0) return 1;
    else return 0;
}

void printRegister(int* r, int length){
    // stampa il registro
    printf("\nR");
    if(length == R1LENGTH){
        printf("1=[");
    }else if(length == R2LENGTH){
        printf("2=[");
    }else if(length == R3LENGTH){
        printf("3=[");
    }else{
        printf("=[");
    }
    for(int i=0; i<length-1; i++){
        printf("%d, ", r[i]);
    }
    printf("%d]", r[length-1]);
}

void initializeRegister (int r[], int length){
    // inizializza il registro  0
    for(int i=0; i<length; i++){
        r[i] = 0;
    }
}

int majorityBit(int r1[], int r2[], int r3[]){
    // calcolo bit di maggioranza
    if ((r1[R1MAJ] == r2[R2MAJ]) || (r1[R1MAJ] == r3[R3MAJ])){
        return r1[R1MAJ];
    } else{
        return r2[R2MAJ];
    }
}

int clockRegister(int r[], int length){
    // clock registro
    int lastBit = r[length-1];
    int firstBit;

    // calcolo bit 0
    if (length == R1LENGTH){
        firstBit = r[13] ^ r[16] ^ r[17] ^ r[18];
    }else if (length == R2LENGTH){
        firstBit = r[20] ^ r[21];
    } else {
        firstBit = r[7] ^ r[20] ^ r[21] ^ r[22];
    }

    for (int i=length-1; i>0; i--){
        r[i] = r[i-1];
    }

    r[0] = firstBit;
    return lastBit;
}

int* streamKey(int r1[], int r2[], int r3[]){
    // 228 clock con regola di maggioranza
    int o1, o2, o3;
    int* output = malloc(228 * sizeof(int));

    for(int i=0; i<228; i++){
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

        output[i] = o1 ^ o2 ^ o3;
    }
    return output;
}

void clockKey(int r1[], int r2[], int r3[], int key[]){
    // 64 clock con key NO maggioranza
    for(int i=0; i<KEYLENGTH; i++){
        r1[0] = r1[0] ^ key[i];
        r2[0] = r2[0] ^ key[i];
        r3[0] = r3[0] ^ key[i];

        clockRegister(r1, R1LENGTH);
        clockRegister(r2, R2LENGTH);
        clockRegister(r3, R3LENGTH);
    }
}

void clockFrame(int r1[], int r2[], int r3[], int frame[]){
    // 22 clock con frame NO maggioranza
    for(int i=0; i<FRAMELENGTH; i++){
        r1[0] = r1[0] ^ frame[i];
        r2[0] = r2[0] ^ frame[i];
        r3[0] = r3[0] ^ frame[i];

        clockRegister(r1, R1LENGTH);
        clockRegister(r2, R2LENGTH);
        clockRegister(r3, R3LENGTH);
    }
}

void clock100(int r1[], int r2[], int r3[]){
    // 100 clock con regola di maggioranza
    for(int i=0; i<100; i++){
        int majBit = majorityBit(r1, r2, r3);

        if(majBit == r1[R1MAJ]){
            clockRegister(r1, R1LENGTH);
        }

        if(majBit == r2[R2MAJ]){
            clockRegister(r2, R2LENGTH);
        }

        if(majBit == r3[R3MAJ]){
            clockRegister(r3, R3LENGTH);
        }
        // printf("%d",i);
        // printRegister(r1, R1LENGTH);
        // printRegister(r2, R2LENGTH);
        // printRegister(r3, R3LENGTH);
        // printf("\n---");
    
    }
}

int* cipherText(int plaintext[], int ptLength, int streamkey[]){
    // plaintext XOR streamKey
    int *ciphertext = malloc(114 * sizeof(int));
    //int pt[114];

    int len = 114;
    if(ptLength < 114){
        len = ptLength;
    }

    for(int i=0; i<len; i++){
        ciphertext[i] = plaintext[i] ^ streamkey[i];
    }

    if (len<114){
        for(int i=len; i<114; i++){
            ciphertext[i] = 0;
        }
    }

    return ciphertext;
}