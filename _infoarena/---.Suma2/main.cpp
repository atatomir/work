#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 200011

long n,i,x;
long dp[2];

int main()
{
    freopen("suma2.in","r",stdin);
    freopen("suma2.out","w",stdout);

    scanf("%ld",&n);

    scanf("%ld",&x);
    dp[1] = x; if(dp[1]<0) dp[1]=0;
    for(i=2;i<=n;i++) {
        scanf("%ld",&x);
        long ans = max(dp[1],dp[0]+x);
        dp[0]=dp[1]; dp[1]=ans;
    }

    printf("%ld",dp[1]);

    return 0;
}
