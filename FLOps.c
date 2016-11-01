#include "FLOps.h"

// FLLT
big* FLLT(struct floatingPoint* x, struct floatingPoint* y, int num)
{
        big *var1 = malloc(((K/4)+1)*num);
        big *var2 = malloc(((K/4)+1)*num);
        big *var3 = malloc(((K/4)+1)*num);
        big *var4 = malloc(((K/4)+1)*num);
        big *var5 = malloc(((K/4)+1)*num);
        big *var6 = malloc(((K/4)+1)*num);
        int i;
        for (i = 0; i < num; i++)
        {
                var1[i] = mirvar(0);
                var1[i] = x[i].p;
                var2[i] = mirvar(0);
                var2[i] = y[i].p;
                var3[i] = mirvar(0);
        }

        var3 = LT(var1, var2, num, idserver);

        for (i = 0; i < num; i++)
        {
                var5[i] = mirvar(0);
                var5[i] = y[i].p;
                var6[i] = mirvar(0);
                var6[i] = x[i].p;
                var4[i] = mirvar(0);
        }

        var4 = LT(var5, var6, num, idserver);


        big one;
        one = mirvar(0);
        one = g;
        big *c = malloc(((K/4)+1)*num);
        big *res4 = malloc(((K/4)+1)*num);

        for (i = 0; i < num; i++)
        {
                res4[i] = mirvar(0);
                c[i] = mirvar(0);

                mad(var3[i], var4[i], var4[i], n2, n2, res4[i]);

                xgcd(res4[i], n2, res4[i], res4[i], res4[i]);

                mad(res4[i], one, one, n2, n2, c[i]);
        }

        big *a = malloc(((K/4)+1)*num);
        big *d = malloc(((K/4)+1)*num);

        big two;
        two = mirvar(2);

        big *es21 = malloc(((K/4)+1)*num);
        big *es22 = malloc(((K/4)+1)*num);

        for (i = 0; i < num; i++)
        {
                es21[i] = mirvar(0);
                copy(x[i].s, es21[i]);
                powmod(es21[i], two, n2, es21[i]);
                xgcd(es21[i], n2, es21[i], es21[i], es21[i]);
                mad(es21[i], one, one, n2, n2, es21[i]);

                es22[i] = mirvar(0);
                copy(y[i].s, es22[i]);
                powmod(es22[i], two, n2, es22[i]);
                xgcd(es22[i], n2, es22[i], es22[i], es22[i]);
                mad(es22[i], one, one, n2, n2, es22[i]);
        }

        for (i = 0; i < num; i++)
        {
                copy(x[i].p, var1[i]);
                copy(y[i].p, var2[i]);
        }

        a = LT(var1, var2, num, idserver);

        big *p1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                p1[i] = mirvar(0);
                copy(x[i].v, var1[i]);
        }

        p1 = mul(es21, var1, num, idserver);

        big *p2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                p2[i] = mirvar(0);
                copy(y[i].v, var2[i]);
        }

        p2 = mul(es22, var2, num, idserver);

        d = LT(p1, p2, num, idserver);

        big *es1 = malloc(((K/4)+1)*num);
        big *es2 = malloc(((K/4)+1)*num);
        big *z1 = malloc(((K/4)+1)*num);
        big *z2 = malloc(((K/4)+1)*num);
        big *bp = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                es1[i] = mirvar(0);
                copy(x[i].s, es1[i]);
                xgcd(es1[i], n2, es1[i], es1[i], es1[i]);
                mad(es1[i], one, one, n2, n2, es1[i]);

                es2[i] = mirvar(0);
                copy(y[i].s,es2[i]);
                xgcd(es2[i], n2, es2[i], es2[i], es2[i]);
                mad(es2[i], one, one, n2, n2, es2[i]);

                z1[i] = mirvar(0);
                copy(x[i].z,z1[i]);
                xgcd(z1[i], n2, z1[i], z1[i], z1[i]);
                mad(z1[i], one, one, n2, n2, z1[i]);

                z2[i] = mirvar(0);
                copy(y[i].z,z2[i]);
                xgcd(z2[i], n2, z2[i], z2[i], z2[i]);
                mad(z2[i], one, one, n2, n2, z2[i]);

                bp[i] = mirvar(0);
        }

                bp = mul(c, d, num, idserver);

        big *bp1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                bp1[i] = mirvar(0);
                copy(c[i], bp1[i]);
                xgcd(bp1[i], n2, bp1[i], bp1[i], bp1[i]);
                mad(one, bp1[i], bp1[i], n2, n2, bp1[i]);
        }

        bp1 = mul(a, bp1, num, idserver);

        big *bm = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                mad(bp[i], bp1[i], bp1[i], n2, n2, bp[i]);
                bm[i] = mirvar(0);
        }

        bm = mul(c, d, num, idserver);

        big *bm1 = malloc(((K/4)+1)*num);
        big *bm2 = malloc(((K/4)+1)*num);
        for (i = 0; i< num; i++)
        {
                bm1[i] = mirvar(0);
                copy(c[i], bm1[i]);
                xgcd(bm1[i], n2, bm1[i], bm1[i], bm1[i]);
                mad(one, bm1[i], bm1[i], n2, n2, bm1[i]);

                bm2[i] = mirvar(0);
                copy(a[i], bm2[i]);
                xgcd(bm2[i], n2, bm2[i], bm2[i], bm2[i]);
                mad(one, bm2[i], bm2[i], n2, n2, bm2[i]);
        }

        bm2 = mul(bm2, bm1, num, idserver);

        for (i = 0; i < num; i++)
                mad(bm[i], bm2[i], bm2[i], n2, n2, bm[i]);

        big *b = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                b[i] = mirvar(0);
                copy(x[i].z, var1[i]);
        }
        b = mul(var1, z2, num, idserver);
        b = mul(b, es2, num, idserver);

        big *b1 = malloc(((K/4)+1)*num);
        for (i = 0; i< num; i++)
        {
                b1[i] = mirvar(0);
                copy(y[i].z, var2[i]);
                copy(x[i].s, var1[i]);
        }

        b1 = mul(z1, var2, num, idserver);
        b1 = mul(b1, var1, num, idserver);

        big *b2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                b2[i] = mirvar(0);
        b2 = mul(z1, z2, num, idserver);

        big *b3 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                b3[i] = mirvar(0);
                copy(x[i].s, var1[i]);
        }

        b3 = mul(var1, es2, num, idserver);

        big *b4 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                b4[i] = mirvar(0);

        b4 = mul(es1, es2, num, idserver);
        b4 = mul(b4, bp, num, idserver);

        big *b5 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                b5[i] = mirvar(0);
                copy(x[i].s, var1[i]);
                copy(y[i].s, var2[i]);
        }

        b5 = mul(var1, var2, num, idserver);
        b5 = mul(b5, bm, num, idserver);

        big *b6 = malloc(((K/4)+1)*num);
        big *b7 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                b6[i] = mirvar(0);
                mad(b5[i], b4[i], b4[i], n2, n2, b6[i]);
                mad (b3[i], b6[i], b6[i], n2, n2, b6[i]);

                b7[i] = mirvar(0);
        }

        b7 = mul(b2, b6, num, idserver);

        big *b8 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                b8[i] = mirvar(0);
                mad(b1[i], b7[i], b7[i], n2, n2, b8[i]);
                mad(b[i], b8[i], b8[i], n2, n2, b[i]);
        }

        return b;
}

