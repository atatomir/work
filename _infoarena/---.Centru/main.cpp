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
#define ll long long

#define maxN 1024 << 1
#define pii pair<int, int>

const int defX[4] = {0, 0, -1, 1};
const int defY[4] = {-1, 1, 0, 0};

int n, k, i, j, x, y, pos;
queue< pii > Q;
int dist[maxN][maxN];

vector<pii> aux[maxN];
int ans;

int x_min, x_max;
int y_min, y_max;

int def;

pii trans(int a, int b) {
    return mp(a - b, a + b);
}

void update(int xx, int yy) {
    x_min = min(x_min, xx);
    x_max = max(x_max, xx);

    y_min = min(y_min, yy);
    y_max = max(y_max, yy);
}

int try_center(int xx, int yy) {
    if ( (xx & 1) != (yy & 1) ) return def;

    int dist = max(x_max - xx, xx - x_min);
    dist = max(dist, y_max - yy);
    dist = max(dist, yy - y_min);

    dist = (dist + 1) / 2;
    return dist * 2 + 1;
}

int main()
{
    freopen("centru.in","r",stdin);
    freopen("centru.out","w",stdout);

    scanf("%d%d", &n, &k);
    def = 2 * n + 3;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            dist[i][j] = def;

    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x, &y);
        x++; y++;

        dist[x][y] = 1;
        Q.push(mp(x, y));
    }

    while (!Q.empty()) {
        auto now = Q.front(); Q.pop();

        for (i = 0; i < 4; i++) {
            int xx = now.first + defX[i];
            int yy = now.second + defY[i];

            if (dist[xx][yy] == def) {
                dist[xx][yy] = dist[now.first][now.second] + 1;
                Q.push(mp(xx, yy));
            }
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            aux[ dist[i][j] - 1 ].pb( trans(i, j) );

    for (pos = 2 * n  + 3; aux[pos].size() == 0 && pos > 0; pos--);
    ans = pos;

    x_min = x_max = aux[pos][0].first;
    y_min = y_max = aux[pos][0].second;

    for (; pos >= 0;) {
        for (auto now : aux[pos])
            update(now.first, now.second);

        int xx = (x_min + x_max) / 2;
        int yy = (y_min + y_max) / 2;

        int l = try_center(xx, yy);
        if ( (xx & 1) != (yy & 1) )
            for (i = 0; i < 4; i++)
                l = min(l, try_center(xx + defX[i], yy + defY[i]));

        for (pos--; aux[pos].size() == 0 && pos > 0; pos--);

        ans = min(ans, max(l - 1, pos) );
    }

    printf("%d", ans);
    cerr << ans;

    return 0;
}
