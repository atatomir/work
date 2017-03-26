#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 133

int n, k, i, j, x, y;
vector<int> list[maxN];
int dp[maxN][maxN], aux[maxN];

void dfs(int node, int root) {
    int i, j;

    for (i = 0; i <= n; i++) dp[node][i] = n + 1;
    dp[node][1] = 0;

    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);

        for (i = 0; i <= n; i++) {
            aux[i] = dp[node][i];
            dp[node][i] = n + 1;
        }

        for (i = 0; i <= n; i++)
            for (j = 0; i + j <= n; j++)
                dp[node][i + j] = min(dp[node][i + j], max(dp[to][i], aux[j]));
    }

    for (i = k; i <= n; i++)
        dp[node][0] = min(dp[node][0], max(i, dp[node][i]));
}

int main()
{
    freopen("judete.in","r",stdin);
    freopen("judete.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);
    printf("%d", dp[1][0]);

    return 0;
}