// FLLT
big* FLLTNew(struct floatingPoint* x, struct floatingPoint* y, int num)
{
        big one;
        one = mirvar(0);
        one = g;
	big *es2 = malloc(((K/4)+1)*2*num);
	big *s1m = malloc(((K/4)+1)*num);
	big *s2m = malloc(((K/4)+1)*num);
	int i, j;

        for (i = 0; i < num; i++)
        {
                es2[i] = mirvar(0);
		s1m[i] = mirvar(0);
                copy(x[i].s, s1m[i]);
		xgcd(s1m[i], n2, s1m[i], s1m[i], s1m[i]);
		mad(s1m[i], s1m[i], s1m[i], n2, n2, es2[i]);
                mad(es2[i], one, one, n2, n2, es2[i]);
	}

	j = 0;
        for (i = num; i < 2*num; i++)
        {
                es2[i] = mirvar(0);
		s2m[j] = mirvar(0);
                copy(y[j].s, s2m[j]);
		xgcd(s2m[j], n2, s2m[j], s2m[j], s2m[j]);
		mad(s2m[j], s2m[j], s2m[j], n2, n2, es2[i]);
                mad(es2[i], one, one, n2, n2, es2[i]);
		j++;
	}

	big *p0 = malloc(((K/4)+1)*num*2);
	big *v0 = malloc(((K/4)+1)*num*2);
        for (i = 0; i < num; i++)
        {
		p0[i] = 0;
		v0[i] = 0;
                copy(x[i].v, v0[i]);
        }

	j = 0;
        for (i = num; i < 2*num; i++)
        {
		p0[i] = 0;
		v0[i] = 0;
                copy(y[j].v, v0[i]);
        }

        p0 = mul(es2, v0, 2*num, idserver);

	big *p1 = malloc(((K/4)+1)*3*num);
        big *p2 = malloc(((K/4)+1)*3*num);
        for (i = 0; i < num; i++)
        {
                p1[i] = mirvar(0);
                copy(p0[i], p1[i]);
        }
	j = 0;
        for (i = num; i < 2*num; i++)
        {
                p1[i] = mirvar(0);
                copy(x[j].p, p1[i]);
		j++;
        }
	j = 0;
        for (i = 2*num; i < 3*num; i++)
        {
                p1[i] = mirvar(0);
                copy(y[j].p, p1[i]);
		j++;
        }

	j = num;
        for (i = 0; i < num; i++)
        {
                p2[i] = mirvar(0);
                copy(p0[j], p2[i]);
		j++;
        }
	j = 0;
        for (i = num; i < 2*num; i++)
        {
                p2[i] = mirvar(0);
                copy(y[j].p, p2[i]);
		j++;
        }
	j = 0;
        for (i = 2*num; i < 3*num; i++)
        {
                p2[i] = mirvar(0);
                copy(x[j].p, p2[i]);
		j++;
        }

	big *var1 = malloc(((K/4)+1)*3*num);
        for (i = 0; i < 3*num; i++)
                var1[i] = mirvar(0);

        var1 = LT(p1, p2, 3*num, idserver);

        big *a = malloc(((K/4)+1)*num);
        big *d = malloc(((K/4)+1)*num);

        for (i = 0; i < num; i++)
        {
		d[i] = mirvar(0);
		copy(var1[i], d[i]);
        }
	
	j = 0;
        for (i = num; i < 2*num; i++)
        {
		a[j] = mirvar(0);
		copy(var1[i], a[j]);
		j++;
        }
      
        big *var2 = malloc(((K/4)+1)*num);
	j = 0;
        for (i = num; i < 2*num; i++)
        {
		var2[j] = mirvar(0);
		copy(var1[i], var2[j]);
		j++;
        }

        big *var3 = malloc(((K/4)+1)*num);
	j = 0;
        for (i = 2*num; i < 3*num; i++)
        {
		var3[j] = mirvar(0);
		copy(var1[i], var3[j]);
		j++;
        }

        big *c = malloc(((K/4)+1)*num);
        big *res1 = malloc(((K/4)+1)*num);

        for (i = 0; i < num; i++)
        {
                res1[i] = mirvar(0);
                c[i] = mirvar(0);

                mad(var2[i], var3[i], var3[i], n2, n2, res1[i]);

                xgcd(res1[i], n2, res1[i], res1[i], res1[i]);

                mad(res1[i], one, one, n2, n2, c[i]);
        }

        big *var4 = malloc(((K/4)+1)*2*num);
        big *var5 = malloc(((K/4)+1)*2*num);
        big *var6 = malloc(((K/4)+1)*2*num);

        for (i = 0; i < num; i++)
        {
                var4[i] = mirvar(0);
                var5[i] = mirvar(0);
		copy(c[i], var4[i]);
		copy(d[i], var5[i]);
                var6[i] = mirvar(0);
        }

	big *cm = malloc(((K/4)+1)*num);
	j = 0;
        for (i = num; i < 2*num; i++)
        {
		cm[j] = mirvar(0);
                var4[i] = mirvar(0);
                var5[i] = mirvar(0);
		copy(c[j], var4[i]);
		xgcd(var4[i], n2, var4[i], var4[i], var4[i]);
		mad(var4[i], one, one, n2, n2, var4[i]);
		copy(var4[i], cm[j]);
		copy(a[j], var5[i]);
                var6[i] = mirvar(0);
		j++;
        }

	var6 = mul(var4, var5, 2*num, idserver);

	big *bp = malloc(((K/4)+1)*num);
	big *bm = malloc(((K/4)+1)*num);
	big *var7 = malloc(((K/4)+1)*num);

	j = num;
        for (i = 0; i < num; i++)
        {
		bp[i] = mirvar(0);
		mad(var6[i], var6[j], var6[j], n2, n2, bp[i]);

		bm[i] = mirvar(0);
		var7[i] = mirvar(0);
		copy(var6[j], var7[i]);
		xgcd(var7[i], n2, var7[i], var7[i], var7[i]);
		mad(var7[i], cm[i], cm[i], n2, n2, var7[i]);
		mad(var6[i], var7[i], var7[i], n2, n2, bm[i]);

		j++;
        }

        big *es = malloc(((K/4)+1)*num);
	big *ez = malloc(((K/4)+1)*num);
        big *res2 = malloc(((K/4)+1)*2*num);
        big *res3 = malloc(((K/4)+1)*2*num);
        big *res4 = malloc(((K/4)+1)*2*num);

        for (i = 0; i < num; i++)
        {
		es[i] = mirvar(0);
		ez[i] = mirvar(0);
		res2[i] = mirvar(0);
		copy(x[i].z, res2[i]);
		res3[i] = mirvar(0);
		copy(y[i].z, res3[i]);
		res4[i] = mirvar(0);
	}

	j = 0;
        for (i = num; i < 2*num; i++)
        {
		res2[i] = mirvar(0);
		copy(x[j].s, res2[i]);
		res3[i] = mirvar(0);
		copy(y[j].s, res3[i]);
		res4[i] = mirvar(0);
		j++;
	}
        
	res4 = mul(res2, res3, 2*num, idserver);

	j = num;
        for (i = 0; i < num; i++)
        {
		copy(res4[i], ez[i]);
		copy(res4[j], es[i]);
		j++;
	}

        big *z1 = malloc(((K/4)+1)*num);
        big *z2 = malloc(((K/4)+1)*num);
        big *ezm = malloc(((K/4)+1)*num);
        big *esm = malloc(((K/4)+1)*num);
        big *s2m1 = malloc(((K/4)+1)*num);
        big *res5 = malloc(((K/4)+1)*2*num);
        big *res6 = malloc(((K/4)+1)*2*num);
        big *res7 = malloc(((K/4)+1)*2*num);

	j = num;
        for (i = 0; i < num; i++)
        {
		z1[i] = mirvar(0);
		z2[i] = mirvar(0);
		ezm[i] = mirvar(0);
		copy(ez[i], ezm[i]);
		xgcd(ezm[i], n2, ezm[i], ezm[i], ezm[i]);

		esm[i] = mirvar(0);
		copy(es[i], esm[i]);
		xgcd(esm[i], n2, esm[i], esm[i], esm[i]);

		res5[i] = mirvar(0);
		mad(x[i].z, ezm[i], ezm[i], n2, n2, res5[i]);

		res6[i] = mirvar(0);
		s2m1[i] = mirvar(0);
		copy(y[i].s, s2m1[i]);
		xgcd(s2m1[i], n2, s2m1[i], s2m1[i], s2m1[i]);
		mad(s2m1[i], one, one, n2, n2, s2m1[i]);
		copy(s2m1[i], res6[i]);

		res5[j] = mirvar(0);
		res6[j] = mirvar(0);
		mad(y[i].z, ezm[i], ezm[i], n2, n2, res5[j]);
		copy(x[i].s, res6[j]);

		res7[i] = mirvar(0);
		res7[j] = mirvar(0);
		j++;
	}

	res7 = mul(res5, res6, 2*num, idserver);

	j = num;
        for (i = 0; i < num; i++)
        {
		copy(res7[i], z1[i]);
		copy(res7[j], z2[i]);
		j++;
	}

        big *z1m = malloc(((K/4)+1)*num);
        big *z2m = malloc(((K/4)+1)*num);

        for (i = 0; i < num; i++)
        {
		z1m[i] = mirvar(0);
		copy(x[i].z, z1m[i]);
                xgcd(z1m[i], n2, z1m[i], z1m[i], z1m[i]);

		z2m[i] = mirvar(0);
		copy(y[i].z, z2m[i]);
                xgcd(z2m[i], n2, z2m[i], z2m[i], z2m[i]);
        }

	big *z31 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
		z31[i] = mirvar(0);
		mad(z1m[i], one, one, n2, n2, z31[i]);
		mad(z31[i], z2m[i], z2m[i], n2, n2, z31[i]);
		mad(z31[i], ezm[i], ezm[i], n2, n2, z31[i]);

        }

	big *s1 = malloc(((K/4)+1)*num);
	big *ss1 = malloc(((K/4)+1)*num*2);
	big *ss2 = malloc(((K/4)+1)*num*2);
	big *ss3 = malloc(((K/4)+1)*num*2);

	j = num;
        for (i = 0; i < num; i++)
        {
		s1[i] = mirvar(0);
		mad(x[i].s, esm[i], esm[i], n2, n2, s1[i]);

		ss1[i] = mirvar(0);
		mad(s1m[i], one, one, n2, n2, ss1[i]);
		mad(ss1[i], s2m[i], s2m[i], n2, n2, ss1[i]);
		mad(ss1[i], esm[i], esm[i], n2, n2, ss1[i]);
		ss2[i] = mirvar(0);
		copy(bp[i], ss2[i]);

		ss1[j] = mirvar(0);
		ss2[j] = mirvar(0);
		copy(es[i], ss1[j]);
		copy(bm[i], ss2[j]);

		ss3[i] = mirvar(0);
		ss3[j] = mirvar(0);
		j++;
        }

	ss3 = mul(ss1, ss2, 2*num, idserver);

        big *z32 = malloc(((K/4)+1)*num);
	big *z3 = malloc(((K/4)+1)*num);

	j = num;
        for (i = 0; i < num; i++)
        {
                z32[i] = mirvar(0);
		mad(ss3[i], ss3[j], ss3[j], n2, n2, z32[i]);
		mad(z32[i], s1[i], s1[i], n2, n2, z32[i]);
		j++;

		z3[i] = mirvar(0);
        }

        z3 = mul(z31, z32, num, idserver);

        big *b = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
		b[i] = mirvar(0);
                mad(z1[i], z2[i], z2[i], n2, n2, b[i]);
                mad(b[i], z3[i], z3[i], n2, n2, b[i]);
        }

        return b;
}

