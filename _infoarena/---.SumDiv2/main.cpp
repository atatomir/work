#include <cstdio>
#include <cmath>

using namespace std;

struct question {
    long a,b;
};

long q,i,j,max,min;
question qu[100005];
long pr[80000];
int ciur[1000005];
long long nr[1000005];


void do_ciur() {
    long h = (long)sqrt((double)max);
    ciur[1] = 0; for (i=2;i<=max;i++) ciur[i] = 1;
    for(i=2;i<=h;i++) {
        if (ciur[i] != 0) {
            for(j=i;j*i<=max;j++) ciur[i*j] = 0;
        }
    }
    pr[0] = 0;
    long t;
    for(i=2;i<=max;i++)
        if(ciur[i]) {
            pr[0]++;
            pr[pr[0]] = i;
            t = pr[0];
        }
}

long rlp(long a,long b) {
    long p = a,rez = 1;;
    while (b) {
        if (b & 1) rez *= p;
        p *= p;
        b /= 2;
    }
    return rez;
}


int main()
{
    freopen("sumdiv2.in","r",stdin);
    freopen("sumdiv2.out","w",stdout);

    scanf("%ld\n",&q);
    max = 0; min = 1000005;
    for(i=1;i<=q;i++) {
        scanf("%ld %ld\n",&qu[i].a,&qu[i].b);
        if (qu[i].b > max) max = qu[i].b;
        if (qu[i].a < min) min = qu[i].a;
    }

    do_ciur();

    long x,put,n,div;
    for(x=1;x<=max;x++) {
        nr[x] = 1; n=x;
        if (ciur[x]) {nr[x] = x+1 ; continue;}

        for(i=1;i<=pr[0];i++)
            if(n % pr[i] == 0) {
                div = pr[i];
                break;
            }
        put = 0;
        while (n % div == 0) { n /= div; put++; }
        put = rlp(div,put);
        nr[x] = nr[n] * ((put*div-1)/(div-1));
    }

    for(i=2;i<=max;i++) nr[i] += nr[i-1];

    for(i=1;i<=q;i++) {
        printf("%lld\n",nr[qu[i].b]-nr[qu[i].a-1]);
    }

    return 0;
}
