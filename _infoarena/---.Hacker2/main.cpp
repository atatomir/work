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

#define maxN 100011
#define maxLog 22
#define pii pair<int, int>
#define def_log 20


int n, i, m, x, y, d;
vector< pii > list[maxN];
vector< pii > Q[maxN];

bool us[maxN];
int dad[maxLog][maxN];
int deep[maxN];
int lvl[maxN];

pair< pair<int, int>, int> ans[maxN];

pii far_down[maxN];
pii far_up[maxN];

void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to.first]) continue;

        lvl[to.first] = lvl[node] + 1;
        deep[to.first] = deep[node] + to.second;
        dad[0][to.first] = node;
        dfs(to.first);
    }
}

void compute_dad() {
    int i, j;

    for (i = 1; i < def_log; i++)
        for (j = 1; j <= n; j++)
            dad[i][j] = dad[ i - 1 ][ dad[i - 1][j] ];
}

void solve_easy() {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (int kk = 0; kk < Q[i].size(); kk++) {
            auto qq = Q[i][kk];

            int node = i;
            for (j = def_log - 1; j >= 0; j--) {
                if (dad[j][node] == 0) continue;
                if (deep[i] - deep[ dad[j][node] ] < qq.second)
                    node = dad[j][node];
            }

            if (dad[0][node] == 0) continue;
            ans[qq.first] = mp( mp(node, dad[0][node]), qq.second - (deep[i] - deep[node]) );

            //! this query is solved
            Q[i][kk] = Q[i][ Q[i].size() - 1 ];
            Q[i].pop_back();
            kk--;
        }
    }
}

void dfs_down(int node) {
    us[node] = true;

    far_down[node] = mp(0, node);

    for (auto to : list[node]) {
        if (us[to.first]) continue;
        dfs_down(to.first);
        far_down[node] = max(far_down[node],
                             mp(far_down[to.first].first + to.second, far_down[to.first].second));
    }
}

bool cmp(const pii &a, const pii& b)  {
    return a.second + far_down[a.first].first > b.second + far_down[b.first].first;
}

void dfs_up(int node) {
    int i;
    us[node] = true;

    //! remove bad edge
    for (i = 0; i < list[node].size(); i++) {
        auto to = list[node][i];

        if (us[to.first]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            break;
        }
    }

    if (list[node].empty()) return;
    if (list[node].size() == 1) {
        auto to = list[node][0];

        far_up[to.first] = mp(far_up[node].first + to.second, far_up[node].second);
        dfs_up(to.first);
        return;
    }

    //! sort the list by deep
    sort(list[node].begin(), list[node].end(), cmp);

    auto to = list[node][0];
    auto from = list[node][1];

    far_up[to.first] = max( mp(far_up[node].first + to.second, far_up[node].second),
                            mp(far_down[from.first].first + from.second + to.second, far_down[from.first].second) );
    dfs_up(to.first);

    for (i = 1; i < list[node].size(); i++) {
        to = list[node][i];
        from = list[node][0];

        far_up[to.first] = max( mp(far_up[node].first + to.second, far_up[node].second),
                                mp(far_down[from.first].first + from.second + to.second, far_down[from.first].second) );
        dfs_up(to.first);
    }
}

int go_up(int node, int how) {
    for (int i = 0; how; i++, how >>= 1) {
        if (how & 1)
            node = dad[i][node];
    }
    return node;
}

int get_lca(int x, int y) {
    if (lvl[x] > lvl[y])
        swap(x, y);

    y = go_up(y, lvl[y] - lvl[x]);
    if (x == y) return x;

    for (int i = def_log - 1; i >= 0; i--) {
        if (dad[i][x] == dad[i][y]) continue;
        x = dad[i][x];
        y = dad[i][y];
    }

    return dad[0][x];
}

void solve_hard() {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (auto qq : Q[i]) {
            auto aux = max(far_down[i], far_up[i]);
            int node = aux.second;

            int lca = get_lca(node, i);
            qq.second -= deep[i] - deep[lca];

            for (j = def_log - 1; j >= 0; j--) {
                if (dad[j][node] == 0) continue;
                if (deep[ dad[j][node] ] - deep[lca] > qq.second)
                    node = dad[j][node];
            }

            ans[qq.first] = mp(mp(node, dad[0][node]), deep[node] - deep[lca] - qq.second);
        }
    }
}

int main()
{
    freopen("hacker2.in","r",stdin);
    freopen("hacker2.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &d);
        list[x].pb(mp(y, d));
        list[y].pb(mp(x, d));
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &d);
        Q[x].pb(mp(i, d));
    }

    dfs(1);
    compute_dad();
    solve_easy();

    memset(us, 0, sizeof(us));
    dfs_down(1);

    memset(us, 0, sizeof(us));
    far_up[1] = mp(0, 1);
    dfs_up(1);

    solve_hard();
    for (i = 1; i <= m; i++)
        printf("%d %d %d\n", ans[i].first.first, ans[i].first.second, ans[i].second);


    return 0;
}
