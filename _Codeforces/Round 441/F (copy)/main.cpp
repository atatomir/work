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

#define maxN 200011
#define inf 1000000000

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

        int loc_inf = -1; //changed to max cost //2000000001;

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
                    if (dist[to] >= dist[node] + pay[node][to]) continue;

                    dist[to] = dist[node] + pay[node][to];
                    prov[to] = node;

                    if (!inQueue[to]) {
                        Q.push(to);
                        inQueue[to] = true;
                    }
                }
            }

            if (prov[D] == 0) return false;

            int flow = inf;
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

int n, m, i, a, b, w;
int S, D, v1, v2;
flow_cost work;

int main()
{
    ///freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);

    S = n + m + 1;
    D = S + 1;
    v1 = D + 1;
    v2 = v1 + 1;
    work.init(v2, S, D);

    work.addEdge(S, v1, inf, 0);
    for (i = 1; i <= n; i++) {
        work.addEdge(S, i, 1, 0);
        work.addEdge(i, v2, 1, 0);
    }

    work.addEdge(v2, D, inf, 0);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        work.addEdge(n + i, D, 1, 0);
        work.addEdge(v1, n + i, 1, 0);

        work.addEdge(a, n + i, 1, w);
        work.addEdge(b, n + i, 1, w);
    }

    cout << work.go_ahead();



    return 0;
}
