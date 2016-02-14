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

#define maxN 211

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, m, i, x, y;
int dist[maxN][maxN];
queue< pair<int, int> > Q;

int main()
{
    freopen("alee.in","r",stdin);
    freopen("alee.out","w",stdout);

    scanf("%d%d", &n, &m);

    for (i = 0; i <= n + 1; i++)
        dist[0][i] = dist[n + 1][i] = dist[i][0] = dist[i][n + 1] = -1;

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        dist[x][y] = -1;
    }

    scanf("%d%d", &x, &y);

    dist[x][y] = 1;
    Q.push(mp(x, y));

    while (!Q.empty()) {
        auto now = Q.front(); Q.pop();

        for (i = 0; i < 4; i++) {
            int xx = now.first + defX[i];
            int yy = now.second + defY[i];

            if (dist[xx][yy]) continue;
            dist[xx][yy] = dist[now.first][now.second] + 1;
            Q.push(mp(xx, yy));
        }
    }

    scanf("%d%d", &x, &y);
    printf("%d", dist[x][y]);


    return 0;
}
