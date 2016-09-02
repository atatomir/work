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

template<typename T>
struct rmq {
    int dim, i, j;
    vector<int> fast_log;
    vector< vector<T> > data;

    void init(int _dim, vector<T> &base) {
        dim = _dim;

        fast_log.resize(dim + 3);
        fast_log[1] = 0;
        for (i = 2; i <= dim; i++) fast_log[i] = fast_log[i / 2] + 1;

        data = vector< vector<T> >(fast_log[dim] + 2, vector<T>(dim + 3));
        data[0] = base;

        for (i = 1; i <= fast_log[dim]; i++) {
            int sz = (1 << i);
            int sm_sz = sz >> 1;

            for (j = 1; j + sz - 1 <= dim; j++)
                data[i][j] = min(data[i - 1][j], data[i - 1][j + sm_sz]);
        }
    }

    T query(int l, int r) {
        int sz = r - l + 1;
        int llog = fast_log[sz];

        return min(data[llog][l], data[llog][r - (1 << llog) + 1]);
    }
};

struct elem {
    int lvl, x, y;

    bool operator<(const elem& who)const {
        return lvl < who.lvl;
    }
};


int n, k, i, x, y;
vector<int> list[maxN], wh[maxN];
int col[maxN];

int lvl[maxN];
int cnt;
int start[maxN];
vector< pair<int, int> > ord;
rmq< pair<int, int> > RMQ;

vector< elem > aux;
int dad[maxN];
int how_many[maxN];

ll ans;

void dfs(int node) {
    start[node] = ++cnt;
    ord.pb(mp(lvl[node], node));

    wh[col[node]].pb(node);

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (lvl[to]) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--;
            continue;
        }

        lvl[to] = lvl[node] + 1;
        dfs(to);

        cnt++;
        ord.pb(mp(lvl[node], node));
    }
}

int get_lca(int x, int y) {
    return RMQ.query(min(start[x], start[y]), max(start[x], start[y])).second;
}

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;

    dad[y] = x;
    how_many[x] += how_many[y];

    return true;
}

void solve_color(int cc) {
    int i;

    if (wh[cc].size() < 2) return;

    for (auto e : wh[cc])
        ans += 1LL * lvl[e] * (wh[cc].size() - 1);

    aux.clear();
    for (i = 1; i < wh[cc].size(); i++)
        aux.pb({lvl[get_lca(wh[cc][i - 1], wh[cc][i])], wh[cc][i - 1], wh[cc][i]});

    sort(aux.begin(), aux.end());
    reverse(aux.begin(), aux.end());

    for (auto e : aux) {
        ans -= 2LL * e.lvl * how_many[Find(e.x)] * how_many[Find(e.y)];
        Merge(e.x, e.y);
    }
}



int main()
{
    freopen("kdist.in","r",stdin);
    freopen("kdist.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    for (i = 1; i <= n; i++) {
        scanf("%d", &col[i]);

        dad[i] = i;
        how_many[i] = 1;
    }

    ord = {mp(0, 0)};
    lvl[1] = 1;
    dfs(1);

    RMQ.init(cnt, ord);

    for (i = 1; i <= k; i++) {
        ans = 0;

        solve_color(i);

        printf("%lld\n", ans);
    }


    return 0;
}
