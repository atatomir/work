#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define mod 10007
#define maxN 10111

long long n,k,x,i,j;
long long dp[maxN];

int main()
{
    freopen("desc2.in","r",stdin);
    freopen("desc2.out","w",stdout);

    scanf("%lld%lld%lld",&n,&k,&x);

    n -= k;
    for (i = 1; i < k; i++) n -= x * i;

    if (n < 0) {
        printf("0");
        return 0;
    }

    for (i = 0; i <= n; i++) dp[i] = 1;
    for (int pas = 2; pas <= k; pas++) {
        for (i = pas; i <= n; i++) {
            dp[i] += dp[i-pas];
            if (dp[i] >= mod) dp[i] -= mod;
        }
    }

    printf("%lld",dp[n]);


    return 0;
}
