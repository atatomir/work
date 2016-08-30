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

class flow_cost {
    public:
        int n, i, S, D;
        vector< vector<int> > list;
        vector< vector<int> > C, F, pay;
        vector< int > dist;
        vector< int > prov;
        queue<int> Q;
        vector<bool> inQueue;
        int flow_cost = 0;

        int loc_inf = 2000000001;

        void init(int _n, int _S, int _D) {
            n = _n; S = _S; D = _D;

            list = vector< vector<int> >(n + 5, vector<int>(0));
            C = vector< vector<int> >(n + 5, vector<int>(n + 5, 0));
            F = vector< vector<int> >(n + 5, vector<int>(n + 5, 0));
            pay = vector< vector<int> >(n + 5, vector<int>(n + 5, 0));

            flow_cost = 0;

            dist = vector<int>(n + 5, loc_inf);
            prov = vector<int>(n + 5, 0);
            inQueue = vector<bool>(n + 5, false);
        }

        void addEdge(int x, int y, int limit, int cost) {
            list[x].pb(y);
            list[y].pb(x);

            C[x][y] = limit;
            F[x][y] = 0;

            pay[x][y] = cost;
            pay[y][x] = -cost;
        }

        bool bellman() {
            for (i = 0; i < n + 5; i++) {
                dist[i] = loc_inf;
                prov[i] = 0;
                inQueue[i] = false;
            }

            while (!Q.empty()) Q.pop();

            Q.push(S);
            inQueue[S] = true;
            dist[S] = 0;

            while (!Q.empty()) {
                int node = Q.front(); Q.pop();
                inQueue[node] = false;

                if (node == D) continue;

                for (auto to : list[node]) {
                    if (F[node][to] == C[node][to]) continue;
                    if (dist[to] <= dist[node] + pay[node][to]) continue;

                    dist[to] = dist[node] + pay[node][to];
                    prov[to] = node;

                    if (!inQueue[to]) {
                        Q.push(to);
                        inQueue[to] = true;
                    }
                }
            }

            if (prov[D] == 0) return false;

            int flow = loc_inf;
            for (int node = D; node != S; node = prov[node])
                flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);

            for (int node = D; node != S; node = prov[node]) {
                F[prov[node]][node] += flow;
                F[node][prov[node]] -= flow;

                flow_cost += flow * pay[ prov[node] ][node];
            }

            return true;
        }

        int go_ahead() {

            while (bellman());

            return flow_cost;
        }
};

//! -----------------------------------------------------------------

#define maxN 422

int n, i, j, k, sal, s, d, target;
flow_cost work;
vector<int> ans[maxN];
int roy[maxN][maxN];


int main()
{
    freopen("paznici2.in","r",stdin);
    freopen("paznici2.out","w",stdout);

    scanf("%d", &n); s = 2 * n + 1; d = 2 * n + 2;
    work.init(2 * n + 2, s, d);

    for (i = 1; i <= n; i++) {
        work.addEdge(s, i, 1, 0);
        work.addEdge(n + i, d, 1, 0);
    }


    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &sal);
            work.addEdge(i, n + j, 1, sal);
        }
    }

    work.go_ahead();
    target = work.flow_cost;

    for (i = 1; i <= 2 * n; i++)
        for (j = 1; j <= 2 * n; j++)
            roy[i][j] = -1000000000;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (work.F[i][n + j] != 0)
                roy[i][n + j] = work.pay[i][n + j];
            else
                roy[n + j][i] = work.pay[n + j][i];
        }
    }

    for (k = 1; k <= 2 * n; k++)
        for (i = 1; i <= 2 * n; i++)
            for (j = 1; j <= 2 * n; j++)
                roy[i][j] = max(roy[i][j], roy[i][k] + roy[k][j]);


    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (roy[i][n + j] == work.pay[i][n + j])
                ans[j].pb(i);

    printf("%d\n", target);
    for (i = 1; i <= n; i++) {
        printf("%d ", ans[i].size());
        for (int e : ans[i])
            printf("%d ", e);
        printf("\n");
    }

    return 0;
}
