#include <iostream>
#include <cstdio>

using namespace std;

long long n,m,p,t;

long long gcd(long long a,long long b){
    long long t;
    if(a<b) {t=a;a=b;b=t;}
    while(b){
        a %= b;
        t=a;a=b;b=t;
    }
    return a;
}

long long myPow(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1) ans = (ans * a)%p;
        b>>=1;
        a = (a*a)%p;
    }
    return ans;
}

int main()
{
    freopen("gcd.in","r",stdin);
    freopen("gcd.out","w",stdout);

    scanf("%lld",&t);
    for(;t;t--){
        scanf("%lld %lld %lld",&n,&m,&p);
        long long ans = myPow(2,gcd(n,m)) - 1;
        if(ans == -1) ans += p;
        printf("%lld\n",ans);
    }

    return 0;
}
