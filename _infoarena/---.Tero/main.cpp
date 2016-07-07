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

#define maxN 711
#define inf 1000000000
#define upd(x) e.after = min(e.after, x)

struct edge {
    int x, y, dist;
    int after;

    bool operator<(const edge& who)const {
        return after > who.after;
    }
};

int n, m, i, x, y, d, R;
vector< pair<int, int> > list[maxN];
vector<edge> E;
int sh_dist[2][maxN];
priority_queue< pair<int, int> > H;

queue<int> Q;
int C[maxN][maxN], F[maxN][maxN];
int prov[maxN];


void dijk(int node, int *aux) {
    int i;

    for (i = 1; i <= n; i++) aux[i] = inf;
    aux[node] = 0;
    H.push(mp(-0, node));

    while (!H.empty()) {
        auto act = H.top(); H.pop();
        int node = act.second;
        int dd = -act.first;

        if (aux[node] != dd) continue;
        for (auto to : list[node]) {
            if (aux[to.first] <= aux[node] + to.second) continue;
            aux[to.first] = aux[node] + to.second;
            H.push(mp(-aux[to.first], to.first));
        }
    }
}

int bellman() {
    int i, flow;

    memset(prov, 0, sizeof(prov));

    prov[1] = 1;
    Q.push(1);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (node == n) continue;

        for (auto e : list[node]) {
            int to = e.first;

            if (prov[to]) continue;
            if (F[node][to] == C[node][to]) continue;
            prov[to] = node;
            Q.push(to);
        }
    }

    if (prov[n] == 0) return 0;

    int ans = 0;

    for (auto e : list[n]) {
        int son = e.first;
        if (prov[son] == 0) continue;

        prov[n] = son;

        flow = inf;
        for (int node = n; node != 1; node = prov[node])
            flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);
        for (int node = n; node != 1; node = prov[node]) {
            F[prov[node]][node] += flow;
            F[node][prov[node]] -= flow;
        }

        ans += flow;
    }


    return ans;
}

void compute_after(edge& e) {
    int x = e.x;
    int y = e.y;

    int sx = sh_dist[0][x] * 10;
    int dx = sh_dist[1][x] * 10;
    int sy = sh_dist[0][y] * 10;
    int dy = sh_dist[1][y] * 10;

    e.after = inf;

    //! S ... x ... D
    upd(max(sx, dx));

    //! S ... y ... D
    upd(max(sy, dy));

    //! S ... x - y ... D
    upd( max((sx + 10 * e.dist + dy + 1) / 2, max(sx, dy)) );

    //! S ... y - x ... D
    upd( max((sy + 10 * e.dist + dx + 1) / 2, max(sy, dx)) );
}




int main()
{
    freopen("tero.in","r",stdin);
    freopen("tero.out","w",stdout);

    scanf("%d%d%d", &n, &m, &R);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &d);
        list[x].pb(mp(y, d));
        list[y].pb(mp(x, d));
        E.pb({x, y, d, 0});
    }

    dijk(1, sh_dist[0]);
    dijk(n, sh_dist[1]);

    for (i = 0; i < E.size(); i++) {
        x = E[i].x;
        y = E[i].y;

        C[x][y] = C[y][x] = 1;
        compute_after(E[i]);
    }

    int act_flow = 0;
    sort(E.begin(), E.end());
    for (auto e : E) {
        C[e.x][e.y] = C[e.y][e.x] = R + 2;

        if (act_flow != 0 && F[e.x][e.y] != 1 && F[e.y][e.x] != 1) continue;
        if (act_flow != 0 && prov[e.x] == 0 && prov[e.y] == 0) continue;

        while(true) {
            int dif = bellman();
            if (dif == 0 || act_flow > R) break;
            act_flow += dif;
        }

        if (act_flow > R) {
            printf("%d.%d", e.after / 10, e.after % 10);
            cerr << e.after / 10 << '.' << e.after % 10;
            return 0;
        }
    }

    cerr << "pacat.. nu a mers";

    return 0;
}
