#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define lSon (node << 1)
#define rSon (lSon | 1)

const int maxN = 200011;

struct aint {
    pair<int, int> data[maxN * 4 + 11];

    void refr(int n) {
        for (int i = 0; i <= 4 * n + 3; i++) data[i] = mp(0, 0);
    }

    void upd(int node, int l, int r, int pos, int v) {
        if (l == r) {
            data[node].first = v;
            data[node].second = l;
            return;
        }

        int mid = (l + r) >> 1;
        if (pos <= mid) upd(lSon, l, mid, pos, v);
        else            upd(rSon, mid + 1, r, pos, v);
        data[node] = max(data[lSon], data[rSon]);
    }

    pair<int, int> que(int node, int l, int r, int qL, int qR) {
        if (qL <= l && r <= qR) return data[node];

        int mid = (l + r) >> 1;
        pair<int, int> ans = mp(0, 0);
        if (qL <= mid) ans = que(lSon, l, mid, qL, qR);
        if (qR > mid) ans = max(ans, que(rSon, mid + 1, r, qL, qR));
        return ans;
    }
};

int t, ti;
int n, m, a, b, i, j, x, pos;
vector<int> list[maxN];
int bg[maxN], en[maxN], cnt[maxN];
aint work;
ll ans;

void dfs(int node) {
    bg[node] = ++pos;
    work.upd(1, 1, n, pos, node);

    for (auto to : list[node])
        dfs(to);

    en[node] = pos;
}

void solve(int node) {
    for (auto to : list[node])
        solve(to);

    while (cnt[node] > 0) {
        auto act = work.que(1, 1, n, bg[node], en[node]);
        if (act.first == 0) return;
        ans += 1LL * act.first - 1LL;
        work.upd(1, 1, n, act.second, 0);
        cnt[node]--;
    }
}

ll solve() {
    int i, j;

    scanf("%d%d%d%d", &n, &m, &a, &b);

    pos = 0;
    for (i = 1; i <= n; i++) {
        list[i].clear();
        cnt[i] = bg[i] = en[i] = 0;
    }
    work.refr(n);

    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        list[x + 1].pb(i);
    }

    dfs(1);

    for (i = 0; i < m; i++) {
        x = (a * i + b) % n;
        cnt[x + 1]++;
    }

    ans = 0;
    solve(1);
    return ans;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';
        printf("Case #%d: %lld\n", ti, solve());
    }


    return 0;
}
