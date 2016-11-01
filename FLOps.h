#ifndef FL_OPS_H
#define FL_OPS_H

#include "IntOps.h"

// data type of floating point
typedef struct floatingPoint
{
        big v; 
        big p;
        big z;
        big s;
}floatingPoint;

big* FLLT(struct floatingPoint*, struct floatingPoint*, int);
big* FLLTNew(struct floatingPoint*, struct floatingPoint*, int);
struct floatingPoint* FLMul(struct floatingPoint*, struct floatingPoint*, int);
struct floatingPoint* FLMulNew(struct floatingPoint*, struct floatingPoint*, int);

#endif
