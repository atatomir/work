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

const ll mod = 998244353;
const ll maxN = 300011;

ll n, A, B, K, i;
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
    ans = (ans * inv_fact[k]) % mod;
    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> A >> B >> K;

    fact[0] = 1;
    for (i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[n] = poww(fact[n], mod - 2);
    for (i = n - 1; i >= 0; i--)
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;

    for (i = 0; i <= n; i++) {
        ll rem = K - A * i;
        if (rem < 0) break;
        if (rem % B) continue;

        ll j = rem / B;
        //cerr << rem << ' ' << comb(n, j) << '\n';
        if (j > n) continue;
        aux = (comb(n, i) * comb(n, j)) % mod;
        ans = (ans + aux) % mod;
    }

    cout << ans;

    return 0;
}
