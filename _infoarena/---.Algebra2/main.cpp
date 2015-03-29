#include <iostream>
#include <cstdio>

using namespace std;

#define mod 1000000009

long long n,a,b;

long long myPow(long long a,long long b){
    long long Ans=1;
    while(b){
        if(b&1) Ans = (Ans*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return Ans;
}

int main()
{
    freopen("algebra2.in","r",stdin);
    freopen("algebra2.out","w",stdout);

    cin >> n;

    a=n; if(!(a&1)) a>>=1;
    b=n+1; if(!(b&1)) b>>=1;

    n %= mod;
    n = myPow(n,a);
    n = myPow(n,b);

    cout << n;

    return 0;
}
