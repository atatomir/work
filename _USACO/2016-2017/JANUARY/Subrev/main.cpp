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

#define maxN 55
#define act dp[l][r][v1][v2]

int n, i, l, r, dim, v1, v2;
int v[maxN];
int dp[maxN][maxN][maxN][maxN];
int ans;

int main()
{
    freopen("subrev.in","r",stdin);
    freopen("subrev.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    dp[1][n][1][50] = 1;

    for (dim = n; dim > 1; dim--) {
        for (l = 1; l + dim - 1 <= n; l++) {
            r = l + dim - 1;


            for (v1 = 1; v1 <= 50; v1++) {
                for (v2 = v1; v2 <= 50; v2++) {
                    if (act == 0) continue;

                    ans = max(ans, act);

                    dp[l + 1][r][v1][v2] = max(dp[l + 1][r][v1][v2], act);
                    dp[l][r - 1][v1][v2] = max(dp[l][r - 1][v1][v2], act);

                    if (v1 <= v[l] && v[r] <= v2)
                        dp[l + 1][r - 1][v[l]][v[r]] = max(dp[l + 1][r - 1][v[l]][v[r]], act + 2);

                    if (v1 <= v[l])
                        dp[l + 1][r][v[l]][v2] = max(dp[l + 1][r][v[l]][v2], act + 1);

                    if (v[r] <= v2)
                        dp[l][r - 1][v1][v[r]] = max(dp[l][r - 1][v1][v[r]], act + 1);

                    swap(v[l], v[r]);

                    if (v1 <= v[l] && v[r] <= v2)
                        dp[l + 1][r - 1][v[l]][v[r]] = max(dp[l + 1][r - 1][v[l]][v[r]], act + 2);

                    if (v1 <= v[l])
                        dp[l + 1][r - 1][v[l]][v2] = max(dp[l + 1][r - 1][v[l]][v2], act + 1);

                    if (v[r] <= v2)
                        dp[l + 1][r - 1][v1][v[r]] = max(dp[l + 1][r - 1][v1][v[r]], act + 1);

                    swap(v[l], v[r]);
                }
            }
        }
    }


    for (i = 1; i <= n; i++) {
        for (v1 = 1; v1 <= 50; v1++) {
            for (v2 = v1; v2 <= 50; v2++) {
                ans = max(ans, dp[i][i][v1][v2] + (v1 <= v[i] && v[i] <= v2 ? 1 : 0));
                ans = max(ans, dp[i][i - 1][v1][v2]);
            }
        }
    }

    printf("%d", ans - 1);



    return 0;
}
