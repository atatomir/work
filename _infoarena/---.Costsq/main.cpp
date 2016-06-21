#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long
#define pb push_back
#define mp make_pair

#define maxN 100011
#define inf (1LL << 60)

int n, k, i, j, ss, dd;
int w[maxN], l[maxN], r[maxN];
ll sum[maxN], dp[2][maxN];

int pos;
ll best_from[maxN];
int Q[maxN], pos_l, pos_r;


void add_pos(int pos) {
    ll aux, sub;

    while (pos_l <= pos_r) {
        int i1 = Q[pos_r];
        int i2 = pos;

        aux = -(dp[ss][i1] - dp[ss][i2] + sum[i1] * sum[i1] - sum[i2] * sum[i2]);
        sub = 2 * (sum[i2] - sum[i1]);

        aux = (aux + sub - 1) / sub;

        if (aux > best_from[i1]) break;
        pos_r--;
    }

    Q[++pos_r] = pos;
    best_from[pos] = aux;
}

int main()
{
    freopen("costsq.in", "r", stdin);
    freopen("costsq.out", "w", stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &w[i], &l[i], &r[i]);
        sum[i] = sum[i - 1] + w[i];
    }

    ss = 0; dd = 1;
    for (i = 1; i <= n; i++) dp[ss][i] = inf;

    for (i = 1; i <= k; i++) {
        pos = 1;
        best_from[0] = -1;
        Q[pos_l = pos_r = 1] = 0;

        for (j = 1; j <= n; j++) {
            //! add to r
            while (pos < r[j])
                add_pos(pos++);

            //! remove to l
            while (pos_l <= pos_r && Q[pos_l] < l[j] - 1) pos_l++;

            //! remove old
            while (pos_l + 1 <= pos_r && sum[j] >= best_from[ Q[pos_l + 1] ]) pos_l++;

            if (pos_l > pos_r || dp[ss][ Q[pos_l] ] >= inf) {
                dp[dd][j] = inf;
                continue;
            }

            int act = Q[pos_l];
            dp[dd][j] = dp[ss][act] + (sum[j] - sum[act]) * (sum[j] - sum[act]);
        }

        for (j = 0; j < i; j++) dp[dd][j] = inf;

        swap(ss, dd);
    }

    printf("%lld", dp[ss][n]);


    return 0;
}
