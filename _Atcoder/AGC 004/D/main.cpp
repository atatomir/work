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

int n, k, i, ans;
int a[maxN];
vector<int> list[maxN];
int dp[maxN];
bool good[maxN];

void dfs(int node) {
    dp[node] = 0;

    for (auto to : list[node]) {
        dfs(to);
        dp[node] = max(dp[node], dp[to] + 1);
    }

    if (dp[node] == k - 1 && node != 1 && !good[node]) {
        ans++;
        dp[node] = -1;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);

    if (a[1] != 1) ans++;
    a[1] = 1;

    for (i = 2; i <= n; i++) {
        list[a[i]].pb(i);
        if (a[i] == 1) good[i] = true;
    }

    dfs(1);
    printf("%d", ans);


    return 0;
}
