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

#define maxN 50011
#define mod 700001

int n, i, j, ss, dd, sq;
int dp[maxN], dp2[maxN];

int main()
{
    freopen("crescator2.in","r",stdin);
    freopen("crescator2.out","w",stdout);

    scanf("%d", &n);
    dp[0] = 1;

    if (n == 1) {
        printf("1");
        return 0;
    }

    sq = sqrt(n);

    for (i = 1; i <= sq; i++) {
        for (j = 0; j + i <= n; j++) {
            if (dp[j] >= mod) dp[j] -= mod;
            dp[j + i] += dp[j];
        }
    }

    for (i = 1; i <= n; i++) dp[i] = (dp[i - 1] + dp[i]) % mod;
    ll ans = dp[n] - 1;

    dp2[0] = 1;
    for (i = 1; i * (sq + 1) <= n; i++) {
        for (j = n; j >= sq + 1; j--) dp2[j] = dp2[j - (sq + 1)];
        for (j = 0; j < sq + 1; j++) dp2[j] = 0;

        for (j = 0; j <= n; j++) {
            dp2[j] %= mod;

            ans = (ans + (1LL * dp2[j] * dp[n - j])) % mod;
            if (j + i <= n)
                dp2[j + i] += dp2[j];
        }
    }


    ans %= mod;
    printf("%d", ans);
    cerr << ans;


    return 0;
}
