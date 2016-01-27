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

#define maxN 3024
#define maxK 205
#define inf 2000000001

int test, t;
int n, k, p, i, j, x, y;
int c[maxN][maxN];
vector<int> list[maxN];

bool us[maxN];
int dp[maxN][maxN];
int best[maxN];

//! ------- flux -----------------

int dim, S, D;
vector<int> dir[maxK];
int F[maxK][maxK];
int C[maxK][maxK];
int pay[maxK][maxK];

int dist[maxK];
int prov[maxK];

bool inQueue[maxN];
queue<int> Q;
int cost;

//! --------------------------------

void refresh() {
    for (int i = 1; i <= 2 * k + 10; i++)
        dir[i].clear();
    memset(F, 0, sizeof(F));
    memset(C, 0, sizeof(C));
    memset(pay, 0, sizeof(pay));

    cost = 0;
}

void add_edge(int n1, int n2, int _pay, int f_act) {
    dir[n1].pb(n2);
    dir[n2].pb(n1);

    pay[n1][n2] = _pay;
    pay[n2][n1] = -_pay;

    C[n1][n2] = 1;
    F[n1][n2] = f_act;
}

bool bellman() {
    int i;

    memset(prov, 0, sizeof(prov));
    memset(inQueue, 0, sizeof(inQueue));
    for (i = 1; i <= dim; i++)
        dist[i] = inf;
    while (!Q.empty()) Q.pop();

    dist[S] = 0;
    Q.push(S);
    inQueue[S] = true;

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        inQueue[node] = false;

        if (node == D) break;

        for (auto to : dir[node]) {
            if (F[node][to] == C[node][to]) continue;
            int cost = dist[i] + pay[node][to];
            if (cost >= dist[to]) continue;

            dist[to] = cost;
            prov[to] = node;
            if (!inQueue[to]) {
                inQueue[to] = true;
                Q.push(to);
            }
        }
    }

    if (prov[D] == 0) return false;

    for (int node = D; node != S; node = prov[node]) {
        F[ prov[node] ][node]++;
        F[node][ prov[node] ]--;

        cost += pay[prov[node]][node];
    }

    return true;
}


//! ------- flux -----------------

void solve(int node) {
    int i, j;
    us[node] = true;

    for (i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (us[to]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }
        solve(to);
    }

    best[node] = inf;
    //! ---------------------------------------------
    for (int col = 1; col <= k; col++) { //! color of node
        for (auto son1 : list[node]) {
            int aux = p;

            //! with P
            for (auto son2 : list[son1])
                aux += best[son2];

            //! without P
            if (list[son1].size() + 1 <= k) {
            refresh();

            dim = k + list[son1].size() + 1;
            S = 0; D = dim;

            int sons = list[son1].size();

            i = 0;
            for (auto to : list[son1]) {
                i++;
                add_edge(S, to, 0, 0);
            }

            for (i = 1; i <= k; i++)
                add_edge(sons + i, D, 0, 0);

            i = 0;
            for (auto son2 : list[son1]) {
                i++;

                for (j = 1; j <= k; j++)
                    if (k != col)
                        add_edge(i, j, dp[son2][j], 0);
            }

            while (bellman());
            aux = min(cost, aux);

            }
            //! take decision
            dp[node][col] += aux;
        }
        dp[node][col] += c[node][col];
        best[node] = min(best[node], dp[node][col]);
    }
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        scanf("%d%d%d", &n, &k, &p);
        for (i = 1; i <= n; i++)
            for (j = 1; j <= k; j++)
                scanf("%d", &c[i][j]);

        memset(us, 0, sizeof(us));
        memset(dp, 0, sizeof(dp));
        memset(best, 0, sizeof(best));

        for (i = 1; i <= n; i++) list[i].clear();
        for (i = 1; i < n; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(y);
            list[y].pb(x);
        }

        solve(1);
        int ans = best[1];
        for (auto to : list[1])
            ans += best[to];

        printf("Case #%d: %d\n", test, ans);
    }



    return 0;
}
