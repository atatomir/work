#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define inf 1000000000
#define maxN 2017
#define maxK 16


int n, m, i, j, k, x, y, d, limit, to;
vector<int> wh;
vector< pair<int, int> > list[maxN];

priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > H;
int main_dist[maxN];
int dist[maxK][maxN];

ll dp[1 << maxK][maxK];

void dijk(int node, int *data) {
    int i, val;

    for (i = 1; i <= n; i++) data[i] = inf;

    data[node] = 0;
    H.push(mp(data[node], node));

    while (!H.empty()) {
        node = H.top().second;
        val = H.top().first;

        H.pop();
        if (data[node] != val) continue;

        for (auto to : list[node]) {
            if (data[node] + to.second < data[to.first]) {
                data[to.first] = data[node] + to.second;
                H.push(mp(data[to.first], to.first));
            }
        }
    }
}

int main()
{
    freopen("ubuntzei.in","r",stdin);
    freopen("ubuntzei.out","w",stdout);

    scanf("%d%d", &n, &m);
    scanf("%d", &k);
    for (i = 1; i <= k; i++) scanf("%d", &x), wh.pb(x);

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &d);
        list[x].pb(mp(y, d));
        list[y].pb(mp(x, d));
    }

    dijk(1, main_dist);
    for (i = 0; i < k; i++) dijk(wh[i], dist[i]);

    if (k == 0) {
        printf("%d", main_dist[n]);
        return 0;
    }

    limit = (1 << k);
    for (i = 0; i < limit; i++)
        for (j = 0; j < k; j++)
            dp[i][j] = 1LL << 60;

    for (i = 0; i < k; i++)
        dp[1 << i][i] = main_dist[wh[i]];

    for (int conf = 1; conf < limit; conf++) {
        for (int node = 0; node < k; node++) {
            if ((conf & (1 << node)) == 0) continue;

            for (to = 0; to < k; to++) {
                if (conf & (1 << to)) continue;

                dp[conf | (1 << to)][to] = min(dp[conf | (1 << to)][to], dp[conf][node] + dist[node][wh[to]]);
            }
        }
    }

    ll ans = 1LL << 60;
    for (i = 0; i < k; i++)
        ans = min(ans, dp[limit - 1][i] + dist[i][n]);

    printf("%lld", ans);


    return 0;
}
