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

#define mod 1000000007

int n, m, i;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);

    if (m - n > 1) {
        printf("0");
        return 0;
    }

    ans = 1;
    for (i = 1; i <= n; i++) ans = (ans * i) % mod;
    for (i = 1; i <= m; i++) ans = (ans * i) % mod;

    if (m == n)
        printf("%lld", (ans * 2) % mod);
    else
        printf("%lld", ans);


    return 0;
}