// FLMul
struct floatingPoint* FLMul(struct floatingPoint *x, struct floatingPoint *y, int num){
        struct floatingPoint *result = malloc(((K/4)+1)*4*num);
        int i;
        for (i = 0; i < num; i++)
        {
                result[i].v = mirvar(0);
                result[i].p = mirvar(0);
                result[i].z = mirvar(0);
                result[i].s = mirvar(0);
        }

        big *v = malloc(((K/4)+1)*num);
        big *v1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                v[i] = mirvar(0);
                v1[i] = mirvar(0);
        }

        big *aa = malloc(((K/4)+1)*num);
        big *bb = malloc(((K/4)+1)*num);
        for(i = 0; i < N; i++)
        {
                aa[i] = mirvar(0);
                aa[i] = x[i].v;
                bb[i] = mirvar(0);
                bb[i] = y[i].v;
        }
        v = mul(aa, bb, num, idserver);

        v1 = Trunc(v, 2*l, l-1, num);

        big *t = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                t[i] = mirvar(2);
                power(t[i], l, n, t[i]);
                t[i] = enc(t[i]);
        }

        big *el = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                el[i] = mirvar(l);
                el[i] = enc(el[i]);
        }

        big *b = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                b[i] = mirvar(0);
        b = LT(v1, t, num, idserver);

        big *v2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                v2[i] = mirvar(0);
        v2 = mul(b, v1, num, idserver);

        big *v3 = malloc(((K/4)+1)*num);
        big two;
        two = mirvar(2);
        for (i = 0; i < num; i++)
        {
                v3[i] = mirvar(0);
                powmod(v2[i], two, n2, v3[i]);
        }

        big *b1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                b1[i] = mirvar(0);
                copy(b[i], b1[i]);
                xgcd(b1[i], n2, b1[i], b1[i], b1[i]);
        }

        big one;
        one = mirvar(0);
        one = g;

        for (i = 0; i < num; i++)
                mad (one, b1[i], b1[i], n2, n2, b1[i]);

        big *v4 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                v4[i] = mirvar(0);

        v4 = mul(b1, v1, num, idserver);

        big *temp1 = malloc(((K/4)+1)*num);
        big *temp2 = malloc(((K/4)+1)*num);
        big *t2 = malloc(((K/4)+1)*num);
        big *z = malloc(((K/4)+1)*num);
        big *zz = malloc(((K/4)+1)*num);
        big *result1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                temp1[i] = mirvar(0);
                temp2[i] = mirvar(0);
                mad(v4[i], v3[i], v3[i], n2, n2, temp1[i]);
        }

        temp2 = Trunc(temp1, l+1, 1, num);

        big *or = malloc(((K/4)+1)*num);
        big *xor = malloc(((K/4)+1)*num);
        big *or1 = malloc(((K/4)+1)*num);
        big *or2 = malloc(((K/4)+1)*num);
        big *xor1 = malloc(((K/4)+1)*num);
        big *xor2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                or[i] = mirvar(0);
                or1[i] = mirvar(0);
                copy(x[i].z, or1[i]);
                or2[i] = mirvar(0);
                copy(y[i].z, or2[i]);
                xor[i] = mirvar(0);
                xor1[i] = mirvar(0);
                copy(x[i].s, xor1[i]);
                xor2[i] = mirvar(0);
                copy(x[i].s, xor2[i]);
        }
        or = OR(or1, or2, num);
        xor = XOR(xor1, xor2, num);
        for (i = 0; i < num; i++)
        {
                result[i].v = temp2[i];
                copy(or[i], result[i].z);
                copy(xor[i], result[i].s);

                mad(x[i].p, y[i].p, y[i].p, n2, n2, result[i].p);

                t2[i] = mirvar(0);
                copy(b[i], t2[i]);
                xgcd(t2[i], n2, t2[i], t2[i], t2[i]);

                mad(el[i], t2[i], t2[i], n2, n2, el[i]);
                mad(result[i].p, el[i], el[i] , n2, n2, result[i].p);

                z[i] = mirvar(0);
                copy(result[i].z, z[i]);
                xgcd(z[i], n2, z[i], z[i], z[i]);
                mad(one, z[i], z[i], n2, n2, z[i]);

                zz[i] = mirvar(0);
                copy(result[i].p, zz[i]);
                result1[i] = mirvar(0);
        }

        result1 = mul(zz, z, num, idserver);
        for (i = 0; i < num; i++)
                copy(result1[i], result[i].p);

        return result;
}

