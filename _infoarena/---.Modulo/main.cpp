#include <iostream>
#include <cstdio>

using namespace std;

long long a,b,mod;
long long ans=1;

int main()
{
    freopen("modulo.in","r",stdin);
    freopen("modulo.out","w",stdout);

    scanf("%lld %lld %lld",&a,&b,&mod);
    a%= mod;

    while(b){
        if(b&1) ans = (ans*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    printf("%lld",ans);

    return 0;
}
