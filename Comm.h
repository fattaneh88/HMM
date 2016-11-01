#ifndef COMM_H
#define COMM_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include "miracl.h"

#define K    1024
#define N    100
#define M    4
#define T    4
#define l    32
#define kapa 48

miracl *mip;
int portno, idserver;
struct hostent *server;
int length;
struct timeval t0, t1, t2, t3, t4, t5;

void connection(int);
int sending(big*, int);
big* receive(int);
void printnum(big n);
void initializer(void);

#endif

