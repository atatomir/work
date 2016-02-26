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

#define maxN 100011
#define maxK 1024

int n, k, s, i, j;
int H[maxN];
int higher[maxN];
vector<int> way;
ll dist_way;

ll dp[maxK];

ll dist(int id1, int id2) {
    ll dif1 = (id2 - id1);
    ll dif2 = (H[id1] - H[id2]);

    return (ll)( sqrt( dif1 * dif1 + dif2 * dif2 ) );
}

int main()
{
    freopen("telecab.in","r",stdin);
    freopen("telecab.out","w",stdout);

    scanf("%d%d%d", &n, &k, &s);
    for (i = 1; i <= n; i++) scanf("%d", &H[i]);

    higher[n] = n + 1;
    for (i = n - 1; i > 0; i--) {
        higher[i] = i + 1;
        while (higher[i] != n + 1 && H[ higher[i] ] <= H[i])
            higher[i] = higher[ higher[i] ];
    }

    way.pb(1);
    for (i = 1; i <= n;) {
        if (higher[i] == n + 1) higher[i] = i + 1;
        i = higher[i];

        if (i <= n) way.pb(i);
    }

    for (i = 1; i < way.size(); i++) {
        dist_way += dist(way[i - 1], way[i]);
        if (H[way[i - 1]] < H[way[i]] && way[i - 1] < k) s -= H[way[i]] - H[way[i - 1]];
    }
    printf("%lld\n", dist_way);

    dist_way = 0;

    //! all dp is clear
    for (i = 1; i < way.size(); i++) {
        ll now_dist = dist(way[i - 1], way[i]);
        dist_way += now_dist;

        if (H[ way[i - 1] ] > H[ way[i] ]) {
            int dif = H[way[i - 1]] - H[way[i]];
            for (j = 0; j + dif <= s; j++)
                dp[j] = max(dp[j], dp[j + dif] + now_dist - 1);
        }

        if (way[i] >= k) {
            ll ans = 0;
            for (j = 0; j <= s; j++) ans = max(ans, dp[j]);
            printf("%lld\n", dist_way - ans);

            break;
        }
    }

    return 0;
}
