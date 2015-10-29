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

#define maxN 135
#define inf 1000000000

int n, m, i, j, sum, how, k, S, D, answer;
int a[maxN][maxN];

vector<int> list[maxN];
vector<int> l_side, r_side;
int xx[maxN], yy[maxN];

int C[maxN][maxN];
int F[maxN][maxN];
int pay[maxN][maxN];

int prov[maxN];
int act_pay[maxN];

queue<int> Q;
bool inQueue[maxN];

void addEdge(int x, int y, int cap, int _pay) {
    list[x].pb(y);
    list[y].pb(x);

    C[x][y] = cap;
    C[y][x] = 0;
    pay[x][y] = _pay;
    pay[y][x] = -_pay;
}

int abss(int x) {
    if (x > 0) return x;
    return -x;
}

bool Flow() {
    memset(prov, 0, sizeof(prov));
    memset(inQueue, 0, sizeof(inQueue));
    for (i = S; i <= D; i++) act_pay[i] = inf;
    act_pay[S] = 0;

    while(!Q.empty()) Q.pop();

    Q.push(S); inQueue[S] = true;
    while (!Q.empty()) {
        int node = Q.front();
        inQueue[node] = false;
        Q.pop();

        if (node == D) continue;

        for (auto to : list[node]) {
            if (F[node][to] == C[node][to]) continue;
            if (act_pay[to] <= act_pay[node] + pay[node][to]) continue;

            act_pay[to] = act_pay[node] + pay[node][to];
            prov[to] = node;
            if (!inQueue[to]) {
                inQueue[to] = true;
                Q.push(to);
            }
        }
    }

    if (prov[D] == 0) return false;

    int act_flow = inf;
    for (int node = D; node != S; node = prov[node])
        act_flow = min(act_flow, C[ prov[node] ][node] - F[ prov[node] ][node]);
    for (int node = D; node != S; node = prov[node]) {
        F[ prov[node] ][node] += act_flow;
        F[node][ prov[node] ] -= act_flow;
        answer += act_flow * pay[ prov[node] ][node];
    }

    return true;
}

int main()
{
    freopen("monede.in","r",stdin);
    freopen("monede.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            sum += a[i][j];
            if (a[i][j]) how++;
        }
    }

    sum /= how;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (a[i][j] == 0) continue;

            a[i][j] -= sum;
            if (a[i][j] == 0) continue;
            if (a[i][j] < 0) {
                r_side.pb(++k);
                xx[k] = i; yy[k] = j;
            } else {
                l_side.pb(++k);
                xx[k] = i; yy[k] = j;
            }
        }
    }

    S = 0; D = k + 1;
    for (auto ll : l_side)
        for (auto rr : r_side)
            addEdge(ll, rr, inf, abss(xx[ll] - xx[rr]) + abss(yy[ll] - yy[rr]) + 1);

    for (auto ll : l_side)
        addEdge(S, ll, a[ xx[ll] ][ yy[ll] ], 0);
    for (auto rr : r_side)
        addEdge(rr, D, -a[ xx[rr] ][ yy[rr] ], 0);

    while (Flow()) {
        answer = answer - 1 + 1;
    }
    printf("%d", answer);

    return 0;
}
