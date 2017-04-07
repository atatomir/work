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

#define maxN 100011

struct edge {
    int to;
    int w;
    int dif;
};

int n, mod, i, x, y, w;
vector< pair<int, int> > list[maxN];
vector<edge> adj[maxN];
int gr[maxN], data[maxN];
queue<int> Q;
bool us[maxN];

int sol[maxN];
vector<int> costs, dif, nodes, inv;

int poww(int a, int b) {
    int ans = 1;
    a %= mod;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void dfs(int node) {
    us[node] = true;
    nodes.pb(node);
    dif.pb(data[node]);

    for (auto to : list[node]) {
        if (us[to.first]) continue;

        costs.pb(to.second);
        dfs(to.first);
    }
}

void solve(int node) {
    us[node] = true;
    nodes.pb(node);

    for (auto e : adj[node]) {
        if (us[e.to]) continue;

        int aux = (e.dif * poww(e.w, mod - 2)) % mod;
        aux = (aux + sol[node]) % mod;
        sol[e.to] = aux;
        solve(e.to);
    }
}

void solve_cycle() {
    int w = 1;
    int i;
    int sum_down = 0;
    int sum_up = 0, sumi = 0;

    for (auto e : costs) inv.pb(poww(e, mod - 2));
    for (auto e : inv) sum_down += e, sum_down %= mod;
    sum_down %= mod;
    sum_down = poww(sum_down, mod - 2);

    for (i = 0; i < costs.size(); i++) {
        sumi += dif[i];
        sumi %= mod;
        sum_up += (sumi * inv[i]) % mod;
        sum_up %= mod;
    }
    sum_up %= mod;

    w = sum_up * sum_down;
    w %= mod;


    dif[0] += mod - w;
    dif[0] %= mod;

    for (i = 0; i + 1 < nodes.size(); i++) {
        int n1 = nodes[i];
        int n2 = nodes[i + 1];

        adj[n1].pb({n2, costs[i], dif[i]});
        adj[n2].pb({n1, costs[i], (mod - dif[i]) % mod});
        dif[i + 1] += dif[i];
        dif[i + 1] %= mod;
    }
}

int main()
{
    freopen("sistem3.in","r",stdin);
    freopen("sistem3.out","w",stdout);

    scanf("%d%d", &n, &mod);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &x, &y, &w);
        list[x].pb(mp(y, w));
        list[y].pb(mp(x, w));
        gr[x]++;
        gr[y]++;
    }

    for (i = 1; i <= n; i++) scanf("%d", &data[i]);

    for (i = 1; i <= n; i++)
        if (gr[i] == 1)
            Q.push(i);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        us[node] = true;

        for (auto to : list[node]) {
            if (us[to.first]) continue;
            if (--gr[to.first] == 1) Q.push(to.first);
            data[to.first] += data[node];
            data[to.first] %= mod;

            adj[node].pb({to.first, to.second, data[node]});
            adj[to.first].pb({node, to.second, (mod - data[node]) % mod});
        }
    }

    for (i = 1; i <= n; i++) {
        if (!us[i]) {
            dfs(i);

            for (auto to : list[nodes.back()])
                if (to.first == nodes[0])
                    costs.pb(to.second);

            solve_cycle();

            memset(us, 0, sizeof(us));
            solve(1);
            break;
        }
    }

    for (i = 1; i <= n; i++)
        printf("%d\n", sol[i]);


    return 0;
}
