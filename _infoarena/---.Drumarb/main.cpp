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

int n, q, i, x, y, paths, a, b, c, d, qq;
vector<int> list[maxN];
int cnt[maxN], lvl[maxN];
int on_path[maxN];
int top[maxN];

vector<int> act;
int last[maxN][2];
pair<int, int> intr[maxN][2];

int ans;



void dfs(int node, int root) {
    cnt[node] = 1;

    for (int to : list[node]) {
        if (to == root) continue;
        lvl[to] = lvl[node] + 1;
        dfs(to, node);
        cnt[node] += cnt[to];
    }

    if (cnt[node] == 1) {
        on_path[node] = ++paths;
    } else {
        pair<int, int> best = mp(0, 0);

        for (int to : list[node])
            if (to != root)
                best = max(best, mp(cnt[to], to));

        on_path[node] = on_path[best.second];
    }

    for (int to : list[node])
        if (to != root)
            top[ on_path[to] ] = node;
}

void upd(int path, int lv1, int lv2, int id) {
    if (last[path][id] != qq)
        intr[path][id] = mp(n + 3, -1);
    last[path][id] = qq;

    intr[path][id].first = min(intr[path][id].first, min(lv1, lv2));
    intr[path][id].second = max(intr[path][id].second, max(lv1, lv2));
}

void put_intervals(int a, int b, int id) {
    act.pb(on_path[a]);
    act.pb(on_path[b]);

    while (on_path[a] != on_path[b]) {
        if ( lvl[top[on_path[a]]] > lvl[top[on_path[b]]] ) swap(a, b);
        upd(on_path[b], lvl[top[on_path[b]]] + 1, lvl[b], id);
        b = top[on_path[b]];

        act.pb(on_path[b]);
    }

    int lca = (lvl[a] < lvl[b] ? a : b);
    upd(on_path[a], lvl[lca], lvl[a], id);
    upd(on_path[b], lvl[lca], lvl[b], id);
}

int get_intersection(int wh) {
    if (last[wh][0] != qq || last[wh][1] != qq) return 0;

    int l = max(intr[wh][0].first, intr[wh][1].first);
    int r = min(intr[wh][0].second, intr[wh][1].second);

    return max(0, r - l + 1);
}

int main()
{
    freopen("drumarb.in","r",stdin);
    freopen("drumarb.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    lvl[1] = 1;
    dfs(1, 0);
    top[on_path[1]] = 0;

    for (qq = 1; qq <= q; qq++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);

        act.clear();
        put_intervals(a, b, 0);
        put_intervals(c, d, 1);

        sort(act.begin(), act.end());
        act.resize(unique(act.begin(), act.end()) - act.begin());

        ans = 0;
        for (auto e : act)
            ans += get_intersection(e);

        printf("%d\n", ans);
    }


    return 0;
}
