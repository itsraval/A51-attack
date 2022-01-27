#include <stdio.h>
#include <stdlib.h>
#include "headers/constant.h"
#include "headers/A51LIB.h"
#include "headers/treeState.h"

void reverseClockRegister(int* r, int len){
    int lastBit;

    if(len == R1LENGTH){
        lastBit = r[0] ^ r[14] ^ r[17] ^ r[18];
    }else if(len == R2LENGTH){
        lastBit = r[0] ^ r[21];
    }else{
        lastBit = r[0] ^ r[8] ^ r[21] ^ r[22];
    }

    for(int i=0; i<len-1;i++){
        r[i] = r[i+1];
    }
    r[len-1] = lastBit;
}

void reverseXorFrame(State s, int* frame){
    for(int i=21; i>=0; i--){
        reverseClockRegister(s->r1, R1LENGTH);
        reverseClockRegister(s->r2, R2LENGTH);
        reverseClockRegister(s->r3, R3LENGTH);
        s->r1[0] = s->r1[0] ^ frame[i];
        s->r2[0] = s->r2[0] ^ frame[i];
        s->r3[0] = s->r3[0] ^ frame[i];
    }
}

int reverseMajBit(int r1[], int r2[], int r3[]){
    // calcolo bit di maggioranza
    if ((r1[R1MAJ+1] == r2[R2MAJ+1]) || (r1[R1MAJ+1] == r3[R3MAJ+1])){
        return r1[R1MAJ+1];
    } else{
        return r2[R2MAJ+1];
    }
}


void clock2(int r1[], int r2[], int r3[]){
    if(r1[R1MAJ]==r2[R2MAJ]){
        reverseClockRegister(r1, R1LENGTH);
        reverseClockRegister(r2, R2LENGTH);
    }else if(r1[R1MAJ]==r3[R3MAJ]){
        reverseClockRegister(r1, R1LENGTH);
        reverseClockRegister(r3, R3LENGTH);
    }else{
        reverseClockRegister(r2, R2LENGTH);
        reverseClockRegister(r3, R3LENGTH);
    }
}

int clock3(int r1[], int r2[], int r3[]){
    if(r1[R1MAJ]==r2[R2MAJ]){
        return 3;
    }else if(r1[R1MAJ]==r3[R3MAJ]){
        return 2;
    }else{
        return 1;
    }
}


