#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
#define mp make_pair
#define pb push_back
 
#define maxN 15
#define inf (1000000000)
 
int n,i,j,t;
int cost[maxN][maxN];
int dp[maxN][1<<maxN];
int bigMask;
 
int compute(int node,int state) {
    if (dp[node][state] != inf) return dp[node][state];
 
    if ( (state & (state - 1)) == 0) {
        dp[node][state] = 0;
        return 0;
    }
 
    vector<int> bits;
    bits.clear();
    for (int i = 0; i < n; i++)
        if ( (state & (1<<i)) && (i != node) )
            bits.pb(i);
 
    int limit = 1 << bits.size();
    for (int auxMask = 1; auxMask < limit; auxMask++) {
        int provMask = 0;
        for (int i = 0;i < bits.size(); i++)
            if ((auxMask & (1 << i)) != 0)
                provMask |= 1 << bits[i];
 
        for (int provNode = 0; provNode < n; provNode++) {
            if ( (provMask & (1 << provNode)) == 0 ) continue;
 
            dp[node][state] = min(dp[node][state],
                                  cost[node][provNode] + max(compute(provNode,provMask), compute(node,state-provMask)));
        }
    }
 
    return dp[node][state];
}
 
int main()
{
    freopen("cast.in","r",stdin);
    freopen("cast.out","w",stdout);
 
    for (scanf("%d",&t); t > 0; t--) {
        scanf("%d",&n);
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                scanf("%d",&cost[i][j]);
 
        bigMask = (1<<n)-1;
        for (int i = 0; i < n; i++)
            for (int mask = 0; mask <= bigMask; mask++)
                dp[i][mask] = inf;
 
        printf("%d\n", compute(0,bigMask) );
    }
 
 
    return 0;
}
