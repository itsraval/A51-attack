#include <stdio.h>
#include <stdlib.h>
#include "headers/A51LIB.h"
#include "headers/constant.h"
#include "headers/stringBitLib.h"


int main(){
    printf("-----------------------\n");
    printf("||| A5/1 ENCRYPTION |||\n");
    printf("-----------------------\n\n");

    int *r1 = malloc(R1LENGTH * sizeof(int));
    int *r2 = malloc(R2LENGTH * sizeof(int));
    int *r3 = malloc(R3LENGTH * sizeof(int));

    int key[KEYLENGTH] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0};
    int frame[FRAMELENGTH] = {0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0};

    int ptLength = 78;
    int plaintext[78] = {1,1,0,1,0,0,0,1,1,0,0,1,0,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,0,1,1,0,0,1,0,0};

    // FASE DI INIZIALIZZAZIONE
    initializeRegister(r1, R1LENGTH);
    initializeRegister(r2, R2LENGTH);
    initializeRegister(r3, R3LENGTH);

    // 64 CLOCK
    clockKey(r1, r2, r3, key);
    
    // 22 CLOCK
    clockFrame(r1, r2, r3, frame);
    
    // 100 CLOCK
    clock100(r1, r2, r3);

    printRegister(r1, R1LENGTH);
    printRegister(r2, R2LENGTH);
    printRegister(r3, R3LENGTH);
    fflush(stdout);
    
    // GENERAZIONE 228 (114 + 114) BIT DI KEY STREAM
    int* output = streamKey(r1, r2, r3);

    printRegister(output, OUTPUTLENGTH);
    return 0;
    
    // GENERAZIONE CRITTO TESTO
    int *cText = cipherText(plaintext, ptLength, output);
    printRegister(cText, 114);
    return 0;
}