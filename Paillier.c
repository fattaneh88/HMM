#include "Paillier.h"

// key generation
void KeyGenerator()
{
     	big p, q, m, pp, qq, B, a, b, SK, temp1, a1, res1, res2; 
     
     	BOOL found = FALSE;
     	BOOL found1 = FALSE;
     	long int count =0;

     	//generating p' and q', p and q
     	big number1, number2;
     	number1 = mirvar(1);
     	number2 = mirvar(2);
     	pp = mirvar(0);
     	p = mirvar(0);
     	while (!found1){
        	found = FALSE;
     		while (!found){
		   	strong_bigdig(&rng, K/2, 2, pp);
        	   	found = isprime(pp);
        	   	count++;
        	}
        	multiply(pp, number2, p);
        	incr(p, 1, p);
		found1 = isprime(p);
     	}
     	printf("number of trials for p': %ld\n", count);
     
    	found = FALSE;
     	found1 = FALSE;
     	qq = mirvar(0);
     	q = mirvar(0);
     	count = 0;
     	while (!found1){
        	found = FALSE;
     		while (!found){
           		strong_bigdig(&rng, K/2, 2, qq);
           		found = isprime(qq);
           		count++;
     		}
        	multiply(qq, number2, q);
        	incr(q, 1, q);
		found1 = isprime(q);
     	}
     	printf("number of trials for q': %ld\n", count);
     
     	//computing m
     	m = mirvar(0);
     	multiply(pp, qq, m);


     	//computing n
     	n = mirvar(0);
     	multiply(p, q, n);

     	//computing B, a, b as random numbers
     	B = mirvar(0);
     	strong_bigrand(&rng, n, B);
     	a = mirvar(0);
     	strong_bigrand(&rng, n, a);
     	b = mirvar(0);
     	strong_bigrand(&rng, n, b);

     	//computing SK, S1, S2
     	SK = mirvar(0);
     	multiply(B, m, SK);
     	big temp2;
     	temp2 = mirvar(0);
     	multiply(n, m, temp2);
     	a1 = mirvar(0);
     	strong_bigrand(&rng, temp2, a1);
     	S1 = mirvar(0);
     	add(SK, a1, S1);
     	if (mr_compare(S1, temp2) >= 0)
       		subtract(S1, temp2, S1);
     	S2 = mirvar(0);
     	add(S1, a1, S2);
     	if (mr_compare(S2, temp2) >= 0)
       		subtract(S1, temp2, S2);

     	//computing g
     	big number3;
     	number3 = mirvar(0);
     	n2 = mirvar(0);
     	g = mirvar(0);
     	res1 = mirvar(0);
     	res2 = mirvar(0);
     	multiply(n, n, n2);
     	incr(n, 1, number3);
     	powmod(number3, a, n2, res1);
     	powmod(b, n, n2, res2);
     	mad(res1, res2, res2, n2, n2, g);

     	//computing phi
     	phi = mirvar(0);
     	mad(a, SK, SK, n, n, phi);
     
     	return;
}

// store key on the file
void store_key()
{
   	/* the elements of the key are stored in three file one value per line*/
   	FILE *fp;
   
   	fp = fopen("Public.txt", "w");
   	mip->IOBASE = 16;
   	cotnum(g, fp);
   	cotnum(n, fp);
   	fclose(fp);

   	fp = fopen("Keys1.txt", "w");
   	mip->IOBASE = 16;
   	cotnum(phi, fp);
   	cotnum(g, fp);
   	cotnum(n, fp);
   	cotnum(S1, fp);
   	fclose(fp);
   
   	fp = fopen("Keys2.txt", "w");
   	mip->IOBASE = 16;
   	cotnum(phi, fp);
   	cotnum(g, fp);
   	cotnum(n, fp);
   	cotnum(S2, fp);
   	fclose(fp);

   	return;
}

// read key from the file
void read_key(char *a) 
{
   	FILE *fp;
   	char *namefile = "Public.txt";

   	if (strcmp(a, namefile) == 0)
   	{
       		fp = fopen("Public.txt", "r");
       		mip->IOBASE = 16;
       		g = mirvar(0);
       		n = mirvar(0);
       		cinnum(g, fp);
       		cinnum(n, fp);
       		phi = mirvar(1);
   	}
   	else
   	{
              	fp = fopen(a, "r");
       		mip->IOBASE = 16;
       		phi = mirvar(0);
       		g = mirvar(0);
       		n = mirvar(0);
       		S = mirvar(0);
       		cinnum(phi, fp);
       		cinnum(g, fp);
       		cinnum(n, fp);
       		cinnum(S, fp);
       
   	}

   	fclose(fp);

   	// computing of 1/16*phi mod n
   	if (strcmp(a, namefile) != 0)
   	{
   		big number1;
   		number1 = mirvar(16);
   		multiply(phi, number1, number1);
   		xgcd(number1, n, number1, number1, number1);
   		alpha = number1;
   	}
   	// computing n2
   	n2 = mirvar(0);
   	multiply(n, n, n2);

   	return;
}

// Encryption
big enc(big pt)
{
read_key("Public.txt");
   	big r, c, res1, res2;
   	res1 = mirvar(0);
  	res2 = mirvar(0);
	c = mirvar(0);
   	r = mirvar(0);
   	strong_bigrand(&rng, n, r);
   	powmod(g, pt, n2, res1);
   	powmod(r, n, n2, res2);
   	mad(res1, res2, res2, n2, n2, c);
	
   	return c;
}

// Decryption party i
big decparty(big c)
{
     	// computing of ci
     	big *c1 = malloc(((K/4)+1)*1);
	big number, result;
     	*c1 = mirvar(0);
     	number = mirvar(4);
     	result = mirvar(0);
     	multiply(number, S, *c1);
     	powmod(c, *c1, n2, *c1);

     	return *c1;
}

//Decryption
big dec(big c1, big c2)
{    
     	big decrypted;

     	// computing of M
     	big number4, number5;
     	number4 = mirvar(8);
     	number5 = mirvar(0);
     	powmod(c1, number4, n2, number4);

     	big number6;
     	number6 = mirvar(0);
    	mad(c2, c2, c2, n2, n2, number5);
     	mad(c2, c2, c2, n2, n2, number6);
     	mad(number5, number6, number5, n2, n2, number5);
     	xgcd(number5, n2, number5, number5, number5);

     	mad(number4, number5, number5, n2, n2, number4);

     	decr(number4, 1, number4);
     	divide(number4, n, number4);

     	decrypted = mirvar(0);
     	mad(number4, alpha, alpha, n, n, decrypted);

     	return decrypted;
}

void initialize(void)
{
	mip = mirsys(2*K+1, 2);
    	mip->NTRY=100;
	char number[length];
    	int i;
    	long randnum;  
    	struct timeval tp;
    	gettimeofday(&tp, NULL);

    	//srandomdev();
    	srandom((unsigned int)tp.tv_usec);
    	for (i = 0; i < 50; i++) {
       		randnum = random();
       		number[i*4] = (randnum & 0xFF000000) >> 24;
       		number[i*4+1] = (randnum & 0xFF0000) >> 16;
       		number[i*4+2] = (randnum & 0xFF00) >> 8;
       		number[i*4+3] = randnum & 0xFF;
    	}
    	gettimeofday(&tp, NULL);
    	strong_init(&rng, K/5 , number, (mr_unsign32)tp.tv_usec);

    	return;
}

void initializekey(int id)
{
	read_key("Public.txt");

	if (id == 1)
     		read_key("Keys1.txt");
     	else
		read_key("Keys2.txt");

	return;
}
