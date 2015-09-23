#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

long long n, i, v;

int main()
{
    freopen("maxunice.in","r",stdin);
    freopen("maxunice.out","w",stdout);

    scanf("%lld", &v);
    n = (long long)sqrt(2.00 * v);

    v -= (n * (n + 1)) / 2;

    if (v < 0) {
        v += (n * (n + 1)) / 2;
        n--;
        v -= (n * (n + 1)) / 2;
    }

    v = n + 1 - v;

    printf("%lld\n", n);
    for (i = 1; i < v; i++) printf("%d\n", i);
    for (i = v; i <= n; i++) printf("%d\n", i + 1);

    return 0;
}
