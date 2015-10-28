#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 55
#define maxK 1024
#define inf 2000000000

struct Edge {
    int to, time, pay;

    Edge() {}
    Edge(int _to, int _time, int _pay) {
        to = _to;
        time = _time;
        pay = _pay;
    }
};

int n, k, i, m, x, y, _t, _w;
vector<Edge> list[maxN];
bool friendly[maxN];

int dp[maxN][maxK];
queue< pair<int, int> > Q;
bool inQueue[maxN][maxK];

int check(int W) {
    int i, j;

    for (i = 1; i <= n; i++)
        for (j = 0; j <= W; j++)
            dp[i][j] = inf;
    while (!Q.empty()) Q.pop();
    memset(inQueue, 0, sizeof(inQueue));

    dp[1][W] = 0;
    Q.push(mp(1, W));
    inQueue[1][W] = true;

    while (!Q.empty()) {
        auto state = Q.front(); Q.pop();
        int node = state.first;
        int energy = state.second;

        inQueue[node][energy] = false;
        for (auto e : list[node]) {
            if (energy - e.pay < 0) continue;

            int destEnergy = energy - e.pay;
            if (friendly[e.to]) destEnergy = W;

            if (dp[e.to][destEnergy] <= dp[node][energy] + e.time) continue;

            dp[e.to][destEnergy] = dp[node][energy] + e.time;
            if (!inQueue[e.to][destEnergy]) {
                inQueue[e.to][destEnergy] = true;
                Q.push(mp(e.to, destEnergy));

                //cerr << "add " << e.to << ' ' << destEnergy << ' ' << dp[e.to][destEnergy] << '\n';
            }
        }
    }

    int ans = inf;
    for (i = 0; i <= W; i++) ans = min(ans, dp[n][i]);
    return ans;
}

int main()
{
    freopen("lanterna.in","r",stdin);
    freopen("lanterna.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (x == 1) friendly[i] = true;
    }

    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &x, &y, &_t, &_w);
        list[x].pb(Edge(y, _t, _w));
        list[y].pb(Edge(x, _t, _w));
    }

    int limit = check(k);

    int ans = -1;
    for (int step = 1 << 12; step > 0; step >>= 1) {
        if (ans + step > k) continue;
        if (check(ans + step) > limit)
            ans += step;
    }

    printf("%d %d", limit, ans + 1);

    return 0;
}
