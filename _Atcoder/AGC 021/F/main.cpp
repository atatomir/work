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

#define mod 998244353
#define maxN 8027
#define maxM 222

ll poww(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}


const ll lim = 8005;
const ll sz = 14;
const ll dim = 1 << sz;
const ll inv_dim = poww(dim, mod - 2);
ll unity_root = 2;

int n, m, i;
ll fact[maxN], inv_fact[maxN];
ll dp[2][maxN], ss, dd;

ll a[1 << sz], b[1 << sz];
ll aux[1 << sz];


ll comb(ll n, ll k) {
    if (n < k) return 0;
    ll ans = (fact[n] * inv_fact[n - k]) % mod;
    return (ans * inv_fact[k]) % mod;
}

void add(ll &a, ll b) {
    if (b >= mod) b %= mod;
    a += b;
    if (a >= mod) a -= mod;
}

void rev(ll *work, int l, int r) {
    int i, p = l;

    if (l == r) return;

    for (i = l; i <= r; i++) aux[i] = work[i];
    for (i = l; i <= r; i += 2) work[p++] = aux[i];
    for (i = l + 1; i <= r; i += 2) work[p++] = aux[i];
    rev(work, l, (l + r) >> 1);
    rev(work, ((l + r) >> 1) + 1, r);
}

void fft(ll* work, double sgn) {
    int len, i, j, k;
    ll u, v, r, w;

    rev(work, 0, dim - 1);
    for (len = 1; 2 * len <= dim; len <<= 1) {
        r = poww(unity_root, (mod - 1) / (2 * len));
        if (sgn == -1) r = poww(r, mod - 2);

        for (i = 0; i < dim; i += 2 * len) {
            w = 1;

            for (j = 0; j < len; j++) {
                u = work[i + j];
                v = work[i + j + len];

                work[i + j] = (u + w * v) % mod;
                work[i + j + len] = (mod + u - ((w * v) % mod)) % mod;

                w *= r;
                w %= mod;
            }
        }
    }

    if (sgn < 0.00) {
        for (i = 0; i < dim; i++)
            work[i] = (work[i] * inv_dim) % mod;
    }
}

void convolute() {
    int i;

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    for (i = 0; i <= n; i++) {
        a[i] = (dp[ss][i] * inv_fact[i]) % mod;
        b[i] = inv_fact[i + 2];
    }
    b[0] = 0;

    fft(a, +1);
    fft(b, +1);
    for (i = 0; i < dim; i++) a[i] = (a[i] * b[i]) % mod;
    fft(a, -1);

    //for (i = 0; i <= 10; i++) cerr << (fact[i + 2] * a[i]) % mod << ' ';
    //cerr << '\n';

    for (i = 0; i <= n; i++) {
        add(dp[dd][i], fact[i + 2] * a[i]);
    }
}

void solve() {
    int col, i, j;

    ss = 0; dd = 1;

    dp[ss][0] = 1;
    for (col = 1; col <= m; col++) {
        memset(dp[dd], 0, sizeof(dp[dd]));

        for (i = 0; i <= n; i++) {
            if (dp[ss][i] == 0) continue;

            //! add absolutely nothing
            add(dp[dd][i], dp[ss][i]);

            //! add 0 new lines
            add(dp[dd][i], dp[ss][i] * comb(i + 1, 2));

            //! add more new lines
            //for (j = 1; i + j <= n; j++)
            //    add(dp[dd][i + j], dp[ss][i] * comb(i + j + 2, j + 2));
        }

        convolute();

        swap(ss, dd);
    }

    ll ans = 0;
    for (i = 0; i <= n; i++)
        add(ans, dp[ss][i] * comb(n, i));

    cout << ans;
}

bool check(ll x) {
    if (poww(x, (mod - 1) / 2) == 1) return false;
    if (poww(x, (mod - 1) / 7) == 1) return false;
    if (poww(x, (mod - 1) / 17) == 1) return false;
    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    fact[0] = 1;
    for (i = 1; i <= lim; i++) fact[i] = (fact[i - 1] * i) % mod;
    inv_fact[lim] = poww(fact[lim], mod - 2);
    for (i = lim - 1; i >= 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;

    while (!check(unity_root)) unity_root++;

    cin >> n >> m;
    solve();


    return 0;
}
