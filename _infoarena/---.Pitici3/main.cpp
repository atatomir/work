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

#define maxN 2016
#define inf (1LL << 50)

int n, m, i, j;
pair<ll, ll> P[maxN];
ll D, sum[maxN];

int ss, dd;
ll dp[2][maxN];


bool cmp(const pair<ll, ll>& a, const pair<ll, ll>& b) {
    return a.first + a.second < b.first + b.second;
}

int clean(ll *bg) {
    for (int i = 0; i <= n; i++)
        bg[i] = -inf;
}

int main()
{
    freopen("pitici3.in","r",stdin);
    freopen("pitici3.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld%lld", &P[i].first, &P[i].second);
    scanf("%lld", &D);

    sort (P + 1, P + n + 1, cmp);

    sum[n] = P[n].first;
    for (i = n - 1; i > 0; i--) sum[i] = sum[i + 1] + P[i].first;

    ss = 0; dd = 1;
    clean(dp[ss]); clean(dp[dd]);
    dp[ss][0] = 0;

    for (i = 0; i < n; i++) {
        clean(dp[dd]);

        for (j = 0; j <= i; j++) {
            if (dp[ss][j] < 0) break;

            dp[dd][j] = max(dp[dd][j], dp[ss][j] + P[i + 1].first);
            if (dp[ss][j] + P[i + 1].first + P[i + 1].second + sum[i + 2] >= D )
                dp[dd][j + 1] = max(dp[dd][j + 1], dp[ss][j]);
        }

        swap(ss, dd);
    }

    for (i = n; i >= 0; i--) {
        if (dp[ss][i] >= 0) {
            printf("%d", i);
            break;
        }
    }



    return 0;
}
