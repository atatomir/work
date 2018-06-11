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

const int maxN = 3017;
const ll inf = 1LL << 60;

ll n, L, i, j, sol;
ll x[maxN], t[maxN];
ll cost_le[maxN], cost_ri[maxN], cost_base[maxN];
ll dp[maxN][maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &L);
    for (i = 1; i <= n; i++) scanf("%lld", &x[i]);
    for (i = 1; i <= n; i++) scanf("%lld", &t[i]);

    for (i = 1; i <= n; i++) {
        ans += t[i] / (2LL * L);
        t[i] %= (2LL * L);

        cost_base[i] = (t[i] == 0 ? 0 : 2);
        cost_le[i] = (2LL * (L - x[i]) >= t[i] ? 1 : 3);
        cost_ri[i] = (2LL * x[i] >= t[i] ? 1 : 3);
    }

    for (i = 0; i <= n; i++)
        for (j = 0; j <= n; j++)
            dp[i][j] = inf;

    dp[0][1] = 1;
    sol = inf;

    for (i = 0; i < n; i++) {
        for (j = 0; j <= i + 1; j++) {
            if (dp[i][j] >= inf) continue;
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + cost_base[i + 1]);
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + cost_ri[i + 1]);
            if (j > 1) {
                dp[i + 1][j - 1] = min(dp[i + 1][j - 1], dp[i][j] + cost_le[i + 1]);
            }
        }

        sol = min(sol, dp[i][1] + cost_le[i + 1] + 2LL * (n - i));
    }

    sol = min(sol, dp[n - 1][1] + cost_le[n]);

    //for (i = 0; i <= n; i++) cerr << dp[i][1] << ' ';
    //cerr << '\n';

    ans = 2LL * ans + sol;
    ans *= L;

    printf("%lld", ans);

    return 0;
}
