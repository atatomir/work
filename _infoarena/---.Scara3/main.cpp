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

#define maxN 1217

int n, i, j, k, l, x, y;
int water[maxN], energy[maxN];

pair<int, int> dp[maxN];

int main()
{
    freopen("scara3.in","r",stdin);
    freopen("scara3.out","w",stdout);

    scanf("%d", &n);

    scanf("%d", &k);
    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x, &y);
        water[x] = y;
    }

    scanf("%d", &l);
    for (i = 1; i <= l; i++) {
        scanf("%d%d", &x, &y);
        energy[x] = y;
    }

    dp[n] = {0, 0};
    for (i = n - 1; i > 0; i--) {
        dp[i] = {dp[i + 1].first + 1, dp[i + 1].second};

        for (j = 1; j <= water[i] && i + j <= n; j++)
            dp[i] = min(dp[i], {dp[i + j].first + 1, dp[i + j].second});

        for (j = 1; j <= energy[i] && i + 2 * j <= n; j++)
            dp[i] = min(dp[i], {dp[i + 2 * j].first + 1, dp[i + 2 * j].second + j});

        for (j = 1; j <= energy[i] && i + 2 * j - 1 <= n; j++)
            dp[i] = min(dp[i], {dp[i + 2 * j - 1].first + 1, dp[i + 2 * j - 1].second + j});
    }

    printf("%d %d", dp[1].first + 1, dp[1].second);



    return 0;
}
