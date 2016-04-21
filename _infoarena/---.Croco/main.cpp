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

#define maxN 121
#define inf 1000000000

int n, i, j, S, D;
int C[maxN][maxN], F[maxN][maxN];
bool us[maxN];
int prov[maxN];
queue<int> Q;

int ans;
vector<int> sol;

int max_flow;
int best_flow, best_D;


bool bellman() {
    int i, j;

    memset(us, 0, sizeof(us));
    memset(prov, 0, sizeof(prov));
    while (!Q.empty()) Q.pop();

    Q.push(S);
    us[S] = true;

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (node == D) continue;

        for (i = 1; i <= n; i++) {
            if (F[node][i] == C[node][i]) continue;
            if (us[i]) continue;

            us[i] = true;
            prov[i] = node;
            Q.push(i);
        }
    }

    if (!us[D]) return false;

    for (int neig = 1; neig <= n; neig++) {
        if (!us[neig] || neig == D) continue;
        prov[D] = neig;

        int flow = inf;
        for (int node = D; node != S; node = prov[node])
            flow = min(flow, C[prov[node]][node] - F[prov[node]][node]);
        for (int node = D; node != S; node = prov[node]) {
            F[prov[node]][node] += flow;
            F[node][prov[node]] -= flow;
        }

        max_flow += flow;
    }



    return true;
}

void dfs(int node) {
    us[node] = true;

    for (int i = 1; i <= n; i++) {
        if (us[i]) continue;
        if (F[node][i] == C[node][i]) continue;

        dfs(i);
    }
}

void print_sol() {
    int i, j;
    for (i = 1; i <= n; i++) {
        if (us[i]) sol.pb(i);

        for (j = i + 1; j <= n; j++)
            if (us[i] == us[j])
                ans += C[i][j];
    }

    printf("%d %d\n", ans, sol.size());
    for (i = 0; i < sol.size(); i++) printf("%d ", sol[i]);
    exit(0);
}

void update_c(int bit) {

}

int main()
{
    freopen("croco.in","r",stdin);
    freopen("croco.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &C[i][j]);

    S = 0; D = n + 1;

    //! check if it is connex
    memset(us, 0, sizeof(us));
    dfs(1);
    for (i = 1; i <= n; i++)
        if (!us[i])
            print_sol();

    //! max flow
    best_flow = 1000000000;
    for (i = 0; i < 7; i++) {
        update_c(i);

        max_flow = 0;
        memset(F, 0, sizeof(F));
        while (bellman());

        if (max_flow < best_flow) {
            best_flow = max_flow;
            best_D = D;
        }
    }

    D = best_D; max_flow = 0;
    memset(F, 0, sizeof(F));
    while (bellman());

    //! get solution
    memset(us, 0, sizeof(us));
    dfs(S);

    print_sol();

    return 0;
}
