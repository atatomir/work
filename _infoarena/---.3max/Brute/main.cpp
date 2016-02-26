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

#define maxN 55111

int n, m, i, j, l, r;
ll v[maxN], sum[maxN];

ll best;
ll dp_l[maxN], dp_r[maxN];

bool is_good(int l, int r) {
    if (n < 3) return false;

    if (r == 1 || l == n) return false;
    return true;
}

int main()
{
    freopen("3max.in","r",stdin);
    freopen("3max.ok","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
        sum[i] = sum[i - 1] + v[i];
    }

    for (i = 1; i <= n; i++)
        dp_l[i] = max(0LL, dp_l[i - 1]) + v[i];
    for (i = 1; i <= n; i++)
        dp_l[i] = max(dp_l[i], dp_l[i - 1]);

    for (i = n; i >= 1; i--)
        dp_r[i] = max(0LL, dp_r[i + 1]) + v[i];
    for (i = n; i >= 1; i--)
        dp_r[i] = max(dp_r[i], dp_r[i + 1]);


    for (int qq = 1; qq <= m; qq++) {
        scanf("%d %d", &l, &r);

        if (!is_good(l, r)) {
            printf("0\n");
            continue;
        }

        best = 0;

        for (i = l; i <= r; i++)
            for (j = i; j <= r; j++)
                best = max(best, max(sum[j] - sum[i - 1], 0LL) + dp_l[i - 1] + dp_r[j + 1]);

        printf("%lld\n", max(best, 0LL));
    }


    return 0;
}
