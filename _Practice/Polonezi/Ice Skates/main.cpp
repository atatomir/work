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

ll max3(ll a, ll b, ll c) {
    return max(a, max(b, c));
}

ll best[maxN << 2], le[maxN << 2], ri[maxN << 2], sum[maxN << 2];

struct aint {
    int n;

    void build (int node, int l, int r, ll init_val) {
        best[node] = le[node] = ri[node] = init_val;
        sum[node] = (r - l + 1) * le[node];
        if (l == r) return;

        int mid = (l + r) >> 1;
        build(lSon, l, mid, init_val);
        build(rSon, mid + 1, r, init_val);
    }

    void init(int _n, ll init_val) {
        n = _n;
        build(1, 1, n, init_val);
    }

    void update(int node, int l, int r, int pos, ll val) {
        if (l == r) {
            best[node] = le[node] = ri[node] = sum[node] = val;
            return;
        }

        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lSon, l, mid, pos, val);
        else
            update(rSon, mid + 1, r, pos, val);

        sum[node] = sum[lSon] + sum[rSon];
        best[node] = max3(best[lSon], best[rSon], ri[lSon] + le[rSon]);
        le[node] = max(le[lSon], sum[lSon] + le[rSon]);
        ri[node] = max(ri[rSon], sum[rSon] + ri[lSon]);
    }
};

int N, n, m, i;
ll k, d, sz, cnt;
ll val[maxN];
aint work;


int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%lld%lld", &n, &m, &k, &d);

    N = n - d;
    work.init(N, -k);

    for (i = 1; i <= N; i++) val[i] = -k;

    for (i = 1; i <= m; i++) {
        scanf("%lld%lld", &sz, &cnt);
        val[sz] += cnt;
        work.update(1, 1, N, sz, val[sz]);

        if (best[1] <= k * d)
            printf("TAK\n");
        else
            printf("NIE\n");
    }


    return 0;
}
