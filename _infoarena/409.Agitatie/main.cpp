#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 3010
#define maxTime 3020

long n,i,j,op,s,d;
long dp[2][maxTime+20]; // elem,timp

int main()
{
    freopen("agitatie.in","r",stdin);
    freopen("agitatie.out","w",stdout);

    scanf("%ld",&n);

    d = 0; s = 1;
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&dp[d][1],&op);
        for(j=2;j<=maxTime;j++){
            dp[d][j] = dp[d][j-1] + op;
            if(dp[d][j] < 0){
                dp[d][j] *= -1;
                op = 1;
            }
        }

        dp[d][1] += dp[s][1];
        for(j=2;j<=maxTime;j++)
            dp[d][j] = min(dp[d][j-1],dp[s][j]+dp[d][j]);

        s ^= 1; d ^= 1;
    }


    printf("%ld",dp[s][maxTime]);
    return 0;
}
