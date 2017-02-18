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

#define maxN 111
#define mod 30011

int n, k, i, x, y, R;
vector<int> list[maxN];
bool bad[maxN];

int dp[maxN][maxN];

void dfs(int node) {
    int act;

    for (auto to : list[node])
        dfs(to);

    for (act = 1; act <= k; act++) {
        dp[node][act] = 1;

        for (auto to : list[node])
            dp[node][act] = (1LL * dp[node][act] * dp[to][act - 1]) % mod;

        dp[node][act] = (dp[node][act] + dp[node][act - 1]) % mod;
    }
}

int main()
{
    freopen("iepuri2.in","r",stdin);
    freopen("iepuri2.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        bad[y] = true;
    }

    for (R = 1; bad[R]; R++);
    dfs(R);

    printf("%d", dp[R][k]);


    return 0;
}
