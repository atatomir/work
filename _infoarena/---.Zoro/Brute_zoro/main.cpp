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

#define maxN 1024
#define inf 1000000000

int n, m, i, j;
int mat[maxN][maxN];
pair<int, int> wh[maxN * maxN];
int dp[maxN][maxN];


void solve(int x, int y) {
    int i, xx, yy;

    if (dp[x][y] < 0) return;

    for (i = 1; i <= n; i++)
        if (mat[i][y] < mat[x][y])
            dp[i][y] = max(dp[i][y], dp[x][y] + 1);

    for (i = 1; i <= m; i++)
        if (mat[x][i] < mat[x][y])
            dp[x][i] = max(dp[x][i], dp[x][y] + 1);
}

int main()
{
    freopen("zoro.in", "r", stdin);
    freopen("zoro.ok","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &mat[i][j]);
            wh[mat[i][j]] = mp(i, j);
            dp[i][j] = -inf;
        }
    }

    for (i = 0; i <= n; i++)
        mat[i][0] = mat[i][m + 1] = inf;

    for (i = 0; i <= m; i++)
        mat[0][i] = mat[n + 1][i] = inf;

    dp[1][1] = 1;
    for (i = n * m; i > 0; i--)
        solve(wh[i].first, wh[i].second);

    printf("%d", dp[n][m]);

    return 0;
}
