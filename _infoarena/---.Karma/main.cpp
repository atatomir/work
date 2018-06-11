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

const int maxN = 22;
const int maxConf = (1 << 20) + 2;
const ll mod = 1000000007;

int n, m, i, j, limit, conf;
char mat[maxN][maxN];
int v[maxN][maxN];
int dp[maxConf], aux[maxN];

inline void upd(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main()
{
    freopen("karma.in","r",stdin);
    freopen("karma.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", mat[i]);
        for (j = 0; j < m; j++) {
            if (mat[i][j] == '(')
                v[j][i] = 1;
            else
                v[j][i] = -1;
        }
    }

    limit = 1 << m;
    dp[0] = 1;

    for (conf = 0; conf < limit; conf++) {
        if (dp[conf] == 0) continue;
        for (i = 1; i <= n; i++) aux[i] = 0;

        for (j = 0; j < m; j++) {
            if (((conf >> j) & 1) == 0) continue;
            for (i = 1; i <= n; i++) aux[i] += v[j][i];
        }

        for (i = 1; i <= n; i++) {
            if (aux[i] < 0) {
                dp[conf] = 0;
                break;
            }
        }

        if (dp[conf] == 0) continue;
        for (i = 0; i < m; i++) {
            if ((conf >> i) & 1) continue;
            upd(dp[conf | (1 << i)], dp[conf]);
        }
    }

    printf("%d", dp[limit - 1]);



    return 0;
}
