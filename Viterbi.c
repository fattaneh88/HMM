#include "FLOps.h"
#include "Data.h"
#include <time.h>

csprng rng;
struct hostent *server;

static floatingPoint p, delta[T][N];
static big khi[T][N], q[T], flag;
 
struct floatingPoint Max(int, int, int);

void write_file();

// main
int main(int argc, char *argv[])
{
	initializer();

   	idserver = atoi(argv[1]);

	if (idserver == 1 && argc < 3)
	{
		printf("Enter hostname and port number\n");
		exit(0);
	}
	
	if (idserver == 2 && argc < 2)
	{
		printf("Enter port number\n");
		exit(0);
	}

	portno = atoi(argv[2]);
	
	if (idserver == 1)
		server = gethostbyname(argv[3]);
	
	

	initialize();

	//KeyGenerator();
     	//store_key(); 
	
	initializekey(idserver);

	gettimeofday(&t2, 0);
	if (idserver == 1)
		OfflineMul();
	OfflineTrunc(idserver);
	OfflineLT(idserver);
	gettimeofday(&t3, 0);

     	int i, j;
     	for(i = 0; i < T; i++){
		for(j = 0; j < N; j++){
			delta[i][j].v = mirvar(0);
			delta[i][j].p = mirvar(0);
			delta[i][j].z = mirvar(0);
			delta[i][j].s = mirvar(0);
		}
     	}

     	for(i = 0; i < T; i++)
		for(j = 0; j < N; j++)
			khi[i][j] = mirvar(0);

     	// read inputs of Viterbi algorithm (they are encryped data)
	read_data_party(idserver);

	connection(idserver);

	BCalculation(idserver);

     	// ******Viterbi algorithm******
     	// intialization step

	struct floatingPoint *a = malloc(((K/4)+1)*N*4);
	struct floatingPoint *b = malloc(((K/4)+1)*N*4);
	struct floatingPoint *c = malloc(((K/4)+1)*N*4);

	for(i = 0; i < N; i++)
	{
		a[i].v = mirvar(0);
		a[i].v = phi1[i].v;
		b[i].v = mirvar(0);
		b[i].v = B[i][0].v;
		c[i].v = mirvar(0);

		a[i].p = mirvar(0);
		a[i].p = phi1[i].p;
		b[i].p = mirvar(0);
		b[i].p = B[i][0].p;
		c[i].p = mirvar(0);

		a[i].z = mirvar(0);
		a[i].z = phi1[i].z;
		b[i].z = mirvar(0);
		b[i].z = B[i][0].z;
		c[i].z = mirvar(0);

		a[i].s = mirvar(0);
		a[i].s = phi1[i].s;
		b[i].s = mirvar(0);
		b[i].s = B[i][0].s;
		c[i].s = mirvar(0);
	}

	c = FLMulNew(a, b, N);

	for (i = 0; i < N; i++)
	{
		delta[0][i].v = c[i].v;
		delta[0][i].p = c[i].p;
		delta[0][i].z = c[i].z;
		delta[0][i].s = c[i].s; 
	}

     	big f;
     	f = mirvar(0);
	f = enc(f);
     	for(i = 0; i < N; i++)
		copy(f, khi[0][i]);

    	struct floatingPoint maximum;
     	maximum.v = mirvar(0);
     	maximum.p = mirvar(0);
     	maximum.z = mirvar(0);
     	maximum.s = mirvar(0);

	struct floatingPoint *a1 = malloc(((K/4)+1)*4);
	struct floatingPoint *b1 = malloc(((K/4)+1)*4);
	struct floatingPoint *c1 = malloc(((K/4)+1)*4);
     	a1[0].v = mirvar(0);
     	a1[0].p = mirvar(0);
     	a1[0].z = mirvar(0);
     	a1[0].s = mirvar(0);	

     	b1[0].v = mirvar(0);
     	b1[0].p = mirvar(0);
     	b1[0].z = mirvar(0);
     	b1[0].s = mirvar(0);

     	c1[0].v = mirvar(0);
     	c1[0].p = mirvar(0);
     	c1[0].z = mirvar(0);
     	c1[0].s = mirvar(0);

     	// recursion step
    	int k;
     	flag = mirvar(0);
     	for(k = 1; k < T; k++){
		for(j = 0; j < N; j++){
			maximum = Max(k,j, 1);

			copy (maximum.v, a1[0].v);
			copy (maximum.p, a1[0].p);
			copy (maximum.z, a1[0].z);
			copy (maximum.s, a1[0].s);

			copy (B[j][k].v, b1[0].v);
			copy (B[j][k].p, b1[0].p);
			copy (B[j][k].z, b1[0].z);
			copy (B[j][k].s, b1[0].s);

			c1 = FLMulNew(a1, b1, 1);

			copy (c1[0].v, delta[k][j].v);
			copy (c1[0].p, delta[k][j].p);
			copy (c1[0].z, delta[k][j].z);
			copy (c1[0].s, delta[k][j].s);

			copy(flag, khi[k][j]);
		}
     	}

     	p.v = mirvar(0);
     	p.p = mirvar(0);
     	p.z = mirvar(0);
     	p.s = mirvar(0);
	
     	// termination step
	for (k = 0; k < T; k++)
		q[k] = mirvar(0);
     	p = Max(k, j, 2);
     	copy(flag, q[T-1]);

	big *decpart = malloc(((K/4)+1)*1);
	*decpart = mirvar(0);

	big *c2 = malloc(((K/4)+1)*1);
	*c2 = mirvar(0);

	big result;
	result = mirvar(0);

     	for(i = T-2; i > -1; i--)
	{

		*decpart = decparty(q[i+1]);
		int output = sending(decpart, 1);
     		if (output < 0)
     		{
			perror("ERROR writing to socket");
     		}


     		*c2 = receive(1)[0];


		if (idserver == 1)
			result = dec(*decpart, *c2);
		else	
			result = dec(*c2, *decpart);

        	copy(khi[i+1][size(result)], q[i]);
	}

    	gettimeofday(&t1, 0);
    	long long elapsed = (t1.tv_sec-t0.tv_sec)*1000000LL + t1.tv_usec-t0.tv_usec;
    	printf("Time:%lld\n", elapsed);

	write_file();

	printf("Counter of Mul:   %d\n", CounterMul);
	printf("Counter of LT:   %d\n", CounterLT);
	printf("Counter of CounterTrunc:   %d\n", CounterTrunc);
	printf("Counter of CounterTrunc11:   %d\n", CounterTrunc11);
	printf("Counter of CounterTrunc12:   %d\n", CounterTrunc12);

     	return 0;
}

