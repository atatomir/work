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

#define maxNode 811
#define inf 1000000000

int n, m, i, k, x, y, z;

int S, D, no_home;
vector<int> list[maxNode];
int cost[maxNode][maxNode];
int C[maxNode][maxNode];
int F[maxNode][maxNode];

int prov[maxNode];
int dist[maxNode];
bool inQueue[maxNode];
queue<int> Q;

int ans;
vector< pair<int, int> > sol;


void add_edge(int x, int y, int pay, int cap) {
    list[x].pb(y);
    cost[x][y] = pay;
    C[x][y] = cap;

    list[y].pb(x);
    cost[y][x] = -pay;
    C[y][x] = 0;
}


bool bellman() {
    int i;

    for (i = S; i <= D; i++) dist[i] = -inf;

    dist[S] = 0;
    Q.push(S);
    inQueue[S] = true;

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        inQueue[node] = false;

        for (int to : list[node]) {
            if (F[node][to] == C[node][to]) continue;
            if (dist[to] >= dist[node] + cost[node][to]) continue;

            dist[to] = dist[node] + cost[node][to];
            prov[to] = node;
            if (!inQueue[to]) {
                inQueue[to] = true;
                Q.push(to);
            }
        }
    }

    if (dist[D] == -inf) return false;

    int flow = inf;
    for (int node = D; node != S; node = prov[node])
        flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);
    for (int node = D; node != S; node = prov[node]) {
        F[prov[node]][node] += flow;
        F[node][prov[node]] -= flow;
    }

    ans += flow * dist[D];

    return true;
}



int main()
{
    freopen("terenuri3d.in","r",stdin);
    freopen("terenuri3d.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);

    S = 0;
    no_home = n + m + 1;
    D = no_home + 1;

    for (i = 1; i <= n; i++) {
        add_edge(S, i, 0, 1);
        add_edge(i, no_home, 0, 1);
    }

    for (i = 1; i <= m; i++)
        add_edge(n + i, D, 0, 1);
    add_edge(no_home, D, 0, n);

    for (i = 1; i <= k; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, n + y, z, 1);
    }

    while (bellman());

    for (i = 1; i <= n; i++)
        for (int to : list[i])
            if (F[i][to] == 1 && to != no_home)
                sol.pb(mp(i, to - n));

    sort(sol.begin(), sol.end());


    printf("%d\n%d\n", ans, sol.size());
    for (auto e : sol)
        printf("%d %d\n", e.first, e.second);

    return 0;
}
