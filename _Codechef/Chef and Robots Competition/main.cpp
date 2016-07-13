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

#define maxN 111
#define inf 1000000000

int t, ti;
int n, m, i, j, K1, K2, K;
int grid[maxN][maxN];
int dist[2][maxN][maxN];
queue< pair<int, int> > Q;

void bfs(int id, int x, int y, int k) {
    int i, j;

    memcpy(dist[id], grid, sizeof(grid));
    dist[id][x][y] = 1;
    Q.push(mp(x, y));

    while (!Q.empty()) {
        x = Q.front().first;
        y = Q.front().second;
        Q.pop();

        for (i = max(1, x - k); i <= min(n, x + k); i++) {
            for (j = max(1, y - k); j <= min(m, y + k); j++) {
                if (dist[id][i][j] != 0) continue;
                if (abs(i - x) + abs(j - y) > k) continue;

                dist[id][i][j] = dist[id][x][y] + 1;
                Q.push(mp(i, j));
            }
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d%d", &n, &m, &K1, &K2);
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                scanf("%d", &grid[i][j]), grid[i][j] *= -1;

        bfs(0, 1, 1, K1);
        bfs(1, 1, m, K2);

        int ans = inf;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if (dist[0][i][j] != -1)
                    if (dist[0][i][j] != 0)
                        if (dist[1][i][j] != 0)
                            ans = min(ans, max(dist[0][i][j], dist[1][i][j]));

        if (ans == inf)
            printf("-1\n");
        else
            printf("%d\n", ans - 1);
    }


    return 0;
}
