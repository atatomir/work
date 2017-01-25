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

ll a[11];
ll ans, aux;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld%lld%lld%lld%lld%lld", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]);

    aux = min(a[0], min(a[3], a[4]));
    ans = a[1] + 3 * aux + 2 * ((a[0] - aux) / 2) + 2 * ((a[3] - aux) / 2) + 2 * ((a[4] - aux) / 2);

    aux = max(0LL, aux - 1);
    ans = max(ans, a[1] + 3 * aux + 2 * ((a[0] - aux) / 2) + 2 * ((a[3] - aux) / 2) + 2 * ((a[4] - aux) / 2));

    printf("%lld", ans);


    return 0;
}
