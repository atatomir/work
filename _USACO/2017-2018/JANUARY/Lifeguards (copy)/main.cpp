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
#define maxK 103
#define inf 2000000000

int n, k, i, j, p, maxi, cnt;
pair<int, int> a[maxN];
int dp[maxN][maxK];
int best = -inf;

void upd(int& a, int b) {
    a = max(a, b);
}

void solve() {
    int i, j, p;

    for (i = 0; i <= n + 1; i++)
        for (j = 0; j <= k + 1; j++)
            dp[i][j] = -inf;

    dp[0][0] = 0;
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= k; j++) {
            if (dp[i][j] <= -inf) continue;

            if (j + n - i == k) best = max(best, dp[i][j]);

            for (p = i + 1; p <= n; p++) {
                if (j + p - i - 1 > k) break;
                upd(dp[p][j + p - i - 1], dp[i][j] + a[p].second - max(a[p].first, a[i].second));
            }
        }
    }

}

int main()
{
    freopen("lifeguards.in","r",stdin);
    freopen("lifeguards.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)
        scanf("%d%d", &a[i].first, &a[i].second);

    sort(a + 1, a + n + 1, [](const pair<int, int>& a, const pair<int, int>& b)->bool const {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    maxi = 0;
    for (i = 1; i <= n; i++) {
        if (a[i].second > maxi) {
            maxi = a[i].second;
            a[++cnt] = a[i];
        } else {
            k--;
        }
    }

    n = cnt;
    k = max(k, 0);

    solve();
    printf("%d", best);



    return 0;
}
