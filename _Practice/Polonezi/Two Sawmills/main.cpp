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

#define maxN 20011
#define inf (1LL << 60)

int n, i;
ll d[maxN], w[maxN];
ll to_end[maxN], sums[maxN];
ll sum_add[maxN];

ll dp[maxN];

ll compute(int p1, int p2) {
    ll ans = sums[p2 + 1];
    ans += sums[p1 + 1] - sums[p2 + 1] - (sum_add[p1 + 1] - sum_add[p2 + 1]) * to_end[p2];
    ans += sums[1] - sums[p1 + 1] - (sum_add[1] - sum_add[p1 + 1]) * to_end[p1];
    return ans;
}

void solve(int l, int r, int ql, int qr) {
    int i;
    int mid = (l + r) >> 1;
    pair<ll, int> best;

    if (l > r) return;

    best = mp(compute(mid, mid), mid);
    for (i = max(mid + 1, ql); i <= qr; i++)
        best = min(best, mp(compute(mid, i), i));

    dp[mid] = best.first;
    solve(l, mid - 1, ql, best.second);
    solve(mid + 1, r, best.second, qr);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld%lld", &w[i], &d[i]);

    for (i = n; i > 0; i--) {
        to_end[i] = to_end[i + 1] + d[i];
        sums[i] = sums[i + 1] + w[i] * to_end[i];
        sum_add[i] = sum_add[i + 1] + w[i];
    }

    ll ans = inf;
    solve(1, n, 1, n);
    for (i = 1; i <= n; i++)
        ans = min(ans, dp[i]);

    printf("%lld", ans);

    return 0;
}
