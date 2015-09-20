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

#define maxN 100011
const long long base = 117LL ;
const long long mod  = 666013LL ;

int n, i, x, y, ans;
vector<int> list[maxN];

int dad[maxN];
int color[maxN];
bool goodTree;
int m, act_color;
vector<int> heads;

long long dp[maxN];
int lvl[maxN];
int gr[maxN];
queue<int> Q;
int arb_nodes;
vector<long long> v_comp;

bool canGo(int from, int to) {
    return color[from] == color[to];
}

void dfs_color(int node) {
    if (dp[node] == 0) return;

    color[node] = act_color;
    for (auto to : list[node])
        if (dad[node] != to)
            dfs_color(to);
}

void dfs_merge(int node) {
    if (goodTree == false) return;

    dp[node] = 1;
    for (auto to : list[node]) {
        if (dad[node] == to) continue;
        dad[to] = node;
        dfs_merge(to);
        dp[node] += dp[to];
    }

    if (dp[node] > m) {
        goodTree = false;
        return;
    }

    if (dp[node] == m) {
        dp[node] = 0;

        color[node] = ++act_color;
        for (auto to : list[node])
            if (dad[node] != to)
                dfs_color(to);

        dfs_color(node);
        heads.pb(node);
    }
}

void dfs_init(int node) {
    gr[node] = 0;
    lvl[node] = 0;
    dp[node] = 0;
    arb_nodes++;

    for (auto to : list[node]) {
        if (!canGo(node, to)) continue;
        gr[node]++;

        if (dad[node] != to) dfs_init(to);
    }

    if (gr[node] == 1) {
        Q.push(node);
        lvl[node] = 1;
    }
}

void computeNode(int node) {
    //! hashing...
    dp[node] = 1;
    v_comp.clear();

    for(auto to : list[node]) {
        if (!canGo(node, to)) continue;
        if (lvl[to] == 0 || lvl[to] >= lvl[node]) continue;

        v_comp.pb( dp[to] );
    }

    sort(v_comp.begin(), v_comp.end());

    for (auto e : v_comp)
        dp[node] = (dp[node] * base + e) % mod;
}

pair<long long, long long> solve_queue() {
    int aux = arb_nodes;
    vector<int> tmp;
    tmp.clear();

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        computeNode(node);

        if (aux-- <= 2) tmp.pb(node);

        for (auto to : list[node]) {
            if (lvl[to] >= lvl[node]) continue;
            if (!canGo(node, to)) continue;

            if (--gr[to] == 1) {
                Q.push(to);
                lvl[to] = lvl[node] + 1;
            }
        }
    }

    if (lvl[tmp[0]] < lvl[tmp[1]]) return mp(dp[tmp[1]], dp[tmp[1]]);
    if (dp[tmp[0]] > dp[tmp[1]]) swap(tmp[0], tmp[1]);
    return mp(dp[tmp[0]], dp[tmp[1]]);
}

bool solve(int _m) {
    m = _m;
    if (n % m != 0) return false;

    goodTree = true;
    heads.clear();
    dfs_merge(1);

    if (dp[1] != 0) goodTree = false;
    if (goodTree == false) return false;

    //! check ...

    pair<long long, long long> must = mp(-1, -1);

    for (auto head : heads) {
        while (!Q.empty()) Q.pop();
        arb_nodes = 0;
        dfs_init(head);

        if (must.first == -1)
            must = solve_queue();
        else {
            auto aux = solve_queue();
            if (aux != must) return false;
        }
    }

    return true;
}

int main()
{
    freopen("divizori2.in","r",stdin);
    freopen("divizori2.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    ans = 2;
    for (int div = 2; div < n; div++)
        if (solve(div)) ans++;

    printf("%d", ans);

    return 0;
}
