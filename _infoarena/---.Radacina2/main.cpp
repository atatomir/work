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

#define maxN 155

int n, x, i, x1, j, x2, bef;
ll mod, prod, val;
ll comb[maxN][maxN];
ll dp[maxN][maxN];
ll big[maxN];

int main()
{
    freopen("radacina2.in","r",stdin);
    freopen("radacina2.out","w",stdout);

    scanf("%d%d%lld", &n, &x, &mod);

    for (i = 0; i <= 2 * n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    dp[1][1] = 1;
    big[1] = 1;

    for (int sum = 2; sum <= n; sum++) {
        int lim = min(n - 1, sum - 1);

        for (i = max(1, sum - n); i <= lim; i++) {
            j = sum - i;
            if (j > i) continue;

            if (i == j) {

                for (x1 = 1; x1 <= i; x1++) {
                    if (dp[i][x1] == 0) continue;

                    for (x2 = 1; x2 <= j; x2++) {
                        if (dp[j][x2] == 0) continue;

                        prod = (((dp[i][x1] * dp[j][x2]) % mod) * comb[i - 1 + j - 1][i - 1]) % mod;
                        if (prod == 0) continue;

                        for (bef = 0; bef <= j; bef++) {
                            if ( bef >= x2) {
                                val = prod * ((comb[bef + x1 - 1][bef] * comb[i - x1 + j - bef][j - bef]) % mod);
                                dp[i + j][x1 + bef] = (dp[i + j][x1 + bef] + val) % mod;
                            }
                        }
                    }
                }

            } else {

                for (x1 = 1; x1 <= i; x1++) {
                    if (dp[i][x1] == 0) continue;

                    prod = (((dp[i][x1] * big[j]) % mod) * comb[i - 1 + j - 1][i - 1]) % mod;
                    if (prod == 0) continue;

                    for (bef = 0; bef <= j; bef++) {
                        val = prod * ((comb[bef + x1 - 1][bef] * comb[i - x1 + j - bef][j - bef]) % mod);
                        dp[i + j][x1 + bef] = (dp[i + j][x1 + bef] + val) % mod;
                    }

                }

            }

        }

        for (i = 1; i <= sum; i++)
            big[sum] += dp[sum][i];
        big[sum] %= mod;
    }



    printf("%lld", dp[n][x]);
    cerr << dp[n][x];


    return 0;
}
