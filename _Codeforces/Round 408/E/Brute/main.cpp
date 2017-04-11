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

#define maxN 111

int n, p, k, i, j, cnt, x, step, pp;
bool on_a[maxN], on_b[maxN];
int dp[maxN][maxN][maxN];

int how_many(int who, int x, int y) {
    int p, i, ans;
    ans = 0;

    if (who == 1) {
        p = min(n, x + k);
        for (i = x + 1; i <= p; i++) {
            if (!on_a[i]) continue;
            if (on_b[i] && i <= y) continue;
            ans++;
        }
    } else {
        p = min(n, y + k);
        for (i = y + 1; i <= p; i++) {
            if (!on_b[i]) continue;
            if (on_a[i] && i <= x) continue;
            ans++;
        }
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok","w",stdout);

    scanf("%d%d%d", &n, &p, &k); pp = p;
    scanf("%d", &cnt);
    for (i = 1; i <= cnt; i++) scanf("%d", &x), on_a[x] = true;
    scanf("%d", &cnt);
    for (i = 1; i <= cnt; i++) scanf("%d", &x), on_b[x] = true;

    for (step = 0; step <= pp; step++) {
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= n; j++) {
                if (step > 0) dp[step][i][j] = max(dp[step][i][j], dp[step - 1][i][j]);

                dp[step][i + 1][j] = max(dp[step][i + 1][j], dp[step][i][j]);
                dp[step][i][j + 1] = max(dp[step][i][j + 1], dp[step][i][j]);

                p = min(n, i + k);
                dp[step + 1][p][j] = max(dp[step + 1][p][j], dp[step][i][j] + how_many(1, i, j));

                p = min(n, j + k);
                dp[step + 1][i][p] = max(dp[step + 1][i][p], dp[step][i][j] + how_many(2, i, j));
            }
        }
    }

    printf("%d", dp[pp][n][n]);


    return 0;
}
