#ifndef INT_OPS_H
#define INT_OPS_H

#include "Paillier.h"

#define numberOffline   11457
#define numberOfflinemul     46599 
#define truncoff   2100

typedef struct MulOffline
{
        big a; 
        big b;
}MulOffline;

typedef struct LTOffline1
{
        big r; 
        big rp;
        int b;
        big a1;
        big a2;
        big erp;
}LTOffline1;

typedef struct LTOffline2
{
        big z1; 
        big z2;
        big r; 
        big rp;
        int b;
        big erp;
}LTOffline2;

typedef struct TruncOff
{
        big r; 
        big er;
        big rt;
        big ert; 

}TruncOff;

struct MulOffline MOf[numberOfflinemul];
struct LTOffline1 L1Of[numberOffline];
struct LTOffline2 L2Of[numberOffline];
big Trunc2[2*truncoff];
struct TruncOff Trunc11[truncoff];
struct TruncOff Trunc12[truncoff];
int CounterMul, CounterLT, CounterTrunc11, CounterTrunc12, CounterTrunc;

big* LTparty1(big*, big*, int);
big* LTparty2(big*, int);
big* LT(big*, big*, int, int);
big* OR(big*, big*, int);
big* XOR(big*, big*, int);
big* ORNew(big*, big*, big*, int);
big* XORNew(big*, big*, big*, int);
big* mul(big*, big*, int, int);
big* Trunc(big*, int, int, int);
void OfflineMul();
void OfflineLT(int);
void OfflineTrunc(int);

#endif
