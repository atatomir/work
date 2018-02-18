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

ll n, i, pos;
pair<ll, ll> p[maxN];

ll r[maxN], l[maxN];

ll h[maxN], hl[maxN];
ll sumh[maxN], sumhl[maxN];

ll ans, aux;

ll sum(ll pl, ll pr) {
    ll ans = (pr - pl + 1) * (pl + pr);
    ans /= 2;
    return ans % mod;
}

int main()
{
    freopen("sprinklers.in","r",stdin);
    freopen("sprinklers.out","w",stdout);

    scanf("%lld", &n);
    for (i = 0; i <= n; i++) l[i] = n + 11;
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &p[i].first, &p[i].second);
        r[p[i].second] = max(r[p[i].second], p[i].first);
        l[p[i].second + 1] = min(l[p[i].second + 1], p[i].first + 1);
    }

    for (i = 1; i <= n; i++) l[i] = min(l[i], l[i - 1]);
    for (i = n - 1; i >= 0; i--) r[i] = max(r[i], r[i + 1]);

    pos = 0;
    for (i = n - 1; i > 0; i--) {
        while (pos + 1 <= r[i]) {
            h[++pos] = i;
        }
    }

    for (i = 1; i < n; i++) {
        hl[i] = h[i] * i;
        sumh[i] = sumh[i - 1] + h[i];
        sumhl[i] = sumhl[i - 1] + hl[i];
    }

    for (i = 1; i < n; i++) {
        ll pl = l[i];
        ll pr = r[i];

        if (pl > pr) continue;

        aux = sumhl[pr] + mod - sumhl[pl - 1];
        aux += (((pl - 1) * (i - 1)) % mod) * (pr - pl + 1);
        aux %= mod;

        aux += mod - (( (i - 1) * sum(pl, pr) ) % mod);
        aux += mod - (( (pl - 1) * (sumh[pr] + mod - sumh[pl - 1]) ) % mod);
        aux %= mod;

        ans += aux;
        ans %= mod;
    }

    printf("%lld", ans);

    return 0;
}
