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

#define maxN 311

int n, m, i, j, now, x, y, mod, lim, not_assigned;
ll comb[maxN][maxN];
int loc[maxN], sum_loc[maxN];
ll dp[maxN][maxN];

int main()
{
    freopen("negustori.in","r",stdin);
    freopen("negustori.out","w",stdout);

    scanf("%d%d%d", &n, &m, &mod);
    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        loc[y]++;
    }
    for (i = 2; i <= n; i++)
        sum_loc[i] = sum_loc[i - 1] + loc[i];


    dp[n + 1][0] = 1;
    for (i = n + 1; i > 1; i--) {
        for (j = 0; j <= n - i + 1; j++) {
            if (dp[i][j] == 0) continue;

            not_assigned = (n - m) - (n - i + 1 - j - sum_loc[n] + sum_loc[i - 1]);
            lim = j + 1 - loc[i - 1];

            for (now = 0; now <= lim; now++) {
                dp[i - 1][lim - now] += dp[i][j] * comb[not_assigned][now];
                dp[i - 1][lim - now] %= mod;
            }
        }
    }

    if (dp[1][0] == 0) {
        printf("NO");
        return 0;
    }
    printf("YES %lld", dp[1][0]);


    return 0;
}
