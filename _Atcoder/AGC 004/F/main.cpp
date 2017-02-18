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

int n, m, x, y, i;
vector<int> list[maxN];
int col[maxN];

bool us[maxN];
ll in[maxN], sum[maxN];

vector<int> way, cyc;


ll abss(ll a) {
    if (a < 0) return -a;
    return a;
}

void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to]) continue;
        col[to] = col[node] ^ 1;
        dfs(to);
    }
}

ll solve_simple(int node, int root) {
    ll ans = 0;

    sum[node] = in[node];

    for (auto to : list[node]) {
        if (to == root) continue;
        ans += solve_simple(to, node);
        sum[node] += sum[to];
    }

    return ans + abss(sum[node]);
}

void find_cyc(int node) {
    if (!cyc.empty()) return;

    way.pb(node);
    us[node] = true;

    for (auto to : list[node]) {
        if (way.size() >= 2)
            if (to == way[way.size() - 2])
                continue;

        if (us[to]) {
            int i;

            cyc.pb(to);
            while (way.back() != to) {
                cyc.pb(way.back());
                way.pop_back();
            }

            return ;

        } else {
            find_cyc(to);
            if (!cyc.empty()) return;
        }
    }

    us[node] = false;
    way.pop_back();
}

void rm_edge(int x, int y) {
    for (int i = 0; i < list[x].size(); i++) {
        if (list[x][i] == y) {
            list[x][i] = list[x].back();
            break;
        }
    }

    swap(x, y);

    for (int i = 0; i < list[x].size(); i++) {
        if (list[x][i] == y) {
            list[x][i] = list[x].back();
            break;
        }
    }

    list[x].pop_back();
    list[y].pop_back();
}

ll check(int u, int v, ll mid) {
    int i;

    for (i = 1; i <= n; i++) in[i] = (col[i] ? 1 : -1);
    in[u] += mid;
    in[v] -= mid;
    ll ans = solve_simple(1, 0);
    in[u] -= mid;
    in[v] += mid;

    return ans;
}

void solve_even() {
    int u, v;
    ll ans;

    u = cyc[0];
    v = cyc[1];

    rm_edge(u, v);

    for (i = 1; i <= n; i++) in[i] = (col[i] ? 1 : -1);
    ans = solve_simple(1, 0);

    if (sum[1] != 0) {
        printf("-1");
        exit(0);
    }

    ll l = -n;
    ll r = n;

    while (r - l + 1 > 10) {
        ll mid1 = (2 * l + r) / 3;
        ll mid2 = (l + 2 * r) / 3;

        ll ans1 = check(u, v, mid1) + abss(mid1);
        ll ans2 = check(u, v, mid2) + abss(mid2);

        if (ans1 <= ans2)
            r = mid2;
        else
            l = mid1;
    }

    ans = 1LL << 60;
    for (int i = l; i <= r; i++)
        ans = min(ans, check(u, v, i) + abss(i));

    printf("%lld", ans);
}

void solve_odd() {
    int i, u, v;

    cyc.pb(cyc[0]);
    for (i = 0; i + 1 < cyc.size(); i++) {
        if (col[cyc[i]] != col[cyc[i + 1]]) continue;
        u = cyc[i];
        v = cyc[i + 1];

        break;
    }

    rm_edge(u, v);

    for (i = 1; i <= n; i++) in[i] = (col[i] ? 1 : -1);
    ll ans = solve_simple(1, 0);
    if (abss(sum[1]) % 2 == 1) {
        printf("-1");
        exit(0);
    }

    for (i = 1; i <= n; i++) in[i] = (col[i] ? 1 : -1);
    in[u] -= sum[1] / 2;
    in[v] -= sum[1] / 2;
    ll add = sum[1] / 2;
    ans = solve_simple(1, 0);

    printf("%lld", ans + abss(add));
}


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);

    if (n - 1 == m) {
        for (i = 1; i <= n; i++) in[i] = (col[i] ? 1 : -1);
        ll ans = solve_simple(1, 0);

        if (sum[1] != 0)
            printf("-1");
        else
            printf("%lld", ans);
    } else {
        memset(us, 0, sizeof(us));
        find_cyc(1);

        if (cyc.size() % 2 == 0)
            solve_even();
        else
            solve_odd();
    }


    return 0;
}
