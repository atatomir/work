#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxN 211
#define maxDim maxN*4 + 25
#define inf 1000000000

int n, i, k, a, b, j;
int Source, Destination, Inter, Middle;
int v[maxN];

int F[maxDim][maxDim];
int C[maxDim][maxDim];
int pay[maxDim][maxDim];
vector<int> list[maxDim];

int cost[maxDim];
int prov[maxDim];
bool inQueue[maxDim];

int answer;
queue<int> Q;

void addEdge(int a, int b, int cap, int _pay) {
    list[a].pb(b);
    list[b].pb(a);

    C[a][b] = cap;
    pay[a][b] = _pay;
    pay[b][a] = -_pay;
};

int abss(int x) {
    if (x > 0) return x;
    return -x;
}

bool Bellman() {
    int i;

    for (i = Source; i <= Destination; i++) {
        cost[i] = inf;
        prov[i] = 0;
        inQueue[i] = false;
    }
    cost[Source] = 0;
    while(!Q.empty()) Q.pop();

    Q.push(Source); inQueue[Source] = true;
    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        inQueue[node] = false;

        if (node == Destination) continue;
        for (i = 0; i < list[node].size(); i++) {
            int to = list[node][i];

            if (F[node][to] == C[node][to]) continue;
            if (cost[node] + pay[node][to] >= cost[to]) continue;

            cost[to] = cost[node] + pay[node][to];
            prov[to] = node;
            if (inQueue[to] == false) {
                inQueue[to] = true;
                Q.push(to);
            }
        }
    }

    if (cost[Destination] == inf) return false;

    int flow = inf;
    int how = 0;

    for (int node = Destination; node != Source; node = prov[node]) {
        flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);
        how += pay[prov[node]][node];
    }

    answer += how * flow;
    for (int node = Destination; node != Source; node = prov[node]) {
        F[prov[node]][node] += flow;
        F[node][prov[node]] -= flow;
    }

    return true;
}

int main()
{
    freopen("smen.in", "r", stdin);
    freopen("smen.out", "w", stdout);

    scanf("%d%d%d%d", &n, &k, &a, &b);

    Source = 0; Middle = maxN * 2;  Inter = maxN * 3; Destination = Inter + 1;

    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    for (i = 1; i <= n; i++) addEdge(Source, i, 1, 0);
    for (i = 1; i <= n; i++)
        for (j = a; j <= b; j++)
            addEdge(i, Middle + j, 1, abss(v[i] - j));

    for (i = a; i <= b; i++)
        addEdge(Middle + i, Inter, 1, 0);

    addEdge(Inter, Destination, k, 0);

    while ( Bellman() );

    printf("%d\n", answer);
    for (i = 1; i <=n ; i++) {
        bool found = false;
        for (j = a; j <= b; j++) {
            if (F[i][Middle + j] == 1) {
                printf("%d ", j);
                found = true;
                break;
            }
        }

        if (found == false) printf("%d ", v[i]);
    }

    return 0;
}
