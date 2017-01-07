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

#define maxN 22
#define inf 1000000000

int n, k, i, j, mask, conf;
int cost[maxN][maxN];
int dp[1 << 21];

vector<int> bits;
int ans = inf;

int main()
{
    //freopen("test.in","r",stdin);

    /*freopen("test.out", "w", stdout);
    printf("20 1\n");
    for (i = 1; i <= 20; i++) {
        for (j = 1; j <= 20; j++)
            printf("%d ", i + j);
        printf("\n");
    }

    return 0;*/


    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    mask = (1 << n) - 1;
    for (i = 0; i <= mask; i++) dp[i] = inf;
    dp[mask] = 0;

    for (conf = mask; conf > 0; conf--) {
        bits.clear();
        for (i = 0; i < n; i++)
            if (conf & (1 << i))
                bits.pb(i);

        if (bits.size() <= k) {
            if (bits.size() == k) ans = min(ans, dp[conf]);
            continue;
        }

        for (auto b1 : bits) {
            for (auto b2 : bits) {
                if (b1 != b2)
                    dp[conf ^ (1 << b1)] = min(dp[conf ^ (1 << b1)], dp[conf] + cost[b1][b2]);
            }
        }
    }

    printf("%d", ans);


    return 0;
}
