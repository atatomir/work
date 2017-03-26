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

#define maxN 33

int n, m, i, j;
ll k;
double dp[maxN][maxN];
double c1, c2, x;

int main()
{
    freopen("alice.in","r",stdin);
    freopen("alice.out","w",stdout);

    scanf("%d%d%lld", &n, &m, &k);
    for (i = 0; i <= n; i++) dp[i][0] = 1 << i;
    for (i = 0; i <= m; i++) dp[0][i] = 1 << i;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            c1 = dp[i - 1][j];
            c2 = dp[i][j - 1];

            if (c1 < c2) swap(c1, c2);
            x = (c1 - c2) / (c1 + c2);
            dp[i][j] = c1 * (1 - x);
        }
    }

    ll ans = floor(dp[n][m] * k);
    printf("%lld", ans);


    return 0;
}
