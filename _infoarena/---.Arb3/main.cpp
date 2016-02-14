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
#define pii pair<ll, int>

int n, q, i, x;
vector<int> list[maxN];
ll v[maxN];
vector< pii > Q[maxN];
ll ans[maxN];
ll y;

ll sum[maxN];

bool cmp(int x, int y) {
    return v[x] > v[y];
}

int binary(int node, ll x) {
    int ans = -1;

    for (int step = 1 << 20; step; step >>= 1) {
        if (ans + step < list[node].size())
            if (v[ list[node][ans + step] ] > x)
                ans += step;
    }

    return ans;
}

void dfs(int node) {
    int i;
    for (auto to : list[node]) dfs(to);
    if (list[node].empty()) return;

    sum[0] = v[ list[node][0] ];
    for (i = 1; i < list[node].size(); i++)
        sum[i] = sum[i - 1] + v[ list[node][i] ];

    for (i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        for (auto q_act : Q[to]) {
            int pos = binary(node, v[to] - q_act.first);

            ll ans = 0;
            if (pos > 0) ans = sum[pos - 1] - pos * v[ list[node][pos] ];

            ll dif = v[ list[node][pos] ] - (v[to] - q_act.first);
            ans += (dif - 1) * (pos + 1);
            ans += i + 1;

            Q[node].pb(mp(ans, q_act.second));
        }
    }
}

int main()
{
    freopen("arb3.in","r",stdin);
    freopen("arb3.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        list[x].pb(i);
    }

    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);
    for (i = 1; i <= n; i++) sort(list[i].begin(), list[i].end(), cmp);

    for (i = 1; i <= q; i++) {
        scanf("%d%lld", &x, &y);

        if (y == 0) {
            ans[i] = 0;
            continue;
        }

        Q[x].pb(mp(y, i));
    }

    dfs(1);
    for (auto q_act : Q[1])
        ans[ q_act.second ] = q_act.first;

    for (i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}
