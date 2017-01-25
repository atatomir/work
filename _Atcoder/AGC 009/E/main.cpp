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

#define maxN 4011
#define mod 1000000007

int n, m, k, i, j, cf, NN, MM;
ll dp[maxN][maxN], ans;
bool ok = true;


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &m, &k);

    dp[0][0] = 1;
    for (i = 0; ok; i++) {
        ok = false;

        for (j = 0; j <= i * (k - 1); j++) {
            if (dp[i][j] == 0) continue;
            dp[i][j] %= mod;
            ok = true;

            for (cf = 0; cf < k; cf++) {
                NN = j + cf;
                MM = i * (k - 1) - j + (k - 1 - cf);

                if (NN > n || MM > m - 1) continue;
                dp[i + 1][NN] += dp[i][j];
                if (NN % (k - 1) == n % (k - 1))
                    if (MM % (k - 1) == (m - 1) % (k - 1))
                        if (cf != 0)
                            ans = (ans + dp[i][j]) % mod;
            }
        }
    }

    printf("%lld", ans);

    return 0;
}
