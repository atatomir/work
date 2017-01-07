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

#define mod 31333
#define maxN 3011
#define maxP 3511

int n, p, i, x, y, j, pos, node;
vector<int> list[maxN];
int val[maxN], cnt[maxN], l[maxN], r[maxN], who[maxN], pows[maxN];
int dp[maxN][maxP];

void dfs(int node, int root) {
    pos++;
    l[node] = pos;
    who[pos] = node;
    cnt[node] = 1;

    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);
        cnt[node] += cnt[to];
    }

    r[node] = pos;
}

int main()
{
    freopen("radare.in","r",stdin);
    freopen("radare.out","w",stdout);

    scanf("%d%d", &n, &p);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    pows[0] = 1;
    for (i = 1; i <= n; i++) {
        pows[i] = (pows[i - 1] * 2) % mod;
        scanf("%d", &val[i]);
    }

    dfs(1, 0);
    dp[1][val[1]] = 1;

    for (i = 1; i < n; i++) {
        node = who[i + 1];

        for (j = val[1]; j <= p; j++) {
            dp[i][j] %= mod;
            if (dp[i][j] == 0) continue;

            if (j + val[node] <= p)
                dp[i + 1][j + val[node]] += dp[i][j];
            dp[ r[ node ] ][j] += (dp[i][j] * pows[ cnt[node] - 1 ]) % mod;
        }
    }

    dp[n][p] %= mod;
    printf("%d", dp[n][p]);


    return 0;
}
