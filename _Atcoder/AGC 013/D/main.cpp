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

#define maxN 3011
#define mod 1000000007

int n, m, i, j, k;
ll dp[maxN][maxN][2];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 0; i <= n; i++) dp[0][i][0] = 1;
    for (i = 0; i < m; i++) {
        for (j = 0; j <= n; j++) {
            for (k = 0; k < 2; k++) {
                dp[i][j][k] %= mod;

                if (j == 0) {
                    dp[i + 1][j][1] += dp[i][j][k];
                    dp[i + 1][j + 1][1] += dp[i][j][k];
                    continue;
                }

                if (j == 1) {
                    if (j != n) dp[i + 1][j][k] += dp[i][j][k];
                    dp[i + 1][j + 1][k] += dp[i][j][k];

                    dp[i + 1][j - 1][1] += dp[i][j][k];
                    dp[i + 1][j][1] += dp[i][j][k];
                    continue;
                }

                dp[i + 1][j - 1][k] += dp[i][j][k];
                dp[i + 1][j][k] += (j != n ? 2LL : 1LL) * dp[i][j][k];
                dp[i + 1][j + 1][k] += dp[i][j][k];
            }
        }
    }

    ll ans = 0;
    for (i = 0; i <= n; i++) ans += dp[m][i][1] % mod;
    ans %= mod;

    printf("%lld", ans);



    return 0;
}
