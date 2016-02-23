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

ll limit = 1;

int n, i;
ll x, y;

ll how_many[111];

ll my_pow(ll a, ll b) {
    ll ans = 1;

    while (b) {
        if (b & 1) {
            if (limit / ans < a)
                return limit;

            ans *= a;
        }

        b >>= 1;

        if (limit / a < a && b > 0)
            return limit;
        a *= a;
    }

    return ans;
}

ll solve(ll maxi) {
    int i, j;
    ll sol = 0;

    if (maxi == 0) return 0;

    int def = 1;
    while ( (1LL << def) <= maxi ) def++;
    limit = 1LL << def;

    ll ans = 1;
    for (i = def; i > 1; i--) {
        for (ll step = limit; step > 0; step >>= 1)
            if (ans + step <= maxi)
                if (my_pow(ans + step, i) <= maxi)
                    ans += step;

        how_many[i] = ans - 1;
    }

    for (i = def; i > 1; i--) {
        for (j = 2 * i; j <= def; j += i) how_many[i] -= how_many[j];
        sol += how_many[i];
    }

    return sol + 1;
}

int main()
{
    freopen("puteri4.in","r",stdin);
    freopen("puteri4.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &x, &y);

        ll ans = solve(y) - solve(x - 1);
        printf("%lld\n", ans);
    }


    return 0;
}
