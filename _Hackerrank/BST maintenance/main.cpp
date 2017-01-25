#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 250011

struct node {
    int id;
    int adj[2];

    node() {
        adj[0] = adj[1] = 0;
    }
};

int n, i, R;
int ord[maxN];
int pos[maxN];
node BST[maxN];

vector<int> st;

bool dead[maxN];
int lvl[maxN];
vector<int> dist[maxN];
vector<int> list[maxN];
vector<int> tree[maxN];
int dad[maxN], cnt[maxN];

ll dp[maxN], prov[maxN], sub[maxN];
ll ans;

void clean(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (dead[v[i]]) {
            v[i] = v.back();
            v.pop_back();
            i--;
            continue;
        }
    }
}

void dfs(int node, int root) {
    clean(list[node]);

    cnt[node] = 1;
    for (auto to : list[node])
        if (to != root)
            dfs(to, node), cnt[node] += cnt[to];
}

int dfs2(int node, int root, int target) {
    bool ok = true;

    for (auto to : list[node]) {
        if (to == root) continue;

        int ans = dfs2(to, node, target);
        if (ans) return ans;

        if (cnt[to] > target / 2)
            ok = false;
    }

    if (target - cnt[node] > target / 2)
        ok = false;

    if (ok) return node;
    return 0;
}

void dfs3(int node, int root, int dst) {
    dist[node].pb(dst);

    for (auto to : list[node]) {
        if (to == root) continue;

        dfs3(to, node, dst + 1);
    }
}

int get_centroid(int node, int act_lvl) {
    int i, target;


    dfs(node, 0);

    target = cnt[node];
    node = dfs2(node, 0, target);

    dfs3(node, 0, 0);

    dead[node] = true;
    for (auto to : list[node]) {
        int aux = get_centroid(to, act_lvl + 1);
        tree[node].pb(aux);
        dad[aux] = node;
    }

    lvl[node] = act_lvl;
    return node;
}

void add_node(int node) {
    ans += dp[node];
    sub[node]++;

    int up, down;
    for (up = dad[node], down = node; up != 0; down = up, up = dad[up]) {
        sub[up]++;

        ans += (dp[up] - prov[down]) + (sub[up] - sub[down]) * dist[node][ lvl[up] ];
        dp[up] += dist[node][ lvl[up] ];
        prov[down] += dist[node][ lvl[up] ];
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &ord[i]), pos[ ord[i] ] = i, BST[i].id = i;

    // Build BST
    st.pb(1);
    for (i = 2; i <= n; i++) {
        if (pos[i] < pos[st[0]]) {
            BST[i].adj[0] = st[0];
            st = {i};
            continue;
        }

        auto it = lower_bound(st.begin(), st.end(), i, [](int a, int b)->bool {
            return pos[a] < pos[b];
        });
        int poss = it - st.begin() - 1;

        BST[st[poss]].adj[1] = i;
        if (poss != st.size() - 1) BST[i].adj[0] = st[poss + 1];
        st.resize(poss + 2);
        st[poss + 1] = i;
    }

    for (i = 1; i <= n; i++) {
        if (BST[i].adj[0]) {
            list[i].pb(BST[i].adj[0]);
            list[BST[i].adj[0]].pb(i);
        }

        if (BST[i].adj[1]) {
            list[i].pb(BST[i].adj[1]);
            list[BST[i].adj[1]].pb(i);
        }
    }

    // Build controid tree
    R = get_centroid(1, 0);

    // Solve the problem
    for (i = 1; i <= n; i++) {
        int node = ord[i];

        add_node(node);
        printf("%lld\n", ans);
    }


    return 0;
}
