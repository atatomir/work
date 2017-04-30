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
int a[maxN];
int dp_inc[maxN], dp_dec[maxN], dp[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);

        dp_inc[i] = dp_dec[i] = 1;
        if (a[i - 1] <= a[i] && i > 1) dp_inc[i] = 1 + dp_inc[i - 1];
        if (a[i - 1] >= a[i] && i > 1) dp_dec[i] = 1 + dp_dec[i - 1];

        dp[i] = 1 + min(dp[i - dp_inc[i]], dp[i - dp_dec[i]]);
    }

    printf("%d", dp[n]);




    return 0;
}
