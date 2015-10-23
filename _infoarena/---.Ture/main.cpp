#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 256
#define maxDim 16

int n, m, i, j, k, p, x, y;
bool bad[maxN][maxN];
bool rev;

long long dp[2][1 << maxDim], ans;
int dp_s, dp_d;

int main()
{
    freopen("ture.in","r",stdin);
    freopen("ture.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &p);
    if (n < m) {
        rev = true;
        swap(n, m);
    }

    for (i = 1; i <= p; i++) {
        scanf("%d%d", &x, &y);
        if (rev) swap(x, y);
        bad[x][y] = true;
    }

    dp_s = 0;
    dp_d = 1;

    dp[dp_s][0] = 1;

    int lim = (1 << m);

    for (i = 1; i <= n; i++) {
        memset(dp[dp_d], 0, sizeof(dp[dp_d]));

        for (int state = 0; state < lim; state++) {
            for (j = 1; j <= m; j++) {
                if (bad[i][j]) continue;
                if ( (state & (1 << (j - 1))) != 0 ) continue;

                dp[dp_d][ state | (1 << (j - 1)) ] += dp[dp_s][state];
            }

            dp[dp_d][state] += dp[dp_s][state];
        }

        swap(dp_s, dp_d);
    }

    for (int _state = 0; _state < lim; _state++) {
        int cnt = 0;
        int state = _state;
        while (state > 0) {
            cnt ++;
            state &= state - 1;
        }

        if (cnt == k) ans += dp[dp_s][_state];
    }

    printf("%lld", ans);

    return 0;
}
