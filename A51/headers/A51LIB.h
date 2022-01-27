#ifndef A51LIB
#define A51LIB

int* makeCopyRegister(int* r, int len);

int complementary(int x);

void printRegister(int r[], int length);

void initializeRegister(int r[], int length);

int majorityBit(int r1[], int r2[], int r3[]);

int clockRegister(int r[], int length);

int* streamKey(int r1[], int r2[], int r3[]);

void clockKey(int r1[], int r2[], int r3[], int key[]);

void clockFrame(int r1[], int r2[], int r3[], int frame[]);

void clock100(int r1[], int r2[], int r3[]);

int* cipherText(int plaintext[], int ptLength, int streamkey[]);

#endif