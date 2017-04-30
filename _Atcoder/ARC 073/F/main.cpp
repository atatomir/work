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

#define maxN 200011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define inf (1LL << 60)

struct aint {
    int dim;
    vector<ll> data;

    void init(int _dim) {
        dim = _dim;
        data = vector<ll>(4 * dim + 11, inf);
    }

    void upd(int node, int l, int r, int pos, ll v) {
        if (l == r) {
            data[node] = min(data[node], v);
            return;
        }

        int mid = (l + r) >> 1;
        if (pos <= mid) upd(lSon, l, mid, pos, v);
        else            upd(rSon, mid + 1, r, pos, v);

        data[node] = min(data[lSon], data[rSon]);
    }

    ll que(int node, int l, int r, int qL, int qR) {
        if (qL > qR) return inf;
        if (qL <= l && r <= qR)
            return data[node];

        int mid = (l + r) >> 1;
        ll ans = inf;

        if (qL <= mid)
            ans = min(ans, que(lSon, l, mid, qL, qR));
        if (qR > mid)
            ans = min(ans, que(rSon, mid + 1, r, qL, qR));

        return ans;
    }
};

int n, q, A, B, i, pos, act;
aint incr, decr;
ll bonus_incr, bonus_decr;

ll dist(ll a, ll b) {
    a -= b;
    if (a < 0) return -a;
    return a;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d%d", &n, &q, &A, &B);
    incr.init(n);
    decr.init(n);

    incr.upd(1, 1, n, A, 0 + A);
    decr.upd(1, 1, n, A, 0 + n - A);
    pos = B;

    for (i = 1; i <= q; i++) {
        scanf("%d", &act);

        ll ri = bonus_incr + incr.que(1, 1, n, act, n) - act;
        ll le = bonus_decr + decr.que(1, 1, n, 1, act) - (n - act);
        ll aux = min(le, ri);

        bonus_incr += dist(pos, act);
        bonus_decr += dist(pos, act);

        incr.upd(1, 1, n, pos, aux + pos - bonus_incr);
        decr.upd(1, 1, n, pos, aux + (n - pos) - bonus_decr);

        pos = act;
    }

    ll ans = inf;
    for (i = 1; i <= n; i++)
        ans = min(ans, incr.que(1, 1, n, i, i) - i + bonus_incr);

    printf("%lld", ans);

    return 0;
}
