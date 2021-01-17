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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
  cerr << "[";
  for (auto e : aux) cerr << e << ' ';
  cerr << "]";
  return cerr;
}

const int maxN = 311;
const int inf = 1 << 30;

class Flow {
    public:
        int dim;
        int S, D;
        vector< vector<int> > C, F, list;
        vector<int> prov;
        queue<int> Q;
        int total;

        void init(int _dim, int _S, int _D) {
            dim = _dim; S = _S; D = _D;
            dim += 5;
            total = 0;

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

                for (int node = D; node != S; node = prov[node]) {
                    flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);
                    //cerr << node << ' ';
                }
                //cerr << " - " << flow << '\n';

                for (int node = D; node != S; node = prov[node]) {
                    F[prov[node]][node] += flow;
                    F[node][prov[node]] -= flow;
                }

                total += flow;
            }

            return true;
        }

        void start_process() {
            while (bellman());
        }
};

int n, m, x, y, ans;
int a[maxN], b[maxN], S, D;
Flow flow;

int main()
{
  //freopen("test.in", "r", stdin);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int j = 1; j <= n; j++) cin >> b[j];
  S = 2 * n + 1; D = 2 * n + 2;

  flow.init(2 * n + 2, S, D);

  ans = 0;
  for (int i = 1; i <= n; i++) {
    if (b[i] > 0) {
      ans += b[i];
      flow.add_dir_edge(2 * i - 1, 2 * i, a[i] + b[i]);
      flow.add_dir_edge(2 * i, D, 2 * b[i]);
    } else {
      ans -= b[i];
      flow.add_dir_edge(2 * i - 1, 2 * i, a[i] - b[i]);
      flow.add_dir_edge(S, 2 * i - 1, -2 * b[i]);
    }
  }

  for (int i = 1; i <= m; i++) {
    cin >> x >> y;
    flow.add_dir_edge(2 * x, 2 * y - 1, inf);
    flow.add_dir_edge(2 * y, 2 * x - 1, inf);
  }

  flow.start_process();

  //cout << ans << ' ' << flow.total << '\n';
  ans -= flow.total;

  //for (int i = 1; i <= n; i++) 
  //  cerr << flow.F[2 * i - 1][2 * i] << ' ';

  cout << ans;


  return 0;
}