// finding maximum in recursion step
struct floatingPoint Max(int k, int j, int s){

    	struct floatingPoint result;
    	result.v = mirvar(0);
    	result.p = mirvar(0);
    	result.z = mirvar(0);
    	result.s = mirvar(0);
	
    	big point[N];
	
    	int i;
	struct floatingPoint *a = malloc(((K/4)+1)*N*4);
	struct floatingPoint *bp1 = malloc(((K/4)+1)*N*4);
	struct floatingPoint *mul1 = malloc(((K/4)+1)*N*4);

	for(i = 0; i < N; i++)
	{
		a[i].v = mirvar(0);
		a[i].v = delta[k-1][i].v;
		bp1[i].v = mirvar(0);
		bp1[i].v = A[i][j].v;
		mul1[i].v = mirvar(0);

		a[i].p = mirvar(0);
		a[i].p = delta[k-1][i].p;
		bp1[i].p = mirvar(0);
		bp1[i].p = A[i][j].p;
		mul1[i].p = mirvar(0);

		a[i].z = mirvar(0);
		a[i].z = delta[k-1][i].z;
		bp1[i].z = mirvar(0);
		bp1[i].z = A[i][j].z;
		mul1[i].z = mirvar(0);

		a[i].s = mirvar(0);
		a[i].s = delta[k-1][i].s;
		bp1[i].s = mirvar(0);
		bp1[i].s = A[i][j].s;
		mul1[i].s = mirvar(0);

		point[i] = mirvar(i);
		point[i] = enc(point[i]);
	}

	if (s == 2)
		for (i = 0; i < N; i++)
			mul1[i] = delta[T-1][i];

	if (s == 1)
		mul1 = FLMulNew(a, bp1, N);

    	int f = N;
    	int len;
    	big one;
    	one = mirvar(1);
    	copy(g, one);

