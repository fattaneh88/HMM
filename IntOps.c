#include "IntOps.h"

// LT
big* LT(big *a, big *b, int num, int id)
{
        big *party1 = malloc(((K/4)+1)*num*3);
        big *rs = malloc(((K/4)+1)*num*3);
        int i;
        for(i = 0; i < num*3; i++)
        {
                party1[i] = mirvar(0);
                rs[i] = mirvar(0);
        }

        if (id == 1)
        {
                party1 = LTparty1(a, b, num);

                int output = sending(party1, num*3);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                rs = receive(num*3);
        }
        else
        {
                party1 = receive(num*3);

                rs = LTparty2(party1, num);

                int output = sending(rs, num*3);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }
        }

        big t;
        t = mirvar(2);
        big t1;
        t1 = mirvar(0);
        big ntemp;
        ntemp = mirvar(0);
        copy(n, ntemp);
        divide(ntemp, t, t1);

        big *decpart = malloc(((K/4)+1)*num);
        big *c2 = malloc(((K/4)+1)*num);
        big *result = malloc(((K/4)+1)*num);

        for (i = 0; i < num; i++)
        {
                decpart[i] = mirvar(0);
                decpart[i] = decparty(rs[i*3+2]);
                c2[i] = mirvar(0);
                result[i] = mirvar(0);
        }

        int output = sending(decpart, num);
        if (output < 0)
        {
                perror("ERROR writing to socket");
        }

        c2 = receive(num);

        big final;
        final = mirvar(0);

        for (i = 0; i < num; i++)
        {
                if (id == 1)
                        final = dec(decpart[i], c2[i]);
                else
                        final = dec(c2[i], decpart[i]);

                if (mr_compare(final, t1) > -1)
                        result[i] = rs[i*3+0];
                else
                        result[i] = rs[i*3+1];
        }

        return result;
}

// LT for Party1
big* LTparty1(big *a, big *b, int num)
{
        big *party1 = malloc(((K/4)+1)*num*3);
        int i;
        for(i = 0; i < num*3; i++)
                party1[i] = mirvar(0);
        big ap;
        ap = mirvar(0);
        copy(g, ap);

        big x, y;
        x = mirvar(0);
        y = mirvar(0);

        big temp1, temp2, temp3, temp4;
        temp1 = mirvar(0);
        temp2 = mirvar(0);
        temp3 = mirvar(0);
        temp4 = mirvar(0);

        for (i = 0; i < num; i++)
        {
                CounterLT++;

                copy(a[i], x);
                copy(b[i], y);
                mad(x, ap, ap, n2, n2, x);

                // compute a1 and a2
                party1[i*3+0] = L1Of[CounterLT].a1;
                party1[i*3+1] = L1Of[CounterLT].a2;

                // enc(-y)
                copy(y, temp1);
                xgcd(temp1, n2, temp1, temp1, temp1);

                // enc(x-y)
                mad(x, temp1, temp1, n2, n2, temp2);

                // enc(r*(x-y))
                if (L1Of[CounterLT].b == 0)
                        powmod(temp2, L1Of[CounterLT].r, n2, temp3);
                else
                {
                        subtract (n, L1Of[CounterLT].r, temp3);
                        powmod(temp2, temp3, n2, temp3);
                }

                // enc(-rp)
                temp4 = L1Of[CounterLT].erp;


                // enc(r*(x-y)-rp)
                mad(temp3, temp4, temp4, n2, n2, party1[i*3+2]);
        }

        return party1;

}

// LT for Party2
big* LTparty2(big *party1, int num)
{
        big *rs = malloc(((K/4)+1)*num*3);
        int i;
        for(i = 0; i < num*3; i++)
                rs[i] = mirvar(0);
        big temp1, temp2, temp3, temp4;
        temp1 = mirvar(0);
        temp2 = mirvar(0);
        temp3 = mirvar(0);
        temp4 = mirvar(0);

        for (i = 0; i < num; i++)
        {
                CounterLT++;

                // compute a1 and a2
                mad(L2Of[CounterLT].z1, party1[i*3+L2Of[CounterLT].b], party1[i*3+L2Of[CounterLT].b], n2, n2, rs[i*3+0]);
                mad(L2Of[CounterLT].z2, party1[i*3+1-L2Of[CounterLT].b], party1[i*3+1-L2Of[CounterLT].b], n2, n2, rs[i*3+1]);

                // compute r(-1)^b and enc(rp(-1)^(1-b))
                temp3 = L2Of[CounterLT].erp;

                // compute enc(x.temp1)
                if (L2Of[CounterLT].b == 1)
                {
                        subtract (n, L2Of[CounterLT].r, temp4);
                        powmod(party1[i*3+2], temp4, n2, temp4);
                }
                else
                        powmod(party1[i*3+2], L2Of[CounterLT].r, n2, temp4);

                // compute a3
                mad(temp3, temp4, temp4, n2, n2, rs[i*3+2]);
        }

        return rs;

}

