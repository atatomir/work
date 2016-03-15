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

#define maxN 37
#define inf 1000000000
#define maxTree 5
#define pii pair<int, state>

struct state {
    int x, y, conf, dir;
    int best;

    state() {}
    state(int _best, int _x, int _y, int _conf, int _dir) {
        best = _best;
        x = _x; y = _y;
        conf = _conf;
        dir = _dir;
    }
};

struct heap_comp {
    bool operator()(const state &a, const state &b) {
        return a.best > b.best;
    }
};

int defX[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int defY[8] = {0, 0, -1, 1, 1, -1, -1, 1};

int n, k, i, j;
int cost[maxN][maxN];
int bottom[maxN][maxN];
int x_min, y_min;

int ans;
int dp[maxN][maxN][1 << maxTree][2]; //! 0 - left, 1 - right

priority_queue< state, vector<state>, heap_comp> H;

int check(int start_x, int start_y, int start_dir) {
    int x, y, dir, i, conf;

    memset(dp, 0, sizeof(dp));

    dp[start_x][start_y][ 0 ][start_dir] = 1 ;
    H.push( state(1, start_x, start_y, 0, start_dir) );

    while (!H.empty()) {
        state now = H.top(); H.pop();

        for (i = 0; i < 8; i++) {
            x = now.x + defX[i];
            y = now.y + defY[i];

            if (cost[x][y] < 0) continue;

            if (now.y < y) dir = 1;
            if (now.y > y) dir = 0;
            if (now.y == y) dir = now.dir;

            conf = now.conf;
            if (now.y != y) {
                conf ^= bottom[x][y];
                if (now.dir != dir)
                    conf ^= bottom[now.x][now.y];
            }

            if (dp[x][y][conf][dir] == 0 || dp[x][y][conf][dir] > dp[now.x][now.y][now.conf][now.dir] + cost[x][y]) {
                dp[x][y][conf][dir] = dp[now.x][now.y][now.conf][now.dir] + cost[x][y];
                H.push(state(dp[x][y][conf][dir], x, y, conf, dir));
            }
        }
    }



    return dp[start_x][start_y][ (1 << k) - 1 ][start_dir];
}

int main()
{
    freopen("gard4.in","r",stdin);
    freopen("gard4.out","w",stdout);

    x_min = y_min = 2016;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);

            if (cost[i][j] < 0) {
                cost[i][j] = -(++k);
                if (x_min > i) {
                    x_min = i;
                    y_min = j;
                }
            }
        }
    }

    for (i = n; i > 0; i--) {
        for (j = 1; j <= n; j++) {
            bottom[i][j] = bottom[i + 1][j];
            if (cost[i][j] < 0)
                bottom[i][j] ^= 1 << (-cost[i][j] - 1);
        }
    }

    for (i = 0; i <= n + 1; i++)
        cost[i][0] = cost[i][n + 1] = cost[0][i] = cost[n + 1][i] = -17;

    ans = inf;

    for (i = 1; i < x_min; i++) {
        ans = min(ans, check(i, y_min, 0)  );
        ans = min(ans, check(i, y_min, 1)  );
    }

    printf("%d", ans - 1);

    return 0;
}
