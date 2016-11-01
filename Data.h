#ifndef DATA_H
#define DATA_H

#include "Paillier.h"
#include "Comm.h"
#include "FLOps.h"

int X[T];
struct floatingPoint phi1[N], B[N][T], A[N][N], Bp[N][M];

void read_data_party(int);
void BCalculation(int);

#endif
