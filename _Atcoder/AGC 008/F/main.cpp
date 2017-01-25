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

#define maxN 200011

int n, i, x, y, C;
vector<int> list[maxN];
char tp[maxN];

int down[maxN], up[maxN], dist[maxN], high[maxN], low[maxN], cnt[maxN];
vector< pair<int, int> > aux;
vector<int> loc;
ll ans;

void dfs(int node, int root) {
    down[node] = 0;

    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);
        down[node] = max(down[node], down[to] + 1);
    }
}

void dfs2(int node, int root) {
    aux.clear();
    loc.clear();

    for (auto e : list[node])
        if (e != root)
        loc.pb(down[e] + 1);
    loc.pb(up[node]);

    if(loc.size() == 1) loc.pb(0);
    sort(loc.begin(), loc.end());
    high[node] = min(loc.back() - 1, loc[loc.size() - 2] + 1);



    dist[node] = max(down[node], up[node]);

    for (auto to : list[node]) {
        if (to == root) continue;
        aux.pb(mp(down[to], to));
    }

    if (aux.empty()) return;
    if (aux.size() == 1) {
        up[aux[0].second] = up[node] + 1;
        dfs2(aux[0].second, node);
        return;
    }

    sort(aux.begin(), aux.end());
    reverse(aux.begin(), aux.end());

    up[aux[0].second] = max(up[node] + 1, aux[1].first + 2);
    for (int i = 1; i < aux.size(); i++)
        up[aux[i].second] = max(up[node] + 1, aux[0].first + 2);

    for (auto e : list[node])
        if (e != root)
            dfs2(e, node);
}

void solve(int node, int root) {
    down[node] = 0;
    cnt[node] = tp[node] - '0';

    low[node] = 1 << 30;
    if (tp[node] == '1')
        low[node] = 0;

    for (auto to : list[node]) {
        if (to == root) continue;
        solve(to, node);
        down[node] = max(down[node], down[to] + 1);
        cnt[node] += cnt[to];

        if (cnt[to])
            low[node] = min(low[node], down[to] + 1);
    }

    if (low[node] <= high[node])
        ans += 1LL * (high[node] - low[node] + 1);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    scanf("\n%s", tp + 1);
    dfs(1, 0);
    dfs2(1, 0);

    C = min_element(dist + 1, dist + n + 1) - dist;
    solve(C, 0);

    if (cnt[C] == 0) {
        printf("0");
        return 0;
    }

    printf("%lld", ans + 1);

    return 0;
}
