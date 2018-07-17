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
const ll maxN = 111;

ll n, i, j, h[maxN], act, bef;
vector<ll> ord;
ll dp[maxN][maxN];

ll poww(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

int get_id(int x) {
    return lower_bound(ord.begin(), ord.end(), x) - ord.begin();
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &h[i]), ord.pb(h[i]);

    ord.pb(0);
    sort(ord.begin(), ord.end());
    ord.resize(unique(ord.begin(), ord.end()) - ord.begin());

    dp[1][0] = 2; //! doua colorari variabile

    //! initializeaza
    act = get_id(h[1]);
    dp[1][1] = ((poww(2, ord[1]) + mod - 2) * poww(2, h[1] - ord[1])) % mod;

    for (i = 2; i <= act; i++) {
        dp[1][i] = ((poww(2, ord[i] - ord[i - 1]) + mod - 1) * 2LL) % mod;
        dp[1][i] = (dp[1][i] * poww(2, h[1] - ord[i])) % mod;
    }

    //! rezolva
    for (i = 2; i <= n; i++) {
        bef = get_id(h[i - 1]);
        act = get_id(h[i]);

        if (h[i] == 1) {
            for (j = 0; j <= bef; j++)
                dp[i][0] = (dp[i][0] + dp[i - 1][j]) % mod;
            dp[i][0] = (dp[i][0] * 2LL) % mod;
            continue;
        }

        if (h[i - 1] <= h[i]) {
            //! creste nebunia
            for (j = 1; j <= bef; j++) {
                dp[i][j] = (dp[i - 1][j] * poww(2, h[i] - ord[bef])) % mod;
            }

            dp[i][0] = (dp[i - 1][0] * 2) % mod;
            for (j = bef + 1; j <= act; j++) {
                dp[i][j] = (dp[i - 1][0] * ( poww(2, ord[j] - ord[j - 1]) + mod - 1 )) % mod;
                dp[i][j] = (dp[i][j] * poww(2, h[i] - ord[j])) % mod;
                dp[i][j] = (dp[i][j] * 2) % mod;
            }
        } else {
            dp[i][0] = (dp[i - 1][0] * 2) % mod;

            for (j = 1; j <= act; j++)
                dp[i][j] = dp[i - 1][j];
            for (j = act + 1; j <= bef; j++)
                dp[i][0] = (dp[i][0] + dp[i - 1][j] * 2LL) % mod;
        }
    }

    ll ans = 0;
    act = get_id(h[n]);
    for (i = 0; i <= act; i++) ans = (ans + dp[n][i]) % mod;

    printf("%lld", ans);

    return 0;
}
