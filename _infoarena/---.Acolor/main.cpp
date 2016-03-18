/*
 * expected : 100 points
 */

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

#define maxN 100001
#define maxK 4
#define mod 10007

int n, R, k, i;
int son[maxN][2];
int dp[maxN][maxK][maxK][maxK]; //! node, col, col_son_left, col_son_right

inline void add_val(int &who, int v) {
    who += v;
    if (who >= mod) who -= mod;
}

void solve(int node) {
    int col, c1, c2;

    int lSon = son[node][0];
    int rSon = son[node][1];

    if (lSon) solve(lSon);
    if (rSon) solve(rSon);

    if (lSon == rSon && lSon == 0) {
        //! it is a leaf
        add_val(dp[node][1][1][1], 1);
        add_val(dp[node][2][2][2], 1);
        add_val(dp[node][3][3][3], 1);
        return;
    }

    for (col = 1; col <= 3; col++) {
        for (c1 = 1; c1 <= 3; c1++) {
            for (c2 = 1; c2 <= 3; c2++) {
                int v1 = 1;
                if (lSon) {
                    v1 = 0;

                    if (c1 == col) {
                        //! k - 1 remaining - second fixed
                        v1 += dp[lSon][1][2][1] * (k - 1) % mod;
                        v1 += dp[lSon][1][2][3] * (k - 1) * (k - 2) % mod;
                    } else {
                        //! k - 2 remaining - second fixed
                        v1 += dp[lSon][1][1][1];
                        v1 += dp[lSon][1][2][2] * (k - 2) % mod;
                        v1 += dp[lSon][1][1][2] * (k - 2) % mod;
                        v1 += dp[lSon][1][2][1] * (k - 2) % mod;
                        v1 += dp[lSon][1][2][3] * (k - 2) * (k - 3) % mod;
                    }

                    v1 %= mod;
                } else {
                    if (c1 != col) v1 = 0;
                }

                int v2 = 1;
                if (rSon) {
                    v2 = 0;

                    if (c2 == col) {
                        //! k - 1 remaining - third fixed
                        v2 += dp[rSon][1][1][2] * (k - 1) % mod;
                        v2 += dp[rSon][1][2][3] * (k - 1) * (k - 2) % mod;
                    } else {
                        //! k - 2 remaining - third fixed
                        v2 += dp[rSon][1][1][1];
                        v2 += dp[rSon][1][1][2] * (k - 2) % mod;
                        v2 += dp[rSon][1][2][1] * (k - 2) % mod;
                        v2 += dp[rSon][1][2][2] * (k - 2) % mod;
                        v2 += dp[rSon][1][2][3] * (k - 2) * (k - 3) % mod;
                    }

                    v2 %= mod;
                } else {
                    if (c2 != col) v2 = 0;
                }

                add_val(dp[node][col][c1][c2], (v1 * v2) % mod);
            }
        }
    }


}



int main()
{
    freopen("acolor.in","r",stdin);
    freopen("acolor.out","w",stdout);

    scanf("%d%d%d", &n, &R, &k);
    for (i = 1; i <= n; i++) scanf("%d%d", &son[i][0], &son[i][1]);

    solve(R);

    int ans = 0;

    ans += dp[R][1][1][1] * k % mod;
    ans += dp[R][1][1][2] * k * (k - 1) % mod;
    ans += dp[R][1][2][1] * k * (k - 1) % mod;
    ans += dp[R][1][2][2] * k * (k - 1) % mod;
    ans += dp[R][1][2][3] * k * (k - 1) % mod * (k - 2) % mod;
    ans %= mod;


    printf("%d", ans);
    cerr << ans;


    return 0;
}
