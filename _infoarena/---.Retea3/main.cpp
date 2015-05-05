#include <iostream>
#include <cstdio>

using namespace std;

#define mod 666013
#define maxM 1024

long long n,m,ans;
long  long dp[maxM][maxM];

long long myPow(long long a,long long b){
    long long ans = 1;

    while(b){
        if(b&1) ans = (ans*a)%mod;
        b >>= 1;
        a = (a*a)%mod;
    }

    return ans;
}

void make_dp(){
    long i,j;
    for(i=1;i<=m;i++){
        for(j=1;j<=m;j++){
            if(i==j && i==1){
                dp[i][j] = 2;
                continue;
            }

            dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
            dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];

            while(dp[i][j]<0) dp[i][j] += mod;
            while(dp[i][j]>=mod) dp[i][j]-=mod;
        }
    }
}

int main()
{
    freopen("retea3.in","r",stdin);
    freopen("retea3.out","w",stdout);

    scanf("%lld %lld",&n,&m);
    make_dp();

    ans = dp[m][m];
    ans = myPow(ans,n-1);

    printf("%lld",ans);

    return 0;
}
