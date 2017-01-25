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

#define maxN 300011

struct intr {
    int l, r, mid;
};

int n, m, i;
ll T[maxN], T2[maxN], sum[maxN];
ll best[maxN], best2[maxN];
ll pre[maxN], pre2[maxN];

vector< intr > todo, todo2;
vector< pair<ll, ll> > st;
ll dp[maxN];

ll P, X;

ll when(ll i, ll j) {
    ll up = 2LL * (dp[j] + sum[j] - dp[i] - sum[i]) + j * j - j - i * i + i;
    up = max(up, 0LL);

    return (up + 2LL * (j - i) - 1) / ( 2LL * (j - i) );
}

void add(int act) {
    pair<ll, ll> pr = {act, n + 11};

    while (st.size() >= 2) {
        auto last = st.back();
        pr.second = when(last.first, act);
        if (pr.second < last.second) break;
        st.pop_back();
    }

    if (!st.empty())
        pr.second = when(st.back().first, act);
    st.pb(pr);
}

ll cost(ll l, ll r) {
    return dp[l] + ((r - l) * (r - l + 1) / 2) - (sum[r] - sum[l]);
}

void compute_pre() {
    int i;

    for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + T[i];

    st = {{0, n + 11}};
    for (i = 1; i <= n; i++) {
        while (i >= st.back().second) st.pop_back();
        dp[i] = max(dp[i - 1], cost(st.back().first, i));
        add(i);
    }

    for (i = 1; i <= n; i++) pre2[n - i + 1] = dp[i];

    /// ---

    for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + T2[i];

    st = {{0, n + 11}};
    for (i = 1; i <= n; i++) {
        while (i >= st.back().second) st.pop_back();
        dp[i] = max(dp[i - 1], cost(st.back().first, i));
        add(i);
    }

    for (i = 1; i <= n; i++) pre[n - i + 1] = dp[i];


}

void adv(ll *T, const vector<intr>& todo, ll *best, ll *pre) {
    int i, pos, aux;

    pos = 1;
    st = {{0, n + 11}};
    for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + T[i];

    for (auto e : todo) {
        while (pos < e.mid) {
            while (st.back().second <= pos) st.pop_back();
            dp[pos] = max(dp[pos - 1], cost(st.back().first, pos));
            add(pos++);
        }

        aux = st.size() - 1;
        for (i = e.mid; i <= e.r; i++) {
            while (i >= st[aux].second) aux--;
            dp[i] = cost(st[aux].first, i) + pre[i + 1];
        }

        best[e.r] = max(best[e.r], dp[e.r]);
        for (i = e.r - 1; i >= e.mid; i--) {
            dp[i] = max(dp[i], dp[i + 1]);
            best[i] = max(best[i], dp[i]);
        }

    }
}

void solve() {
    int i;

    todo2.clear();
    for (i = 0; i < todo.size(); i++) {
        todo[i].mid = (todo[i].l + todo[i].r) >> 1;
        todo2.pb({n - todo[i].r + 1, n - todo[i].l + 1, n - todo[i].mid + 1});
    }

    reverse(todo2.begin(), todo2.end());

    adv(T, todo, best, pre);
    adv(T2, todo2, best2, pre2);

    todo2 = todo;
    todo.clear();

    for (auto e : todo2) {
        if (e.l < e.mid)
            todo.pb({e.l, e.mid - 1, 0});
        if (e.r > e.mid)
            todo.pb({e.mid + 1, e.r, 0});
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &T[i]);
        best[i] = 1 - T[i];

        T2[n - i + 1] = T[i];
        best2[n - i + 1] = best[i];
    }

    compute_pre();

    todo = {{1, n, (1 + n) >> 1}};
    while (!todo.empty())
        solve();

    for (i = 1; i <= n; i++) {
        best[i] = max(best[i], best2[n - i + 1]);
    }

    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        scanf("%lld%lld", &P, &X);

        ll ans = pre[P + 1] + pre2[n - (P - 1) + 1];
        ans = max(ans, best[P] + T[P] - X);

        printf("%lld\n", ans);
    }


    return 0;
}
