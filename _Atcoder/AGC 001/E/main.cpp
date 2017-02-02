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

#define maxN 4016
#define mod 1000000007

const int delta = 2003;

int n, i, j;
pair<int, int> ske[200011];

ll dp[maxN][maxN];
ll fact[maxN * 2], inv_fact[maxN * 2];
ll ans;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll comb(ll n, ll k) {
    ll ans = (fact[n] * inv_fact[k]) % mod;
    ans *= inv_fact[n - k];
    return ans % mod;
}

void pre() {
    int i;

    fact[0] = 1;
    for (i = 1; i <= 4 * delta; i++) fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[4 * delta] = poww(fact[4 * delta], mod - 2);
    for (i = 4 * delta - 1; i > 0; i--)
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;

    inv_fact[0] = 1;
}

int main()
{
    freopen("test.in","r",stdin);

    pre();

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &ske[i].first, &ske[i].second);
        ans += mod - comb(2 * ske[i].first + 2 * ske[i].second, 2 * ske[i].second);
        dp[delta - ske[i].first][delta - ske[i].second]++;
    }

    for (i = 1; i <= 2 * delta; i++) {
        for (j = 1; j <= 2 * delta; j++) {
            dp[i][j] += dp[i - 1][j] + dp[i][j - 1];
            dp[i][j] %= mod;
        }
    }

    for (i = 1; i <= n; i++)
        ans += dp[delta + ske[i].first][delta + ske[i].second];

    ans %= mod;
    ans *= poww(2, mod - 2);
    ans %= mod;

    printf("%lld", ans);



    return 0;
}
