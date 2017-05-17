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

int n, m, i, x, y, z, R, target;
vector< pair<int, ll> > list[maxN];
ll len;

bool dead[maxN];
int dad[maxN], dp[maxN], lvl[maxN];
vector<ll> pre[maxN];

vector<ll> down[maxN], subtr[maxN];

void rm_dead(vector< pair<int, ll> >& aux) {
    int i;

    for (i = 0; i < aux.size(); i++) {
        if (dead[aux[i].first]) {
            aux[i] = aux.back();
            aux.pop_back();
            i--;
        }
    }
}

void dfs1(int node, int root) {
    rm_dead(list[node]);

    dp[node] = 1;
    for (auto to : list[node]) {
        if (to.first == root) continue;
        dfs1(to.first, node);
        dp[node] += dp[to.first];
    }
}

int dfs2(int node, int root, int target) {
    bool ok = (target - dp[node] <= (target / 2));

    for (auto to : list[node]) {
        if (to.first == root) continue;

        int ans = dfs2(to.first, node, target);
        if (ans != -1) return ans;

        if (dp[to.first] > target / 2) ok = false;
    }

    if (!ok) return -1;
    return node;
}

void dfs3(int node, int root, ll act) {
    pre[node].pb(act);

    for (auto to : list[node]) {
        if (to.first == root) continue;
        dfs3(to.first, node, act + to.second);
    }
}

int build_tree(int R, int _lvl) {
    dfs1(R, 0);
    R = dfs2(R, 0, dp[R]);
    dfs3(R, 0, 0);

    dead[R] = true;
    lvl[R] = _lvl;
    for (auto to : list[R]) {
        int aux = build_tree(to.first, _lvl + 1);
        dad[aux] = R;
    }

    return R;
}

void add_node(int node) {
    int up, last;

    up = node; last = 0;
    for (; up != 0; last = up, up = dad[up]) {
        down[up].pb(pre[node][lvl[up]]);
        subtr[last].pb(pre[node][lvl[up]]);
    }
}

int query(int node, ll len) {
    int up, last;
    ll aux;
    int ans = 0;

    up = node; last = 0;
    for (; up != 0; last = up, up = dad[up]) {
        aux = len - pre[node][lvl[up]];

        ans += upper_bound(down[up].begin(), down[up].end(), aux) - down[up].begin();
        ans -= upper_bound(subtr[last].begin(), subtr[last].end(), aux) - subtr[last].begin();
    }

    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        list[x].pb(mp(y, z));
        list[y].pb(mp(x, z));
    }

    R = build_tree(1, 0);
    for (i = 1; i <= n; i++) add_node(i);

    down[0].clear(); subtr[0].clear();
    for (i = 1; i <= n; i++) {
        sort(down[i].begin(), down[i].end());
        sort(subtr[i].begin(), subtr[i].end());
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%lld", &x, &len);
        printf("%d\n", query(x, len));
    }


    return 0;
}
