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

#define maxN 888

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, m, k, i, j;
char tp[maxN][maxN];
int dist[maxN][maxN];
queue<pair<int, int> > Q;
int best;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d\n", &n, &m, &k);
    for (i = 1; i <= n; i++) scanf("%s\n", tp[i] + 1);

    for (i = 1; i <= n; i++)
        tp[i][0] = tp[i][m + 1] = '#';

    for (i = 1; i <= n; i++)
        tp[0][i] = tp[n + 1][i] = '#';

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (tp[i][j] == 'S')
                Q.push(mp(i, j));

    best = n;

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        if (dist[x][y] > k) break;
        best = min(best, x - 1);
        best = min(best, y - 1);
        best = min(best, n - x);
        best = min(best, m - y);

        for (int i = 0; i < 4; i++) {
            int xx = x + defX[i];
            int yy = y + defY[i];

            if (tp[xx][yy] != '.') continue;
            tp[xx][yy] = '#';
            dist[xx][yy] = dist[x][y] + 1;
            Q.push(mp(xx, yy));
        }
    }

    cout << 1 + (best + k - 1) / k;


    return 0;
}
