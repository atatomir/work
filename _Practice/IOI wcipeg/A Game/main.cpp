#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG
#define maxN 111

long n,i,x,d;
long dp[maxN][maxN],sum[maxN],a[maxN];

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&x); a[i]=x;
        sum[i] = x+sum[i-1];
    }

    for(i=1;i<=n;i++) dp[i][i]=a[i];

    for(d=2;d<=n;d++){
        for(i=1;i<=n-d+1;i++){
            long how = sum[i+d-2]-sum[i-1];
            dp[i][i+d-1] = (how-dp[i][i+d-2])+a[i+d-1];

            /**/ how = sum[i+d-1]-sum[i];
            dp[i][i+d-1] = max(dp[i][i+d-1],(how-dp[i+1][i+d-1])+a[i]);
        }
    }

    printf("%ld %ld",dp[1][n] , sum[n]-dp[1][n] );

    return 0;
}
