#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define limit 1000000000LL

int n, i, t;
long long l1, l2, c1, c2;

long long hl, hc, hhl, hhc;
long long ans, p;

long long how_many(long long lim, long long bit) {
    long long gr = lim / bit;
    long long ans = (gr / 2) * bit;

    if (gr % 2 == 1) gr--;

    lim -= gr * bit;
    if (lim <= bit)
        return ans;
    return ans + lim - bit;
}

int main()
{
    freopen("xor.in","r",stdin);
    freopen("xor.out","w",stdout);

    for (scanf("%d%lld", &t, &p); t > 0; t--) {
        scanf("%lld%lld%lld%lld", &l1, &c1, &l2, &c2);

        l1++; l2++;
        c1++; c2++;

        ans = 0;

        for (long long bit = 1; bit <= limit; bit <<= 1) {
            hl = how_many(l2, bit) - how_many(l1 - 1, bit);
            hc = how_many(c2, bit) - how_many(c1 - 1, bit);

            hhl = l2 - l1 + 1 - hl;
            hhc = c2 - c1 + 1 - hc;

            ans += (bit % p) * (((hl * hhc) + (hc * hhl)) % p);
            ans %= p;
        }

        printf("%lld\n", ans);
    }



    return 0;
}
