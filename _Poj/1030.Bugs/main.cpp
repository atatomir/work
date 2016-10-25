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

#define maxN 155
#define maxM 15

#define maxSt 59077
#define inf 1000000


int Q, qq;
int n, m, i, j, x, y, k, sz;
bool deny[maxN][maxM];

int dp[maxM][maxSt];
int null[maxM][maxSt];

int conf[maxSt][13];
int dif[13];


void create_confs() {
    int i, j, p;
    int aux;

    for (sz = 1, i = 1; i <= m; i++, sz *= 3);
    aux = sz;

    for (j = 1; j <= m; j++) {
        aux /= 3;
        dif[j] = aux;

        for (i = 0; i < sz; i += 3 * aux) {
            for (p = 0; p < aux; p++) conf[i + p][j] = 0;
            for (p = 0; p < aux; p++) conf[i + p + aux][j] = 1;
            for (p = 0; p < aux; p++) conf[i + p + 2 * aux][j] = 2;
        }
    }
}

int null_state(int act, int pos) {
    act -= dif[pos] * conf[act][pos];
    return act;
}

int plus_state(int act, int pos) {
    if (conf[act][pos] == 2) return act;
    return act + dif[pos];
}


void compute_dp() {
    int i, j, act, go;

    for (i = 0; i <= m; i++)
        for (j = 0; j < sz; j++) null[i][j] = -inf;

    memcpy(dp, null, sizeof(null));
    dp[0][0] = 0;

    for (i = 1; i <= n; i++) {

        for (j = 0; j < m; j++) {
            for (act = 0; act < sz; act++) {
                if (dp[j][act] < 0) continue;

                //! dont cut any rectangle
                if (deny[i][j + 1]) {
                    go = null_state(act, j + 1);
                    dp[j + 1][go] = max(dp[j + 1][go], dp[j][act]);
                } else {
                    go = plus_state(act, j + 1);
                    dp[j + 1][go] = max(dp[j + 1][go], dp[j][act]);
                }

                //! cut 3x2
                if (j + 2 <= m && deny[i][j + 1] == 0 && deny[i][j + 2] == 0) {
                    if (conf[act][j + 1] == 2 && conf[act][j + 2] == 2) {
                        go = null_state(act, j + 1);
                        go = null_state(go, j + 2);

                        dp[j + 2][go] = max(dp[j + 2][go], dp[j][act] + 1);
                    }
                }

                //! cut 2x3
                if (j + 3 <= m && deny[i][j + 1] == 0 && deny[i][j + 2] == 0 && deny[i][j + 3] == 0) {
                    if (conf[act][j + 1] >= 1 && conf[act][j + 2] >= 1 && conf[act][j + 3] >= 1) {
                        go = null_state(act, j + 1);
                        go = null_state(go, j + 2);
                        go = null_state(go, j + 3);

                        dp[j + 3][go] = max(dp[j + 3][go], dp[j][act] + 1);
                    }
                }


            }
        }


        memcpy(null[0], dp[m], sizeof(dp[m]));
        memcpy(dp, null, sizeof(null));
    }

}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &Q);
    for (qq = 1; qq <= Q; qq++) {
        scanf("%d%d%d", &n, &m, &k);
        memset(deny, 0, sizeof(deny));
        for (i = 1; i <= k; i++) {
            scanf("%d%d", &x, &y);
            deny[x][y] = true;
        }

        create_confs();
        compute_dp();

        int ans = 0;
        for (i = 0; i < sz; i++)
            ans = max(ans, dp[0][i]);

        printf("%d\n", ans);
    }


    return 0;
}
