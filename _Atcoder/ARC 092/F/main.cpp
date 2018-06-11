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

const int maxN = 1024;

int n, m, i, x, y;
vector< pair<int, int> > to[maxN], from[maxN], list[maxN];
pair<int, int> rez[maxN * maxN];

bool way_back[maxN][maxN];
bool way_forw[maxN * maxN];
bool us[maxN];

void dfs_back(int node, int src) {
    way_back[src][node] = true;

    for (auto e : to[node])
        if (way_back[src][e.first] == false)
            dfs_back(e.first, src);
}

void dfs_forw(int node, int deny) {
    us[node] = true;
    for (auto e : to[node])
        if (us[e.first] == false && deny != e.first)
            dfs_forw(e.first, deny);
}

void solve_forw(int node) {
    int i;

    memset(us, 0, sizeof(us));
    for (auto y : to[node]) {
        if (us[y.first]) {
            way_forw[y.second] = true;
        } else {
            dfs_forw(y.first, node);
        }
    }

    memset(us, 0, sizeof(us));
    reverse(to[node].begin(), to[node].end());
    for (auto y : to[node]) {
        if (us[y.first]) {
            way_forw[y.second] = true;
        } else {
            dfs_forw(y.first, node);
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> m;
    for (i = 1; i <= m; i++) {
        cin >> x >> y;
        rez[i] = mp(x, y);
        to[x].pb(mp(y, i));
        from[y].pb(mp(x, i));

        list[x].pb(mp(y, i));
        list[y].pb(mp(x, i));
    }

    for (i = 1; i <= n; i++)
        dfs_back(i, i);

    for (i = 1; i <= n; i++)
        solve_forw(i);

    for (i = 1; i <= m; i++) {
        x = rez[i].first;
        y = rez[i].second;

        if (way_back[y][x] == way_forw[i])
            cout << "same\n";
        else
            cout << "diff\n";
    }


    return 0;
}
