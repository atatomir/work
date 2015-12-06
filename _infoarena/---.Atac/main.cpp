#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 32011
#define maxLog 17
#define inf 2000000000

int n, m, p, i;
int x, y, z, xx, yy, a, b, c, d;
vector< pair<int, int> > list[maxN];

int up[maxLog][maxN];
int up_min[maxLog][maxN];
int lvl[maxN];
bool us[maxN];

void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to.first]) continue;

        lvl[to.first] = lvl[node] + 1;
        up[0][to.first] = node;
        up_min[0][to.first] = to.second;
        dfs(to.first);
    }
}

void go_up(int &who, int how) {
    if (how <= 0)
        return;

    for (int i = 0; how > 0; i++, how >>= 1) {
        if (how & 1) {
            z = min(z, up_min[i][who]);
            who = up[i][who];
        }
    }
}

void Patrascu(int x, int y) {
    for (int actLog = maxLog - 1; actLog >= 0; actLog--) {
        if (up[actLog][x] == up[actLog][y]) continue;

        z = min(z, up_min[actLog][x]);
        z = min(z, up_min[actLog][y]);

        x = up[actLog][x];
        y = up[actLog][y];
    }

    z = min(z, up_min[0][x]);
    z = min(z, up_min[0][y]);
}

int solve() {
    xx = x; yy = y;
    z = 0;

    if (xx == yy)
        return z;
    z = inf;

    if (lvl[xx] > lvl[yy])
        swap(xx, yy);

    go_up(yy, lvl[yy] - lvl[xx]);
    if (xx == yy)
        return z;
    Patrascu(xx, yy);

    return z;
}

int main()
{
    freopen("atac.in","r",stdin);
    freopen("atac.out","w",stdout);

    scanf("%d%d%d", &n, &m, &p);
    p = m - p + 1;
    for (i = 2; i <= n; i++) {
        scanf("%d%d", &x, &y);
        list[i].pb(mp(x, y));
        list[x].pb(mp(i, y));
    }

    dfs(1);
    for (int actLog = 1; actLog < maxLog; actLog++) {
        for (i = 1; i <= n; i++) {
            up_min[actLog][i] = min(up_min[actLog - 1][i], up_min[actLog - 1][ up[actLog - 1][i] ]);
            up[actLog][i] = up[actLog - 1][ up[actLog - 1][i] ];
        }
    }

    scanf("%d%d%d%d%d%d", &x, &y, &a, &b, &c, &d);
    for (i = 1; i <= m; i++) {
        if (i < p)
            solve();
        else
            printf("%d\n", solve());

        xx = (x * a + y * b) % n + 1;
        yy = (y * c + z * d) % n + 1;

        x = xx; y = yy;
    }

    return 0;
}
