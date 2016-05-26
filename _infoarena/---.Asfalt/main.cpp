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

#define maxN 555
#define inf 1000000000

//! ------------------
        /* flow */
    int C[maxN][maxN];
    int F[maxN][maxN];
    vector<int> adj[maxN];
    int dist[maxN], prov[maxN];
    queue<int> Q;

    int ans_flow;
//!--------------------

int n, m, i, x, y, c, S, D;
vector< pair<int, int> > list[maxN];
int dijk[2][maxN];

priority_queue< pair<int, int> > H;

bool us[maxN];
vector<int> dir[maxN];
vector< pair<int, int> > edges;

void compute_dijk(int sour, int *dijk) {
    int i;

    for (i = 1; i <= n; i++) dijk[i] = inf;

    dijk[sour] = 0;
    H.push(mp(-0, sour));

    while (!H.empty()) {
        int cost = -H.top().first;
        int node = H.top().second;
        H.pop();

        if (dijk[node] != cost) continue;
        for (auto to : list[node]) {
            if (dijk[to.first] > dijk[node] + to.second) {
                dijk[to.first] = dijk[node] + to.second;
                H.push(mp(-dijk[to.first], to.first));
            }
        }
    }
};

bool bellman() {
    int i;

    while (!Q.empty()) Q.pop();
    for (i = 1; i <= n; i++) dist[i] = inf;

    dist[S] = 0;
    Q.push(S);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (node == D) continue;

        for (int to : adj[node]) {
            if (dist[to] <= dist[node] + 1) continue;
            if (C[node][to] == F[node][to]) continue;

            dist[to] = dist[node] + 1;
            prov[to] = node;
            Q.push(to);
        }
    }

    if (dist[D] == inf) return false;

    for (int bg : adj[D]) {
        if (dist[bg] == inf) continue;
        prov[D] = bg;

        int flow = inf;
        for (int node = D; node != S; node = prov[node])
            flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);

        for (int node = D; node != S; node = prov[node]) {
            F[prov[node]][node] += flow;
            F[node][prov[node]] -= flow;
        }

        ans_flow += flow;
    }

    return true;
}

void dfs(int node) {
    us[node] = true;

    for (int to : adj[node]) {
        if (us[to]) continue;

        if (C[node][to] != F[node][to])
            dfs(to);
    }
}


int main()
{
    freopen("asfalt.in","r",stdin);
    freopen("asfalt.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &S, &D);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        list[y].pb(mp(x, c));
    }

    //! get distances
    compute_dijk(S, dijk[0]);
    compute_dijk(D, dijk[1]);

    //! add edges to flow network
    for (i = 1; i <= n; i++) {
        for (auto to : list[i]) {
            if (dijk[0][i] + to.second + dijk[1][to.first] == dijk[0][D] ) {
                C[i][to.first] = 1;
                adj[i].pb(to.first);
                adj[to.first].pb(i);

                dir[i].pb(to.first);
            }
        }
    }

    //! compute flow
    while (bellman());

    //! get edges
    dfs(S);

    for (i = 1; i <= n; i++)
        if (us[i])
            for (int to : dir[i])
                if (us[to] == false)
                    edges.pb(mp(i, to));

    printf("%d\n", ans_flow);
    for (auto e : edges) {
        if (e.first > e.second) swap(e.first, e.second);
        printf("%d %d\n", e.first, e.second);
    }


    return 0;
}
