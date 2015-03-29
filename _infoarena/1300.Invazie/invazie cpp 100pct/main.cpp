#include <iostream>
#include <cstdio>


#define mod 666013

using namespace std;

long k,p,t,ti;
long long n;
long long a[2][2],put[2][2];

inline void multiplicate(long long a[2][2],long long b[2][2]){
    long long aux[2][2],bl[2][2];
    long i,j;
    for(i=0;i<2;i++)
        for(j=0;j<2;j++) aux[i][j] = a[i][j],bl[i][j] = b[i][j];

    a[0][0] = (aux[0][0]*bl[0][0] + aux[0][1]*bl[0][1])%mod;
    a[0][1] = (aux[0][0]*bl[0][1] + aux[0][1]*bl[0][0])%mod;
}

int main()
{
    freopen("invazie.in","r",stdin);
    freopen("invazie.out","w",stdout);

    scanf("%ld",&t);
    for(ti=t;ti;ti--){
        scanf("%ld %ld %lld",&k,&p,&n);

        a[0][0] = 1; a[0][1] = 0;
        a[0][1] = 0; a[1][1] = 1;

        put[0][0] = k; put[0][1] = p;
        put[1][0] = p; put[1][1] = k;

        while(n){
            if(n&1) multiplicate(a,put);
            multiplicate(put,put);
            n >>= 1;
        }

        printf("%lld\n",a[0][0]);
    }

    return 0;
}
