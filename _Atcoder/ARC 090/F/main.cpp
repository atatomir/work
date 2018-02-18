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

const ll mod = 1000000007LL;
const ll limit = 10000000LL;

ll S, i, j, p, act, aux;
ll last, sols;

ll pows[11];

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll cnt(ll x) {
    ll pin = 0;

    while (pows[pin] <= x) pin++;

    last = pin;
    return pin;
}

void check(ll len) {
    if (len > aux) return;

    ll val = S / len;
    ll cnt = poww(10, val) - poww(10, val - 1) + mod;
    sols += cnt - len + 1 + mod;
    sols += mod - 1;
    sols %= mod;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld", &S);

    pows[0] = 1;
    for (i = 1; i <= 10; i++) pows[i] = pows[i - 1] * 10LL;

    act = 0;
    while (act + cnt(p + 1) <= S) {
        act += last;
        p++;
    }

    for (i = 1; i < limit; i++) {
        if (act + cnt(p + 1) <= S) {
            act += last;
            p++;
        }

        if (act == S) {
            sols++;

            /*act = 0;
            for (j = i; j <= p; j++) act += cnt(j);
            if (act != S) sols--;*/
        }
        if (act == 0) break;
        act -= cnt(i);
    }

    aux = S / 8;
    sols += aux;

    for (ll d = 1; d * d <= S; d++) {
        if (S % d) continue;
        check(d);
        if (d * d != S) check(S / d);
    }

    printf("%lld", sols);

    return 0;
}
