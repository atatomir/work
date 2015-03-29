#include <iostream>
#include <cstdio>

#define mod 666013

using namespace std;

long t,ti;
long long x,y,z,za,zb,zc,n;
long long r[3][3],aux[3][3],a[3][3],standard[3][3],zero[3][3];

inline void copyMatrix(long long from[3][3],long long to[3][3]){
    for(long i=0;i<3;i++)
        for(long j=0;j<3;j++)
            to[i][j] = from[i][j];
}

inline void multiplicate(long long a[3][3],long long b[3][3],long n,long m,long dim){
    for(long i=0;i<n;i++){
        for(long j=0;j<m;j++){
            aux[i][j] = 0;
            for(long p=0;p<dim;p++)
                aux[i][j] = (aux[i][j] + a[i][p]*b[p][j])% mod;
        }
    }
    copyMatrix(aux,a);
}

int main()
{
    freopen("iepuri.in","r",stdin);
    freopen("iepuri.out","w",stdout);

    standard[0][0] = standard[1][1] = standard[2][2] = 1;

    scanf("%ld\n",&t);
    for(ti=1;ti<=t;ti++){
        scanf("%lld %lld %lld %lld %lld %lld %lld\n",&x,&y,&z,&za,&zb,&zc,&n);
        copyMatrix(standard,r);
        copyMatrix(zero,a);
        n -= 2;

        a[0][0] = za; a[0][1] = zb; a[0][2] = zc;
        a[1][0] = 1; a[2][1] = 1;

        while(n){
            if(n&1){
                multiplicate(r,a,3,3,3);
            }
            multiplicate(a,a,3,3,3);
            n >>= 1;
        }
        a[0][0]=z; a[1][0] = y; a[2][0] = x;
        multiplicate(r,a,3,1,3);

        printf("%lld\n",r[0][0]);
    }

    return 0;
}
