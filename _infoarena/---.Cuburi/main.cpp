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

#define lvl 4
#define maxN 41
#define def (1 << lvl)

#define mod 10000

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int cnt, dim;
pair< vector<int>, vector<int> > pre[1 << lvl][1 << lvl];
int work[5][5][5];

int poww[maxN * 4];

int n, k, i, j;
int st, d1, d2, new_st, new_d1, new_d2;
int ss, dd;
int dp[2][1 << lvl][4 * maxN][4 * maxN];
ll ans;


void dfs(int lv, int x, int y) {
    work[lv][x][y] = cnt;
    dim++;

    for (int i = 0; i < 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (work[lv][xx][yy] == 0)
            dfs(lv, xx, yy);
    }
}

void precompute() {
    int i, j, k, s1, s2, aux;
    vector<int> p1, p2;

    for (i = 0; i <= 4; i++)
        for (j = 0; j <= 4; j++)
            for (k = 0; k <= 4; k++)
                work[i][j][k] = 1;

    for (s1 = 0; s1 < def; s1++) {
        for (s2 = 0; s2 < def; s2++) {
            p1.clear(); p2.clear();

            //! set old level
            aux = s1;
            for (i = 1; i <= 2; i++)
                for (j = 1; j <= 2; j++)
                    work[1][i][j] = aux & 1, aux >>= 1;

            //! set new level
            aux = s2;
            for (i = 1; i <= 2; i++)
                for (j = 1; j <= 2; j++)
                    work[2][i][j] = aux & 1, aux >>= 1;

            //! fill old level
            cnt = 0;
            for (i = 1; i <= 2; i++) {
                for (j = 1; j <= 2; j++) {
                    if (work[1][i][j] != 0) continue;

                    cnt--;
                    dfs(1, i, j);
                }
            }

            //! fill new level
            cnt = 0;
            for (i = 1; i <= 2; i++) {
                for (j = 1; j <= 2; j++) {
                    if (work[2][i][j] != 0) continue;

                    cnt--; dim = 0;
                    dfs(2, i, j);

                    if (cnt == -1)
                        p1.pb(dim);
                    else
                        p2.pb(dim);
                }
            }

            //! compute result
            for (i = 1; i <= 2; i++) {
                for (j = 1; j <= 2; j++) {
                    if (work[1][i][j] == 1 || work[2][i][j] == 1) continue;

                    if (work[2][i][j] == -1)
                        p1.pb(work[1][i][j]);
                    else
                        p2.pb(work[1][i][j]);
                }
            }

            //! unique
            sort(p1.begin(), p1.end());
            p1.resize(unique(p1.begin(), p1.end()) - p1.begin());

            sort(p2.begin(), p2.end());
            p2.resize(unique(p2.begin(), p2.end()) - p2.begin());

            if (p1 == p2 && p1.size() > 1) {
                //! one component in two diagonal places...

                p1.pb(1);
                p2.clear();
            }

            pre[s1 ^ 15][s2 ^ 15] = mp(p1, p2);
        }
    }
}





int main()
{
    freopen("cuburi.in","r",stdin);
    freopen("cuburi.out","w",stdout);

    poww[0] = 1;
    for (i = 1; i < maxN * 4; i++)
        poww[i] = (poww[i - 1] * 2) % mod;

    precompute();

    scanf("%d%d", &n, &k);

    ss = 0; dd = 1;
    dp[ss][0][0][0] = 1;

    for (i = 0; i < n; i++) {
        memset(dp[dd], 0, sizeof(dp[dd]));

        for (int st = 0; st < def; st++) {
            for (d1 = 0; d1 < k; d1++) {
                for (d2 = 0; d2 < k; d2++) {
                    if (dp[ss][st][d1][d2] == 0) continue;
                    dp[ss][st][d1][d2] %= mod;

                    for (new_st = 0; new_st < def; new_st++) {

                        //! first comp
                        new_d1 = 0;
                        for (auto e : pre[st][new_st].first) {
                            if (e > 0) {
                                new_d1 += e;
                            } else {
                                new_d1 += (e == -1 ? d1 : d2);
                            }
                        }

                        //! second comp
                        new_d2 = 0;
                        for (auto e : pre[st][new_st].second) {
                            if (e > 0) {
                                new_d2 += e;
                            } else {
                                new_d2 += (e == -1 ? d1 : d2);
                            }
                        }

                        //! two columns of height 2 in same component
                        if (st == 9 || st == 6)
                            if (new_st == st && d2 == 0)
                                new_d1 = d1 + 2, new_d2 = 0;

                        //! continuing second column in same component
                        if (st == 9 && (new_st & 8) == 8 && (new_st & 1) == 0 && d2 == 0)
                            new_d1 = d1 + pre[st][new_st].first.back();

                        if (st == 6 && (new_st & 4) == 4 && (new_st & 2) == 0 && d2 == 0)
                            new_d1 = d1 + pre[st][new_st].first.back();

                        //! compute next steps

                        if (max(new_d1, new_d2) >= k) {
                            ans += dp[ss][st][d1][d2] * poww[4 * (n - i - 1)];
                            ans %= mod;
                            continue;
                        }


                        dp[dd][new_st][new_d1][new_d2] += dp[ss][st][d1][d2];
                    }

                }
            }
        }

        swap(ss, dd);
    }

    printf("%lld", ans);
    cerr << ans;

    return 0;
}
