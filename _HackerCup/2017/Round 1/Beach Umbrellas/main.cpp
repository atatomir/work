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

#define maxN 2017
#define mod 1000000007

const int def = 10011;

int t, ti;
ll n, m, i;
ll v[maxN];

ll l, r, sum, have;
ll data[2 * def + 11];
ll inv[2 * def + 11];

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll A(ll n, ll k) {
    if (n < 0 || k < 0) return 0;
    if (n < k) return 0;

    if (n == 0) return 1;
    if (k == 0) return 1;

    if (n < l || n > r) return 0;
    if (n == k) return data[n - l];

    return (data[n - l] * inv[n - l - k]) % mod;
}

ll solve() {
    ll i, bonus, pos, cnt, bonus2, pos2, cnt2, aux;
    ll ans = 0;

    if (n == 1) return m;

    sum = 0;
    for (i = 1; i <= n; i++) sum += 2 * v[i];

    have = m - 1 - sum;
    l = max(1LL, have - def);
    r = max(1LL, have + def);
    r = min(r, 1LL * mod - 1);

    for (i = 0; l + i <= r; i++) {
        data[i] = (i != 0 ? data[i - 1] : 1) * (l + i);
        data[i] %= mod;
    }

    inv[r - l] = poww(data[r - l], mod - 2);
    for (i = r - l - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (l + i + 1);
        inv[i] %= mod;
    }


    // no bonus
    if (have >= 0) {
        ans += A(n + have, n);
    }

    // one bonus
    sort(v + 1, v + n + 1);
    pos = 1;

    for (bonus = 1; pos <= n; bonus++) {
        while (pos <= n && v[pos] < bonus) pos++;
        if (pos > n) break;

        cnt = n - pos + 1;

        ans += (2LL * A(have + bonus + n - 1, n - 1) * cnt) % mod;
        ans %= mod;
    }

    // two bonuses
    if (n == 1) return ans;

    pos = 1;
    for (bonus = 1; pos <= n; bonus++) {
        while (pos <= n && v[pos] < bonus) pos++;
        if (pos > n) break;

        cnt = n - pos + 1;

        pos2 = 1;
        for (bonus2 = 1; pos2 <= n; bonus2++) {
            while (pos2 <= n && v[pos2] < bonus2) pos2++;
            if (pos2 > n) break;

            cnt2 = n - pos2 + 1;

            aux = (cnt * cnt2 - min(cnt, cnt2)) % mod;
            ans += ( A(have + bonus + bonus2 + n - 2, n - 2) * aux ) % mod;
            ans %= mod;
        }
    }



    return ans;

}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Start solving " << t << " tests\n";
    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%lld%lld", &n, &m);
        for (i = 1; i <= n; i++) scanf("%lld", &v[i]);

        printf("Case #%d: %lld\n", ti, solve());
    }


    return 0;
}
