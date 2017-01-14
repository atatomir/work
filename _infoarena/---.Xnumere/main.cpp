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

#define mod 666013
#define maxN 100011

ll k, x, n, i;
ll fact[maxN], inv_fact[maxN];
ll sum, aux, aux2;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void pre() {
    ll i;

    fact[0] = 1;
    for (i = 1; i <= x; i++)
        fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[x] = poww(fact[x], mod - 2);
    for (i = x - 1; i > 0; i--)
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    inv_fact[0] = 1;
}

ll comb(ll n, ll k) {
    ll ans = (fact[n] * inv_fact[k]) % mod;
    return (ans * inv_fact[n - k]) % mod;
}

int main()
{
    freopen("xnumere.in","r",stdin);
    freopen("xnumere.out","w",stdout);

    scanf("%lld%lld%lld", &k, &x, &n);

    pre();
    for (i = 0; i < x; i++) {
        aux = comb(x, i) * poww(x - i, n);
        aux %= mod;

        if (i & 1) aux = mod - aux;
        sum += aux;
    }

    sum %= mod;

    aux = 1;
    for (i = k - x + 1; i <= k; i++) aux = (aux * (i % mod)) % mod;
    aux2 = 1;
    for (i = 1; i <= x; i++) aux2 = (aux2 * i) % mod;
    aux2 = poww(aux2, mod - 2);

    sum *= (aux * aux2) % mod;
    sum %= mod;

    printf("%lld", sum);
    cerr << sum;


    return 0;
}
