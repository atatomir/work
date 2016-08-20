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

#define maxN 200011

int n, i, x, R;
vector<int> list[maxN];
int dp[maxN][2];


void dfs(int node) {
    pair<int, int> best = mp(-(1 << 30), -(1 << 30));
    if (list[node].empty()) return;

    for (int to : list[node]) {
        dfs(to);
        dp[node][0] += max(dp[to][0], dp[to][1]); // degree 0

        int val = dp[to][0] + 1 - max(dp[to][0], dp[to][1]);
        if (val >= best.first) {
            best.second = best.first;
            best.first = val;
        } else
        if (val >= best.second)
            best.second = val;
    }

    int pure = dp[node][0];
    dp[node][0] += max(0, best.first); // degree 1
    dp[node][1] = max(dp[node][0], pure + best.first + best.second); // degree 2
}

int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (x) list[x].pb(i);
        if (x == 0) R = i;
    }

    dfs(R);
    int ans = max(dp[R][0], dp[R][1]);

    printf("%d", 2 * (n - ans) - 1);

    return 0;
}
