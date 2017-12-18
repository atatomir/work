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
        int flow_cost;

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
            flow_cost = 0;

            while (bellman());

            return flow_cost;
        }
};

//! -----------------------------------------------------------------

#define maxN 355

int n, m, s, d, i;
int x, y, c, pay;

flow_cost work;

int main()
{
    freopen("fmcm.in","r",stdin);
    freopen("fmcm.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &s, &d);
    work.init(n, s, d);

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &x, &y, &c, &pay);
        work.addEdge(x, y, c, pay);
    }

    printf("%d", work.go_ahead());

    return 0;
}
