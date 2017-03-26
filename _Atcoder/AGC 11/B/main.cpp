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

#define maxN 100011

int n, i;
ll a[maxN], sum, last;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);

    last = sum = 0;
    for (i = 1; i < n; i++) {
        sum += a[i];
        if (2 * sum < a[i + 1])
            last = a[i + 1];
    }

    ll ans = 0;
    for (i = 1; i <= n; i++)
        if (a[i] >= last)
            ans++;

    printf("%lld", ans);


    return 0;
}
