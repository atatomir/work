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

struct state {
    int x1, y1, x2, y2;
    int val;

    bool operator<(const state& who) const {
        return val < who.val;
    }
};

const int maxN = 25;
const int inf = 100000000;

const int defX[5] = {-1, 1, 0, 0, 0};
const int defY[5] = {0, 0, -1, 1, 0};

int n, m, i, j, k, l, ans;
char mat[maxN][maxN];
pair<int, int> S, F, D;
int dp[maxN][maxN][maxN][maxN];
queue<state> Q;

void solve() {
    int i, j, k, l;
    int xx, yy, xxx, yyy;

    for (i = 0; i <= n + 1; i++)
        for (j = 0; j <= m + 1; j++)
            for (k = 0; k <= n + 1; k++)
                for (l = 0; l <= m + 1; l++)
                    dp[i][j][k][l] = inf;

    dp[S.first][S.second][D.first][D.second] = 0;
    Q.push({S.first, S.second, D.first, D.second, 0});

    while (!Q.empty()) {
        state act = Q.front();
        Q.pop();

        if (act.x1 == F.first && act.y1 == F.second)
            ans = min(ans, act.val);

        act.val++;
        for (i = 0; i < 5; i++) {
            xx = act.x1 + defX[i];
            yy = act.y1 + defY[i];

            for (j = 0; j < 5; j++) {
                xxx = act.x2 + defX[j];
                yyy = act.y2 + defY[j];

                if (mat[xxx][yyy] != '0') continue;
                if (mat[xx][yy] != '1' && mp(xx, yy) != mp(xxx, yyy)) continue;
                if (dp[xx][yy][xxx][yyy] > act.val) {
                    dp[xx][yy][xxx][yyy] = act.val;
                    Q.push({xx, yy, xxx, yyy, act.val});
                }
            }
        }
    }

}

int main()
{
    freopen("delfin.in","r",stdin);
    freopen("delfin.ok","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", mat[i] + 1);
        for (j = 1; j <= m; j++) {
            if (mat[i][j] == 'S') {
                S = mp(i, j);
                mat[i][j] = '1';
            }

            if (mat[i][j] == 'F') {
                F = mp(i, j);
                mat[i][j] = '1';
            }

            if (mat[i][j] == 'D') {
                D = mp(i, j);
                mat[i][j] = '0';
            }
        }
    }

    for (i = 0; i <= n + 1; i++)
        mat[i][0] = mat[i][m + 1] = '@';

    for (i = 0; i <= m + 1; i++)
        mat[0][i] = mat[n + 1][i] = '@';

    ans = inf;
    solve();

    printf("%d", ans);

    return 0;
}
