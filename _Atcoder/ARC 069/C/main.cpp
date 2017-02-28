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

ll n, m, k;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &m);
    k = max(0LL, (m - 2 * n) / 4);

    n += k;
    m -= 2 * k;

    printf("%lld", min(n, m / 2));





    return 0;
}
