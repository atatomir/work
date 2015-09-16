#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, x, y, cost, k, R;
vector< pair<int, int> > list[maxN];
long long dp[maxN][2]; //! full/half
bool us[maxN];

void dfs(int node, long long riremito) {
    us[node] = true;
    if (node != R && list[node].size() == 1) {
        dp[node][0] = dp[node][1] = 0;
        return;
    }

    dp[node][0] = dp[node][1] = 0;
    for (auto neigh : list[node]) {
        int dir = neigh.first;
        long long cc  = neigh.second;

        if (us[dir]) continue;
        dfs(dir, riremito + cc);

        long long add_now = min(2 * cc + dp[dir][0], cc + dp[dir][1] + riremito);
        dp[node][0] += add_now;
        dp[node][1] = min(dp[node][1], cc + dp[dir][1] - add_now);
    }

    dp[node][1] += dp[node][0];
}

int main()
{
    freopen("riremito.in","r",stdin);
    freopen("riremito.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &cost);
        list[x].pb(mp(y, cost));
        list[y].pb(mp(x, cost));
    }

    for (scanf("%d", &k); k > 0; k--) {
        scanf("%d", &R);
        memset(dp, 0, sizeof(dp));
        memset(us, 0, sizeof(us));

        dfs(R, 0);
        printf("%lld\n", dp[R][1]);
    }

    return 0;
}
