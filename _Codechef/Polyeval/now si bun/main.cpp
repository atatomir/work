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

#define def 1024
#define maxN 1024 * 1024

const ll mod = 786433;
const int dim = mod / 3;
const ll root = 10;

int n, i, x;
ll data[maxN], aux[maxN], rez[maxN];
ll sol[maxN];



ll poww(ll a, ll b) {
    ll ans = 1;

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void find_root() {
    ll i, aux;
    vector<int> divs;

    aux = mod - 1;
    divs.clear();

    for (i = 2; i * i <= aux; i++) {
        if (aux % i) continue;

        divs.pb(i);
        while (aux % i == 0) aux /= i;
    }
    if (aux != 1) divs.pb(aux);

    for (i = 2; i <= 1000000; i++) {
        bool good = true;

        for (auto e : divs)
            if (poww(i, mod / e) == 1)
                {good = false; break;}

        if (good) {
            cerr << "found root " << i;
            return;
        }
    }
}

void test_root(ll x) {
    ll step = x;
    for (i = 1; i + 1 < mod; i++) {
        if (x == 1) {
            cerr << "err";
            return;
        }

        x = (x * step) % mod;
    }
}

void prepare(int l, int r) {
    if (l == r) return;

    int i, pos;

    pos = l;
    for (i = l; i <= r; i++) aux[i] = data[i];
    for (i = l; i <= r; i += 2) data[pos++] = aux[i];
    for (i = l + 1; i <= r; i += 2) data[pos++] = aux[i];

    int mid = (l + r) >> 1;
    prepare(l, mid);
    prepare(mid + 1, r);
}

void ntt(int dim) {
    ll i, j, len;
    ll w, u, v, step;

    prepare(0, dim - 1);

    for (len = 1; 2 * len <= dim; len <<= 1) {
        step = poww(root, (mod - 1) / (2 * len));

        for (i = 0; i < dim; i += 2 * len) {
            w = 1;

            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];

                data[i + j] = (u + w * v) % mod;
                data[i + len + j] = (mod + u - ((w * v) % mod)) % mod;

                w = (w * step) % mod;
            }
        }
    }
}

void solve(ll add) {
    memcpy(rez, data, sizeof(rez));

    ntt(dim);

    ll w = 1;
    ll step = poww(root, (mod - 1) / dim);

    for (i = 0; i < dim; i++) {
        sol[ (w * add) % mod ] = data[i];
        w = (w * step) % mod;

    }

    memcpy(data, rez, sizeof(rez));
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 0; i <= n; i++) scanf("%lld", &data[i]);
    sol[0] = data[0];


    solve(1);

    for (i = 0; i <= n; i++) data[i] = (data[i] * poww(root, i)) % mod;
    solve(root);

    for (i = 0; i <= n; i++) data[i] = (data[i] * poww(root, i)) % mod;
    solve(root * root);


    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        x %= mod;

        printf("%lld\n", sol[x]);
    }


    return 0;
}
