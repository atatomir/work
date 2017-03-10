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

int n, m, k, i, j;
char s[maxN][maxN];
int dp[maxN][maxN];
int pr[maxN], u;

int old[maxN], act[maxN];

void prep(int node) {
    int i;

    u = pr[1] = 0;
    for (i = 2; i <= k; i++) {
        while (u != 0 && s[node][u + 1] != s[node][i]) u = pr[u];
        if (s[node][u + 1] == s[node][i]) u++;
        pr[i] = u;
    }

    for (int to = 1; to <= n; to++) {
        u = 0;
        for (i = 1; i <= k; i++) {
            while (u != 0 && s[node][u + 1] != s[to][i]) u = pr[u];
            if (s[node][u + 1] == s[to][i]) u++;
        }

        if (u == k) u = pr[u];
        dp[node][to] = k - u;
    }
}

int main()
{
    freopen("zip.in","r",stdin);
    freopen("zip.out","w",stdout);

    scanf("%d%d%d\n", &n, &m, &k);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);
    for (i = 1; i <= n; i++) prep(i);

    for (i = 1; i <= n; i++) old[i] = k;
    for (int pas = 2; pas <= m; pas++) {
        for (i = 1; i <= n; i++) act[i] = k * m;

        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                act[j] = min(act[j], old[i] + dp[i][j]);

        memcpy(old, act, sizeof(act));
    }

    int ans = k * m;
    for (i = 1; i <= n; i++)
        ans = min(ans, old[i]);

    printf("%d", ans);


    return 0;
}
