#include <stdio.h>
#include <stdlib.h>
#include "headers/constant.h"
#include "headers/A51LIB.h"


int main(){
    int r1[R1LENGTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0};
    int r2[R2LENGTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0};
    int r3[R3LENGTH] = {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};
    
    
    
    // int r1[R1LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0};
    // int r2[R2LENGTH] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1};
    // int r3[R3LENGTH] = {0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0};

    // int r1s[R1LENGTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1};
    // int r2s[R2LENGTH] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1};
    // int r3s[R3LENGTH] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1};

    int* outputStream = malloc(OUTPUTLENGTH * sizeof(int));
    int o1, o2, o3;
    int a = 0;
    int b = 0;
    int c = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    printRegister(r1, R1LENGTH);
    printRegister(r2, R2LENGTH);
    printRegister(r3, R3LENGTH);
    printf("\nR1-%d R2-%d R3-%d",a,b,c);
    printf("\n----------------------------\n");

    for(int i=0; i<OUTPUTLENGTH; i++){
        int majBit = majorityBit(r1, r2, r3);

        if(majBit == r1[R1MAJ]){
            o1 = clockRegister(r1, R1LENGTH);
            count1++;
            a=1;
        }else{
            o1 = r1[R1LENGTH-1];
        }

        if(majBit == r2[R2MAJ]){
            o2 = clockRegister(r2, R2LENGTH);
            count2++;
            b=1;
        }else{
            o2 = r2[R2LENGTH-1];
        }

        if(majBit == r3[R3MAJ]){
            o3 = clockRegister(r3, R3LENGTH);
            count3++;
            c=1;
        }else{
            o3 = r3[R3LENGTH-1];
        }

        outputStream[i] = o1 ^ o2 ^ o3;

    printf("%d",i);    
    printRegister(r1, R1LENGTH);
    printRegister(r2, R2LENGTH);
    printRegister(r3, R3LENGTH);
    printRegister(outputStream, i+1);
    printf("\nR1-%d R2-%d R3-%d   %d",a,b,c,outputStream[i]);
    printf("\nR3-round: %d",count1);
    printf("\nR3-round: %d",count2);
    printf("\nR3-round: %d",count3);
    printf("\n----------------------------\n");

        a=0;
        b=0;
        c=0;


        //if(i==55) break;
    }

    printRegister(outputStream, 56);
    printRegister(outputStream, OUTPUTLENGTH);
    
    free(outputStream);
}