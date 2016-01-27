#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2016
#define mod  19997

int n, k, i, j;
int dp[maxN];

int comb[maxN][maxN];
int perm[maxN];

int main()
{
    freopen("cifru.in","r",stdin);
    freopen("cifru.out","w",stdout);

    scanf("%d%d", &n, &k);

    comb[0][0] = 1;
    for (i = 1; i <= n; i++) {
        comb[i][0] = 1;
        comb[i][1] = i;

        for (j = 2; j <= i; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= mod) comb[i][j] -= mod;
        }
    }

    perm[0] = perm[1] =  1;
    for (i = 2; i <= n; i++)
        perm[i] = (perm[i - 1] * i) % mod;

    dp[0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = 0; j < i; j++) {
            int dim = i - j;

            if (k % dim != 0) continue;
            dp[i] += (((dp[j] * comb[i - 1][dim - 1]) % mod) * perm[dim - 1]) % mod;
            if (dp[i] >= mod) dp[i] -= mod;
        }
    }

    printf("%d", dp[n]);


    return 0;
}