// OR
big* OR(big *x, big *y, int num)
{
        // enc(x+y)
        big *result = malloc(((K/4)+1)*num);
        big *temp1 = malloc(((K/4)+1)*num);
        int i;
        for (i = 0; i < num; i++)
        {
                result[i] = mirvar(0);
                temp1[i] = mirvar(0);
                mad(x[i], y[i], y[i], n2, n2, temp1[i]);
        }

        // enc(x*y)
        big *temp2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                temp2[i] = mirvar(0);

        temp2 = mul(x, y, num, idserver);

        // enc(-x*y) & enc(x+y-x*y)
        for (i = 0; i < num; i++)
        {
                xgcd(temp2[i], n2, temp2[i], temp2[i], temp2[i]);
                mad(temp1[i], temp2[i], temp2[i], n2, n2, result[i]);
        }

        return result;
}

big* ORNew(big *x, big *y, big *temp2, int num)
{
        // enc(x+y)
        big *result = malloc(((K/4)+1)*num);
        big *temp1 = malloc(((K/4)+1)*num);
        int i;
        for (i = 0; i < num; i++)
        {
                result[i] = mirvar(0);
                temp1[i] = mirvar(0);
                mad(x[i], y[i], y[i], n2, n2, temp1[i]);
        }

        // enc(-x*y) & enc(x+y-x*y)
        for (i = 0; i < num; i++)
        {
                xgcd(temp2[i], n2, temp2[i], temp2[i], temp2[i]);
                mad(temp1[i], temp2[i], temp2[i], n2, n2, result[i]);
        }

        return result;
}

// XOR
big* XOR(big *x, big *y, int num)
{
        // enc(x+y)
        big *result = malloc(((K/4)+1)*num);
        big *temp1 = malloc(((K/4)+1)*num);
        int i;
        for (i = 0; i < num; i++)
        {
                result[i] = mirvar(0);
                temp1[i] = mirvar(0);
                mad(x[i], y[i], y[i], n2, n2, temp1[i]);
        }

        // enc(x*y)
        big *temp2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                temp2[i] = mirvar(0);

        temp2 = mul(x, y, num, idserver);
        
        // enc(2x*y)
        for (i = 0; i < num; i++)
                mad(temp2[i], temp2[i], temp2[i], n2, n2, temp2[i]);

        // enc(-2x*y) & enc(x+y-2x*y)
        for (i = 0; i < num; i++)
        {
                xgcd(temp2[i], n2, temp2[i], temp2[i], temp2[i]);
                mad(temp1[i], temp2[i], temp2[i], n2, n2, result[i]);
        }

        return result;
}

// XOR
big* XORNew(big *x, big *y, big *temp2, int num)
{
        // enc(x+y)
        big *result = malloc(((K/4)+1)*num);
        big *temp1 = malloc(((K/4)+1)*num);
        int i;
        for (i = 0; i < num; i++)
        {
                result[i] = mirvar(0);
                temp1[i] = mirvar(0);
                mad(x[i], y[i], y[i], n2, n2, temp1[i]);
        }
        
        // enc(2x*y)
        for (i = 0; i < num; i++)
                mad(temp2[i], temp2[i], temp2[i], n2, n2, temp2[i]);

        // enc(-2x*y) & enc(x+y-2x*y)
        for (i = 0; i < num; i++)
        {
                xgcd(temp2[i], n2, temp2[i], temp2[i], temp2[i]);
                mad(temp1[i], temp2[i], temp2[i], n2, n2, result[i]);
        }

        return result;
}

