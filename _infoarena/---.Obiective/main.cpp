#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>


using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 33011
#define maxLog 17

int n, m, k, t, i, x, y;


vector<int> list_to[maxN];
vector<int> list_from[maxN];
vector<int> aux;
bool us[maxN];

int components;
int belong[maxN];

int gr_in[maxN], gr_out[maxN];
vector<int> list[maxN];
map< pair<int, int>, bool > check_edge;

bool is_set[maxN];
vector<int> tree_edge[maxN];
vector<int> back_edge[maxN];
queue<int> Q;
int Head;

int dad[maxLog][maxN];
int lvl[maxN];
int low[maxLog][maxN];



void dfs_to(int node) {
    us[node] = true;

    for (int to : list_to[node])
        if (us[to] == false)
            dfs_to(to);

    aux.pb(node);
}

void dfs_from(int node) {
    belong[node] = components;

    for (int to : list_from[node])
        if (belong[to] == 0)
            dfs_from(to);
}

void strong_connected() {
    int i;

    memset(us, 0, sizeof(us));
    aux.clear();

    for (i = 1; i <= n; i++)
        if (!us[i])
            dfs_to(i);

    reverse(aux.begin(), aux.end());

    for (int node : aux) {
        if (belong[node]) continue;
        belong[node] = ++components;
        dfs_from(node);
    }

    check_edge.clear();

    for (i = 1; i <= n; i++) {
        for (int to : list_to[i]) {
            if (belong[i] == belong[to]) continue;

            pair<int, int> check_elem = mp(belong[i], belong[to]);
            if ( check_edge[ check_elem ] == false ) {
                check_edge[ check_elem ] = true;
                list[ belong[i] ].pb(belong[to]);

                gr_in[ belong[to] ]++;
                gr_out[ belong[i] ]++;
            }
        }
    }

    //! n becomes components
    n = components;
}

void build_tree() {
    int i;

    while (!Q.empty()) Q.pop();
    for (i = 1; i <= n; i++)
        if (gr_in[i] == 0)
            Q.push(i);

    Head = Q.front();

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        is_set[node] = true;

        for (int to : list[node]) {
            if (is_set[to]) continue;

            gr_in[to]--;
            if (gr_in[to] == 0) {
                tree_edge[node].pb(to);
                Q.push(to);
                dad[0][to] = node;
            } else {
                back_edge[to].pb(node);
            }
        }
    }

}

void precompute_lca() {
    int i, j;

    for (i = 1; i < maxLog; i++)
        for (j = 1; j <= n; j++)
            dad[i][j] = dad[i - 1][ dad[i - 1][j] ];
}

void dfs(int node) {
    low[0][node] = dad[0][node];
    if (node == Head)  low[0][node] = Head;

    for (int to : tree_edge[node]) {
        lvl[to] = lvl[node] + 1;
        dfs(to);

        if (lvl[ low[0][to] ] < lvl[ low[0][node] ])
            low[0][node] = low[0][to];
    }

    for (int to : back_edge[node])
        if (lvl[to] < lvl[low[0][node]])
            low[0][node] = to;
}

void precompute_low() {
    int i, j;

    for (i = 1; i < maxLog; i++)
        for (j = 1; j <= n; j++)
            low[i][j] = low[i - 1][ low[i - 1][j] ];
}

int go_up(int x, int how) {
    for (int i = 0; how; i++, how >>= 1)
        if (how & 1)
            x = dad[i][x];
    return x;
}

int get_lca_level(int x, int y) {
    if (lvl[x] > lvl[y]) swap(x, y);

    y = go_up(y, lvl[y] - lvl[x]);
    if (x == y) return lvl[x];

    for (int i = maxLog - 1; i >= 0; i--) {
        if (dad[i][x] != dad[i][y]) {
            x = dad[i][x];
            y = dad[i][y];
        }
    }

    return lvl[x] - 1;
}

int get_cost(int x, int target) {
    int i, pay;

    if (target >= lvl[x]) return 0;

    pay = 0;

    for (i = maxLog - 1; i >= 0; i--) {
        int upper = low[i][x];

        if (lvl[upper] > target)
            x = upper, pay += (1 << i);
    }

    return pay + 1;
}


int main()
{
    freopen("obiective.in","r",stdin);
    freopen("obiective.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list_to[x].pb(y);
        list_from[y].pb(x);
    }

    strong_connected();
    build_tree();
    precompute_lca();
    dfs(Head);
    precompute_low();

    scanf("%d", &t);

    for (; t; t--) {
        scanf("%d %d", &x, &y);

        x = belong[x];
        y = belong[y];

        int lca_level = get_lca_level(x, y);
        int ans = get_cost(x, lca_level);

        printf("%d\n", ans);
    }


    return 0;
}
