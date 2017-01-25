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

#define maxN 333
#define inf 1LL << 60

int t, ti;
int n, m, i, j, k;
ll cost[maxN][maxN], dp[maxN][maxN];

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Start solving " << t << " tests.\n";

    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                scanf("%lld", &cost[i - 1][j]);

        for (i = 0; i <= n; i++)
            for (j = 0; j <= n; j++)
                dp[i][j] = inf;

        dp[0][1] = 0;
        for (i = 0; i < n; i++) {
            sort(cost[i] + 1, cost[i] + m + 1);
            for (k = 1; k <= m; k++) cost[i][k] += cost[i][k - 1];

            for (j = 1; j <= n; j++) {
                if (dp[i][j] >= inf) continue;

                dp[i + 1][j - 1] = min(dp[i + 1][j - 1], dp[i][j]);
                for (k = 1; k <= m && j - 1 + k <= n; k++)
                    dp[i + 1][j - 1 + k] = min(dp[i + 1][j - 1 + k], dp[i][j] + cost[i][k] + 1LL * k * k);
            }
        }

        ll ans = inf;
        for (i = 1; i <= n; i++)
            ans = min(ans, dp[n][i]);

        printf("Case #%d: %lld\n", ti, ans);
    }



    return 0;
}
