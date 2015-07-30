#include <iostream>
#include <cstdio>

using namespace std;

long def,q,t,ans,n;

long cnt(long x){
    long ans = 0;
    while(x){
        x >>= 1;
        ans += x;
    }
    return ans;
}

int main()
{
    freopen("bits.in","r",stdin);
    freopen("bits.out","w",stdout);

    scanf("%ld %ld",&def,&q);
    for(;q;q--){
        scanf("%ld %ld",&n,&t); n=def-n;
        if(n==t)
            ans = 1;
        else if(n>t)
            ans = 0;
        else{
            ans = cnt(t) - cnt(n) - cnt(t-n);
            if(ans==0) ans = 1; else ans=0;
        }
        printf("%ld\n",ans);
    }

    return 0;
}
