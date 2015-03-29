#include <iostream>
#include <cstdio>

using namespace std;

#define mod 9967

long n,d,i;
long ans[1024],a[1024];

void multip(long *a,long *b){
    long c[1024],i,j,dest;
    for(i=0;i<d;i++) c[i] = 0;
    for(i=0;i<d;i++){
        for(j=0;j<d;j++){
            dest = i+j; if(dest>=d) dest-=d;
            c[dest] = c[dest] + a[i]*b[j];
            if(c[dest] >=mod)
            if(c[dest] >= 2*mod) c[dest]%=mod; else c[dest]-=mod;
        }
    }
    for(i=0;i<d;i++) a[i] = c[i];
}

int main()
{
    freopen("cuvinte2.in","r",stdin);
    freopen("cuvinte2.out","w",stdout);

    scanf("%ld%ld",&n,&d);

    ans[0] = 1;
    for(i=0;i<26;i++)
        a[i%d]++;

    while(n){
        if(n&1) multip(ans,a);
        n >>= 1;
        multip(a,a);
    }

    printf("%ld",ans[0]);

    return 0;
}
