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

#define maxN 1024

int c, k, q, ss, dd, i, j, tot;
double dp[2][maxN], ans;

int main()
{
    freopen("albume.in","r",stdin);
    freopen("albume.out","w",stdout);

    scanf("%d%d%d", &c, &k, &q);
    tot = k * c;

    ss = 0; dd = 1;
    dp[ss][1] = 1.00;

    for (i = 1; i < q; i++) {
        memset(dp[dd], 0, sizeof(dp[dd]));
        for (j = 1; j <= c; j++) {
            dp[dd][j] += (1.00 * dp[ss][j] * (k * j - i)) / (1.0 * (tot - i));
            dp[dd][j + 1] += (1.00 * dp[ss][j] * (tot - k * j)) / (1.0 * (tot - i));
        }
        swap(ss, dd);
    }

    for (i = 1; i <= c; i++) ans += 1.00 * i * dp[ss][i];

    printf("%.10lf", ans);



    return 0;
}
