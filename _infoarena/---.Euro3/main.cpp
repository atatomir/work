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

#define maxN 8111

int t, ti;
int n, limit, i, j;
int v[maxN];

int ss, dd;
int dp[maxN];
int ans[maxN];

int main()
{
    freopen("euro3.in","r",stdin);
    freopen("euro3.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &limit);
        for (i = 1; i <= n; i++) scanf("%d", &v[i]);

        sort(v + 1, v + n + 1);

        memset(dp, 0, sizeof(dp));
        for (i = 1; i <= limit; i++) ans[i] = limit + 10;

        for (i = 1; i <= n; i++) {
            for (j = limit - v[i]; j > 0; j--) {
                if (dp[j] == 0) continue;

                ans[j + v[i]] = min(ans[j + v[i]], v[i] - dp[j]);
                dp[j + v[i]] = max(dp[j + v[i]], dp[j]);
            }

            dp[v[i]] = v[i];
            ans[v[i]] = 0;
        }

        for (i = 1; i <= limit; i++) {
            if (ans[i] > limit)
                printf("-1 ");
            else
                printf("%d ", ans[i]);
        }
        printf("\n");
    }




    return 0;
}
