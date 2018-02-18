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
pair<ll, int> dp[maxN];
int best = -inf;


void upd(pair<ll, int>& a, pair<ll, int> b) {
    a = max(a, b);
}

pair<ll, int> solve(ll bonus) {
    int i, j, p;
    pair<ll, int> ans = mp(-inf, -1);

    for (i = 0; i <= n + 1; i++)
        dp[i] = mp(-inf, -1);

    dp[0] = mp(0, 0);
    for (i = 0; i <= n; i++) {
        ans = max(ans, mp(dp[i].first + bonus * (n - i), dp[i].second + (n - i)));
        for (j = i + 1; j <= n && j - i <= k + 1; j++) {
            upd(dp[j], mp(dp[i].first + bonus * (j - i - 1) + a[j].second - max(a[j].first, a[i].second), dp[i].second + j - i - 1));
        }
    }

    return ans;
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

    ll ans = 0;
    for (ll step = 1LL << 30; step > 0; step >>= 1)
        if (solve(ans + step).second <= k)
            ans += step;

    if (solve(ans).second < k) ans++;

    printf("%lld", solve(ans).first - ans * k);



    return 0;
}
