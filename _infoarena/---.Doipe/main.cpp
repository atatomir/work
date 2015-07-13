#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxS 2015
#define mod 29997
#define maxN maxS

int t,i,j,n,s,d;
char S[maxS];
int dp[2][maxN];

int main()
{
    freopen("doipe.in","r",stdin);
    freopen("doipe.out","w",stdout);

    for(scanf("%d",&t);t--;){
        scanf("%d\n%s\n",&n,S+1);
        dp[0][1] = 1; s = 0; d=1;

        for(i=2;i<=n;i++){
            for(j=1;j<=i;j++){
                if(S[i-1]=='>')
                    dp[d][j] = dp[s][i-1]-dp[s][j-1];
                else
                    dp[d][j] = dp[s][j-1];

                while(dp[d][j] < 0) dp[d][j] += mod;
                while(dp[d][j] >=mod) dp[d][j] -= mod;
            }

            swap(s,d);
            for(j=2;j<=i;j++){
                dp[s][j] += dp[s][j-1];
                while(dp[s][j] < 0) dp[s][j] += mod;
                while(dp[s][j] >=mod) dp[s][j] -= mod;
            }
        }

        printf("%d\n",dp[s][n]);
    }



    return 0;
}
