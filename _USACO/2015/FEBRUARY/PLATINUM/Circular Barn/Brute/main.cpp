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

int n, k, i, j;
ll cnt[maxN];
ll best = 1LL << 60;

ll dp[maxK][maxN];

ll try_now() {
    int i, j, l;

    for (i = 1; i <= n; i++) dp[0][i] = 1LL << 60;
    dp[0][n + 1] = 0;
    for (i = 1; i <= k; i++) {
        for (j = n; j > 0; j--) {
            dp[i][j] = 1LL << 60;

            ll aux = 0;
            for (l = j; l <= n; l++) {
                aux += 1LL * cnt[l] * (l - j);
                dp[i][j] = min(dp[i][j], dp[i - 1][l + 1] + aux);
            }

        }
    }

    return dp[k][1];
}

int main()
{
    freopen("cbarn.in","r",stdin);
    freopen("cbarn.ok","w",stdout);

    scanf("%d%d", &n, &k);
    k = min(k, n);
    for (i = 1; i <= n; i++) scanf("%lld", &cnt[i]);

    for (i = 1; i <= n; i++) {
        best = min(best, try_now());
        cnt[n + 1] = cnt[1];
        for (j = 1; j <= n; j++)
            cnt[j] = cnt[j + 1];
    }

    printf("%lld", best);


    return 0;
}
