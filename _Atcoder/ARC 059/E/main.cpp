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

#define maxN 444
#define mod 1000000007

int n, c, i, j, k;
int a[maxN], b[maxN];
ll sum[maxN][maxN];
ll dp[maxN][maxN];

ll get_sum(ll a, ll b) {
    return ((a + b) * (b - a + 1)) / 2;
}

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &c);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (i = 1; i <= n; i++) scanf("%d", &b[i]);

    for (i = 1; i <= 400; i++) {
        sum[i][0] = 0;
        for (j = 1; j <= 400; j++)
            sum[i][j] = (sum[i][j - 1] + poww(j, i)) % mod;
    }

    dp[0][1] = 1;
    for (i = 0; i <= c; i++) {
        for (j = 1; j <= n; j++) {
            dp[i][j] %= mod;

            dp[i][j + 1] += (dp[i][j] * (b[j] - a[j] + 1)) % mod;

            for (k = 1; i + k <= c; k++)
                dp[i + k][j + 1] += (dp[i][j] * (mod + sum[k][b[j]] - sum[k][a[j] - 1])) % mod;
        }
    }

    dp[c][n + 1] %= mod;
    printf("%lld", dp[c][n + 1]);


    return 0;
}
