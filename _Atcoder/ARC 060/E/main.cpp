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
#define maxLog 19

int n, i, q, a, b, p;
ll x[maxN], L;
ll dad[maxLog][maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &x[i]);
    scanf("%lld", &L);

    for (i = n; i > 0; i--) {
        int pos = upper_bound(x + 1, x + n + 1, x[i] + L) - x - 1;
        dad[0][i] = pos;

        for (int act = 1; act < maxLog; act++)
            dad[act][i] = dad[act - 1][ dad[act - 1][i] ];
    }

    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        scanf("%d%d", &a, &b);
        if (a > b) swap(a, b);

        int ans = 0;
        p = a;

        for (int step = maxLog - 1; step >= 0; step--)
            if (dad[step][p] != 0)
                if (dad[step][p] < b)
                    p = dad[step][p], ans += 1 << step;

        printf("%d\n", ans + 1);
    }


    return 0;
}
