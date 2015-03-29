#include <iostream>
#include <cstdio>

using namespace std;

#define mod 30013
#define maxN 5011

long n,k,v,o,s,d;
long C[2][maxN];

void make_Comb(long lim){
    long i,j;
    s=0;d=1;
    for(i=1;i<=lim;i++){
        C[d][1] = i; C[s][i]=0; C[d][0] = 1;
        for(j=2;j<=i;j++) C[d][j] = (C[s][j-1]+C[s][j])%mod;
        s^=1;d^=1;
    }
}

int main()
{
    freopen("drum3.in","r",stdin);
    freopen("drum3.out","w",stdout);

    scanf("%ld %ld",&n,&k);
    ----n;
    o = 1+k/2;
    v = k/2; if(k&1) v++;

    o--;v--;
    make_Comb(n);
    long long ans = ((long long)C[s][o]*(long long)C[s][v]*2)%mod;
    printf("%lld",ans);

    return 0;
}
