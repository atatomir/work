#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024
#define mod 1000000

int n,i,pos,maxVal;
int dp[maxN][maxN];
/*
 *  dp[i][j] - nr de siruri de lungime i
 *             si val <= j
 */
 int sums[maxN][maxN];

int main()
{
    freopen("sir23.in","r",stdin);
    freopen("sir23.out","w",stdout);

    scanf("%d",&n);

    dp[0][0] = sums[0][0] = 1;
    for (maxVal = 1; maxVal <= n; maxVal++) {
        dp[1][maxVal] = maxVal;
        dp[0][maxVal] = 1;

        sums[1][maxVal] = sums[1][maxVal-1] + dp[1][maxVal];
        sums[0][maxVal] = sums[0][maxVal-1] + dp[0][maxVal];
    }
    for (pos = 2; pos <= n; pos++) {
        for (maxVal = 1; maxVal <= n; maxVal++){
            dp[pos][maxVal] = dp[pos][maxVal-1] + //! nu apare maxVal
                              dp[pos-2][maxVal-1] + //! maxVal doar pe pos-1 si pos
                              dp[pos-1][maxVal-1] ; //! maxVal doar pe pos
            if (maxVal > 1)   dp[pos][maxVal] += sums[pos-2][maxVal-2] ; //! maxVal doar pe pos-1

            while (dp[pos][maxVal] >= mod) dp[pos][maxVal] -= mod;
            sums[pos][maxVal] = sums[pos][maxVal-1] + dp[pos][maxVal];
            while (sums[pos][maxVal] >= mod) sums[pos][maxVal] -= mod;
        }
    }

    printf("%d", dp[n][n] );

    return 0;
}
