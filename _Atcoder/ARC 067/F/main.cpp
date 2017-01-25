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

#define lSon (node << 1)
#define rSon (lSon | 1)

#define maxN 5011
#define maxM 211
#define inf 1LL << 60

struct aint {
    int n;
    vector<ll> data;
    vector<ll> add;

    void init(int _n) {
        n = _n;
        data = add = vector<ll>(n * 4 + 11, 0);
    }

    void update(int node, int l, int r, int qL, int qR, ll v) {
        if (qL <= l && r <= qR) {
            add[node] += v;
            data[node] += v;
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid)
            update(lSon, l, mid, qL, qR, v);
        if (qR > mid)
            update(rSon, mid + 1, r, qL, qR, v);

        data[node] = max(data[lSon], data[rSon]) + add[node];
    }

    ll query(int node, int l, int r, int qL, int qR) {
        if (qL <= l && r <= qR)
            return data[node];

        int mid = (l + r) >> 1;
        ll ans = -inf;
        if (qL <= mid)
            ans = max(ans, query(lSon, l, mid, qL, qR));
        if (qR > mid)
            ans = max(ans, query(rSon, mid + 1, r, qL, qR));

        return ans;
    }


};

int n, m, i, j;
ll dist[maxN];
ll pay[maxN][maxM];

vector< pair<ll, int> > S[maxN];
aint work;
ll ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 2; i <= n; i++) scanf("%lld", &dist[i]), dist[i] += dist[i - 1];
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%lld", &pay[i][j]);

    for (i = 1; i <= m; i++) S[i] = {{inf, n + 1}};

    work.init(n);
    for (i = 2; i <= n; i++)
        work.update(1, 1, n, i, i, -dist[i]);

    for (i = n; i > 0; i--) {
        for (j = 1; j <= m; j++)
            work.update(1, 1, n, i, i, pay[i][j]);

        for (j = 1; j <= m; j++) {
            while (S[j].back().first < pay[i][j]) {
                int l = S[j].back().second;
                int r = S[j][ S[j].size() - 2 ].second - 1;
                work.update(1, 1, n, l, r, pay[i][j] - S[j].back().first);
                S[j].pop_back();
            }
            S[j].pb(mp(pay[i][j], i));
        }

        ans = max(ans, work.query(1, 1, n, i, n) + dist[i]);
    }

    printf("%lld", ans);


    return 0;
}