    	while (f > 1)
    	{
		if (f % 2 == 1)
			len = (f-1)/2;
		else
			len = f/2;
		struct floatingPoint *b1 = malloc(((K/4)+1)*(len)*4);
		struct floatingPoint *b2 = malloc(((K/4)+1)*(len)*4);
		big *b = malloc(((K/4)+1)*(len));
			
		int j = 0;
		for ( i = 0; i < f; i++)
		{
			b1[j].v = mirvar(0);
			b1[j].p = mirvar(0);
			b1[j].z = mirvar(0);
			b1[j].s = mirvar(0);
			copy(mul1[i].v, b1[j].v);
			copy(mul1[i].p, b1[j].p);
			copy(mul1[i].z, b1[j].z);
			copy(mul1[i].s, b1[j].s);
			i++;

			b2[j].v = mirvar(0);
			b2[j].p = mirvar(0);
			b2[j].z = mirvar(0);
			b2[j].s = mirvar(0);
			copy(mul1[i].v, b2[j].v);
			copy(mul1[i].p, b2[j].p);
			copy(mul1[i].z, b2[j].z);
			copy(mul1[i].s, b2[j].s);

			b[j] = mirvar(0);
			j++;
		}

		b = FLLTNew(b1, b2, len);
		big *bp = malloc(((K/4)+1)*(len));
		for ( i = 0; i < len; i++)
		{
			bp[i] = mirvar(0);
			copy(b[i], bp[i]);
			xgcd(bp[i], n2, bp[i], bp[i], bp[i]);
			mad(bp[i], one, one, n2, n2, bp[i]);
		}

		big *m1 = malloc(((K/4)+1)*10*(len));
		big *m2 = malloc(((K/4)+1)*10*(len));
		big *m = malloc(((K/4)+1)*10*(len));
		j = 0;
		for (i = 0; i < len; i++)
		{	
			m1[j] = mirvar(0);
			copy(b[i], m1[j]);
			m2[j] = mirvar(0);
			copy(point[2*i+1], m2[j]);
			m[j] = mirvar(0);
			j++;				

			m1[j] = mirvar(0);
			copy(bp[i], m1[j]);
			m2[j] = mirvar(0);
			copy(point[2*i], m2[j]);
			m[j] = mirvar(0);
			j++;

			m1[j] = mirvar(0);
			copy(b[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i+1].v, m2[j]);
			m[j] = mirvar(0);
			j++;				

			m1[j] = mirvar(0);
			copy(bp[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i].v, m2[j]);
			m[j] = mirvar(0);
			j++;

			m1[j] = mirvar(0);
			copy(b[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i+1].p, m2[j]);
			m[j] = mirvar(0);
			j++;				

			m1[j] = mirvar(0);
			copy(bp[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i].p, m2[j]);
			m[j] = mirvar(0);
			j++;

			m1[j] = mirvar(0);
			copy(b[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i+1].z, m2[j]);
			m[j] = mirvar(0);
			j++;				

			m1[j] = mirvar(0);
			copy(bp[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i].z, m2[j]);
			m[j] = mirvar(0);
			j++;

			m1[j] = mirvar(0);
			copy(b[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i+1].s, m2[j]);
			m[j] = mirvar(0);
			j++;				

			m1[j] = mirvar(0);
			copy(bp[i], m1[j]);
			m2[j] = mirvar(0);
			copy(mul1[2*i].s, m2[j]);
			m[j] = mirvar(0);
			j++;
		}

		m = mul(m1, m2, 10*(len), idserver);
		j = 0;
		for ( i = 0; i < len; i++)
		{
			mad(m[j], m[j+1], m[j+1], n2, n2, flag);
			j += 2;

			mad(m[j], m[j+1], m[j+1], n2, n2, mul1[i].v);
			j += 2;

			mad(m[j], m[j+1], m[j+1], n2, n2, mul1[i].p);
			j += 2;

			mad(m[j], m[j+1], m[j+1], n2, n2, mul1[i].z);
			j += 2;

			mad(m[j], m[j+1], m[j+1], n2, n2, mul1[i].s);
			j += 2;

			copy(flag, point[i]);
		}

		if (f % 2 == 1)
		{
			mul1[i].v = mul1[f-1].v;
			mul1[i].p = mul1[f-1].p;
			mul1[i].z = mul1[f-1].z;
			mul1[i].s = mul1[f-1].s;
			point[i] = point[f-1];
			len++;
		}

          	f = len;
    	}
    
    	result = mul1[0];
    	copy(point[0], flag);
    
    	return result;
}

void write_file()
{
     	FILE *fp;
   
     	fp = fopen("Result.txt", "w");
     	mip->IOBASE = 16;

       	cotnum(p.v, fp);
   	cotnum(p.p, fp);
       	cotnum(p.z, fp);
   	cotnum(p.s, fp);

     	int i;
	for(i = 0; i < T; i++)
        	cotnum(q[i], fp);

     fclose(fp);

     return;
} 
