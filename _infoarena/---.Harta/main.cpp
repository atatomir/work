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
#define inf 2000000001

class Flow {
    public:
        int dim;
        int S, D;
        vector< vector<int> > C, F, list;
        vector<int> prov;
        queue<int> Q;

        void init(int _dim, int _S, int _D) {
            dim = _dim; S = _S; D = _D;
            dim += 5;

            list = vector< vector<int> >(dim, vector<int>(0, 0));
            C = F = vector< vector<int> >(dim, vector<int>(dim, 0));
            prov = vector<int>(dim, 0);
        }

        void add_edge(int x, int y, int cap) {
            list[x].pb(y);
            list[y].pb(x);
            C[x][y] = C[y][x] = cap;
            F[x][y] = F[y][x] = 0;
        }

        void add_dir_edge(int x, int y, int cap) {
            list[x].pb(y);
            list[y].pb(x);
            C[x][y] = cap;
            F[x][y] = F[y][x] = 0;
        }

        bool bellman() {
            int i;

            for (i = 0; i < dim; i++) prov[i] = 0;
            prov[S] = S;
            Q.push(S);

            while (!Q.empty()) {
                int node = Q.front(); Q.pop();

                if (node == D) continue;
                for (int to : list[node]) {
                    if (prov[to]) continue;
                    if (F[node][to] == C[node][to]) continue;

                    prov[to] = node;
                    Q.push(to);
                }
            }

            if (prov[D] == 0) return false;

            for (int to : list[D]) {
                if (prov[to] == 0) continue;

                int flow = inf;
                prov[D] = to;

                for (int node = D; node != S; node = prov[node])
                    flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);

                for (int node = D; node != S; node = prov[node]) {
                    F[prov[node]][node] += flow;
                    F[node][prov[node]] -= flow;
                }
            }

            return true;
        }

        void start_process() {
            while (bellman());
        }


};

int n, i, j, x, y, sum_x, sum_y;
Flow work;
vector< pair<int, int> > ans;

int main()
{
    freopen("harta.in","r",stdin);
    freopen("harta.out","w",stdout);

    scanf("%d", &n);
    work.init(2 * n + 2, 1, 2 * n + 2);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (i != j)
                work.add_dir_edge(1 + i, 1 + n + j, 1);

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        work.add_dir_edge(work.S, 1 + i, x);
        work.add_dir_edge(1 + n + i, work.D, y);

        sum_x += x;
        sum_y += y;
    }

    if (sum_x != sum_y) {
        cerr << "Sums not equal";
        return 0;
    }

    work.start_process();
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (work.F[1 + i][1 + n + j] == 1)
                ans.pb(mp(i, j));

    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d %d\n", e.first, e.second);

    if (ans.size() != sum_x) {
        cerr << "error reconstructing..";
        return 0;
    }


    return 0;
}