// mul 
big* mul(big *a, big *b, int num, int id)
{
        big *resultmul = malloc(((K/4)+1)*num);
        int i, counter;
        for (i = 0; i < num; i++)
                resultmul[i] = mirvar(0);
        if (id == 1)
        {
                big *result = malloc(((K/4)+1)*num);

                counter = CounterMul;

                for (i = 0; i < num; i++)
                {
                        result[i] = mirvar(0);
                        CounterMul++;
                        mad(a[i], MOf[CounterMul].b, MOf[CounterMul].b, n2, n2, result[i]);
                }

                int output = sending(result, num);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                big *decpart = malloc(((K/4)+1)*num);

                for (i = 0; i < num; i++)
                {
                        decpart[i] = mirvar(0);
                        decpart[i] = decparty(result[i]);
                }

                output = sending(decpart, num);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                big *result1 = malloc(((K/4)+1)*num);

                for (i = 0; i < num; i++)
                {
                        result1[i] = mirvar(0);
                        counter++;
                        powmod(b[i], MOf[counter].a, n2, result1[i]);
                }

                output = sending(result1, num);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                big *result2 = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                        result2[i] = mirvar(0);

                result2 = receive(num);

                for (i = 0; i < num; i++)
                        mad(result1[i], result2[i], result2[i], n2, n2, resultmul[i]);
        }
        if (id == 2)
        {
                big *res1 = malloc(((K/4)+1)*num);

                for (i = 0; i < num; i++)
                        res1[i] = mirvar(0);

                res1 = receive(num);

                big *decpart = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                {
                        decpart[i] = mirvar(0);
                        decpart[i] = decparty(res1[i]);
                }

                big *c2 = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                        c2[i] = mirvar(0);

                c2 = receive(num);

                big *res2 = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                {
                        res2[i] = mirvar(0);
                        res2[i] = dec(c2[i], decpart[i]);
                }

                big *result1 = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                {
                        result1[i] = mirvar(0);
                        powmod(b[i], res2[i], n2, result1[i]);
                }

                int output = sending(result1, num);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                big *resultf = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                        resultf[i] = mirvar(0);

                resultf = receive(num);

                for (i = 0; i < num; i++)
                        mad(result1[i], resultf[i], resultf[i], n2, n2, resultmul[i]);
        }

        return resultmul;
}

// Trunc
big* Trunc(big *x, int k, int m, int num)
{
        big *s1 = malloc(((K/4)+1)*num*2);
        int i;
        for (i = 0; i < 2*num; i++)
                s1[i] = mirvar(0);

        big *s2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                s2[i] = mirvar(0);

        big *s3 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                s3[i] = mirvar(0);

        big *result = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                result[i] = mirvar(0);

        big *result1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                result1[i] = mirvar(0);

        big c;
        c = mirvar(2);
        power(c, m, n, c);

        if (idserver == 1)
        {
                int counter1 = CounterTrunc11;
                int counter2 = CounterTrunc12;
                for (i = 0; i < num; i++)
                {
                        if (m == l-1)
                        {
                                CounterTrunc11++;
                                mad(x[i], Trunc11[CounterTrunc11].er, Trunc11[CounterTrunc11].er, n2, n2, s1[2*i]);
                                copy(Trunc11[CounterTrunc11].ert, s1[2*i+1]);
                        }
                        else
                        {
                                CounterTrunc12++;
                                mad(x[i], Trunc12[CounterTrunc12].er, Trunc12[CounterTrunc12].er, n2, n2, s1[2*i]);
                                copy(Trunc12[CounterTrunc12].ert, s1[2*i+1]);
                        }
                }

                int output = sending(s1, 2*num);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                for (i = 0; i < num; i++)
                        s2[i] = decparty(s1[2*i]);

                output = sending(s2, num);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                s3 = receive(num);

                CounterTrunc11 = counter1;
                CounterTrunc12 = counter2;
                for (i = 0; i < num; i++)
                {
                        if (m == l-1)
                        {
                                CounterTrunc11++;
                                mad(Trunc11[CounterTrunc11].ert, s3[i], s3[i], n2, n2, result[i]);
                        }
                        else
                        {
                                CounterTrunc12++;
                                mad(Trunc12[CounterTrunc12].ert, s3[i], s3[i], n2, n2, result[i]);
                        }
                }
        }
        else if (idserver == 2)
        {
                s1 = receive(2*num);
                big *decpart = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                {
                        decpart[i] = mirvar(0);
                        decpart[i] = decparty(s1[2*i]);
                }

                s2 = receive(num);

                big *temp3 = malloc(((K/4)+1)*num);
                for (i = 0; i < num; i++)
                {
                        temp3[i] = mirvar(0);
                        temp3[i] = dec(s2[i], decpart[i]);

                        divide (temp3[i], c, temp3[i]);
                        powmod(g, temp3[i], n2, temp3[i]);
                        CounterTrunc++;
                        mad(temp3[i], Trunc2[CounterTrunc], Trunc2[CounterTrunc], n2, n2, s3[i]);
                }
                int output = sending(s3, num);
                if (output < 0)
                {
                        perror("ERROR writing to socket");
                }

                for (i = 0; i < num; i++)
                        mad(s1[2*i+1], s3[i], s3[i], n2, n2, result[i]);
        }

        big *temp6 = malloc(((K/4)+1)*num);
        big *error = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                temp6[i] = mirvar(0);
                powmod(result[i], c, n2, temp6[i]);
                error[i] = mirvar(0);
        }
        error = LT(x, temp6, num, idserver);

        for (i = 0; i < num; i++)
        {
                xgcd(error[i], n2, error[i], error[i], error[i]);
                mad(error[i], result[i], result[i], n2, n2, result1[i]);
        }

        return result1;
}


