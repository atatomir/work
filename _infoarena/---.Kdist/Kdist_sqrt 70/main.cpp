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

int limit = sqrt(200000);

int n, k, i, x, y;
vector<int> list[maxN], wh[maxN];
int col[maxN];

int lvl[maxN];
int cnt;
int start[maxN];
vector< pair<int, int> > ord;
rmq< pair<int, int> > RMQ;

int how_many[maxN];
ll up[maxN];

int act_color;
ll ans;

void dfs(int node) {
    start[node] = ++cnt;
    ord.pb(mp(lvl[node], node));

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

int get_dist(int x, int y) {
    int lca = RMQ.query(min(start[x], start[y]), max(start[x], start[y])).second;

    return lvl[x] + lvl[y] - 2 * lvl[lca];
}

ll brute(vector<int> &pos) {
    static int i, j;
    static ll ans;

    ans = 0;

    for (i = 0; i < pos.size(); i++)
        for (j = i + 1; j < pos.size(); j++)
            ans += 1LL * get_dist(pos[i], pos[j]);

    return ans;
}

void solve(int node) {
    up[node] = how_many[node] = 0;

    for (int to : list[node]) {
        solve(to);
        how_many[node] += how_many[to];
        up[node] += up[to] + how_many[to];
    }

    for (int to : list[node])
        ans += (up[to] + how_many[to]) * (how_many[node] - how_many[to]);

    if (col[node] == act_color) {
        how_many[node]++;
        ans += up[node];
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
        wh[col[i]].pb(i);
    }

    ord = {mp(0, 0)};
    lvl[1] = 1;
    dfs(1);

    RMQ.init(cnt, ord);

    for (i = 1; i <= k; i++) {
        ans = 0;

        if (wh[i].size() <= limit)
            ans = brute(wh[i]);
        else
            act_color = i, solve(1);

        printf("%lld\n", ans);
    }


    return 0;
}
