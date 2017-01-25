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

#define maxN 111
#define maxK 5111
#define inf 1LL << 55

int t, ti;
int n, m, k, i, j, x, y;
ll d;
ll roy[maxN][maxN];
pair<int, int> Q[maxK];

ll dp[maxK];


void pre() {
    int i, j, k;

    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                roy[i][j] = min(roy[i][j], roy[i][k] + roy[k][j]);

}

ll solve() {
    int i, j;

    for (i = 1; i <= k; i++) {
        if (roy[1][Q[i].first] >= inf) return -1;
        if (roy[1][Q[i].second] >= inf) return -1;

        dp[i] = inf;
    }

    Q[0] = {1, 1};
    dp[0] = 0;

    for (i = 0; i < k; i++) {
        dp[i + 1] = min(dp[i + 1], dp[i] + roy[Q[i].second][Q[i + 1].first]
                                         + roy[Q[i + 1].first][Q[i + 1].second]);

        if (i + 1 == k) continue;

        dp[i + 2] = min(dp[i + 2], dp[i] + roy[Q[i].second][Q[i + 1].first]
                                         + roy[Q[i + 1].first][Q[i + 2].first]
                                         + roy[Q[i + 2].first][Q[i + 1].second]
                                         + roy[Q[i + 1].second][Q[i + 2].second]);
    }

    return dp[k];
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Start solving " << t << " tests.\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%d%d%d", &n, &m, &k);

        for (i = 0; i <= n; i++)
            for (j = 0; j <= n; j++)
                roy[i][j] = (i == j ? 0 : inf);

        for (i = 1; i <= m; i++) {
            scanf("%d%d%lld", &x, &y, &d);
            roy[x][y] = min(roy[x][y], d);
            roy[y][x] = min(roy[y][x], d);
        }

        pre();

        for (i = 1; i <= k; i++)
            scanf("%d%d", &Q[i].first, &Q[i].second);

        printf("Case #%d: %lld\n", ti, solve());
    }


    return 0;
}
