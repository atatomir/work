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
#define ll long long

#define maxN 5011
#define inf (1LL << 60)

int n, m, s, b, x, y, c, i, j, k;
vector< pair<int, int> > list[maxN], rev[maxN];
ll A[maxN], B[maxN];
priority_queue< pair<ll, int> > H;

ll v[maxN], sum[maxN];
ll dp[maxN][maxN];



void dijk(int node, vector< pair<int, int> > list[], ll dist[]) {
    int i;

    for (i = 1; i <= n; i++) dist[i] = inf;
    dist[node] = 0;
    while (!H.empty()) H.pop();
    H.push(mp(-0, node));

    while (!H.empty()) {
        auto act = H.top(); H.pop();
        act.first = -act.first;
        node = act.second;

        if (dist[act.second] != act.first) continue;
        for (auto to : list[node]) {
            if (dist[to.first] > dist[node] + to.second) {
                dist[to.first] = dist[node] + to.second;
                H.push(mp(-dist[to.first], to.first));
            }
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d%d", &n, &b, &s, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        rev[y].pb(mp(x, c));
    }

    dijk(b + 1, list, A);
    dijk(b + 1, rev, B);

    for (i = 1; i <= b; i++) v[i] = A[i] + B[i];
    sort(v + 1, v + b + 1);

    for (i = 1; i <= b; i++) sum[i] = sum[i - 1] + v[i], dp[1][i] = sum[i] * (i - 1);
    for (i = 2; i <= s; i++) {
        for (j = i; j <= b; j++) {
            dp[i][j] = inf;

            for (k = 1; i * k <= j; k++)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - k] + (k - 1) * (sum[j] - sum[j - k]));
        }
    }

    printf("%lld", dp[s][b]);


    return 0;
}
