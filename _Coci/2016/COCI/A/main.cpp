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

ll n, x, i, ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld", &x, &n);
    ans = x * (n + 1);

    for (i = 1; i <= n; i++) {
        scanf("%lld", &x);
        ans -= x;
    }

    printf("%lld", ans);


    return 0;
}
