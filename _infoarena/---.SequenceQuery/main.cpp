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

#define maxN 100011
#define lSon (node << 1)
#define rSon (lSon | 1)

struct aint {
    int dim, i;
    ll *best, *le, *ri, *from;
    vector< pair<int, pair<int, int> > > nodes;

    void init(int _dim, ll *_from, ll *_best, ll *_le, ll *_ri) {
        dim = _dim;
        from = _from;
        best = _best;
        le = _le; ri = _ri;

        for (i = 1; i <= dim; i++) from[i] += from[i - 1];
        build(1, 1, dim);
    }

    void build(int node, int l, int r)  {
        if (l == r) {
            best[node] = le[node] = ri[node] = from[l] - from[l - 1];
            return;
        }

        int mid = (l + r) >> 1;
        build(lSon, l, mid);
        build (rSon, mid + 1, r);

        best[node] = max(best[lSon], best[rSon]);
        best[node] = max(best[node], ri[lSon] + le[rSon]);

        le[node] = max(le[lSon], from[mid] - from[l - 1] + le[rSon]);
        ri[node] = max(ri[rSon], ri[lSon] + from[r] - from[mid]);
    }

    void get_nodes(int node, int l, int r, int qL, int qR) {
        if (qL <= l && r <= qR) {
            nodes.pb(mp(node, mp(l, r)));
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid) get_nodes(lSon, l, mid, qL, qR);
        if (qR > mid) get_nodes(rSon, mid + 1, r, qL, qR);
    }

    ll query(int l, int r) {
        nodes.clear();
        get_nodes(1, 1, dim, l, r);

        ll ans = best[nodes[0].first];
        for (auto e : nodes)
            ans = max(ans, best[e.first]);

        ll last = ri[ nodes[0].first ] - from[ nodes[0].second.second ];
        for (i = 1; i < nodes.size(); i++) {
            auto e = nodes[i];

            ans = max(ans, from[e.second.first - 1] + le[e.first] + last);
            last = max(last, ri[e.first] - from[e.second.second]);
        }

        return ans;
    }
};

int n, q, i, l, r;
ll v[maxN];

ll __best[maxN << 2], __le[maxN << 2], __ri[maxN << 2];
aint work;

int main()
{
    freopen("sequencequery.in","r",stdin);
    freopen("sequencequery.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);
    work.init(n, v, __best, __le, __ri);

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &l, &r);
        printf("%lld\n", work.query(l, r));
    }

    return 0;
}
