#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1055
#define def 120
#define maxT def + 11
#define inf 2000000000
#define pii pair<int, pair<int, int> >
#define spii pair<int, int>
#define comp 1000LL
#define comp2 10000000LL

int n, m, p, i, x, y, j, k;
vector<int> list[maxN];
int pay[maxN];

int dp[maxN][maxT];
bool deny[maxN][maxT];
int way[11];

unordered_map< long long, bool > deny_edge;

struct cmp {
    bool operator()(const spii a, const spii b)const {
        return a.first > b.first;
    }
};

priority_queue< spii, vector< spii >, cmp> H;

int main()
{
    freopen("patrol.in","r",stdin);
    freopen("patrol.out","w",stdout);

    scanf("%d%d%d", &n, &m, &p);
    for (i = 1; i <= n; i++)
        scanf("%d", &pay[i]);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    deny_edge.clear();
    for (i = 1; i <= p; i++) {
        scanf("%d", &k);
        for (j = 1; j <= k; j++) scanf("%d", &way[j]);

        int id = 1;
        int sign = +1;
        for (int _t = 1; _t <= def; _t++) {
            int _next = id + sign;
            if (_next == k + 1) {
                sign = -1;
                _next -= 2;
            }
            if (_next == 0) {
                sign = 1;
                _next = 2;
            }

            deny[ way[id] ][_t] = true;
            deny_edge[1LL * _t + comp * way[id] + comp2 * way[_next]] = true;
            id = _next;
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= def; j++)
            dp[i][j] = inf;

    while (!H.empty()) H.pop();
    H.push(mp(pay[1],1 * comp + 1));

    while (!H.empty()) {
        auto act = H.top(); H.pop();
        int cost = act.first;
        int node = act.second / comp;
        int time = act.second % comp;

        if (dp[node][time] < cost) continue;
        dp[node][time] = cost;

        int next_time = time + 1;
        if (next_time > def) next_time -= def;

        for (auto to : list[node]) {
            if (deny[to][next_time]) continue;
            if (deny_edge[1LL * time + comp * to + comp2 * node]) continue;
            if (dp[to][next_time] > cost + pay[to]) {
                H.push(mp(cost + pay[to], to * comp + next_time));
                dp[to][next_time] = cost + pay[to];
            }
        }
    }

    int ans = inf;
    for (i = 1; i <= def; i++)
        ans = min(ans, dp[n][i]);

    printf("%d", ans);

    return 0;
}
