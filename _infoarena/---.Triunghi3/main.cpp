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

int n, i, j, x;
vector<int> lf[maxN];
vector<int> rh[maxN];

ll dp[maxN][maxN];
ll ans, pre;

int main()
{
    freopen("triunghi3.in","r",stdin);
    freopen("triunghi3.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            scanf("%d", &x);

            lf[j].pb(x);
            rh[n - (i - j + 1) + 1].pb(x);
        }
    }

    for (i = 1; i <= n; i++) {
        reverse(lf[i].begin(), lf[i].end());
        reverse(rh[i].begin(), rh[i].end());

        for (j = 1; j < lf[i].size(); j++) lf[i][j] += lf[i][j - 1];
        for (j = 1; j < rh[i].size(); j++) rh[i][j] += rh[i][j - 1];
    }

    for (i = 2; i <= n; i++) {
        ans += lf[i][ lf[i].size() - 1 ];
        ans += lf[i - 1][ lf[i - 1].size() - 1 ];
        ans -= lf[i - 1][0];

        ans += rh[i][ rh[i].size() - 1 ];
        ans += rh[i - 1][ rh[i - 1].size() - 1 ];
        ans -= rh[i][0];
    }

    pre = ans;
    ans = 1LL << 60;

    dp[1][n] = 0;
    for (i = 1; i <= n; i++) {
        for (j = n; j >= i; j--) {
            if (i == 1 && j == n) continue;

            dp[i][j] = 1LL << 60;

            if (i != 1) {
                int dim = j - i + 1;
                ll aux = dp[i - 1][j] + 1LL * (lf[i][dim - 1] + lf[i - 1][dim] - lf[i - 1][0]) * (dim - 1);
                dp[i][j] = min(dp[i][j], aux);
            }

            if (j != n) {
                int dim = j - i + 1;
                ll aux = dp[i][j + 1] + 1LL * (rh[j][dim - 1] + rh[j + 1][dim] - rh[j + 1][0]) * (dim - 1);
                dp[i][j] = min(dp[i][j] , aux);
            }

            if (i == j) ans = min(ans, pre + dp[i][i]);
        }
    }

    printf("%lld", ans);

    return 0;
}
