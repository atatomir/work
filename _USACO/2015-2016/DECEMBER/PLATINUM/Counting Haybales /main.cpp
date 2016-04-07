#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 200011
#define ll long long

#define lSon (node << 1)
#define rSon (lSon | 1)

class aint {
    public:
        void init(int _n, ll *_added, ll *_sum, ll *_mini, ll *_from) {
            n = _n; from = _from;

            added = _added;
            sum = _sum;
            mini = _mini;

            init_tree(1, 1, n);
        }

        void update(int node, int l, int r, int qL, int qR, ll val) {
            if (qL <= l && r <= qR) {
                added[node] += val;
                update_node(node, l, r);
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, val);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR, val);

            update_node(node, l, r);
        }

        ll query_min(int node, int l, int r, int qL, int qR, ll overall) {
            if (qL <= l && r <= qR)
                return overall + mini[node];

            ll ans = 1LL << 60;

            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans = query_min(lSon, l, mid, qL, qR, overall + added[node]);
            if (qR >  mid)
                ans = min(ans, query_min(rSon, mid + 1, r, qL, qR, overall + added[node]) );

            return ans;
        }

        ll query_sum(int node, int l, int r, int qL, int qR, ll overall) {
            if (qL <= l && r <= qR)
                return overall * (r - l + 1) + sum[node];

            ll ans = 0;

            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans += query_sum(lSon, l, mid, qL, qR, overall + added[node]);
            if (qR >  mid)
                ans += query_sum(rSon, mid + 1, r, qL, qR, overall + added[node]);

            return ans;
        }

    private:
        int n, i;
        ll *added;
        ll *sum;
        ll *mini;
        ll *from;

        void update_node(int node, int l, int r) {
            if (l == r) {
                sum[node] = added[node];
                mini[node] = added[node];
                return;
            }

           sum[node] = sum[lSon] + sum[rSon] + added[node] * (r - l + 1);
           mini[node] = min(mini[lSon], mini[rSon]) + added[node];
        }

        void init_tree(int node, int l, int r) {
            if (l == r) {
                added[node] = from[l];
                sum[node] = from[l];
                mini[node] = from[l];
                return;
            }

            int mid = (l + r) >> 1;
            init_tree(lSon, l, mid);
            init_tree(rSon, mid + 1, r);

            update_node(node, l, r);
        }
};

int n, q, i;

ll aint_from[maxN];
ll aint_added[maxN << 2];
ll aint_sum[maxN << 2];
ll aint_mini[maxN << 2];

aint work;
char op;
ll a, b, c;

int main()
{
    freopen("haybales.in","r",stdin);
    freopen("haybales.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++)
        scanf("%lld", &aint_from[i]);

    work.init(n, aint_added, aint_sum, aint_mini, aint_from);

    scanf("\n");
    for (i = 1; i <= q; i++) {
        scanf("%c", &op);
        if (op == 'M') {
            scanf("%lld %lld\n", &a, &b);
            printf("%lld\n", work.query_min(1, 1, n, a, b, 0));
        }

        if (op == 'P') {
            scanf("%lld %lld %lld\n", &a, &b, &c);
            work.update(1, 1, n, a, b, c);
        }

        if (op == 'S') {
            scanf("%lld %lld\n", &a, &b);
            printf("%lld\n", work.query_sum(1, 1, n, a, b, 0));
        }
    }


    return 0;
}
