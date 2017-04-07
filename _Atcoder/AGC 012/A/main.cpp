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

#define maxN 500011

int n, i;
ll a[maxN], ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= 3 * n; i++) scanf("%lld", &a[i]);
    sort(a + 1, a + 3 * n + 1);
    for (i = 1; i <= n; i++) ans += a[3 * n - (2 * i - 1)];

    printf("%lld", ans);


    return 0;
}
