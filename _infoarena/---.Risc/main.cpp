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

#define maxN 333
#define maxQ 100011
#define inf 1 << 29

struct query {
    int x, y;
    int rmax, id;

    bool operator<(const query& who)const {
        return rmax < who.rmax;
    }
};

int n, m, q, i, j, x, y, l, rmax, pos;
int R[maxN];
vector< pair<int, int> > Risk;
int adj[maxN][maxN];
vector<query> Q;
int ans[maxQ];

void add_node(int node) {
    int i, j;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            adj[i][j] = min(adj[i][j], adj[i][node] + adj[node][j]);
}

int main()
{
    freopen("risc.in","r",stdin);
    freopen("risc.out","w",stdout);

    scanf("%d%d%d", &n, &m, &q);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        Risk.pb(mp(x, i));
        R[i] = i;
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            adj[i][j] = (i == j ? 0 : inf);

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &l);
        adj[x][y] = adj[y][x] = min(adj[x][y], l);
    }

    for (i = 1; i <= q; i++) {
        scanf("%d%d%d", &x, &y, &rmax);
        Q.pb({x, y, rmax, i});
    }

    sort(Q.begin(), Q.end());

    pos = 0;
    sort(Risk.begin(), Risk.end());

    for (auto e : Q) {
        while (pos < Risk.size()) {
            if (Risk[pos].first > e.rmax) break;
            add_node(Risk[pos].second);
            pos++;
        }

        if (adj[e.x][e.y] >= inf)
            ans[e.id] = -1;
        else
            ans[e.id] = adj[e.x][e.y];
    }

    for (i = 1; i <= q; i++)
        printf("%d\n", ans[i]);




    return 0;
}
