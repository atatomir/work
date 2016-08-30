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

int n, i, A, B, lim;
int l, r, last;

int ans;

int main()
{
    freopen("nrdivunique.in","r",stdin);
    freopen("nrdivunique.out","w",stdout);

    scanf("%d", &n);
    for (int tt = 1; tt <= n; tt++) {
        scanf("%d%d", &A, &B);

        if (B >= 2 * A) {
            printf("%d\n", B);
            continue;
        }

        lim = sqrt(B);
        last = B + 1;
        ans = 0;

        for (i = 1; i <= lim; i++) {
            l = i * (A / i);
            if (l < A) l += i;

            r = i * (B / i);

            if (l > r) continue;

            //! case one : divisor <= lim
            ans++;

            //! case two : divisor > lim
            l = max(l, (lim + 1) * i);
            if (l > r) continue;

            l /= i;
            r /= i;

            ans += min(last - 1, r) - l + 1;
            last = l;
        }

        printf("%d\n", ans);
    }


    return 0;
}