void OfflineMul()
{
        CounterMul = -1;

        int i;
        for (i = 0; i < numberOfflinemul; i++)
        {
                MOf[i].a = mirvar(0); 
                MOf[i].b = mirvar(0);
        }

        for (i = 0; i < numberOfflinemul; i++)
        {
                strong_bigrand(&rng, n, MOf[i].a);
                subtract (n, MOf[i].a, MOf[i].b);
                MOf[i].b = enc(MOf[i].b); 
        }

        return;
}

void OfflineLT(int id)
{
        CounterLT = -1;

        int i;
        big f, zero;
        f = mirvar(0);
        zero = mirvar(0);

        if (id == 1)
        {
                for (i = 0; i < numberOffline; i++)
                {
                        L1Of[i].r = mirvar(0); 
                        L1Of[i].rp = mirvar(0); 
                        L1Of[i].erp = mirvar(0);
                }

                for (i = 0; i < numberOffline; i++)
                {
                        strong_bigdig(&rng, K/5, 2, L1Of[i].r);
                        strong_bigrand(&rng, L1Of[i].r, L1Of[i].rp);
                        strong_bigdig(&rng, K/10, 2, f);
                        L1Of[i].b = remain (f, 2);
                        L1Of[i].a1 = mirvar(1 - L1Of[i].b);
                        L1Of[i].a1 = enc(L1Of[i].a1);
                        L1Of[i].a2 = mirvar(L1Of[i].b);
                        L1Of[i].a2 = enc(L1Of[i].a2); 
			if (L1Of[i].b == 0)
			{
				big sub;
				sub = mirvar(0);
                        	subtract (n, L1Of[i].rp, sub);
                        	L1Of[i].erp = enc(sub);
			}
			else
                        	L1Of[i].erp = enc(L1Of[i].rp); 
                }

        }
        else
        {
                for (i = 0; i < numberOffline; i++)
                {
                        L2Of[i].z1 = mirvar(0); 
                        L2Of[i].z2 = mirvar(0);
                        L2Of[i].r = mirvar(0); 
                        L2Of[i].rp = mirvar(0); 
                        L2Of[i].erp = mirvar(0); 
                }

                for (i = 0; i < numberOffline; i++)
                {
                        L2Of[i].z1 = enc(zero);
                        L2Of[i].z2 = enc(zero);
                        strong_bigdig(&rng, K/5, 2, L2Of[i].r);
                        strong_bigrand(&rng, L2Of[i].r, L2Of[i].rp);
                        strong_bigdig(&rng, K/10, 2, f);
                        L2Of[i].b = remain (f, 2);
			if (L2Of[i].b == 0)
			{       
				big sub;
				sub = mirvar(0);                 
				subtract (n, L2Of[i].rp, sub);
                        	L2Of[i].erp = enc(sub);
			}
			else
                        	L2Of[i].erp = enc(L2Of[i].rp); 
                }

        }

        return;
}

void OfflineTrunc(int id)
{
        CounterTrunc = -1;
        CounterTrunc11 = -1;
        CounterTrunc12 = -1;

        int i;

        if (id == 1)
        {
                for (i = 0; i < truncoff; i++)
                {
                        Trunc11[i].r = mirvar(0);
                        Trunc11[i].er = mirvar(0);
                        Trunc11[i].rt = mirvar(0);
                        Trunc11[i].ert = mirvar(0);

                        Trunc12[i].r = mirvar(0);
                        Trunc12[i].er = mirvar(0);
                        Trunc12[i].rt = mirvar(0);
                        Trunc12[i].ert = mirvar(0);
                }

                big c,c1;
                c = mirvar(2);
                power(c, l-1, n, c);
                c1 = mirvar(2);

                for (i = 0; i < truncoff; i++)
                {
                        strong_bigdig(&rng, 2*l+l-1+kapa, 2, Trunc11[i].r);

                        Trunc11[i].er = enc(Trunc11[i].r);

                        copy(Trunc11[i].r, Trunc11[i].rt);
                        divide (Trunc11[i].rt, c, Trunc11[i].rt);
                        subtract (n, Trunc11[i].rt, Trunc11[i].rt);

                        Trunc11[i].ert = enc(Trunc11[i].rt);

                        strong_bigdig(&rng, l+2+kapa, 2, Trunc12[i].r);

                        Trunc12[i].er = enc(Trunc12[i].r);

                        copy(Trunc12[i].r, Trunc12[i].rt);
                        divide (Trunc12[i].rt, c1, Trunc12[i].rt);
                        subtract (n, Trunc12[i].rt, Trunc12[i].rt);

                        Trunc12[i].ert = enc(Trunc12[i].rt);
                }
        }
        else
        {
                big zero;
                zero = mirvar(0);
                for (i = 0; i < 2*truncoff; i++)
                {
                        Trunc2[i] = mirvar(0);
                        Trunc2[i] = enc(zero);
                } 
        }

        return;
}
