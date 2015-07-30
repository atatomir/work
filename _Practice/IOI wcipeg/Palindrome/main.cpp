#include <iostream>
#include <cstring>

using namespace std;

#define maxN 5012

char a[maxN],b[maxN];
long dp[2][maxN];
long n,i,j,s,d;
long ans;


int main()
{
    cin >> n ;
    cin >> a+1;
    for(i=n;i;i--) b[n-i+1] = a[i];

    s=0; d=1; ans = n-1;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(a[i]==b[j]){
                dp[d][j] = dp[s][j-1]+1;
            } else {
                dp[d][j] = max(dp[s][j],dp[d][j-1]);
            }
        }

        ans = min(ans, n-dp[d][n-i]*2 );
        ans = min(ans, n-1-dp[d][n-i-1]*2);

        s^=1; d^=1;
    }

    printf("%ld",ans);

    return 0;
}
