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
#define mod 1000000007

int n, i, x, y;
vector<int> list[maxN], son[maxN];
ll ans = 1;
bool us[maxN];

int nodes, edges;

bool need;
vector<int> way, act;
bool cyc[maxN], any_father[maxN];

ll fact[maxN], inv_fact[maxN];
ll dp[maxN], down[maxN];

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void dfs(int node) {
    us[node] = true;
    nodes++;
    edges += list[node].size();
    act.pb(node);

    if (need) way.pb(node);

    for (auto to : list[node]) {
        if (us[to] && need) {
            if (to != way[way.size() - 2])
                way.pb(to), need = false;
            continue;
        }

        if (us[to]) continue;

        dfs(to);
    }

    if (need) way.pop_back();
}

void assoc(int n1, int n2) {
    int p = 0;

    while (list[n1][p] != n2) {
        son[n1].pb(list[n1][p]);
        any_father[ list[n1][p] ] = true;
        p++;
    }

}

void dfs_low(int node, int root) {
    for (auto to : list[node]) {
        if (cyc[to]) continue;
        if (to == root) continue;
        dfs_low(to, node);
        assoc(to, node);
    }
}

ll dfs_calc(int node) {
    dp[node] = 1;
    down[node] = 1;

    for (auto to : son[node]) {
        dp[node] *= dfs_calc(to);
        dp[node] %= mod;
        down[node] += down[to];
    }

    dp[node] *= fact[down[node] - 1];
    dp[node] %= mod;

    for (auto to : son[node]) {
        dp[node] *= inv_fact[down[to]];
        dp[node] %= mod;
    }

    return dp[node];
}

ll solve(ll R) {
    ll ans1 = 1;
    ll ans2 = 1;

    nodes = edges = 0;
    act.clear();
    way.clear(); need = true;

    dfs(R);

    edges /= 2;
    if (nodes != edges)
        return 0;

    reverse(way.begin(), way.end());
    for (i = 1; way[i] != way[0]; i++);
    way.resize(i);

    for (auto e : way) cyc[e] = true;
    way.pb(way[0]);

    //! first try
    for (auto e : act) any_father[e] = false;
    for (auto e : act) son[e].clear();
    for (i = 0; i + 1 < way.size(); i++) {
        assoc(way[i], way[i + 1]);
        dfs_low(way[i], 0);
    }

    ans1 = fact[act.size()];
    for (auto e : act) {
        if (any_father[e]) continue;
        ans1 *= dfs_calc(e);
        ans1 %= mod;
        ans1 *= inv_fact[down[e]];
        ans1 %= mod;
    }

    //! second try
    for (auto e : act) any_father[e] = false;
    for (auto e : act) son[e].clear();
    for (i = 0; i + 1 < way.size(); i++) {
        assoc(way[i + 1], way[i]);
        dfs_low(way[i], 0);
    }

    ans2 = fact[act.size()];
    for (auto e : act) {
        if (any_father[e]) continue;
        ans2 *= dfs_calc(e);
        ans2 %= mod;
        ans2 *= inv_fact[down[e]];
        ans2 %= mod;
    }

    return (ans1 + ans2) % mod;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= 2 * n; i++) {
        cin >> x >> y;
        list[x].pb(n + y);
        list[n + y].pb(x);
    }

    fact[0] = 1;
    for (i = 1; i <= 2 * n; i++)
        fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[2 * n] = poww(fact[2 * n], mod - 2);
    for (i = 2 * n - 1; i > 0; i--)
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    inv_fact[0] = 1;

    for (i = 1; i <= 2 * n; i++)
        sort(list[i].begin(), list[i].end());

    ans = fact[2 * n];
    for (i = 1; i <= 2 * n; i++) {
        if (us[i]) continue;
        ans *= solve(i);
        ans %= mod;

        ans *= inv_fact[nodes];
        ans %= mod;
    }

    cout << ans;

    return 0;
}
