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

#define maxN 52
#define maxT 1024

int n, x, i, T, T1, T2;
int d[maxN], s[maxN];


int dp[maxT][maxT];
int ans[maxT][maxT];

int vr[maxN][maxT];
int aux[maxT];

int sol;



void compute() {
    int i, j, k;
    int TT1 = T2 - d[n];
    int TT2 = T - (T1 + d[n]);

    memset(dp, 0, sizeof(dp));
    for (i = 1; i <= x; i++) {

        for (j = TT1; j >= 0 ; j--) {
            for (k = T - j - d[n]; k >= d[i]; k--) {
                if (j >= d[i])
                    dp[j][k] = max(dp[j][k], dp[j - d[i]][k] + s[i]);

                dp[j][k] = max(dp[j][k], dp[j][k - d[i]] + s[i]);
            }

            if (j >= d[i])
                for (k = d[i] - 1; k >= 0; k--)
                    dp[j][k] = max(dp[j][k], dp[j - d[i]][k] + s[i]);
        }

    }

    memcpy(ans, dp, sizeof(ans));

    // -------------------------------------------------------------------------------//

    memset(dp, 0, sizeof(dp));
    for (i = x + 1; i < n; i++) {

        for (j = TT1; j >= 0 ; j--) {
            for (k = T - j - d[n]; k >= d[i]; k--) {
                if (j >= d[i])
                    dp[j][k] = max(dp[j][k], dp[j - d[i]][k] + s[i]);

                dp[j][k] = max(dp[j][k], dp[j][k - d[i]] + s[i]);
            }

            if (j >= d[i])
                for (k = d[i] - 1; k >= 0; k--)
                    dp[j][k] = max(dp[j][k], dp[j - d[i]][k] + s[i]);
        }

    }

    for (i = 0; i <= T; i++)
        for (j = 0; j <= T; j++)
            ans[i][j] += dp[i][j];
}

void vraja() {
    int i, j;

    memset(vr, 0, sizeof(vr));
    for (i = 1; i <= x; i++) {
        memcpy(vr[i], vr[i - 1], sizeof(vr[i]));
        for (j = d[i]; j <= T; j++)
            vr[i][j] = max(vr[i - 1][j], vr[i - 1][j - d[i]] + s[i]);
    }

    memcpy(aux, vr[x], sizeof(aux));

    memset(vr, 0, sizeof(vr));
    for (i = x + 1; i < n; i++) {
        memcpy(vr[i], vr[i - 1], sizeof(vr[i]));
        for (j = d[i]; j <= T; j++)
            vr[i][j] = max(vr[i - 1][j], vr[i - 1][j - d[i]] + s[i]);
    }

    for (i = 1; i <= T; i++)
        ans[0][i] = aux[i] + vr[n - 1][i];
}



int main()
{
    freopen("core2.in","r",stdin);
    freopen("core2.out","w",stdout);

    scanf("%d%d%d", &n, &x, &T);
    for (i = 1; i <= n; i++) scanf("%d%d", &d[i], &s[i]);
    scanf("%d%d", &T1, &T2);

    compute();
    vraja();
    sol = ans[0][T];

    for (i = T1; i + d[n] <= T2; i++)
        sol = max(sol, ans[i][T - i - d[n]] + s[n]);

    printf("%d", sol);
    cerr << sol;

    return 0;
}
