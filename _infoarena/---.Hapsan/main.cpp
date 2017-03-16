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

struct aint {
    int n;
    vector<int> data;

    void init(int _n) {
        n = _n;
        data = vector<int>(n * 4 + 11, n + 11);
    }

    void upd(int node, int l, int r, int qL, int qR, int v) {
        if (qL <= l && r <= qR) {
            data[node] = min(data[node], v);
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid)
            upd(lSon, l, mid, qL, qR, v);
        if (qR > mid)
            upd(rSon, mid + 1, r, qL, qR, v);
    }

    int query(int node, int l, int r, int pos) {
        if (l == r)
            return data[node];

        int mid = (l + r) >> 1;
        if (pos <= mid)
            return min(data[node], query(lSon, l, mid, pos));
        else
            return min(data[node], query(rSon, mid + 1, r, pos));
    }
};

int n, i, j, k, m, x, y;
int tp[maxN];
vector< pair<int, int> > ord;

ll aib[maxN], dp[maxN];
aint work;
ll ans;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, ll v) {
    while (pos <= n) {
        aib[pos] = max(aib[pos], v);
        pos += zrs(pos);
    }
}

ll sum(int pos) {
    ll ans = 0;

    while (pos > 0) {
        ans = max(ans, aib[pos]);
        pos -= zrs(pos);
    }

    return ans;
}


int main()
{
    freopen("hapsan.in","r",stdin);
    freopen("hapsan.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &tp[i]);
        ord.pb(mp(tp[i], i));
    }
    sort(ord.begin(), ord.end());

    work.init(n);

    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        work.upd(1, 1, n, x, y, x - 1);
    }

    for (i = 0; i < ord.size(); i = j) {
        for (j = i; j < ord.size(); j++)
            if (ord[i].first != ord[j].first)
                break;

        for (k = i; k < j; k++) {
            int pos = ord[k].second;
            int le = min(pos - 1, work.query(1, 1, n, pos));
            dp[k] = ord[k].first + sum(le);
        }

        for (k = i; k < j; k++) {
            int pos = ord[k].second;
            add(pos, dp[k]);
            ans = max(ans, dp[k]);
        }
    }

    printf("%lld", ans);


    return 0;
}
