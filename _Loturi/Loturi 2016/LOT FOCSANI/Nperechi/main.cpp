#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back
#define eps 0.0001

#define step 0.001

ll A, B, C, D;
double x, y, d;
ll ans;

int main()
{
    freopen("nperechi.in", "r", stdin);
    freopen("nperechi.out", "w", stdout);

    scanf("%lld%lld%lld%lld", &A, &B, &C, &D);

    for (x = step; x < 1.000; x += step) {
        for (y = step; y < 1.000; y += step) {
            d = x * A + y * B;
            d -= floor(d);
            if (d > eps) continue;

            d = x * C + y * D;
            d -= floor(d);
            if (d > eps) continue;

            ans++;
        }
    }

    printf("%lld", ans);



    return 0;
}
