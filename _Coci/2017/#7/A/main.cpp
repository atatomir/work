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

#define maxN 22

const int dif = 20;

int n, i, j, k;
ll v[maxN];
ll dp[maxN][maxN];

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> v[i], v[i] <<= dif;
    sort(v + 1, v + n + 1);

    for (i = n; i >= 1; i--) {
        dp[i][i] = v[i];
        for (j = i + 1; j <= n; j++) {
            dp[i][j] = 0;
            for (k = i; k < j; k++)
                dp[i][j] = max(dp[i][j], (dp[i][k] + dp[k + 1][j]) / 2);
        }
    }

    double ans = (1.00 * dp[1][n]) / (1.00 * (1 << dif));
    printf("%.10lf", ans);


    return 0;
}
