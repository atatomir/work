#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 270
#define mod 666013LL
#define ll long long

int n, m, i, j, l, k, x, y;
vector<int> list[maxN];
vector<int> rev[maxN];

vector<int> aux;
bool us[maxN];

int cnt;
int belong[maxN];
int how_in[maxN];

bool adj[maxN][maxN];
ll dp[maxN][maxN];
int gr[maxN];
int count_down[maxN];

ll util[maxN];

//!--------------------------

void dfs(int node) {
    us[node] = true;
    for (auto to : list[node]) {
        if (us[to]) continue;
        dfs(to);
    }
    aux.pb(node);
}

void dfs_rev(int node) {
    belong[node] = cnt;
    how_in[cnt]++;

    for (auto to : rev[node])
        if (!belong[to])
            dfs_rev(to);
}

void compute_comp() {
    int i, j;

    memset(us, 0, sizeof(us));
    for (i = 1; i <= n; i++)
        if (!us[i])
            dfs(i);

    while (!aux.empty()) {
        int node = aux[aux.size() - 1];
        aux.pop_back();

        if (belong[node]) continue;
        ++cnt;
        dfs_rev(node);
    }

    memset(adj, 0, sizeof(adj));

    for (i = 1; i <= n; i++) {
        for (auto to : list[i]) {
            if (belong[i] != belong[to])
                adj[ belong[i] ][ belong[to] ] = true;
        }
    }

    //! ----------------------------------------------
    n = cnt; //! n va fi folosit ca nr de comp biconexe
    for (i = 1; i <= n; i++)
        list[i].clear();
    list[n + 1].clear();

    for (i = 1; i <= n; i++) {
        int best = 0;

        for (j = 1; j <= n && adj[i][j] == false; j++);
        if (j > n) continue;

        best = j;
        for (j = best + 1; j <= n; j++) {
            if (adj[i][j]) {
                if (adj[best][j]) {
                    adj[i][j] = false;
                } else {
                    adj[i][best] = false;
                    best = j;
                }
            }
        }

        list[best].pb(i);
        gr[i]++;
    }
}

void combine(int s1, int s2) {
    int i, j;

    memcpy(util, dp[s1], sizeof(util));
    memset(dp[s1], 0, sizeof(dp[s1]));
    for (i = 0; i <= k; i++) {
        int lim = k - i;
        if (util[i] == 0) continue;

        for (j = 0; j <= lim; j++)
            dp[s1][i + j] = (1LL * dp[s1][i + j] + 1LL * util[i] * dp[s2][j]) % mod;
    }
}

void solve(int node) {
    int i, j;

    count_down[node] = how_in[node];

    dp[node][0] = 1;
    for (auto to : list[node]) {
        solve(to);
        count_down[node] += count_down[to];

        combine(node, to);
    }

    if (count_down[node] <= k) {
        dp[node][ count_down[node] ]++;
        if (dp[node][ count_down[node] ] >= mod)
             dp[node][ count_down[node] ] -= mod;
    }
}

int main()
{
    freopen("dep.in","r",stdin);
    freopen("dep.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    k = n - k;

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        adj[x][y] = true;
    }

    for (l = 1; l <= n; l++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (i != j)
                    adj[i][j] |= adj[i][l] & adj[l][j];

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (adj[i][j]) {
                list[i].pb(j);
                rev[j].pb(i);
            }
        }
    }


    compute_comp();
    for (i = 1; i <= n; i++)
        if (!gr[i])
            list[n + 1].pb(i);

    n++;
    solve(n);
    printf("%lld", dp[n][k]);


    return 0;
}
