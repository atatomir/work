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

#define maxN 2012
#define mod 1000000007


int n, k, need, i, j;
ll dp[maxN][maxN], ans;
ll adds[maxN][maxN];

int main() {
    freopen("test.in", "r", stdin);

    scanf("%d%d", &n, &k);

    if (n == 1) {
        printf("1");
        return 0;
    }

    for (i = 1; i <= n; i++) dp[i][i - 1] = 1;

    for (i = 1; i + 1 < n; i++) {
        dp[i][0] %= mod;
        adds[i][0] %= mod;

        dp[i + 1][0] += dp[i][0] + adds[i][0];
        adds[i + 1][1] += dp[i][0];

        for (j = 1; j <= i; j++) {
            dp[i][j] %= mod;
            adds[i][j] %= mod;

            dp[i + 1][j] += dp[i][j] + adds[i][j];
            dp[i + 1][j - 1] += dp[i][j];
            dp[i + 1][j + 1] += dp[i][j];
            adds[i + 1][j + 1] += adds[i][j];
        }
    }

    need = n - k;
    ans = dp[n - 1][need] + adds[n - 1][need];

    for (i = 1; i < need; i++) {
        ans *= 2LL;
        ans %= mod;
    }

    printf("%lld", ans);

    return 0;
}
