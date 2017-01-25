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

#define maxN 800011
#define mod 1000000007
#define lSon (node << 1)
#define rSon (lSon | 1)

// folosibil la 1

struct aint {
    int n;
    vector<ll> le, ri, mid;
    vector<ll> d[2][2];

    void combine(int node, int l, int mid, int r) {
        int p1, p2, p3;
        ll aux;

        d[0][0][node] = d[0][1][node] = d[1][0][node] = d[1][1][node] = 0;

        for (p1 = 0; p1 < 2; p1++) {
            for (p2 = 0; p2 < 2; p2++) {
                for (p3 = 0; p3 < 2; p3++) {
                    aux = d[p1][p2][lSon] * d[p2][p3][rSon];
                    aux %= mod;

                    d[p1][p3][node] += (aux * (p2 == 1 ? (ri[mid] * le[mid + 1]) % mod : 1) ) % mod;
                }
            }
        }

        d[0][0][node] %= mod;
        d[0][1][node] %= mod;
        d[1][0][node] %= mod;
        d[1][1][node] %= mod;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            d[0][0][node] = d[0][1][node] = d[1][0][node] = 1;
            d[1][1][node] = 0;
            return;
        }

        int mid = (l + r) >> 1;
        build(lSon, l, mid);
        build(rSon, mid + 1, r);

        combine(node, l, mid, r);
    }

    void init(int _n) {
        n = _n;
        d[0][0] = d[0][1] = d[1][0] = d[1][1] = vector<ll>(n * 4 + 11, 0);
        le = ri = vector<ll>(n + 11, 0);
        mid = vector<ll>(n + 11, 1);

        build(1, 1, n);
    }

    void update(int node, int l, int r, int pos) {
        if (l == r) {
            d[0][0][node] = mid[l];
            d[0][1][node] = 1;
            d[1][0][node] = 1;
            d[1][1][node] = 0;
            return;
        }

        int midd = (l + r) >> 1;
        if (pos <= midd)
            update(lSon, l, midd, pos);
        if (pos > midd)
            update(rSon, midd + 1, r, pos);

        combine(node, l, midd, r);
    }

};

int t, ti;
int n, m, i;
ll w1, aw, bw;
ll d1, ad, bd;
ll s1, as, bs;
ll w, s, d, z;

aint work;
ll ans;


int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << "\n";

        scanf("%d%d", &n, &m);
        scanf("%lld%lld%lld", &w1, &aw, &bw);
        scanf("%lld%lld%lld", &d1, &ad, &bd);
        scanf("%lld%lld%lld", &s1, &as, &bs);

        ans = 0;
        work.init(n);

        w = w1; s = s1; d = d1;
        for (i = 1; i <= m; i++) {
            z = max(1LL, min(1LL * n, w + d - 1));

            if (z < w)
                work.le[w] = (work.le[w] + s) % mod;
            if (z == w)
                work.mid[w] = (work.mid[w] + s) % mod;
            if (w < z)
                work.ri[w] = (work.ri[w] + s) % mod;

            work.update(1, 1, n, w);
            ans = (ans + work.d[0][0][1]) % mod;

            w = ((aw * w + bw) % n) + 1;
            d = (ad * d + bd) % 3;
            s = ((as * s + bs) % 1000000000) + 1;
        }

        printf("Case #%d: %lld\n", ti, ans);
    }


    return 0;
}