// FLMul after modification
struct floatingPoint* FLMulNew(struct floatingPoint *x, struct floatingPoint *y, int num){
        struct floatingPoint *result = malloc(((K/4)+1)*4*num);
        int i;
        for (i = 0; i < num; i++)
        {
                result[i].v = mirvar(0);
                result[i].p = mirvar(0);
                result[i].z = mirvar(0);
                result[i].s = mirvar(0);
        }

        big *v0 = malloc(((K/4)+1)*num*3);
        big *v = malloc(((K/4)+1)*num);
        big *v1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                v[i] = mirvar(0);
                v1[i] = mirvar(0);
        }

        big *aa = malloc(((K/4)+1)*num*3);
        big *bb = malloc(((K/4)+1)*num*3);
        for(i = 0; i < num; i++)
        {
		v0[i] = mirvar(0);
                aa[i] = mirvar(0);
                aa[i] = x[i].v;
                bb[i] = mirvar(0);
                bb[i] = y[i].v;
        }

	int j = 0;
        for(i = num; i < 2*num; i++)
        {
		v0[i] = mirvar(0);
                aa[i] = mirvar(0);
                aa[i] = x[j].z;
                bb[i] = mirvar(0);
                bb[i] = y[j].z;
		j++;
        }

	j = 0;
        for(i = 2*num; i < 3*num; i++)
        {
		v0[i] = mirvar(0);
                aa[i] = mirvar(0);
                aa[i] = x[j].s;
                bb[i] = mirvar(0);
                bb[i] = y[j].s;
		j++;
        }

        big *or = malloc(((K/4)+1)*num);
        big *xor = malloc(((K/4)+1)*num);
        big *or1 = malloc(((K/4)+1)*num);
        big *or2 = malloc(((K/4)+1)*num);
        big *or3 = malloc(((K/4)+1)*num);
        big *xor1 = malloc(((K/4)+1)*num);
        big *xor2 = malloc(((K/4)+1)*num);
        big *xor3 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                or[i] = mirvar(0);
                or1[i] = mirvar(0);
                copy(x[i].z, or1[i]);
                or2[i] = mirvar(0);
                copy(y[i].z, or2[i]);
                xor[i] = mirvar(0);
                xor1[i] = mirvar(0);
                copy(x[i].s, xor1[i]);
                xor2[i] = mirvar(0);
                copy(y[i].s, xor2[i]);
		or3[i] = mirvar(0);
		xor3[i] = mirvar(0);
        }

        v0 = mul(aa, bb, 3*num, idserver);

        for(i = 0; i < num; i++)
		copy(v0[i], v[i]);

	j = 0;
        for(i = num; i < 2*num; i++)
	{
		or3[j] = v0[i];
		j++;
	}

	j = 0;
        for(i = 2*num; i < 3*num; i++)
	{
		xor3[j] = v0[i];
		j++;
	}


        v1 = Trunc(v, 2*l, l-1, num);

        big *t = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                t[i] = mirvar(2);
                power(t[i], l, n, t[i]);
                t[i] = enc(t[i]);
        }

        big *el = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                el[i] = mirvar(l);
                el[i] = enc(el[i]);
        }

        big *b = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                b[i] = mirvar(0);
        b = LT(v1, t, num, idserver);

        big *v2 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
                v2[i] = mirvar(0);
        v2 = mul(b, v1, num, idserver);

        big *v3 = malloc(((K/4)+1)*num);
        big two;
        two = mirvar(2);
        for (i = 0; i < num; i++)
        {
                v3[i] = mirvar(0);
		mad(v2[i], v2[i], v2[i], n2, n2, v3[i]);
        }

        big *v4 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
	{
                v4[i] = mirvar(0);
		copy(v2[i], v4[i]);
		xgcd(v4[i], n2, v4[i], v4[i], v4[i]);
	}

        big *v5 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
	{
		v5[i] = mirvar(0);
                mad (v1[i], v4[i], v4[i], n2, n2, v5[i]);
	}

        big *temp1 = malloc(((K/4)+1)*num);
        big *temp2 = malloc(((K/4)+1)*num);
        big *t2 = malloc(((K/4)+1)*num);
        big *z = malloc(((K/4)+1)*num);
        big *zz = malloc(((K/4)+1)*num);
        big *result1 = malloc(((K/4)+1)*num);
        for (i = 0; i < num; i++)
        {
                temp1[i] = mirvar(0);
                temp2[i] = mirvar(0);
                mad(v5[i], v3[i], v3[i], n2, n2, temp1[i]);
        }

	big one;
	one = mirvar(0);
	one = g;

        temp2 = Trunc(temp1, l+1, 1, num);
        or = ORNew(or1, or2, or3, num);
        xor = XORNew(xor1, xor2, xor3, num);
        for (i = 0; i < num; i++)
        {
                copy(temp2[i], result[i].v);
                copy(or[i], result[i].z);
                copy(xor[i], result[i].s);

                mad(x[i].p, y[i].p, y[i].p, n2, n2, result[i].p);

                t2[i] = mirvar(0);
                copy(b[i], t2[i]);
                xgcd(t2[i], n2, t2[i], t2[i], t2[i]);

                mad(el[i], t2[i], t2[i], n2, n2, el[i]);
                mad(result[i].p, el[i], el[i] , n2, n2, result[i].p);

                z[i] = mirvar(0);
                copy(result[i].z, z[i]);
                xgcd(z[i], n2, z[i], z[i], z[i]);
                mad(one, z[i], z[i], n2, n2, z[i]);

                zz[i] = mirvar(0);
                copy(result[i].p, zz[i]);
                result1[i] = mirvar(0);
        }

        result1 = mul(zz, z, num, idserver);
        for (i = 0; i < num; i++)
                copy(result1[i], result[i].p);

        return result;
}
