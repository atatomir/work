#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll int

#define maxN 1024

int n, p, i, j, st, conf, to;
ll v[maxN];
int d[maxN];

ll dp[1 << 12][maxN];
vector<int> bits;


int main()
{
    freopen("morcovi.in","r",stdin);
    freopen("morcovi.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);
    scanf("%d", &p);
    for (i = 0; i < p; i++) scanf("%d", &d[i]);

    for (i = 1; i <= n; i++) dp[0][i] = v[i];
    st = (1 << p);

    for (conf = 0; conf < st; conf++) {
        bits.clear();
        for (i = 0; i < p; i++)
            if ( ((conf >> i) & 1) == 0 ) bits.pb(i);

        for (i = 1; i <= n; i++) {
            if (dp[conf][i] == 0) continue;

            for (int bit : bits) {
                to = conf | (1 << bit);
                if (i > d[bit]) dp[to][i - d[bit]] = max(dp[to][i - d[bit]], dp[conf][i] + v[ i - d[bit] ]);
                if (i + d[bit] <= n) dp[to][i + d[bit]] = max(dp[to][i + d[bit]], dp[conf][i] + v[ i + d[bit] ]);
            }
        }
    }

    ll ans = 0;
    for (i = 1; i <= n; i++) ans = max(ans, dp[st - 1][i]);

    printf("%d", ans);

    return 0;
}
