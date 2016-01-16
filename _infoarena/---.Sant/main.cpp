#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111
#define maxS 1111
#define inf 32000

int S, n, i, j, k, c, l[25], p[25];
short dp[maxN][maxS];
short prov[maxN][maxS];
vector<int> sol;

int get(int n, int S, int c) {
    int i, j, k;

    for (i = 0; i <= n; i++)
        for (j = 0; j <= S; j++)
            dp[i][j] = inf;

    dp[0][0] = 0;

    for (k = 1; k < c; k++) {
        for (i = 0; i < n; i++)
            for (j = 0; j <= S - l[k]; j++)
                dp[i + 1][j + l[k]] = min(1 * dp[i + 1][j + l[k]], dp[i][j] + p[k]);
    }

    for (i = 0; i <= n; i++)
        for (j = 0; j <= S; j++)
            prov[i][j] = 0;

    for (i = 0; i < n; i++)
        for (j = 0; j <= S - l[k]; j++)
            if (dp[i + 1][j + l[k]] > dp[i][j] + p[k]) {
                dp[i + 1][j + l[k]] =  dp[i][j] + p[k];
                prov[i + 1][j + l[k]] = prov[i][j] + 1;
            }
            else
            if (dp[i + 1][j + l[k]] == dp[i][j] + p[k])
                if (prov[i + 1][j + l[k]] < prov[i][j] + 1) {
                    dp[i + 1][j + l[k]] =  dp[i][j] + p[k];
                    prov[i + 1][j + l[k]] = prov[i][j] + 1;
                }

    return prov[n][S];
}

int main()
{
    freopen("sant.in","r",stdin);
    freopen("sant.out","w",stdout);

    scanf("%d%d%d", &S, &n, &c);
    for (i = c; i >= 1; i--)
        scanf("%d %d", &l[i], &p[i]);

    get(n, S, c);
    if (dp[n][S] == inf) {
        printf("0");
        return 0;
    }
    printf("%d\n", dp[n][S]);

    for (i = c; i > 0; i--) {
        int ans = get(n, S, i);

        n -= ans;
        S -= l[i] * ans;

        while (ans > 0) {
            sol.pb(i);
            ans--;
        }
    }

    for (auto e : sol)
        printf("%d ", c - e + 1);

    return 0;
}
