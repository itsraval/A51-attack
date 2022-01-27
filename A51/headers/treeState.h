#ifndef treeState
#define treeState

typedef struct state{
    int* r1;
    int* r2;
    int* r3;
    struct state *s1;
    struct state *s2;
    struct state *s3;
    struct state *s4;
}state;   
typedef struct state *State;


State newNode(int* r1, int* r2, int* r3);

void printState(State s);

#endif