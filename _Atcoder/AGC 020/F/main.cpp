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

#define maxN 6
#define maxNC 300

int n, c, i;
int L[maxN];
int ord[maxN], wh[maxN];

ll dp[maxNC + 1][1 << maxN][maxNC]; //! [pos][conf][last]
ll ans;

ll solve() {
    int pos, conf, last, i;
    int lim_nc = n * c;
    int lim_conf = 1 << n;

    int fin_id;
    int fin_block;
    int fin_frac;

    int act_id;
    int act_block;
    int act_frac;

    int act_fin_block;
    int best;

    memset(dp, 0, sizeof(dp));
    for (i = 0; i < n; i++) wh[ord[i]] = i;

    dp[0][1][0] = 1;
    for (pos = 0; pos < lim_nc; pos++) {
        for (conf = 0; conf < lim_conf; conf++) {
            for (last = 0; last < lim_nc; last++) {
                if (dp[pos][conf][last] == 0) continue;

                dp[pos + 1][conf][last] += dp[pos][conf][last];
                act_id = ord[pos % n];
                if ((conf >> act_id) & 1) continue;

                fin_id = ord[last % n];
                fin_block = (last / n) + L[fin_id];
                fin_frac = last % n;

                act_block = pos / n;
                act_fin_block = act_block + L[act_id];
                act_frac = pos % n;

                if (fin_block < act_block) continue;
                if (fin_block == act_block && fin_frac < act_frac) continue;

                best = pos;
                if (act_fin_block < fin_block) best = last;
                if (act_fin_block == fin_block && act_frac < fin_frac) best = last;

                dp[pos + 1][conf | (1 << act_id)][best] += dp[pos][conf][last];
            }
        }
    }

    ll ans = 0;
    for (pos = 0; pos < lim_nc; pos++) {
        act_id = ord[pos % n];
        act_block = (pos / n) + L[act_id];

        if (act_block >= c)
            ans += dp[lim_nc][lim_conf - 1][pos];
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &c);
    for (i = 0; i < n; i++) scanf("%d", &L[i]), ord[i] = i;
    sort(L, L + n);
    reverse(L, L + n);

    do {
        ans += solve();
    } while (next_permutation(ord + 1, ord + n));


    double sol = 1.00 * ans;
    for (i = 1; i < n; i++) sol /= 1.00 * i;
    for (i = 1; i < n; i++) sol /= 1.00 * c;

    printf("%.20lf", sol);


    return 0;
}
