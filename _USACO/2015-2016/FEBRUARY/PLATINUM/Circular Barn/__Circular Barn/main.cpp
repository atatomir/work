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
#define maxK 11
#define inf (1LL << 60)

int n, k, i, j;
ll cnt[maxN];
ll best = inf;

ll dist[maxN];
ll sums[maxN];
ll how[maxN];

ll dp[maxK][maxN];
ll win[maxN];

int pos_l, pos_r;
int Q[maxN];

ll compute(int l, int r, int pas) {
    ll aux = dp[pas - 1][r + 1] + sums[r] - sums[l] - 1LL * l * (how[r] - how[l]);

    return aux;
}

ll get_win_point(int l, int r, int pas) {
    win[l] = -(dp[pas - 1][l + 1] - dp[pas - 1][r + 1] + sums[l] - sums[r]) / (how[r] - how[l]);
    return win[l];
}

ll try_now() {
    int i, j, pas, pos;

    for (i = 1; i <= n; i++) dist[i] = cnt[i] * i;
    for (i = 1; i <= n; i++) sums[i] = dist[i] + sums[i - 1];
    for (i = 1; i <= n; i++) how[i] = how[i - 1] + cnt[i];

    for (i = 1; i <= n; i++) dp[1][i] = compute(i, n, 1);
    for (pas = 2; pas <= k; pas++) {
        pos_l = 1;
        pos_r = 0;

        for (i = n; i > 0; i--) {
            //! remove old values from back
            win[i] = n + 1;
            while (pos_l <= pos_r && win[ Q[pos_r] ] <= get_win_point(i, Q[pos_r], pas)  ) pos_r--;
            //! add new value
            Q[++pos_r] = i;

            //! remove from front
            while (pos_l < pos_r && i <= win[ Q[pos_l + 1] ]) pos_l++;
            //! get actual value
            dp[pas][i] = compute(i, Q[pos_l], pas);
        }
    }

    //cerr << dp[k][1] << '\n';
    return dp[k][1];
}

int main()
{
    freopen("cbarn.in","r",stdin);
    freopen("cbarn.out","w",stdout);

    scanf("%d%d", &n, &k);
    k = min(k, n);
    for (i = 1; i <= n; i++) scanf("%lld", &cnt[i]);

    for (i = 1; i <= n; i++) {
        best = min(best, try_now());
        cnt[n + 1] = cnt[1];
        for (j = 1; j <= n; j++)
            cnt[j] = cnt[j + 1];
    }

    printf("%lld", best);


    return 0;
}
