#ifndef PAILLIER_H
#define PAILLIER_H

#include <stdlib.h>
#include "Comm.h"

big g, n, S1, S2, S, n2, phi, alpha;
extern csprng rng;

void initialize(void);
void initializekey(int);
void KeyGenerator(void);
void store_key(void);
big enc(big);
void read_key(char*);
big decparty(big);
big dec(big, big);

#endif
