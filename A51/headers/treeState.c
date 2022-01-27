#include <stdio.h>
#include <stdlib.h>
#include "constant.h"
#include "A51LIB.h"
#include "treeState.h"

// typedef struct state{
//     int* r1;
//     int* r2;
//     int* r3;
//     struct state *s1;
//     struct state *s2;
//     struct state *s3;
//     struct state *s4;
// }state;   
// typedef struct state *State;

State newNode(int* r1, int* r2, int* r3){
    State node = malloc(sizeof(state));
    node->r1 = makeCopyRegister(r1, R1LENGTH);
    node->r2 = makeCopyRegister(r2, R2LENGTH);
    node->r3 = makeCopyRegister(r3, R3LENGTH);

    node->s1 = NULL;
    node->s2 = NULL;
    node->s3 = NULL;
    node->s4 = NULL;
    return node;
}

void printState(State s){
    printRegister(s->r1, R1LENGTH);
    printRegister(s->r2, R2LENGTH);
    printRegister(s->r3, R3LENGTH);
    printf("\n%p - %p - %p - %p", s->s1, s->s2, s->s3, s->s4);
    printf("\n\n");
}