int reverseClockMajBit(State s, int round, int* frame){
    // calcolo bit di maggioranza
    if(round == 0){
        reverseXorFrame(s, frame);
        printState(s);
        return 1;
    }

    int maj = reverseMajBit(s->r1, s->r2, s->r3);
    State node = newNode(s->r1, s->r2, s->r3);
    if((s->r1[R1MAJ+1] == maj) && (s->r2[R2MAJ+1] == maj) && (s->r3[R3MAJ+1] != maj) && (s->r3[R3MAJ+1] == s->r3[R3MAJ])){
        // si' = sj' != sk' = sk
        reverseClockRegister(node->r1, R1LENGTH);
        reverseClockRegister(node->r2, R2LENGTH);
        s->s1 = node;
        reverseClockMajBit(node, round-1, frame);
    }else if((s->r1[R1MAJ+1] == maj) && (s->r3[R3MAJ+1] == maj) && (s->r2[R2MAJ+1] != maj) && (s->r2[R2MAJ+1] == s->r2[R2MAJ])){
        // si' = sj' != sk' = sk
        reverseClockRegister(node->r1, R1LENGTH);
        reverseClockRegister(node->r3, R3LENGTH);
        s->s1 = node;
        reverseClockMajBit(node, round-1, frame);
    }else if((s->r2[R2MAJ+1] == maj) && (s->r3[R3MAJ+1] == maj) && (s->r1[R1MAJ+1] != maj) && (s->r1[R1MAJ+1] == s->r1[R1MAJ])){
        // si' = sj' != sk' = sk
        reverseClockRegister(node->r2, R2LENGTH);
        reverseClockRegister(node->r3, R3LENGTH);
        s->s1 = node;
        reverseClockMajBit(node, round-1, frame);        
    }else if((s->r1[R1MAJ+1] == maj) && (s->r2[R2MAJ+1] == maj) && (s->r3[R3MAJ+1] != maj) && (s->r3[R3MAJ+1] != s->r3[R3MAJ])){
        // si' = sj' != sk' != sk
        // Caso non possibile
        return 0;
    }else if((s->r1[R1MAJ+1] == maj) && (s->r3[R3MAJ+1] == maj) && (s->r2[R2MAJ+1] != maj) && (s->r2[R2MAJ+1] != s->r2[R2MAJ])){
        // si' = sj' != sk' != sk
        // Caso non possibile
        return 0;
    }else if((s->r2[R2MAJ+1] == maj) && (s->r3[R3MAJ+1] == maj) && (s->r1[R1MAJ+1] != maj) && (s->r1[R1MAJ+1] != s->r1[R1MAJ])){
        // si' = sj' != sk' != sk
        // Caso non possibile
        return 0;      
    }else{
        // caso con s1' = s2' = s3'
        int r1m = s->r1[R1MAJ];
        int r2m = s->r2[R2MAJ];
        int r3m = s->r3[R3MAJ];

        if((r1m == maj) && (r2m == maj) && (r3m == maj)){
            // s1' = s2' = s3' = s1 = s2 = s3
            reverseClockRegister(node->r1, R1LENGTH);
            reverseClockRegister(node->r2, R2LENGTH);
            reverseClockRegister(node->r3, R3LENGTH);
            s->s1 = node;
            reverseClockMajBit(node, round-1, frame);  
        }else if(((r1m == r2m) && (r1m == maj) && (r1m != r3m)) || ((r1m == r3m) && (r1m == maj) && (r1m != r2m)) || ((r2m == r3m) && (r2m == maj) && (r2m != r1m))){
            // s1' = s2' = s3' = si = sj != sk
            State node1 = newNode(s->r1, s->r2, s->r3);
            clock2(node1->r1, node1->r2, node1->r3);
            s->s1 = node1;
            reverseClockMajBit(node1, round-1, frame);  

            State node2 = newNode(s->r1, s->r2, s->r3);
            reverseClockRegister(node2->r1, R1LENGTH);
            reverseClockRegister(node2->r2, R2LENGTH);
            reverseClockRegister(node2->r3, R3LENGTH);
            s->s2 = node2;
            reverseClockMajBit(node2, round-1, frame);  
        }else if(((r1m == r2m) && (r1m != maj) && (r3m == maj)) || ((r1m == r3m) && (r1m != maj) && (r2m == maj)) || ((r2m == r3m) && (r2m != maj) && (r1m == maj))){
            // s1' = s2' = s3' = si != sj = sk
            int diff = clock3(s->r1, s->r2, s->r3);
            State node1 = newNode(s->r1, s->r2, s->r3);
            State node2 = newNode(s->r1, s->r2, s->r3);
            if(diff==1){
                reverseClockRegister(node1->r1, R1LENGTH);
                reverseClockRegister(node1->r2, R2LENGTH);

                reverseClockRegister(node2->r1, R1LENGTH);
                reverseClockRegister(node2->r3, R3LENGTH);
            }else if(diff==2){
                reverseClockRegister(node1->r1, R1LENGTH);
                reverseClockRegister(node1->r2, R2LENGTH);

                reverseClockRegister(node2->r2, R2LENGTH);
                reverseClockRegister(node2->r3, R3LENGTH);
            }else{
                reverseClockRegister(node1->r1, R1LENGTH);
                reverseClockRegister(node1->r3, R3LENGTH);

                reverseClockRegister(node2->r2, R2LENGTH);
                reverseClockRegister(node2->r3, R3LENGTH);
            }
            s->s1 = node1;
            reverseClockMajBit(node1, round-1, frame); 
            s->s2 = node2;
            reverseClockMajBit(node2, round-1, frame); 

            State node3 = newNode(s->r1, s->r2, s->r3);
            reverseClockRegister(node3->r1, R1LENGTH);
            reverseClockRegister(node3->r2, R2LENGTH);
            reverseClockRegister(node3->r3, R3LENGTH);
            s->s3 = node3;
            reverseClockMajBit(node3, round-1, frame); 
        }else if((r1m != maj) && (r2m != maj) && (r3m != maj)){
            // s1' = s2' = s3' != s1 = s2 = s3
            State node1 = newNode(s->r1, s->r2, s->r3);
            reverseClockRegister(node1->r1, R1LENGTH);
            reverseClockRegister(node1->r2, R2LENGTH);
            s->s1 = node1;
            reverseClockMajBit(node1, round-1, frame); 

            State node2 = newNode(s->r1, s->r2, s->r3);
            reverseClockRegister(node2->r1, R1LENGTH);
            reverseClockRegister(node2->r3, R3LENGTH);
            s->s2 = node2;
            reverseClockMajBit(node2, round-1, frame); 

            State node3 = newNode(s->r1, s->r2, s->r3);
            reverseClockRegister(node3->r2, R2LENGTH);
            reverseClockRegister(node3->r3, R3LENGTH);
            s->s3 = node3;
            reverseClockMajBit(node3, round-1, frame); 

            State node4 = newNode(s->r1, s->r2, s->r3);
            reverseClockRegister(node4->r1, R1LENGTH);
            reverseClockRegister(node4->r2, R2LENGTH);
            reverseClockRegister(node4->r3, R3LENGTH);
            s->s4 = node4;
            reverseClockMajBit(node4, round-1, frame); 
        }else{
            printf("\nERRORE COME CI SIAMO CAPITATI QUI??\n%d-%d-%d-%d\n", r1m, r2m, r3m, maj);
            return 0;
        }
    }
}

void reverse100Clock(State s, int* frame){
    reverseClockMajBit(s, 100, frame);
}

// int main(){
//     int r1[R1LENGTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0};
//     int r2[R2LENGTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0};
//     int r3[R3LENGTH] = {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};
//     int frameState[FRAMELENGTH] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0};
//     int* frame = makeCopyRegister(frameState, FRAMELENGTH);

//     State root = newNode(r1, r2, r3);
//     reverse100Clock(root, frame); 
// }