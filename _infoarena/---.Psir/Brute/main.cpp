#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 2015

long long mod = 1LL<<32;
int n,i,j,k;
long long dp[maxN][maxN];
long long v[maxN];
long long ans;

void keep(long long who){
    while (who<0) who += mod;
    while (who>=mod) who -= mod;
}

int main()
{
    freopen("psir.in","r",stdin);
    freopen("psir.out","w",stdout);

    scanf("%d",&n);
    for (i=1;i<=n;i++) scanf("%lld",&v[i]);

    for (k=2;k<=n;k++){
        for (j=k-1;j>0;j--){
            dp[j][k]=1;

            for (i=j-1;i>0;i--){
                if ( (v[k]-v[j])*(v[k]-v[i])>=0LL ) continue;
                dp[j][k] += dp[i][j];

                keep(dp[j][k]);
            }
        }
    }

    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            { ans += dp[i][j]; keep(ans); }

    printf("%lld",ans);

    return 0;
}
