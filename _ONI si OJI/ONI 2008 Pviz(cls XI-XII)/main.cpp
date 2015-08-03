#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define mod 10007
#define maxN 2015
#define def 2003

int n,m,i,j;
int v[maxN];
int dp[maxN][maxN];
int ans;

int main()
{
    freopen("pviz.in","r",stdin);
    freopen("pviz.out","w",stdout);

    fordef(i,1,def){
        dp[i][0] = 1;
        fordef(j,1,i) dp[i][j] = (dp[i][j-1]*(i-j+1))%mod;
    }

    scanf("%d%d",&n,&m);
    fordef(i,1,m) scanf("%d",&v[i]);

    ans = 1;
    for(i=m-1;i>=0;i--){
        if(v[i+1]-v[i]==1) continue;
        ans *= dp[ n-v[i]-1 ][ v[i+1]-v[i]-1 ];
        ans %= mod;
    }

    printf("%d",ans);

    return 0;
}
