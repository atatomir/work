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

const ll mod = 1000000007;
const ll maxN = 25011;
const ll maxK = 411;

ll n, k, m, i;
ll a[maxN], ans;
ll last[maxK];

ll s, d;
ll dp[2][maxK], dp2[2][maxN];

ll poww(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

ll solve_all_dif() {
    ll i, j, ss, dd, aux, aux2;

    memset(dp, 0, sizeof(dp));
    memset(dp2, 0, sizeof(dp2));
    ss = 0; dd = 1;

    dp[0][0] = 1;
    dp[0][1] = mod - 1;
    for (i = 0; i < n; i++) {
        memset(dp[dd], 0, sizeof(dp[dd]));
        memset(dp2[dd], 0, sizeof(dp2[dd]));
        
        for (j = 0; j <= k; j++) {
            if (j > 0) {
                add(dp[ss][j], dp[ss][j - 1]);
                add(dp2[ss][j], dp2[ss][j - 1]);
            }

            //! adauga-l pe urmatorul
            if (j + 1 < k) {
                aux = (dp[ss][j] * (k - j))% mod;
                aux2 = (dp2[ss][j] * (k - j)) % mod;
                if (j + 1 >= m) add(aux2, aux);

                add(dp[dd][j + 1], aux);
                add(dp[dd][j + 2], mod - aux);

                add(dp2[dd][j + 1], aux2);
                add(dp2[dd][j + 2], mod - aux2);
            }

            //! adauga o dublura
            add(dp[dd][1], dp[ss][j]);
            add(dp[dd][j + 1], mod - dp[ss][j]);

            add(dp2[dd][1], dp2[ss][j]);
            add(dp2[dd][j + 1], mod - dp2[ss][j]);

            if (j >= m) {
                add(dp2[dd][m], dp[ss][j]);
                add(dp2[dd][j + 1], mod - dp[ss][j]);
            }
        }

        swap(ss, dd);
    }

    ll ans = 0;
    for (i = 1; i < k; i++) add(ans, dp[ss][i]);
    return ans;
}

ll solve_two_zones() {
    
}

ll count_not_col() {
    ll i, j, p;
    
    p = 1;
    for (i = 1; i <= n; i++) {
        p = max(p, last[a[i]] + 1);
        last[a[i]] = i;
        if (i - p + 1 == k) return 0;
    }

    if (p == 1) {
        return solve_all_dif();
    } else {
        return solve_two_zones();
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld%lld%lld", &n, &k, &m);
    for (i = 1; i <= m; i++) scanf("%lld", &a[i]);

    ans = (n - m + 1) * poww(k, n - m);
    ans = (ans % mod) + mod - count_not_col();
    ans %= mod;

    printf("%lld", ans);

    return 0;
}
