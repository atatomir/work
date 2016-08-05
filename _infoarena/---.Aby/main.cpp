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

#define maxN 12

int t, ti;
int n, m, i, j, x, y;
bool adj[maxN][maxN];

int ss, dd, ans;
bool dp[2][maxN][1 << maxN][2];
//! dp[ss/dd][node][state][0 - before magic / 1 - after magic]

bool can_move(const int node, const int st, const int to) {
    static bool ch;

    ch = ((st >> node) & 1) ^ ((st >> to) & 1);
    if (ch == false)
        return adj[node][to];
    else
        return adj[to][node];
}

void solve() {
    int i, j, st, max_st;
    bool need;

    max_st = (1 << n);

    memset(dp, 0, sizeof(dp));
    ss = 0; dd = 1;

    for (st = 0; st < max_st; st++)
        dp[ss][n - 1][st][0] = dp[ss][n - 1][st][1] = true;

    need = true;
    while (need) {
        memcpy(dp[dd], dp[ss], sizeof(dp[ss]));
        need = false;

        for (i = 0; i < n; i++) {
            for (st = 0; st < max_st; st++) {
                if (dp[dd][i][st][0] == false) {
                    dp[dd][i][st][0] = true;
                    for (j = 0; j < n; j++)
                        if (dp[ss][i][st ^ (1 << j)][1] == false)
                            {dp[dd][i][st][0] = false; break;}
                }

                if (dp[dd][i][st][1] == false) {
                    for (j = 0; j < n; j++) {
                        if (dp[ss][j][st][0] == false) continue;
                        if (!can_move(i, st, j)) continue;

                        dp[dd][i][st][1] = true;
                        break;
                    }
                }

                need |= dp[ss][i][st][0] ^ dp[dd][i][st][0];
                need |= dp[ss][i][st][1] ^ dp[dd][i][st][1];
            }
        }

        swap(ss, dd);
    }

    ans = dp[ss][0][0][1];
}

int main()
{
    freopen("aby.in","r",stdin);
    freopen("aby.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        memset(adj, 0, sizeof(adj));

        scanf("%d%d", &n, &m);
        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            adj[x][y] = true;
        }

        solve();
        printf("%d\n", ans);
    }


    return 0;
}
