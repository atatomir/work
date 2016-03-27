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

#define maxN 277

int Pay[maxN];

struct cover {
    int value;
    vector<int> nodes;

    cover() {
        value = 0;
        nodes.clear();
    }

    cover(vector<int> who) {
        nodes = who;
        value = 0;
        for (auto e : nodes)
            value += Pay[e];
    }

    void operator+=(cover who) {
        value += who.value;
        for (int e : who.nodes)
            nodes.pb(e);
    }

    void get_max(cover who) {
        if (who.value > value) {
            value = who.value;
            nodes = who.nodes;
        }
    }
};

int n, m, i, j, x, y;
bool adj[maxN][maxN];

bool us[maxN];
vector<int> aux;

cover ans;


void dfs(int node) {
    us[node] = true;
    aux.pb(node);

    for (int i = 1; i <= n; i++)
        if (us[i] == false && adj[i][node])
            dfs(i);
}

cover solve(vector<int> nodes, bool cliq) {
    int i, j;
    cover ans;
    vector< vector<int> > act;

    //! there is only one node
    if (nodes.size() == 1)
        return cover(nodes);

    act.clear();
    for (int e : nodes) us[e] = false;

    //! swap edges
    for (auto n1 : nodes)
        for (auto n2 : nodes)
            adj[n1][n2] ^= 1;

    //! get connex components
    for (int e : nodes) {
        if (us[e]) continue;

        aux.clear();
        dfs(e);
        act.pb(aux);
    }

    //! solve for each component
    for (auto comp : act) {
        if (!cliq)
            ans.get_max(solve(comp, cliq ^ 1));
        else
            ans += solve(comp, cliq ^ 1);
    }

    return ans;
}


int main()
{
    freopen("soc.in","r",stdin);
    freopen("soc.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d", &Pay[i]);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        adj[x][y] = adj[y][x] = true;
    }

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        aux.clear();
        dfs(i);

        ans.get_max( solve(aux, 1) );
    }

    sort(ans.nodes.begin(), ans.nodes.end());
    printf("%d\n%d\n", ans.value, ans.nodes.size());
    for (int e : ans.nodes)
        printf("%d ", e);



    return 0;
}
