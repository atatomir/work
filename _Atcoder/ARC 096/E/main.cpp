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

const int maxN = 3011;

ll n, mod, i, j;
ll ans, aux, inside, outside;

ll p2[maxN * maxN], p2_spec[maxN * maxN];
ll comb[maxN][maxN];

ll dp[maxN][maxN]; //! pui j biti in i grupe (+ grupa nula)
ll ways[maxN][maxN];

ll poww(ll a, ll b, ll moddo) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

void solve() {
    ll i, j, step, ans, aux, a, b, c;

    dp[0][0] = 1;
    for (i = 0; i <= n; i++) {
        for (j = i; j <= n; j++) {
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % mod;
            dp[i][j + 1] = (dp[i][j + 1] + dp[i][j] * (i + 1)) % mod;
        }
    }

    ans = 0;

    for (a = 0; a <= n; a++) {
        for (b = 0; a + b <= n; b++) {
            c = n - a - b;

            if (a + b == 0) {
                ans = poww(2, p2_spec[n], mod);
                continue;
            }

            aux = (dp[a][a + b] * p2[c * a]) % mod;
            aux = (aux * poww(2, p2_spec[c], mod)) % mod;
            aux = (aux * comb[n][a + b]) % mod;

            if ((a + b) % 2 == 0)
                ans = (ans + aux) % mod;
            else
                ans = (ans - aux + mod) % mod;
        }
    }

    printf("%lld", ans);
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> mod;

    p2[0] = p2_spec[0] = 1;
    for (i = 1; i <= n * n; i++) {
        p2[i] = (p2[i - 1] * 2) % mod;
        p2_spec[i] = (p2_spec[i - 1] * 2) % (mod - 1);
    }

    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    solve();


    return 0;
}
