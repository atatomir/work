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

#define maxN 10000011

int n, k, i;
ll pos[maxN];

ll l;
ll dp_l[maxN];
ll dp_r[maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%lld", &n, &k, &l);
    for (i = 1; i <= n; i++) scanf("%lld", &pos[i]);

    int last_zero = upper_bound(pos + 1, pos + n + 1, 0) - pos - 1;

    if (last_zero == n) {
        printf("0");
        return 0;
    }

    for (i = last_zero + 1; i <= n; i++)
        pos[i - last_zero] = pos[i];
    n -= last_zero;

    for (i = 1; i <= n; i++) {
        int from = max(0, i - k);
        dp_l[i] = dp_l[from] + 2 * pos[i];
    }

    for (i = n; i > 0; i--) {
        int from = min(n + 1, i + k);
        dp_r[i] = dp_r[from] + 2 * (l - pos[i]);
    }

    ans = min(dp_l[n], dp_r[1]);
    for (i = 1; i < n; i++) ans = min(ans, dp_l[i] + dp_r[i + 1]);

    for (i = 0; i <= n; i++) {
        int to = min(n, i + k);
        ans = min(ans, dp_l[i] + l + dp_r[to + 1]);
    }

    printf("%lld", ans);

    return 0;
}
