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

#define maxN 555

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, m, i, j, op, x, y, panda_x, panda_y;
int panda_code, mask, s, t;

int dist[maxN][maxN];
bool food[maxN][maxN];

queue< pair<int, int> > Q;

int main()
{
    freopen("panda.in","r",stdin);
    freopen("panda.out","w",stdout);

    scanf("%d%d%d%d%d%d%d%d", &op, &n, &m, &t, &panda_x, &panda_y, &panda_code, &s);
    mask = (1 << s) - 1;
    panda_code &= mask;

    for (i = 1; i <= t; i++) {
        scanf("%d%d", &x, &y);
        food[x][y] = true;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &dist[i][j]);
            dist[i][j] &= mask;

            if ((dist[i][j] & panda_code) != 0)
                dist[i][j] = -1;
            else
            if ( (dist[i][j] | panda_code) != mask )
                dist[i][j] = -1;
            else
                dist[i][j] = 0;
        }
    }

    if (op == 1) {
        int cnt = 0;

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if (dist[i][j] == 0)
                    cnt++;

        if (dist[panda_x][panda_y] == 0) cnt--;
        printf("%d", cnt);

        return 0;
    }

    for (i = 0; i <= n + 1; i++)
        dist[i][0] = dist[i][m + 1] = -1;
    for (i = 0; i <= m + 1; i++)
        dist[0][i] = dist[n + 1][i] = -1;


    dist[panda_x][panda_y] = 1;
    Q.push(mp(panda_x, panda_y));

    while (!Q.empty()) {
        auto now = Q.front();
        Q.pop();

        for (i = 0; i < 4; i++) {
            int xx = now.first + defX[i];
            int yy = now.second + defY[i];

            if (dist[xx][yy]) continue;
            dist[xx][yy] = dist[now.first][now.second] + 1;
            Q.push(mp(xx, yy));
        }
    }

    int best, cnt;
    best = n * m + 17;
    cnt = 0;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (!food[i][j]) continue;
            if (dist[i][j] <= 0) continue;

            if (dist[i][j] == best) {
                cnt++;
            }
            if (dist[i][j] < best) {
                best = dist[i][j];
                cnt = 1;
            }
        }
    }

    if (food[panda_x][panda_y]) {
        best = 0;
        cnt = 1;
    }

    printf("%d %d", best - 1, cnt);


    return 0;
}
