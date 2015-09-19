#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 42
#define maxT 8
#define inf 500000000

int n, m, i, j, t, x, y, cost;
int roy[maxN][maxN];

int boss[maxT];
int list[maxT][maxT];

int dp[maxN][1 << maxT];

/*
 * dp[head][conf] - cost minim al unui arbore cu radacina in head
 *                  si nodurile selectate(dintre cele obligatorii)
 *                  corespondente in conf.
 * De remarcat ca orice stare provine din 2 alte stari nenule!!
 */

void roy_floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                roy[i][j] = min(roy[i][j], roy[i][k] + roy[k][j]);
}

bool isSet(int conf, int bit) {
    return (conf & (1 << bit)) != 0;
}

int compute(int head, int state) {
    if (state == 0) return 0;

    if (dp[head][state] != -1) return dp[head][state];
    if ( (state & (state - 1)) == 0 ) {
        int node;
        for (i = 0; i < t; i++)
            if(isSet(state, i))
                node = boss[i + 1];

        dp[head][state] = roy[head][node];
        return dp[head][state];
    }

    dp[head][state] = inf;

    vector<int> aux; aux.clear();
    for (int bit = 0; bit < t; bit++)
        if (isSet(state, bit) && boss[bit + 1] != head) aux.pb(bit);

     for (int vState = (1 << aux.size()) - 1; vState > 0; vState--) {
        int provState = 0;

        for (int bit = 0; bit < aux.size(); bit++)
            if (isSet(vState, bit))
                provState |= 1 << aux[bit];

        for (int i = 1; i <= n; i++) {
            dp[head][state] = min(dp[head][state],
                                  compute(i, provState) + roy[head][i] + compute(head, state ^ provState) );
        }
     }

     return dp[head][state];
}

int main()
{
    freopen("subarbore.in","r",stdin);
    freopen("subarbore.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            roy[i][j] = (i == j ? 0 : inf);

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &cost);
        roy[x][y] = roy[y][x] = cost;
    }

    roy_floyd();
    scanf("%d", &t);
    for (i = 1; i <= t; i++) scanf("%d", &boss[i]);

    if (t == 1) {
        printf("0");
        return 0;
    }

    for (int i = 0; i <= n; i++)
        for (int state = (1 << t); state >= 0; state--)
            dp[i][state] = -1;

    int lim = (1 << t) - 1;
    int ans = inf;
    for (i = 1; i <= n; i++) ans = min(ans, compute(i, lim));

    printf("%d", ans);

    return 0;
}
