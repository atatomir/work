#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

#define maxN 50011 * 5
#define lSon (node << 1)
#define rSon (lSon | 1)

ll full[maxN << 2], lf[maxN << 2], rh[maxN << 2], best[maxN << 2];
ll *from;

ll work_to[maxN], work_from[maxN];

class aint {
    public:
        void init(int _n, ll *_from) {
            n = _n; from = _from;
            init_tree(1, 1, n);
        }

        ll Query(int l, int r) {
            nodes.clear();
            _query(1, 1, n, l, r);

            int cnt = nodes.size();
            ll ans = 0;

            for (auto e : nodes) ans = max(ans, best[e]);

            work_to[0] = lf[ nodes[0] ];
            for (int i = 1; i < cnt; i++)
                work_to[i] = work_to[i - 1] - lf[ nodes[i - 1] ] + full[ nodes[i - 1] ] + lf[ nodes[i] ];

            work_from[cnt - 1] = rh[ nodes[cnt - 1] ];
            for (int i = cnt - 2; i >= 0; i--)
                work_from[i] = work_from[i + 1] - rh[ nodes[i + 1] ] + full[ nodes[i + 1] ] + rh[ nodes[i] ];

            ll fully = work_from[0] - rh[ nodes[0] ] + full[ nodes[0] ];
            ll can_use = work_from[0];

            for (int i = 1; i < cnt; i++) {
                ans = max(ans, work_to[i] + can_use - fully);
                can_use = max(can_use, work_from[i]);
            }

            return ans;
        }

    private:
        int n;
        vector<int> nodes;

        void init_tree(int node, int l, int r) {
            if (l == r) {
                full[node] = from[l];
                lf[node] = rh[node] = max(0LL, from[l]);
                best[node] = lf[node];
                return;
            }

            int mid = (l + r) >> 1;
            init_tree(lSon, l, mid);
            init_tree(rSon, mid + 1, r);

            full[node] = full[lSon] + full[rSon];
            lf[node] = max(lf[lSon], full[lSon] + lf[rSon]);
            rh[node] = max(rh[rSon], full[rSon] + rh[lSon]);

            best[node] = max(best[lSon], best[rSon]);
            best[node] = max(best[node], rh[lSon] + lf[rSon]);
        }

        void _query(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR) {
                nodes.pb(node);
                return ;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid) _query(lSon, l, mid, qL, qR);
            if (qR > mid) _query(rSon, mid + 1, r, qL, qR);
        }
};


int n, m, i, cnt, l, r;
ll v[maxN], dp_l[maxN], dp_r[maxN];
ll aux[maxN];

aint work;

int main()
{
    freopen("3max.in", "r", stdin);
    freopen("3max.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);

    for (i = 1; i <= n; i++)
        dp_l[i] = max(0LL, dp_l[i - 1]) + v[i];
    for (i = 1; i <= n; i++)
        dp_l[i] = max(dp_l[i], dp_l[i - 1]);

    for (i = n; i >= 1; i--)
        dp_r[i] = max(0LL, dp_r[i + 1]) + v[i];
    for (i = n; i >= 1; i--)
        dp_r[i] = max(dp_r[i], dp_r[i + 1]);

    for (i = 1; i <= n; i++) {
        aux[++cnt] = v[i];

        aux[++cnt] = -dp_l[i];
        aux[++cnt] = +dp_l[i];

        aux[++cnt] = +dp_r[i + 1];
        aux[++cnt] = -dp_r[i + 1];
    }

    work.init(cnt, aux);
    for (int qq = 1; qq <= m; qq++) {
        scanf("%d %d", &l, &r);

        l = max(1, ((l - 1) * 5) - 3);
        r = min(cnt, ((r) * 5 ) + 3);

        printf("%lld\n", max(0LL, work.Query(l, r) ));
    }

    return 0;
}
