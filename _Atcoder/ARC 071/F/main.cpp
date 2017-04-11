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

#define maxN 1000011
#define mod 1000000007

int n, i;
ll dp[maxN], sum[maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);

    if (n == 1) {
        printf("1");
        return 0;
    }

    if (n == 2) {
        printf("4");
        return 0;
    }

    dp[0] = dp[1] = 1;
    sum[0] = 1; sum[1] = 2;

    for (i = 2; i <= n; i++) {
        dp[i] = mod + sum[i - 1] - dp[i - 2];
        dp[i] %= mod;

        sum[i] = sum[i - 1] + dp[i];
        sum[i] %= mod;
    }

    for (i = 0; i <= n - 2; i++) {
        // put an infinite loop
        ans += dp[i] * ((1LL * (n - 1) * (n - 1)) % mod);
        ans %= mod;

        // put an unfininished group
        ans += dp[i] * (i + 1);
        ans %= mod;
    }

    ans += dp[n - 1] * ((1LL * (n - 1)) % mod);
    ans %= mod;

    ans += dp[n];
    ans %= mod;

    printf("%lld", ans);


    return 0;
}
