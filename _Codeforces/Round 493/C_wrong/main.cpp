#include <complex>
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

#define sz (2 * 1024 * 1024)
#define maxN (sz + 11)

const ll mod = 998244353;
const ll root = 3;

ll n, i, ans, part;
ll data[maxN], aux[maxN], sol[maxN];

ll fact[maxN], inv_fact[maxN];

ll A[maxN], B[maxN];


ll poww(ll a, ll b) {
    ll ans = 1;

    if (b > (mod - 1)) b %= (mod - 1);

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void bottom(int l, int r, ll* data) {
    int i, pos;

    if (l == r) {data[l] %= mod; return;}
    for (i = l; i <= r; i++) aux[i] = data[i];

    pos = l;
    for (i = l; i <= r; i += 2) data[pos++] = aux[i];
    for (i = l + 1; i <= r; i += 2) data[pos++] = aux[i];

    bottom(l, (l + r) >> 1, data);
    bottom(((l + r) >> 1) + 1, r, data);
}

void fft(int dim, ll* data, ll sign) {
    int len, i, j;
    ll u, v, w, step;

    bottom(0, dim - 1, data);
    for (len = 1; 2 * len <= dim; len <<= 1) {
        step = poww(root, (mod - 1) / (2 * len));
        if (sign == -1)
            step = poww(step, mod - 2);

        for (i = 0; i < dim; i += 2 * len) {
            w = 1;

            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];

                ll ss = (w * v) % mod;
                data[i + j] = (u + ss) % mod;
                data[i + len + j] = (mod + u - ss) % mod;

                w *= step;
                w %= mod;
            }
        }
    }

    ll dd = poww(dim, mod - 2);

    if (sign == -1)
        for (i = 0; i < dim; i++)
            data[i] = (data[i] * dd) % mod;
}

ll comb(ll n, ll k) {
    ll ans = (fact[n] * inv_fact[k]) % mod;
    return (ans * inv_fact[n - k]) % mod;
}

void mv(ll bg, ll mid, ll en) {
    ll i, j, dim;

    for (dim = 1; dim < en - bg + 1; dim <<= 1);
    dim <<= 1;

    for (i = bg; i <= mid; i++) {
        A[i - bg] = data[i];
        B[i - bg] = inv_fact[i - bg];
    }

    for (i = mid - bg + 1; i < dim; i++) {
        A[i] = 0;
        B[i - bg] = inv_fact[i - bg];
    }

    fft(dim, A, +1);
    fft(dim, B, +1);

    for (i = 0; i < dim; i++) A[i] = (A[i] * B[i]) % mod;
    fft(dim, A, -1);

    for (i = mid + 1; i <= en; i++) sol[i] = (sol[i] + A[i - bg]) % mod;
}

void solve(ll l, ll r) {
    if (l == r) {
        ll i = l;
        sol[i] = (sol[i] * inv_fact[n - i]) % mod;
        sol[i] = (mod + data[i] - sol[i]) % mod;
        data[i] = (sol[i] * fact[n - i]) % mod;
        return;
    }

    int mid = (l + r) >> 1;
    solve(l, mid);
    mv(l, mid, r);
    solve(mid + 1, r);
}

ll combo() {
    ll i, j;
    ll cnt, part, part2, dest;

    for (i = 1; i <= n; i++) {
        cnt = n * (n - i);
        part = poww(3, cnt);
        part2 = poww( (mod + poww(3, n - i) - 1) % mod , n);
        dest = (part + mod - part2) % mod;
        data[n - i] = (dest * 3LL * comb(n, i)) % mod;
    }

    solve(0, n - 1);
    /*for (i = 0; i < n; i++) {
        sol[i] = data[i];
        for (j = 0; j < i; j++)
            sol[i] = sol[i] - data[j] * comb(n - j, n - i);
    }*/

    ll ans = 0;
    for (i = 0; i < n; i++) ans = (ans + sol[i]) % mod;
    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &n);

    fact[0] = 1;
    for (i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[n] = poww(fact[n], mod - 2);
    for (i = n - 1; i >= 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;

    part = (mod + poww(3, n * n) - (poww( (mod + poww(3, n) - 3) % mod , n))) % mod;
    part = (part * 2) % mod;

    ans = (mod + part - combo()) % mod;
    printf("%lld", ans);

    return 0;
}
