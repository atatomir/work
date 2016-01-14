#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, k, x;
vector<int> list[maxN];
int need[maxN];
int dp[maxN];

bool cmp(int a, int b) {
    return dp[a] < dp[b];
}

void dfs(int node) {
    for (auto to : list[node])
        dfs(to);

    sort(list[node].begin(), list[node].end(), cmp);
    for (int i = 0; i < need[node]; i++)
        dp[node] += dp[ list[node][i] ];

    if (list[node].empty())
        dp[node] = 1;
}

int main()
{
    freopen("dominouri.in","r",stdin);
    freopen("dominouri.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &k);
        for (; k; k--) {
            scanf("%d", &x);
            list[i].pb(x);
        }
    }

    for (i = 1; i <= n; i++)
        scanf("%d", &need[i]);

    dfs(1);
    printf("%d", dp[1]);


    return 0;
}
