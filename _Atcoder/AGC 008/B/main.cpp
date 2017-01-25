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

int n, k, i;
ll a[maxN], l[maxN], r[maxN], sum[maxN];
ll ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        l[i] = l[i - 1] + max(0LL, a[i]);
        sum[i] = sum[i - 1] + a[i];
    }

    for (i = n; i > 0; i--)
        r[i] = r[i + 1] + max(0LL, a[i]);

    for (i = 1; i + k - 1 <= n; i++) {
        ans = max(ans, l[i - 1] + r[i + k] + max(0LL, sum[i + k - 1] - sum[i - 1]));
    }

    printf("%lld", ans);


    return 0;
}
