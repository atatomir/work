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

#define lSon (node << 1)
#define rSon (lSon | 1)

const int maxN = 50011;
const int inf = 1000000023;

struct aint {
    int dim;
    vector<int> data;

    void init(int _dim) {
        dim = _dim;
        data = vector<int>(dim * 4 + 11, inf);
    }

    void upd(int node, int l, int r, int qL, int qR, int v) {
        if (qL <= l && r <= qR) {
            data[node] = min(data[node], v);
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid) upd(lSon, l, mid, qL, qR, v);
        if (qR > mid) upd(rSon, mid + 1, r, qL, qR, v);
    }

    int que(int node, int l, int r, int pos) {
        if (l == r) return data[node];
        int mid = (l + r) >> 1;
        if (pos <= mid) return min(data[node], que(lSon, l, mid, pos));
        return min(data[node], que(rSon, mid + 1, r, pos));
    }
};

int n, m, i, x, y, z;
vector< pair<int, int> > list[maxN];

int id[maxN], daddy_edge[maxN], pos[maxN], down[maxN], lvl[maxN], go_to[maxN];
vector< vector<int> > paths;
vector<aint> work;

int ans[maxN];

void dfs(int node, int root) {
    int i;

    down[node] = 1;
    for (i = 0; i < list[node].size(); i++) {
        if (list[node][i].first == root) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--; continue;
        }

        daddy_edge[list[node][i].first] = list[node][i].second;
        lvl[list[node][i].first] = lvl[node] + 1;
        dfs(list[node][i].first, node);

        down[node] += down[list[node][i].first];
        if (down[list[node][i].first] > down[list[node][0].first])
            swap(list[node][i], list[node][0]);

        go_to[id[list[node][i].first]] = node;
    }

    if (list[node].empty()) {
        paths.pb({node});
        pos[node] = 1;
        id[node] = paths.size() - 1;
        return;
    }

    id[node] = id[list[node][0].first];
    paths[id[node]].pb(node);
    pos[node] = paths[id[node]].size();
}

void update() {
    while (id[x] != id[y]) {
        int l1 = lvl[paths[id[x]].back()];
        int l2 = lvl[paths[id[y]].back()];

        if (l1 < l2) {
            swap(x, y);
            swap(l1, l2);
        }

        int l = id[x];
        work[l].upd(1, 1, work[l].dim, pos[x], work[l].dim, z);
        x = go_to[l];
    }

    if (x == y) return;
    if (lvl[x] < lvl[y]) swap(x, y);

    int l = id[x];
    work[l].upd(1, 1, work[l].dim, pos[x], pos[y] - 1, z);
}

int main()
{
    freopen("disrupt.in","r",stdin);
    freopen("disrupt.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(mp(y, i));
        list[y].pb(mp(x, i));
    }

    dfs(1, 0);
    for (i = 0; i < paths.size(); i++) {
        work.emplace_back();
        work[i].init(paths[i].size());
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        update();
    }

    for (i = 1; i <= n; i++) {
        ans[daddy_edge[i]] = work[id[i]].que(1, 1, work[id[i]].dim, pos[i]);
    }

    for (i = 1; i < n; i++) {
        if (ans[i] == inf)
            printf("-1\n");
        else
            printf("%d\n", ans[i]);
    }


    return 0;
}
