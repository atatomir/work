#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 511

int n,i,j;
int v[maxN];
long long dp[maxN][maxN];

long long solve(int l,int r){
    if(dp[l][r]!=-1) return dp[l][r];
    if(r-l<=1){
        if(l==r) dp[l][r]=0; else
        dp[l][r] = 1LL*v[l]*v[l+1]*v[l+2];
        return dp[l][r];
    }

    dp[l][r] = (1LL<<60);
    for(int k=l;k<r;k++) dp[l][r] = min(dp[l][r], solve(l,k)+solve(k+1,r)+  1LL*v[l]*v[k+1]*v[r+1] );
    return dp[l][r];
}

int main()
{
    freopen("podm.in","r",stdin);
    freopen("podm.out","w",stdout);

    scanf("%d",&n);
    for(i=1;i<=n+1;i++) scanf("%d",&v[i]);

    for(i=1;i<=n;i++)
        for(j=i;j<=n;j++)
            dp[i][j] = -1;

    printf("%lld",solve(1,n));

    return 0;
}
