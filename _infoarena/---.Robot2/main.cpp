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

#define triple(a, b, c) mp(mp(a, b), c)
#define pii pair< pair<int, int>, int>
#define maxN 1024

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, +1};


int n, i, j, dir1, dir2;
int mat[maxN][maxN];
int dp[2][maxN][maxN][4];
pair<int, int> S, D;

queue< pii > Q;
bool inQueue[maxN][maxN][4];

int ans;
int how;
int def;

void Lee(int id, int x, int y) {
    int i, j, dir, xx, yy;

    for (i = 0; i < 4; i++) {
        dp[id][x][y][i] = 1;
        Q.push( triple(x, y, i) );
        inQueue[x][y][i] = true;
    }

    while (!Q.empty()) {
        pii act = Q.front(); Q.pop();
        x = act.first.first;
        y = act.first.second;
        dir = act.second;
        inQueue[x][y][dir] = false;

        //! change direction
        for (i = 0; i < 4; i++) {
            if (dp[id][x][y][i] == 0 || dp[id][x][y][i] > dp[id][x][y][dir] + 1) {
                dp[id][x][y][i] = dp[id][x][y][dir] + 1;
                if (!inQueue[x][y][i]) {
                    Q.push(triple(x, y, i));
                    inQueue[x][y][i] = true;
                }
            }
        }

        //! move in direction dir
        xx = x + defX[dir];
        yy = y + defY[dir];

        if (mat[xx][yy]) continue;
        if (dp[id][xx][yy][dir] == 0 || dp[id][xx][yy][dir] > dp[id][x][y][dir]) {
            dp[id][xx][yy][dir] = dp[id][x][y][dir];
            if (!inQueue[xx][yy][dir]) {
                inQueue[xx][yy][dir] = true;
                Q.push(triple(xx, yy, dir));
            }
        }
    }
}

void swap_it(int &v) {
    switch (v) {
        case 0 : v = 1;
                 break;
        case 1 : v = 0;
                 break;
        case 2 : v = 3;
                 break;
        case 3 : v = 2;
                 break;
    }
}

int solve(int x, int y, int d1, int d2) {
    int xx1, yy1, xx2, yy2;

    if (d1 == d2) return def;

    swap_it(d1);
    swap_it(d2);

    xx1 = x + defX[d1];
    yy1 = y + defY[d1];

    xx2 = x + defX[d2];
    yy2 = y + defY[d2];

    swap_it(d1);
    swap_it(d2);

    if (dp[0][xx1][yy1][d1] == 0 || dp[1][xx2][yy2][d2] == 0) return def;

    if ( (d1 <= 1 && d2 <= 1)  ||  (d1 >= 2 && d2 >= 2) )
        return dp[0][xx1][yy1][d1] + dp[1][xx2][yy2][d2] - 2;
    else
        return dp[0][xx1][yy1][d1] + dp[1][xx2][yy2][d2] - 2 + 1;
}

int main()
{
    freopen("robot2.in","r",stdin);
    freopen("robot2.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]);
    scanf("%d%d", &S.first, &S.second);
    scanf("%d%d", &D.first, &D.second);


    for (i = 0; i <= n + 1; i++)
        mat[i][0] = mat[i][n + 1] = mat[0][i] = mat[n + 1][i] = 1;

    Lee(0, S.first, S.second);
    Lee(1, D.first, D.second);

    //! solve first task
    ans = dp[0][D.first][D.second][0];
    for (i = 1; i < 4; i++)
        ans = min(ans, dp[0][D.first][D.second][i]);

    ans--;
    printf("%d ", ans);
    def = ans;

    //! solve other tasks
    ans++;
    how = 0;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (mat[i][j] == 0) continue;

            int act_min = ans + 1;
            for (dir1 = 0; dir1 < 4; dir1++)
                for (dir2 = 0; dir2 < 4; dir2++)
                    act_min = min(act_min, solve(i, j, dir1, dir2));

            if (act_min < ans) {
                ans = act_min;
                how = 0;
            }

            if (act_min == ans) how++;
        }
    }

    printf("%d %d\n", ans, how);


    return 0;
}
