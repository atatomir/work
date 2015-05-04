#include <iostream>
#include <cstdio>

using namespace std;

#define mod 666013

long long n,k,w;
long long cN,cK;
long long sup,sub;
long long i;

long long myPow(long long a,long b){
    long long ans = 1;
    while(b){
        if(b&1) ans = (ans*a)%mod;
        b >>= 1;
        a = (a*a)%mod;
    }
    return ans;
}

int main()
{
    freopen("nmult.in","r",stdin);
    freopen("nmult.out","w",stdout);

    scanf("%lld %lld %lld",&n,&k,&w);
    n -= (k-1)*w+1;

    if(n<0) printf("0"); else{
        cN = n+k; cK = k;

        sup =1;sub = 1;

        if(cK > cN-cK){
            for(i=cK+1;i<=cN;i++) sup = (sup*i)%mod;
            for(i=2;i<=cN-cK;i++) sub = (sub*i)%mod;
        }else {
            for(i=cN-cK+1;i<=cN;i++) sup = (sup*i)%mod;
            for(i=2;i<=cK;i++) sub = (sub*i)%mod;
        }

        sub = myPow(sub,mod-2);

        printf("%lld", (sup*sub)%mod );
    }


    return 0;
}
