#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 2011
#define INF 1000000000
#define long long long

long L,P,D,C,n,i,j,cost,add,lL,scad;
long dp[maxN],a[maxN];

int main()
{
    freopen("gaz.in","r",stdin);
    freopen("gaz.out","w",stdout);

    scanf("%lld %lld %lld %lld %lld %lld",&L,&P,&D,&C,&n,&a[1]);
    dp[1] = P;

    for(i=2;i<=n+1;i++){
        if(i!=n+1) scanf("%lld",&a[i]);
        dp[i] = INF;

        cost = add = 0; lL = L;
        for(j=i-1;j;j--){
            if(dp[i] > P+dp[j]+cost) dp[i] = P+dp[j]+cost;

            scad = min(lL,a[j]);
            lL -= scad;

            add += a[j] - scad;
            cost += add*C;
        }
    }

    dp[n+1] -= P;
    for(i=1;i<=n;i++) dp[n+1] += D*a[i];

    printf("%lld",dp[n+1]);

    return 0;
}
