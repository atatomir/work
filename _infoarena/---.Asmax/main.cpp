#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 16100

long n,i,x,y;
long val[maxN],dp[maxN];
vector<long> list[maxN];
long ans=-1000000000;
bool vis[maxN];

void dfs(long nod){
    vis[nod] = true;
    for(long i=0;i<list[nod].size();i++){
        if(!vis[list[nod][i]]) dfs(list[nod][i]); else continue;
        if(dp[list[nod][i]] > 0) dp[nod]+= dp[list[nod][i]];
    }
    dp[nod] += val[nod];
    ans = max(ans,dp[nod]);
}

int main()
{
    freopen("asmax.in","r",stdin);
    freopen("asmax.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&val[i]);
    for(i=1;i<n;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    dfs(1);
    printf("%ld",ans);
    return 0;
}
