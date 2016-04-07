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
#define def 30000
#define maxVal 2 * def + 17
#define inf (1LL << 50)

int n, i, j;
ll x, y, z, val, val2;

int ss, dd;
ll dp[2][maxVal];

int main()
{
    freopen("landscape.in","r",stdin);
    freopen("landscape.out","w",stdout);

    scanf("%d%lld%lld%lld", &n, &x, &y, &z);

    ss = 0; dd = 1;
    for (i = -def; i < 0; i++) dp[ss][i + def] = - y * i;
    for (i = 1; i <= def; i++) dp[ss][i + def] = x * i;

    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &val, &val2);
        val -= val2;

        for (j = -def; j <= def; j++) {
            if (-def > j - val || j - val > def) {
                dp[dd][j + def] = inf;
                continue;
            }

            dp[dd][def + j] = dp[ss][def + j - val] + abs(j);
        }

        for (j = 1; j <= 2 * def; j++)
            dp[dd][j] = min(dp[dd][j], dp[dd][j - 1] + x);
        for (j = 2 * def - 1; j >= 0; j--)
            dp[dd][j] = min(dp[dd][j], dp[dd][j + 1] + y);

        swap(ss, dd);
    }

    printf("%lld", dp[ss][def]);


    return 0;
}
