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

ll x, y;
ll ans;

ll go(ll x, ll y) {
    if (x > y)
        return 1LL << 60;
    return y - x;
}

int main()
{

    scanf("%lld%lld", &x, &y);

    ans = 1LL << 60;
    ans = min(ans, go(x, y));
    ans = min(ans, 1 + go(-x, y));
    ans = min(ans, 1 + go(x, -y));
    ans = min(ans, 2 + go(-x, -y));

    printf("%lld", ans);

    return 0;
}
