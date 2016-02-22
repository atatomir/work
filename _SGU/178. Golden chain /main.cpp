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

ll n, i;

bool check(ll x) {
    ll sum = x;

    for (ll how = 0; how <= x; how++)
        sum += min(sum + 1, n - sum);

    return sum >= n;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld", &n);

    for (i = 0; i <= n; i++) {
        if (check(i)) {
            printf("%lld", i);
            return 0;
        }
    }

    return 0;
}
