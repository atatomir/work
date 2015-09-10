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

#define maxN 2015
#define maxM 15011

int n,m,i,x,y,cost;
vector< pair< int, pair<int, int> > > Edges;
vector< pair<int, int> > list[maxN];

int dist[maxN];
queue<int> Q;
bool inQueue[maxN];

bool unused[maxM];
vector<int> listTo[maxN];
vector<int> listFrom[maxN];
bool us[maxN];
vector<int> order;
int comp[maxN];
int act_comp;

void Bellman() {
    int i;
    for (i = 1; i <= n; i++) dist[i] = 1 << 30;

    dist[0] = 0;
    inQueue[0] = true;
    Q.push(0);

    while(!Q.empty()) {
        int node = Q.front(); Q.pop();
        inQueue[node] = false;

        for (auto neigh : list[node]) {
            int dir = neigh.first;
            int newCost = dist[node] + neigh.second;

            if (newCost >= dist[dir]) continue;
            dist[dir] = newCost;
            if (!inQueue[dir]) {
                inQueue[dir] = true;
                Q.push(dir);
            }
        }
    }
}

void dfsTo(int node) {
    us[node] = true;

    for (auto dir : listTo[node]) {
        if (us[dir]) continue;
        dfsTo(dir);
    }

    order.pb(node);
}

void dfsFrom(int node) {
    comp[node] = act_comp;

    for (auto dir : listFrom[node]) {
        if (comp[dir]) continue;
        dfsFrom(dir);
    }
}

int main()
{
    freopen("zeroc.in","r",stdin);
    freopen("zeroc.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d",&x,&y,&cost);
        Edges.pb( mp(cost, mp(x, y)) );
        list[x].pb( mp(y, cost) );
    }
    for (i = 1; i <= n; i++) list[0].pb( mp(i, 0) );

    Bellman();
    for (i = 0; i < m; i++) {
        int from = Edges[i].second.first;
        int to   = Edges[i].second.second;
        int cc   = Edges[i].first;

        if (dist[from] + cc == dist[to]) {
            listTo[from].pb(to);
            listFrom[to].pb(from);
        } else {
            unused[i] = true;
        }
    }

    for (i = 1; i <= n; i++)
        if (!us[i]) dfsTo(i);


    for (i = n-1; i >= 0; i--) {
        int e = order[i];

        if (comp[e]) continue;
        act_comp++;

        dfsFrom(e);
    }

    int ans = 0;
    for (i = 0; i < m; i++)
        if (comp[Edges[i].second.first] == comp[Edges[i].second.second] && !unused[i]) ans++;

    printf("%d", ans);

    return 0;
}
