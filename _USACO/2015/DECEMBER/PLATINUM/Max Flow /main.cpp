#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 50011
#define maxLog 21

int n, m, i, x, y, ans;
vector<int> list[maxN];
int lvl[maxN];
int dad[maxLog][maxN];
bool us[maxN];

int addRoute[maxN];
int delRoute[maxN];
int fast_del[maxN];
int dp[maxN];

void dfs(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (us[to]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        lvl[to] = lvl[node] + 1;
        dad[0][to] = node;
        dfs(to);
    }
}

int goUp(int x, int how) {
    for (int i = 0; how > 0; i++, how >>= 1)
        if (how & 1)
            x = dad[i][x];
    return x;
}

int getLca(int x, int y) {
    y = goUp(y, lvl[y] - lvl[x]);

    if (x == y)
        return x;

    for (int actLog = maxLog - 1; actLog >= 0; actLog--) {
        if (dad[actLog][x] != dad[actLog][y]) {
            x = dad[actLog][x];
            y = dad[actLog][y];
        }
    }

    return dad[0][x];
}

void dfs_solve(int node) {
    dp[node] = addRoute[node] + fast_del[node];

    for (auto to : list[node]) {
        dfs_solve(to);
        dp[node] += dp[to];
        dp[node] += delRoute[to];
    }
}

int main()
{
    freopen("maxflow.in","r",stdin);
    freopen("maxflow.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    lvl[1] = 1;
    dfs(1);

    for (int actLog = 1; actLog < maxLog; actLog++)
        for (i = 1; i <= n; i++)
            dad[actLog][i] = dad[ actLog - 1 ][ dad[actLog - 1][i] ];

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);

        if (lvl[x] > lvl[y])
            swap(x, y);

        int lca = getLca(x, y);

        if (lca == x) {
            addRoute[y]++;
            delRoute[x]--;
        } else {
            addRoute[x]++;
            addRoute[y]++;
            delRoute[lca]--;
            fast_del[lca]--;
        }
    }

    dfs_solve(1);
    for (i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    printf("%d", ans);

    return 0;
}
