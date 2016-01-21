#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define mod 999017
#define maxN 555
#define moddo(x) if(x >= mod) x -= mod;

int n, i, p, q, dir, pp, qq;
int last, now_p, now_dif, last_move, now_pos;

int ss, dd;
int dp[2][maxN][maxN][2][2];
//! dp[ss/dd][last][p][p - q][up/down]

int main()
{
    freopen("intuitie.in","r",stdin);
    freopen("intuitie.out","w",stdout);

    scanf("%d%d%d", &n, &p, &q);

    if (p < q) swap(p, q);
    if (p - q > 1) {
        printf("0");
        return 0;
    }

    ss = 0; dd = 1;
    dp[ss][2][0][0][0] = 1; //! doar perm 1 2

    for (i = 3; i <= n; i++) {
        memset(dp[dd], 0, sizeof(dp[dd]));

        for (last = 1; last < i; last++) {
            for (now_pos = 1; now_pos <= i; now_pos++)
                for (now_p = 0; now_p <= p; now_p++) {

                    //! q = p - 1 && up
                    if (now_p >= 1) {
                        if (now_pos > last) {
                            dp[dd][now_pos][now_p][1][0] += dp[ss][last][now_p][1][0];
                            moddo(dp[dd][now_pos][now_p][1][0]);
                        } else {
                            //! p - q > 1
                        }
                    }

                    //! q = p && up
                    if (now_pos > last) {
                        dp[dd][now_pos][now_p][0][0] += dp[ss][last][now_p][0][0];
                        moddo(dp[dd][now_pos][now_p][0][0])
                    } else {
                        dp[dd][now_pos][now_p + 1][1][1] += dp[ss][last][now_p][0][0];
                        moddo(dp[dd][now_pos][now_p + 1][1][1]);
                    }

                    //! q = p - 1 && down
                    if (now_p >= 1) {
                        if (now_pos > last) {
                            dp[dd][now_pos][now_p][0][0] += dp[ss][last][now_p][1][1];
                            moddo(dp[dd][now_pos][now_p][0][0]);
                        } else {
                            dp[dd][now_pos][now_p][1][1] += dp[ss][last][now_p][1][1];
                            moddo(dp[dd][now_pos][now_p][1][1]);
                        }
                    }

                    //! q = p && down
                    if (now_pos > last) {
                        //! q - p > 0
                    } else {
                        dp[dd][now_pos][now_p][0][1] += dp[ss][now_pos][now_p][0][1];
                        moddo(dp[dd][now_pos][now_p][0][1]);
                    }
            }
        }

        swap(ss, dd);
    }

    int ans = 0;
    for (i = 1; i <= n; i++) {
        ans += dp[ss][i][p][p - q][0];
        ans += dp[ss][i][p][p - q][1];
        while (ans >= mod) ans -= mod;
    }

    if (p == q)
        ans = (ans * 2) % mod;

    printf("%d", ans);


    return 0;
}
