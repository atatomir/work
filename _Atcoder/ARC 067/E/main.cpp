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

#define mod 1000000007
#define maxN 1011

int n, i, j, k;
int a, b, c, d;
ll dp[maxN][maxN], aux;
ll comb[maxN][maxN];
ll pre[maxN];

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;

        for (j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= mod) comb[i][j] -= mod;
        }
    }


    dp[a][0] = 1;
    for (i = a; i <= b; i++) {

        pre[1] = 1;
        for (k = 2; i * k <= n; k++)
            pre[k] = (pre[k - 1] * comb[i * k - 1][i - 1]) % mod;

        for (j = 0; j <= n; j++) {
            if (dp[i][j] == 0) continue;
            dp[i][j] %= mod;

            dp[i + 1][j] += dp[i][j];
            dp[i + 1][j] %= mod;

            for (k = c; k <= d && j + i * k <= n; k++) {
                aux = pre[k];

                dp[i + 1][j + i * k] += (((dp[i][j] * aux) % mod) * comb[j + i * k][i * k]) % mod;
                dp[i + 1][j + i * k] %= mod;
            }
        }
    }

    printf("%lld", dp[b + 1][n] % mod);


    return 0;
}
