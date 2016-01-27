#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024
#define inf 1000000000
#define ll long long

int n, m, x, y, modX, modY, setX, setY, i, j, k;
int how_x[maxN];
int how_y[maxN];
int dist[maxN][maxN];

bool us[maxN][maxN];
int period;

ll cnt[maxN * maxN];

int go_x(int xx) {
    return (1LL * xx * xx + setX) % modX;
}

int go_y(int yy) {
    return (1LL * yy * yy + setY) % modY;
}

int find_dist(int x, int y) {
    if (dist[x][y])
        return dist[x][y];

    dist[x][y] = inf;
    dist[x][y] = min(inf, find_dist( go_x(x), go_y(y) ) + 1);
    return dist[x][y];
}

void dfs(int xx, int yy, int d) {
    us[xx][yy] = true;

    xx = go_x(xx);
    yy = go_y(yy);

    if (us[xx][yy]) {
        if (xx == x && yy == y)
            period = d;
        return;
    }
    dfs(xx, yy, d + 1);
}

int main()
{
    freopen("robotei.in","r",stdin);
    freopen("robotei.out","w",stdout);

    scanf("%d%d%d%d%d%d%d%d", &n, &k, &x, &y, &modX, &modY, &setX, &setY);
    m = n;

    for (i = 0; i < n; i++)
        how_x[ go_x(i) ]++;
    for (i = 0; i < m; i++)
        how_y[ go_y(i) ]++;

    n = modX; m = modY;

    dist[x][y] = 1;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (dist[i][j] == 0)
                find_dist(i, j);

    period = 0;
    dfs(x, y, 1);

    //! -----------------------------
    int xx = go_x(x);
    int yy = go_y(y);

    if (period)
        cnt[1 + (k / period)]++;
    else
        cnt[1]++;

    k--;
    //!---------------------

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            dist[i][j]--;

            if (dist[i][j] >= inf - 1) {
                ll now = how_x[i] * how_y[j];
                if (i == xx && yy == j) now--;

                cnt[0] += now;
                continue;
            }

            if (dist[i][j] > k) continue;
            int aux = k - dist[i][j];

            ll now = how_x[i] * how_y[j];
            if (i == xx && yy == j) now--;

            if (period)
                cnt[1 + (aux / period)] += now;
            else
                cnt[1] += now;
        }
    }

    for (i = 0; i <= 1000000; i++)
        if (cnt[i])
            printf("%d %lld\n", i, cnt[i]);

    return 0;
}


