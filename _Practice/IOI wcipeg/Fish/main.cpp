#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 500011
#define lSon (node << 1)
#define rSon (lSon | 1)

int mod;

class aint{
    public:
        int n;
        vector<int> data;

        void init(int _n) {
            n = _n;
            data.resize(n * 4 + 3);
            init_tree(1, 1, n);
        }

        void update(int node, int l, int r, int pos, int val) {
            if (l == r) {
                data[node] = val % mod;
                return;
            }

            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(lSon, l, mid, pos, val);
            else
                update(rSon, mid + 1, r, pos, val);

            data[node] = (1LL * data[lSon] * data[rSon]) % mod;
        }

        int query(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR) return data[node];

            int mid = (l + r) >> 1;
            int ans = 1;

            if (qL <= mid) ans = query(lSon, l, mid, qL, qR);
            if (qR > mid) ans = (1LL * ans * query(rSon, mid + 1, r, qL, qR)) % mod;

            return ans;
        }

    private:
        void init_tree(int node, int l, int r) {
            data[node] = 1;
            if(l == r) return;

            int mid = (l + r) >> 1;
            init_tree(lSon, l, mid);
            init_tree(rSon, mid + 1, r);
        }
};


int n, k, i, p;
pair<int, int> F[maxN];

vector<int> ord;
vector<int> bucket[maxN];
int used[maxN];
map<int, int> M;

aint work;
int ans, act;


int cb(int val) {
    int ans = 0;

    for (int step = (1 << 19); step; step >>= 1)
        if (ans + step <= k)
            if (bucket[ans + step].back() < 2 * val)
                ans += step;

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &k, &mod);
    for (i = 1; i <= n; i++) scanf("%d%d", &F[i].first, &F[i].second);
    sort(F + 1, F + n + 1);

    for (i = n; i >= 1; i--) {
        if (M[F[i].second]) continue;
        M[F[i].second] = 1;
        ord.pb(F[i].second);
    }

    reverse(ord.begin(), ord.end());
    for (i = 0; i < ord.size(); i++)
        M[ord[i]] = i + 1;
    for (i = 1; i <= n; i++)
        bucket[ M[F[i].second] ].pb(F[i].first);

    work.init(k); p = 0;
    for (i = 1; i <= k; i++) {
        //! add new fish to aint
        int L = bucket[i].back();
        while (p + 1 <= n && F[p + 1].first * 2 <= L) {
            int id = M[F[++p].second];

            work.update(1, 1, k, id, 1 + (++used[id]));
        }

        //! get states with lower groups
        ans += work.query(1, 1, k, 1, i);

        //! get states with upper groups
        int limit = *upper_bound(bucket[i].begin(), bucket[i].end(), L / 2);
        int pos = cb(limit);

        act = 1;

        if (i > 1) act = (act * work.query(1, 1, k, 1, i - 1)) % mod;
        if (pos > i)
            act = (act * (work.query(1, 1, k, i + 1, pos) + mod - 1)) % mod;
        else
            act = 0;

        ans = (ans + act) % mod;
    }

    printf("%d", ans);

    return 0;
}
