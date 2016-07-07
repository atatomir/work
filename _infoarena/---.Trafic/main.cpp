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

#define maxN 162
#define inf 1000000000
#define base 100

struct edge {
    int x, y, dist;
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

int check(int lim) {
    int x, y;
    bool good;
    int dist, dx, dy;
    int ans, dif;

    for (auto e : E) {
        x = e.x;
        y = e.y;
        dist = e.dist;
        good = false;

        //! S ... x ... D
        dx = lim - sh_dist[0][x];
        dy = lim - sh_dist[1][x];

        if (dx >= 0 && dy >= 0)
            good = true;

        //! S ... y ... D
        dx = lim - sh_dist[0][y];
        dy = lim - sh_dist[1][y];

        if (dx >= 0 && dy >= 0)
            good = true;

        //! S ... x - y ... D
        dx = lim - sh_dist[0][x];
        dy = lim - sh_dist[1][y];

        if (dx >= 0 && dy >= 0 && dx + dy >= dist)
            good = true;

        //! S ... y - x ... D
        swap(x, y);
        dx = lim - sh_dist[0][x];
        dy = lim - sh_dist[1][y];

        if (dx >= 0 && dy >= 0 && dx + dy >= dist)
            good = true;

        C[x][y] = C[y][x] = (good ? 1 : 1000000);
    }

    ans = 0;
    memset(F, 0, sizeof(F));

    while (true) {
        dif = bellman();
        if (dif == 0) break;
        ans += dif;
    }

    return ans;
}



int main()
{
    freopen("trafic.in","r",stdin);
    freopen("trafic.out","w",stdout);

    scanf("%d%d%d", &n, &m, &R);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &d); d *= base;
        list[x].pb(mp(y, d));
        list[y].pb(mp(x, d));
        E.pb({x, y, d});
    }

    dijk(1, sh_dist[0]);
    dijk(n, sh_dist[1]);


    if (check(1024 * base * n) > R) {
        printf("-1");
        return 0;
    }

    int ans = 0;
    for (int step = (1 << 30); step > 0; step >>= 1)
        if (check(ans + step) > R)
            ans += step;

    ans = (ans + 1) / 10;
    printf("%d.%d", ans / 10, ans % 10);

    cerr << ans / 10 << '.' << ans % 10;

    return 0;
}
