#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 277

int n, m, i, x, y;
vector<int> list[maxN], rev[maxN];

int comps;
bool us[maxN];
stack<int> S;
int belong[maxN], daddy[maxN];;

bool is_root[maxN], is_leaf[maxN];
vector<int> adj[maxN];

queue<int> Q;
int leaf_id[maxN];
vector<int> roots, leaves;
vector<int> bip_list[maxN];
int l[maxN], r[maxN];

vector<int> unused[2];
vector< pair<int, int> > paired;
vector< pair<int, int> > ans;


void dfs_to(int node) {
    us[node] = true;

    for (int to : list[node])
        if (!us[to])
            dfs_to(to);

    S.push(node);
}

void dfs_from(int node) {
    us[node] = true;
    belong[node] = comps;

    for (int to : rev[node])
        if (!us[to])
            dfs_from(to);
}

void strong_connected() {
    int i;

    for (i = 1; i <= n; i++)
        if (!us[i])
            dfs_to(i);

    memset(us, 0, sizeof(us));
    while (!S.empty()) {
        int node = S.top(); S.pop();

        if (!us[node])
            daddy[++comps] = node, dfs_from(node);
    }

    for (i = 1; i <= comps; i++) is_root[i] = true;

    for (i = 1; i <= n; i++) {
        for (auto to : list[i]) {
            if (belong[i] != belong[to]) {
                adj[belong[i]].pb(belong[to]);
                is_root[belong[to]] = false;
            }
        }
    }

    n = comps;
    for (i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].resize(unique(adj[i].begin(), adj[i].end()) - adj[i].begin());
    }

    for (i = 1; i <= n; i++)
        is_leaf[i] = adj[i].empty();
}

void add_edges(int node, int id) {
    int i;

    memset(us, 0, sizeof(us));
    us[node] = true;
    Q.push(node);

    while (!Q.empty()) {
        node = Q.front(); Q.pop();

        if (is_leaf[node]) bip_list[id].pb(leaf_id[node]);

        for (int to : adj[node])
            if (!us[to])
                us[to] = true, Q.push(to);
    }
}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (int to : bip_list[node])
        if (r[to] == -1)
            {l[node] = to; r[to] = node; return true;}

    for (int to : bip_list[node])
        if (pairUp(r[to]))
            {l[node] = to; r[to] = node; return true;}

    return false;
}


int main()
{
    freopen("plan.in","r",stdin);
    freopen("plan.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        rev[y].pb(x);
    }

    strong_connected();
    for (i = 1; i <= n; i++) {
        if (is_root[i]) roots.pb(i);
        if (is_leaf[i]) leaves.pb(i), leaf_id[i] = leaves.size() - 1;
    }

    if (n == 1) {
        printf("0");
        return 0;
    }

    for (i = 0; i < roots.size(); i++) add_edges(roots[i], i);
    for (i = 0; i <= n; i++) l[i] = r[i] = -1;

    bool need = true;
    while (need) {
        memset(us, 0, sizeof(us));
        need = false;

        for (i = 0; i < roots.size(); i++)
            if (l[i] == -1)
                need |= pairUp(i);
    }

    for (i = 0; i < roots.size(); i++)
        if (l[i] == -1)
            unused[0].pb( roots[i] );

    for (i = 0; i < leaves.size(); i++)
        if (r[i] == -1)
            unused[1].pb( leaves[i] );

    for (i = 0; i < roots.size(); i++)
        if (l[i] != -1)
            paired.pb(mp(roots[i], leaves[l[i]]));

    paired.pb(paired[0]);
    for (i = 1; i < paired.size(); i++)
        ans.pb(mp(paired[i - 1].second, paired[i].first));

    while (unused[0].size() < unused[1].size()) unused[0].pb(paired[0].first);
    while (unused[1].size() < unused[0].size()) unused[1].pb(paired[0].first);

    for (i = 0; i < unused[0].size(); i++)
        ans.pb(mp(unused[1][i], unused[0][i]));

    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d %d\n", daddy[e.first], daddy[e.second]);

    return 0;
}
