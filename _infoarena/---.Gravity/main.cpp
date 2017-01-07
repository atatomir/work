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

#define maxN 1811

int defX[4] = {-1, +1, 0, 0};
int defY[4] = {0, 0, -1, +1};

int n, m, i, j;
char mat[maxN][maxN], ans[maxN][maxN];

int dist[maxN][maxN];
bool done[maxN][maxN];
vector< pair<int, int> > dijk[maxN];

int main()
{
    freopen("gravity.in","r",stdin);
    freopen("gravity.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) scanf("%s\n", mat[i] + 1);

    for (i = 0; i <= n + 1; i++) mat[i][0] = mat[i][m + 1] = 'x';
    for (i = 0; i <= m + 1; i++) mat[0][i] = mat[n + 1][i] = 'x';

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            dist[i][j] = n + 1;

    for (i = 1; i <= m; i++) {
        dist[n][i] = 0;
        dijk[0].pb(mp(n, i));
    }

    for (i = 0; i <= n; ) {
        if (dijk[i].empty()) {
            i++;
            continue;
        }

        auto pos = dijk[i].back();
        dijk[i].pop_back();

        int x = pos.first;
        int y = pos.second;

        if (done[x][y]) continue;
        done[x][y] = true;


        if (mat[x][y] == '.') {
            if (mat[x - 1][y] == 'x') continue;
            if (dist[x - 1][y] > dist[x][y] + 1) {
                dist[x - 1][y] = dist[x][y] + 1;
                dijk[dist[x - 1][y]].pb(mp(x - 1, y));
            }
        } else {
            for (int j = 0; j < 4; j++) {
                int xx = x + defX[j];
                int yy = y + defY[j];

                if (mat[xx][yy] != '#') continue;
                if (dist[xx][yy] > dist[x][y]) {
                    dist[xx][yy] = dist[x][y];
                    dijk[dist[xx][yy]].pb(mp(xx, yy));
                }
            }

            if (mat[x - 1][y] == 'x') continue;
            if (dist[x - 1][y] > dist[x][y]) {
                dist[x - 1][y] = dist[x][y];
                dijk[dist[x - 1][y]].pb(mp(x - 1, y));
            }
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            ans[i][j] = '.';

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (mat[i][j] == '#')
                ans[i + dist[i][j]][j] = '#';

    for (i = 1; i <= n; i++)
        printf("%s\n", ans[i] + 1);


    return 0;
}
