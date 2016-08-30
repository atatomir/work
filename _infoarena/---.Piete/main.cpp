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
#define inf 1000000

int n, m, i, j, S, F, sm, bg, act;
int cost[maxN][maxN];

vector<int> bits;
vector< pair<int, int> > jump;

int main()
{
    freopen("piete.in","r",stdin);
    freopen("piete.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &S, &F);
    for (i = 1; i <= n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &cost[i][j]);

    for (int conf = (1 << m) - 1; conf > 0; conf--) {
        bits.clear();
        for (i = 0; i < m; i++)
            if ( (conf & (1 << i)) != 0 )
                bits.pb(i);

        sm = inf;
        bg = -inf;

        for (i = 1; i <= n; i++) {
            act = 0;

            for (int bit : bits)
                act += cost[i][bit];

            sm = min(sm, act);
            bg = max(bg, act);
        }

        if (sm != bg) jump.pb(mp(sm, bg - sm));
    }

    //sort(jump.begin(), jump.end());

    for (i = 0; i < 105; i++) {
        if (S >= F) {
            printf("%d", i);
            return 0;
        }

        int now = 0;
        for (auto e : jump)
            if (S >= e.first)
                now = max(now, e.second);

        S += now;
    }

    printf("-1");


    return 0;
}
