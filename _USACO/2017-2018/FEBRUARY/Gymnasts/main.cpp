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

#define maxN 100011
#define mod 1000000007

ll n, i, j, limit, conf, ans, d1, d2;
ll a[maxN], b[maxN];

ll dp[maxN];

bool check() {
    int i, j;

    memset(b, 0, sizeof(ll) * n);
    for (i = 0; i < n; i++)
        for (j = 0; j < a[i]; j++)
            b[(i + j) % n]++;

    for (i = 0; i < n; i++)
        if (a[i] != b[i])
            return false;

    return true;
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

void solve(ll k) {
    int i, v1, v2;

    if (k == 1) {
        ans = (ans + n) % mod;
        return;
    }

    for (int s = 1; 2 * s <= k; s++) {
        for (v1 = 1; v1 <= n; v1++) {
            for (v2 = v1 - 1; v2 <= v1 + 1; v2++) {
                if (v2 < 1 || v2 > n || v1 == v2) continue;
                if (2 * s == k && v1 > v2) continue;

                for (i = 0; i < n; i++) {
                    if (i % k < s)
                        a[i] = v2;
                    else
                        a[i] = v1;
                }

                if (check())
                    ans = (ans + k) % mod;
            }
        }
    }
}

void smart_old() {
    ll i, j;

    dp[1] = 2;
    for (i = 2; i <= n; i++) {
        dp[i] = poww(2, i);
        for (j = 1; j < i; j++) {
            if (i % j == 0) {
                dp[i] += mod - dp[j];
                if (dp[i] >= mod) dp[i] -= mod;
            }
        }
    }

    ans = n % mod;
    for (i = 2; i < n; i++) {
        if (n % i) continue;

        ans += dp[i] * ((n / i) - 1);
        ans %= mod;
    }

    cout << ans;
    cerr << ans;
}

void smart() {
    ll i, j;
    vector< pair<ll, ll> > dp = {};

    cin >> n;

    for (i = 1; i * i <= n; i++) {
        if (n % i) continue;
        dp.pb(mp(i, 0));
        if (i * i != n) dp.pb(mp(n / i, 0));
    }

    sort(dp.begin(), dp.end());
    for (i = 0; i < dp.size(); i++) {
        dp[i].second = poww(2, dp[i].first);
        for (j = 0; j < i; j++) {
            if (dp[i].first % dp[j].first == 0) {
                dp[i].second += mod - dp[j].second;
            }
        }
        dp[i].second %= mod;
    }

    ans = n % mod;
    for (i = 1; i + 1 < dp.size(); i++) {
        ans += dp[i].second * (((n / dp[i].first) - 1) % mod);
        ans %= mod;
    }

    cout << ans;
    cerr << ans;
}

int main()
{
    freopen("gymnasts.in","r",stdin);
    freopen("gymnasts.out","w",stdout);

    /*n = 10;
    limit = poww(n, n);

    for (conf = 0; conf < limit; conf++) {
        ll aux = conf;

        d1 = d2 = 0;
        for (i = 0; i < n; i++) {
            a[i] = 1 + (aux % n);
            aux /= n;

            if (d1 == 0) {d1 = a[i]; continue;}
            if (a[i] != d1 && d2 == 0) {d2 = a[i]; continue;}
            if (a[i] != d1 && a[i] != d2) break;

            if (d2 != 0 && abs(d1 - d2) > 1) break;
        }

        if (a[1] == 3 && a[0] == 2 && a[2] == 2 && a[3] == 3)
            i += 0;

        if (i != n) continue;

        if (check()) {
            ans++;
            for (i = 0; i < n; i++) cerr << a[i] << ' ';
            cerr << '\n';
        }
    }
    cerr << ans;*/

    /*cin >> n;
    solve(1);
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            solve(d);
            if (d * d != n) solve(n / d);
        }
    }
    cout << ans;
    cerr << ans;*/

    cin >> n;
    smart();


    return 0;
}
