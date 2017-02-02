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

int n, k, i, x, y;
vector<int> list[maxN];

pair<int, int> dp[maxN], up[maxN];
pair<int, int> le[maxN], ri[maxN];

pair<int, int> get_best(pair<int, int> a, pair<int, int> b) {
    if (a.second <= b.first) return a;
    if (b.second <= a.first) return b;
    return {min(a.first, b.first), max(a.first, b.first)};
}

void dfs(int node, int root) {
    dp[node] = {n + 11, n + 11};

    for (auto to : list[node]) {
        if (to == root) continue;

        dfs(to, node);
        dp[node] = get_best({dp[to].first + 1, dp[to].second + 1}, dp[node]);
    }

    if (dp[node].first == n + 11)
        dp[node].first = 0;
}

void dfs2(int node, int root) {
    int i;

    for (i = 0; i < list[node].size(); i++) {
        if (list[node][i] == root) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            break;
        }
    }

    for (i = 0; i < list[node].size(); i++) {
        le[i] = ri[i] = {dp[ list[node][i] ].first + 2, dp[ list[node][i] ].second + 2};
        if (i != 0)
            le[i] = get_best(le[i - 1], le[i]);
    }

    for (i = list[node].size() - 2; i >= 0; i--)
        ri[i] = get_best(ri[i], ri[i + 1]);

    for (i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        up[to] = {up[node].first + 1, up[node].second + 1};
        if (i > 0) up[to] = get_best(up[to], le[i - 1]);
        if (i + 1 < list[node].size()) up[to] = get_best(up[to], ri[i + 1]);
    }

    for (auto to : list[node])
        dfs2(to, node);
}

int main()
{
    freopen("statiuni.in","r",stdin);
    freopen("statiuni.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    if (n == 1) {
        printf("0");
        return 0;
    }

    if (n == 2) {
        if (k == 0)
            printf("0");
        else
            printf("2");
        return 0;
    }

    int R = 1;
    while (list[R].size() == 1) R++;

    up[R] = {k + 11, k + 11};
    dfs(R, 0);
    dfs2(R, 0);

    int ans = 0;
    for (i = 1; i <= n; i++)
        if (get_best(dp[i], up[i]).second <= k)
            ans++;

    printf("%d", ans);


    return 0;
}
