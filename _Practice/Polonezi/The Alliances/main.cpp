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

#define maxN 77
#define maxDim maxN * maxN * 5

int n, m, i, j, cnt;
int tp[maxN][maxN];

int le[maxN][maxN], ri[maxN][maxN], up[maxN][maxN], down[maxN][maxN];

bool us[maxDim];
vector<int> list[maxDim];
int l[maxDim];
int r[maxDim];

char ans[maxN << 2][maxN << 2];


void add_edge(int x, int y, bool x_left) {
    if (x_left)
        list[x].pb(y);
    else
        list[y].pb(x);
}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (r[to] == 0)
            {l[node] = to; r[to] = node; return true;}
    }

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (pairUp(r[to]))
            {l[node] = to; r[to] = node; return true;}
    }

    return false;
}




int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);

    for (i = 0; i <= n + 1; i++)
        for (j = 0; j <= m + 1; j++)
            le[i][j] = ri[i][j] = down[i][j] = up[i][j] = -1;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &tp[i][j]);

            if (tp[i][j] == 1) {
                cnt++;
                le[i][j] = ri[i][j] = up[i][j] = down[i][j] = cnt;
            }

            if (tp[i][j] == 2) {
                cnt++;
                le[i][j] = ri[i][j] = cnt;
                cnt++;
                up[i][j] = down[i][j] = cnt;
            }

            if (tp[i][j] == 3) {
                le[i][j] = ++cnt;
                ri[i][j] = ++cnt;
                up[i][j] = ++cnt;
                down[i][j] = ++cnt;

                cnt++;
                add_edge(cnt - 1, cnt, i % 2 == j % 2);
                add_edge(cnt - 2, cnt, i % 2 == j % 2);
                add_edge(cnt - 3, cnt, i % 2 == j % 2);
                add_edge(cnt - 4, cnt, i % 2 == j % 2);
            }

            if (tp[i][j] == 4) {
                le[i][j] = ++cnt;
                ri[i][j] = ++cnt;
                up[i][j] = ++cnt;
                down[i][j] = ++cnt;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (i % 2 != j % 2) continue;

            if (tp[i][j - 1])
                add_edge(le[i][j], ri[i][j - 1], true);

            if (tp[i - 1][j])
                add_edge(up[i][j], down[i - 1][j], true);

            if (tp[i][j + 1])
                add_edge(ri[i][j], le[i][j + 1], true);

            if (tp[i + 1][j])
                add_edge(down[i][j], up[i + 1][j], true);
        }
    }

    bool need = true;
    while (need) {
        memset(us, 0, sizeof(us));
        need = false;

        for (i = 1; i <= cnt; i++)
            if (!l[i])
                need |= pairUp(i);
    }

    for (i = 1; i <= 3 * n; i++)
        for (j = 1; j <= 3 * m; j++)
            ans[i][j] = '.';

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (tp[i][j])
                ans[ (i - 1) * 3 + 2 ][ (j - 1) * 3 + 2 ] = 'O';

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (i % 2 != j % 2) continue;

            int x = (i - 1) * 3 + 2;
            int y = (j - 1) * 3 + 2;

            if (l[ le[i][j] ] == ri[i][j - 1]) {
                ans[x][y - 2] = ans[x][y - 1] = 'X';
                tp[i][j - 1]--;
                tp[i][j]--;
            }

            if (l[ up[i][j] ] == down[i - 1][j]) {
                ans[x - 2][y] = ans[x - 1][y] = 'X';
                tp[i - 1][j]--;
                tp[i][j]--;
            }

            if (l[ ri[i][j] ] == le[i][j + 1]) {
                ans[x][y + 1] = ans[x][y + 2] = 'X';
                tp[i][j]--;
                tp[i][j + 1]--;
            }

            if (l[ down[i][j] ] == up[i + 1][j]) {
                ans[x + 1][y] = ans[x + 2][y] = 'X';
                tp[i][j]--;
                tp[i + 1][j]--;
            }
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (tp[i][j] != 0) {
                printf("Impossible!\n");
                return 0;
            }

    for (i = 1; i <= 3 * n; i++)
        printf("%s\n", ans[i] + 1);

    return 0;
}
