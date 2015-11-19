#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2015
#define mod 30013

int n, k, i, j;
int dp[maxN][maxN]; //! dim, greseli
int dp_aux[maxN][maxN]; //! cnt, dim

int ans;

void compute_dp_for_one() {
    //! dp for k == 1
    //! combine this dp with the second one for k > 1
    dp[1][0] = 1;

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            int ii, jj, how;

            ii = i + 1;
            jj = j;
            how = i - j;
            dp[ii][jj] = (dp[ii][jj] + how * dp[i][j]) % mod;

            ii = i + 1;
            jj = j + 1;
            how = 1;
            dp[ii][jj] = (dp[ii][jj] + how * dp[i][j]) % mod;

            ii = i + 1;
            jj = j - 1;
            how = j;
            dp[ii][jj] = (dp[ii][jj] + how * dp[i][j]) % mod;
        }
    }
}

void compute_dp_aux() {
    for (i = 1; i <= k; i++) dp_aux[1][i] = i;
    for (i = k + 1; i <= n; i++) dp_aux[1][i] = k;

    for (i = 2; i <= n; i++) {
        for (j = i; j <= n; j++) {
            int val = (j - k - 1 < 0 ? 0 : dp_aux[i - 1][j - k - 1]);
            dp_aux[i][j] = dp_aux[i - 1][j - 1] - val;
            dp_aux[i][j] += dp_aux[i][j - 1] + mod;

            while (dp_aux[i][j] >= mod)
                dp_aux[i][j] -= mod;
        }
    }
}

int main()
{
    freopen("kcons.in","r",stdin);
    freopen("kcons.out","w",stdout);

    scanf("%d%d", &n, &k);
    compute_dp_for_one();
    compute_dp_aux();

    for (i = 1; i <= n; i++) {
        int for_one = dp[i][0];
        int for_more = dp_aux[i][n] - dp_aux[i][n - 1];

        ans = (ans + for_one * for_more) % mod;
    }

    printf("%d", ans);

    return 0;
}
