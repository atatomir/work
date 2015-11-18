#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define eps 1e18

int n, i, p, xx, yy, x, y;
double alfa[maxN];

double PI = acos(-1.00);
long long ans;

int main()
{
    freopen("hawaii.in","r",stdin);
    freopen("hawaii.out","w",stdout);

    scanf("%d%d%d", &n, &xx, &yy);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        alfa[i] = atan2(y - yy, x - xx);
    }
    sort(alfa + 1, alfa + n + 1);
    for (i = 1; i <= n; i++) alfa[i + n] = alfa[i] + 2 * PI;

    p = 1;

    ans = 1LL * n * (n - 1) * (n - 2);
    ans /= 6LL;

    for (i = 1; i <= n; i++) {
        while (p + 1 < i + n && alfa[p + 1] - alfa[i] <= PI) p++;

        //! C[p - i][2]
        long long aux = 1LL * (p - i) * (p - i - 1);
        aux /= 2LL;

        ans -= aux;
    }

    printf("%lld", ans);

    return 0;
}
