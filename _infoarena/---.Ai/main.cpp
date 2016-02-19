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

#define maxN 1024

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, i, k;
int T_x, T_y, S_x, S_y, S2_x, S2_y, R_x, R_y, R2_x, R2_y;
int x, y;
int aux[maxN][maxN];
int dist[maxN][maxN];

int dp[maxN][maxN];
queue< pair<int, int> > Q;

void solve_task_one() {
    int i, j;
    int best = 0;

    for (i = 1; i <= n; i++) {
        dp[i][0] = 0;

        for (j = 1; j <= n; j++) {
            if (aux[i][j] != -1) {
                dp[i][j] = 0;
                continue;
            }

            dp[i][j] = dp[i][j - 1] + 1;
            best = max(best, dp[i][j]);
        }
    }

    for (j = 1; j <= n; j++) {
        dp[0][j] = 0;

        for (i = 1; i <= n; i++) {
            if (aux[i][j] != -1) {
                dp[i][j] = 0;
                continue;
            }

            dp[i][j] = dp[i - 1][j] + 1;
            best = max(best, dp[i][j]);
        }
    }

    printf("%d\n", best);
}

bool between(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
    if (p1.second > p3.second) swap(p1, p3);
    if (p2.second < p1.second || p2.second > p3.second) return false;

    if (p1 > p3) swap(p1, p3);
    if (p2.first < p1.first || p2.first > p3.first) return false;

    p2.first -= p1.first;
    p2.second -= p1.second;

    p3.first -= p1.first;
    p3.second -= p1.second;

    if (p2.first * p3.second - p2.second * p3.first != 0) return false;
    return true;
}

void Lee(int pos_x, int pos_y) {
    int i, j;

    memcpy(dist, aux, sizeof(dist));

    dist[pos_x][pos_y] = 1;
    Q.push(mp(pos_x, pos_y));

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
}

void solve_task_two() {
    int i, j;

    int ans[2][2];
    ans[0][0] = ans[0][1] = ans[1][0] = ans[1][1] = n * n + 17;

    //! launch first robot...
    Lee(R_x, R_y);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (dist[i][j] <= 0) continue;
            if (!between(mp(T_x, T_y), mp(i, j), mp(S_x, S_y))) continue;

            ans[0][0] = min(ans[0][0], dist[i][j]);
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (dist[i][j] <= 0) continue;
            if (!between(mp(T_x, T_y), mp(i, j), mp(S2_x, S2_y))) continue;

            ans[0][1] = min(ans[0][1], dist[i][j]);
        }
    }

    //! launch second robot...
    Lee(R2_x, R2_y);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (dist[i][j] <= 0) continue;
            if (!between(mp(T_x, T_y), mp(i, j), mp(S_x, S_y))) continue;

            ans[1][0] = min(ans[1][0], dist[i][j]);
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (dist[i][j] <= 0) continue;
            if (!between(mp(T_x, T_y), mp(i, j), mp(S2_x, S2_y))) continue;

            ans[1][1] = min(ans[1][1], dist[i][j]);
        }
    }

    //! conclusions
    int v1 = max(ans[0][0], ans[1][1]) - 1;
    int v2 = max(ans[0][1], ans[1][0]) - 1;

    printf("%d\n", min(v1, v2));
}

int main()
{
    freopen("ai.in","r",stdin);
    freopen("ai.out","w",stdout);

    scanf("%d", &n);
    scanf("%d%d", &T_x, &T_y);
    scanf("%d%d", &S_x, &S_y);
    scanf("%d%d", &S2_x, &S2_y);
    scanf("%d%d", &R_x, &R_y);
    scanf("%d%d", &R2_x, &R2_y);

    scanf("%d", &k);
    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x, &y);
        aux[x][y] = -1;
    }

    aux[T_x][T_y] = -1;
    for (i = 0; i <= n + 1; i++)
        aux[0][i] = aux[n + 1][i] = aux[i][0] = aux[i][n + 1] = -1;

    solve_task_one();
    solve_task_two();

    return 0;
}
