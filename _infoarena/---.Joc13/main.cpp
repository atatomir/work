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

#define maxN 5011
#define inf 1000000000

int n, k, i, j;
int a[maxN], b[maxN];
int dp[maxN][2];

int main()
{
    freopen("joc13.in","r",stdin);
    freopen("joc13.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] += a[i - 1];
    for (i = 1; i <= n; i++) scanf("%d", &b[i]), b[i] += b[i - 1];

    for (i = 1; i <= n; i++) dp[i][0] = dp[i][1] = -inf;
    for (i = 1; i <= n && i <= k; i++) dp[i][0] = a[i];

    for (i = 2; i <= n; i++) {
        for (j = 2; j <= i && j <= k; j++) {
            dp[i][0] = max(dp[i][0], dp[i - j + 1][1] + a[i] - a[i - j]);
            dp[i][1] = max(dp[i][1], dp[i - j + 1][0] + b[i] - b[i - j]);
        }
    }

    printf("%d", max(dp[n][1], dp[n][0] + b[n] - b[n - 1]));


    return 0;
}
