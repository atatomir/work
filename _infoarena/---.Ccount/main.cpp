#include <iostream>
#include <cstdio>

using namespace std;

#define mod 9007
#define maxN 100011

long n,k,i,x;
long dp[maxN],ans;
bool known[maxN];

int main()
{
    freopen("ccount.in","r",stdin);
    freopen("ccount.out","w",stdout);

    scanf("%ld%ld",&n,&k);
    for(i=1;i<=k;i++) {
        scanf("%ld",&x);
        known[x]=true;
    }

    if(known[n]) printf("0"); else {
        dp[n]=1;
        for(i=n;i>2;i--){
            if(known[i]) continue;
            dp[i-1] = (dp[i]+dp[i-1])%mod;
            dp[i-2] = (dp[i]+dp[i-2])%mod;
            ans = (ans+dp[i])%mod;
        }
    }
    printf("%ld",ans);

    return 0;
}
