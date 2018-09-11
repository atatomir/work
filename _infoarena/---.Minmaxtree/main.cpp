#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define lSon (node << 1)
#define rSon (lSon | 1)

const int maxN = 70011;
const int low = -1;
const int high = 1000000001;

struct aint {
    vector<int> lo, hi;

    int size() {
        return (lo.size() - 11) / 4;
    }

    void init(int sz) {
        lo = vector<int>(sz * 4 + 11, low);
        hi = vector<int>(sz * 4 + 11, high);
    }

    void upd(int node, int l, int r, int qL, int qR, pair<int, int> v) {
        if (qL <= l && r <= qR) {
            lo[node] = max(lo[node], v.first);
            hi[node] = min(hi[node], v.second);
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid) upd(lSon, l, mid, qL, qR, v);
        if (qR > mid) upd(rSon, mid + 1, r, qL, qR, v);
    }

    void get(int node, int l, int r, pair<int, int> up, pair<int, int>* sol) {
        up.first = max(up.first, lo[node]);
        up.second = min(up.second, hi[node]);

        if (l == r) {
            sol[l - 1] = up;
            return;
        }
        int mid = (l + r) >> 1;
        get(lSon, l, mid, up, sol);
        get(rSon, mid + 1, r, up, sol);
    }
};

int n, m, i, x, y, z;
vector<int> list[maxN];
char c;

int down[maxN], lvl[maxN];;
vector< vector<int> > paths;
vector<aint> data;
int pos[maxN], id[maxN], up[maxN];
pair<int, int> aux[maxN];
pair<int, int> sol[maxN];
map<int, int> zz;

int nodes_left, nodes_right;
vector<int> adj[maxN];
int l[maxN], r[maxN], rez[maxN];
bool us[maxN];

int v[maxN];

void dfs(int node, int root) {
    pair<int, int> best = mp(0, 0);
    down[node] = 1;

    for (auto to : list[node]) {
        if (to == root) continue;
        lvl[to] = lvl[node] + 1;
        dfs(to, node);
        down[node] += down[to];
        best = max(best, mp(down[to], to));
    }

    if (best.first == 0) {
        paths.pb({node});
        id[node] = paths.size() - 1;
        pos[node] = 0;
        return;
    }

    id[node] = id[best.second];
    paths[id[node]].pb(node);
    pos[node] = paths[id[node]].size() - 1;

    for (auto to : list[node])
        if (to != root && id[to] != id[node])
            up[id[to]] = node;
}

void build_heavy() {
    int i, j;

    lvl[1] = 1;
    dfs(1, 0);
    data.resize(paths.size());

    for (i = 0; i < paths.size(); i++)
        data[i].init(paths[i].size());
}

void add_query(int x, int y, pair<int, int> v) {
    while (id[x] != id[y]) {
        if (lvl[up[id[x]]] < lvl[up[id[y]]])
            swap(x, y);

        data[id[x]].upd(1, 1, data[id[x]].size(), pos[x] + 1, data[id[x]].size(), v);
        x = up[id[x]];
    }

    if (x == y) return;
    if (lvl[x] < lvl[y]) swap(x, y);
    data[id[x]].upd(1, 1, data[id[x]].size(), pos[x] + 1, pos[y], v);
}

void get_vals() {
    int i, j;

    for (i = 0; i < paths.size(); i++) {
        data[i].get(1, 1, data[i].size(), {low, high}, aux);
        for (j = 0; j < paths[i].size(); j++)
            sol[paths[i][j]] = aux[j];
    }

}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (auto to : adj[node]) {
        if (r[to] == 0) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    for (auto to : adj[node]) {
        if (pairUp(r[to])) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    return false;
}

void cuplaj() {
    bool any = true;

    while (any) {
        any = false;
        memset(us, 0, sizeof(us));

        for (i = 1; i <= nodes_left; i++)
            if (l[i] == 0)
                any |= pairUp(i);
    }
}

void dfs2(int node, int root) {
    for (auto to : list[node]) {
        if (to == root) continue;
        printf("%d %d %d\n", node, to, v[to]);
        dfs2(to, node);
    }
}

int main()
{
    freopen("minmaxtree.in","r",stdin);
    freopen("minmaxtree.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    build_heavy();
    scanf("%d\n", &m);
    for (i = 1; i <= m; i++) {
        scanf("%c%d%d%d\n", &c, &x, &y, &z);

        pair<int, int> act = mp(low, high);
        if (c == 'm')
            act.first = z;
        else
            act.second = z;

        add_query(x, y, act);
        zz[z] = i;
        rez[i] = z;
    }

    get_vals();

    nodes_left = n;
    nodes_right = m;
    for (i = 1; i <= n; i++) {
        if (zz[sol[i].first] != 0) {
            adj[i].pb(zz[sol[i].first]);
        }
        if (zz[sol[i].second] != 0) {
            adj[i].pb(zz[sol[i].second]);
        }
    }

    cuplaj();
    for (i = 1; i <= n; i++) {
        if (l[i] == 0) continue;
        v[i] = rez[l[i]];
    }

    for (i = 1; i <= n; i++)
        if (v[i] == 0)
            v[i] = max(0, sol[i].first);

    dfs2(1, 0);


    return 0;
}
