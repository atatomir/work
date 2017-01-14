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

#define maxN 100011
#define mod 1000000007

int n, x, y, i;
vector<int> list[maxN];
ll dp[maxN][2], cnt[maxN][2];

void dfs(int node, int root) {
    dp[node][0] = 0;
    dp[node][1] = 1;
    cnt[node][0] = cnt[node][1] = 1;

    for (auto to : list[node]) {
        if (root == to) continue;
        dfs(to, node);

        dp[node][0] += max(dp[to][0], dp[to][1]);
        dp[node][1] += max(dp[to][0], dp[to][1] - 1);

        ll aux = 0;
        ll maxi = max(dp[to][0], dp[to][1]);

        if (maxi == dp[to][0]) aux += cnt[to][0];
        if (maxi == dp[to][1]) aux += cnt[to][1];

        cnt[node][0] = (cnt[node][0] * aux) % mod;

        // once again

        aux = 0;
        maxi = max(dp[to][0], dp[to][1] - 1);

        if (maxi == dp[to][0]) aux += cnt[to][0];
        if (maxi == dp[to][1] - 1) aux += cnt[to][1];

        cnt[node][1] = (cnt[node][1] * aux) % mod;
    }
}

int main()
{
    freopen("arbore7.in","r",stdin);
    freopen("arbore7.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);

    ll sol = max(dp[1][0], dp[1][1]);
    ll how_many = 0;
    if (dp[1][0] == sol) how_many += cnt[1][0];
    if (dp[1][1] == sol) how_many += cnt[1][1];
    how_many %= mod;

    printf("%lld %lld\n", sol, how_many);


    return 0;
}
