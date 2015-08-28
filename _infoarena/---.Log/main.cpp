#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10011
#define maxK 111
#define maxA 100
#define inf (1LL<<60)

long long n,t1,t2,t3,i;
long long aa[maxN],bb[maxN];
long long dp[maxN][maxK];
long long best[maxN];

long long op_calc(long long a,long long b) {
    return t3 * (a-b)*(a-b);
}

int main()
{
    freopen("log.in","r",stdin);
    freopen("log.out","w",stdout);

    scanf("%lld%lld%lld%lld",&n,&t1,&t2,&t3);
    scanf("%lld%lld",&aa[1],&bb[1]);

    for (i = 1; i <= maxA; i++) dp[1][i] = inf;
    dp[1][aa[1]] = 0;
    best[1] = op_calc(aa[1],bb[1]);

    for (int pas = 2; pas <= n; pas++) {
        scanf("%lld%lld",&aa[pas],&bb[pas]);

        for (i = 1; i <= maxA; i++) dp[pas][i] = inf;

        if (aa[pas] == bb[pas-1])
            for (i = 1; i <= maxA; i++) dp[pas][i] = t2 + dp[pas-1][i];

        dp[ pas ][ aa[pas] ] = min( best[pas-1] + t1, dp[ pas ][ aa[pas] ] );

        best[pas] = inf;
        for (i = 1; i <= maxA; i++){
            if (dp[pas][i] >= inf) continue;
            long long act = dp[pas][i] + op_calc(i,bb[pas]);

            best[pas] = min(best[pas], act);
        }
    }

    printf("%lld",best[n]);

    return 0;
}
