#include "Data.h"

void read_data_party(int id)
{
     	int i, j;
     	for(i = 0; i < N; i++){
		phi1[i].v = mirvar(0);
		phi1[i].p = mirvar(0);
		phi1[i].z = mirvar(0);
		phi1[i].s = mirvar(0);
	}

     	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			A[i][j].v = mirvar(0);
			A[i][j].p = mirvar(0);	
			A[i][j].z = mirvar(0);
			A[i][j].s = mirvar(0);
		}
     	}

	FILE *fp;
	fp = fopen("data.txt", "r");
     	mip->IOBASE = 16;

	if(id == 1)
	{
		for(i = 0; i < N; i++){
			for(j = 0; j < M; j++){
				Bp[i][j].v = mirvar(0);
				Bp[i][j].p = mirvar(0);
				Bp[i][j].z = mirvar(0);
				Bp[i][j].s = mirvar(0);
			}
     		}
		for (i = 0; i < N; i++){
       			cinnum(phi1[i].v, fp);
   			cinnum(phi1[i].p, fp);
       			cinnum(phi1[i].z, fp);
   			cinnum(phi1[i].s, fp);
     		}

     		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				cinnum(A[i][j].v, fp);
   				cinnum(A[i][j].p, fp);
        			cinnum(A[i][j].z, fp);
   				cinnum(A[i][j].s, fp);	
			}
     		}

     		for(i = 0; i < N; i++){
			for(j = 0; j < M; j++){
				cinnum(Bp[i][j].v, fp);
   				cinnum(Bp[i][j].p, fp);
        			cinnum(Bp[i][j].z, fp);
   				cinnum(Bp[i][j].s, fp);
			}
     		}
		big number;
		number = mirvar(0);
		for (i = 0; i < T; i++){
		       	cinnum(number, fp);
			X[i] = size(number);
		}

	}
	else
	{
		for (i = 0; i < N; i++){
       			cinnum(phi1[i].v, fp);
   			cinnum(phi1[i].p, fp);
       			cinnum(phi1[i].z, fp);
   			cinnum(phi1[i].s, fp);
     		}

     		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				cinnum(A[i][j].v, fp);
   				cinnum(A[i][j].p, fp);
        			cinnum(A[i][j].z, fp);
   				cinnum(A[i][j].s, fp);	
			}
     		}
	}

	return;
}

void BCalculation(int id)
{
	big *b = malloc(((K/4)+1)*N*T*4);
	int i, j, k;
	for(i = 0; i < N*T*4; i++)
		b[i] = mirvar(0);

     	for(i = 0; i < N; i++){
		for(j = 0; j < T; j++){
			B[i][j].v = mirvar(0);
			B[i][j].p = mirvar(0);
			B[i][j].z = mirvar(0);
			B[i][j].s = mirvar(0);
		}
     	}

	if(id == 1)
	{
		i = 0;
		for(j = 0; j < N; j++)
			for(k = 0; k < T; k++)
			{
				b[i] = Bp[j][X[k]].v;
				i++;
				b[i] = Bp[j][X[k]].p;
				i++;
				b[i] = Bp[j][X[k]].z;
				i++;
				b[i] = Bp[j][X[k]].s;
				i++;
			}

		big zero, zero1;
		zero = mirvar(0);
		zero1 = mirvar(0);
		for(i = 0; i < N*T*4; i++)
		{
			zero = enc(zero1);
			mad(b[i], zero, zero, n2, n2, b[i]);
		}

		i = 0;
		for(j = 0; j < N; j++)
			for(k = 0; k < T; k++)
			{
				B[j][k].v = b[i];
				i++;
				B[j][k].p = b[i];
				i++;
				B[j][k].z = b[i];
				i++;
				B[j][k].s = b[i];
				i++;
			}

     		int output = sending(b, N*T*4);
     		if (output < 0)
     		{
			perror("ERROR writing to socket");
     		}
	}
	else
	{
		b = receive(N*T*4);
		i = 0;
		for(j = 0; j < N; j++)
			for(k = 0; k < T; k++)
			{
				B[j][k].v = b[i];
				i++;
				B[j][k].p = b[i];
				i++;
				B[j][k].z = b[i];
				i++;
				B[j][k].s = b[i];
				i++;
			}
	}

	return;
}
