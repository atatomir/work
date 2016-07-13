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
#define mod 123457

int n, mug, i, j, lim, k, dim;
int comb[2][maxN];
int catalan[maxN];

int ss, dd;
int dp[2][maxN];

int main()
{
    freopen("mugur.in","r",stdin);
    freopen("mugur.out","w",stdout);

    ss = 0; dd = 1;
    catalan[0] = 1;

    for (i = 0; i <= 1000; i++) {
        comb[dd][0] = 1;
        lim = min(500, i);

        for (j = 1; j <= lim; j++) {
            comb[dd][j] = comb[ss][j - 1] + comb[ss][j];
            if (comb[dd][j] >= mod) comb[dd][j] -= mod;
        }

        if (i % 2 == 0)
            catalan[i / 2] = (mod + comb[dd][i / 2] - comb[dd][(i / 2) - 1]) % mod;

        swap(ss, dd);
    }

    scanf("%d%d", &n, &mug);

    ss = 0; dd = 1;
    dp[0][0] = 1;
    for (i = 0; i < mug; i++) {
        lim = n - mug + i;

        for (j = i; j <= lim; j++)
            for (k = j + 1; k <= lim + 1; k++)
                dp[dd][k] = (1LL * dp[ss][j] * catalan[k - j - 1] + dp[dd][k]) % mod;

        swap(ss, dd);
        memset(dp[dd], 0, sizeof(dp[dd]));
    }

    printf("%d", dp[ss][n]);

    return 0;
}
