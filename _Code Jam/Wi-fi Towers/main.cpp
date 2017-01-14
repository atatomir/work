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

#define maxN 511
#define inf 1000000000

struct tower {
    int x, y, r, s;
};

int t, ti;
int n, i, j, S, D;
tower T[maxN];

int F[maxN][maxN], C[maxN][maxN];
vector<int> list[maxN];
int ans;

int dist[maxN], prov[maxN];
queue<int> Q;

bool bellman() {
    int i;

    memset(dist, 0, sizeof(dist));
    memset(prov, 0, sizeof(prov));

    dist[S] = 1;
    Q.push(S);
    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (node == D) continue;

        for (auto to : list[node]) {
            if (dist[to]) continue;
            if (C[node][to] == F[node][to]) continue;

            Q.push(to);
            dist[to] = dist[node] + 1;
            prov[to] = node;
        }
    }

    if (dist[D] == 0) return false;

    for (auto pr : list[D]) {
        if (dist[pr] == 0) continue;
        prov[D] = pr;

        int flow = inf;
        for (int node = D; node != S; node = prov[node])
            flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);
        for (int node = D; node != S; node = prov[node]) {
            F[prov[node]][node] += flow;
            F[node][prov[node]] -= flow;
        }

        ans -= flow;
    }


    return true;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Solving " << t << " cases.\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << "\n";

        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d%d%d%d", &T[i].x, &T[i].y, &T[i].r, &T[i].s);

        for (i = 1; i <= n + 2; i++) list[i].clear();
        memset(F, 0, sizeof(F));
        memset(C, 0, sizeof(C));
        S = n + 1;
        D = n + 2;

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (i == j) continue;

                int dist = (T[i].x - T[j].x) * (T[i].x - T[j].x) + (T[i].y - T[j].y) * (T[i].y - T[j].y);
                if (dist <= T[i].r * T[i].r) {
                    C[i][j] = inf;
                    list[i].pb(j);
                    list[j].pb(i);
                }
            }
        }

        ans = 0;
        for (i = 1; i <= n; i++) {
            if (T[i].s > 0) {
                ans += T[i].s;
                C[S][i] = T[i].s;
                list[S].pb(i);
                list[i].pb(S);
            } else {
                C[i][D] = -T[i].s;
                list[D].pb(i);
                list[i].pb(D);
            }
        }

        while (bellman());
        printf("Case #%d: %d\n", ti, ans);
    }



    return 0;
}
