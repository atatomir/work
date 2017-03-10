#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int n, i, x, y, z;
vector< pair<int, int> > list[maxN];
ll dp[maxN][2];
ll ans;

void dfs(int node, int root) {
    int gg;

    dp[node][0]++;

    for (auto to : list[node]) {
        if (to.first == root) continue;
        dfs(to.first, node);

        gg = to.second & 1;
        ans += dp[to.first][1 ^ gg] * dp[node][0];
        ans += dp[to.first][gg] * dp[node][1];
        dp[node][0] += dp[to.first][gg];
        dp[node][1] += dp[to.first][1 ^ gg];
    }

}

int main()
{
    freopen("plopi.in","r",stdin);
    freopen("plopi.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        list[x].pb(mp(y, z));
        list[y].pb(mp(x, z));
    }

    dfs(1, 0);
    printf("%lld", ans);


    return 0;
}
