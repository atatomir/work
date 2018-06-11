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
const ll maxN = 1000011;

ll n, i, sg, db;
ll fact[maxN], inv_fact[maxN];
ll ans, aux;

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
    ll ans = (fact[n] * inv_fact[n - k]) % mod;
    return (ans * inv_fact[k]) % mod;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &n);

    fact[0] = 1;
    for (i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[n] = poww(fact[n], mod - 2);
    for (i = n - 1; i >= 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;

    for (i = (n + 1) / 2; i < n; i++) {
        db = n - i;
        sg = i - db;

        aux = (comb(sg + db - 1, sg) * fact[sg + db]) % mod;
        aux = (aux * fact[n - 1 - sg - db]) % mod;

        ans = (ans + aux) % mod;
    }

    ans = mod + ((fact[n - 1] * n) % mod) - ans;
    ans %= mod;

    printf("%lld", ans);


    return 0;
}
