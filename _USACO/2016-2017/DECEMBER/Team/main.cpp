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
#define maxK 11
#define mod 1000000009

int n, m, k, i, j, act, ss, dd;
int a[maxN], b[maxN];
int dp[2][maxN][maxK];

int main()
{
    freopen("team.in","r",stdin);
    freopen("team.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (i = 1; i <= m; i++) scanf("%d", &b[i]);

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);

    ss = 0; dd = 1;
    dp[ss][0][0] = 1;
    for (i = 1; i <= n; i++) {
        memset(dp[dd], 0, sizeof(dp[dd]));

        dp[dd][0][0] = 1;
        for (j = 1; j <= m; j++) {
            dp[dd][j][0] = 1;

            for (act = 1; act <= k; act++) {
                dp[dd][j][act] = dp[ss][j][act] + dp[dd][j - 1][act] - dp[ss][j - 1][act];
                while (dp[dd][j][act] < 0) dp[dd][j][act] += mod;
                while (dp[dd][j][act] >= mod) dp[dd][j][act] -= mod;

                if (a[i] > b[j]) {
                    dp[dd][j][act] += dp[ss][j - 1][act - 1];
                    if (dp[dd][j][act] >= mod) dp[dd][j][act] -= mod;
                }
            }
        }

        swap(ss, dd);
    }

    int ans = dp[ss][m][k];
    printf("%d", ans);


    return 0;
}
