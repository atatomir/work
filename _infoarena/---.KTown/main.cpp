#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN (1024*4)

long n,i,s,d,j;
long long k,a[maxN],srt[maxN];
long long dp[2][maxN];

inline long long abss(long long x){
    if(x<0) return -x;
    return x;
}

int main()
{
    freopen("ktown.in","r",stdin);
    freopen("ktown.out","w",stdout);

    scanf("%ld %lld",&n,&k);
    for(i=1;i<=n;i++) {scanf("%lld",&a[i]);a[i]-=(1LL*i-1LL)*k;srt[i]=a[i];}
    sort(srt+1,srt+n+1);

    s=0; d=1; dp[s][0] = 1LL<<60;
    for(i=1;i<=n;i++) dp[s][i] = min(dp[s][i-1],abss(a[1]-srt[i]));
    for(i=2;i<=n;i++){
        dp[d][0] = 1LL<<60;
        for(j=1;j<=n;j++) dp[d][j] = min(dp[d][j-1],dp[s][j]+abss(a[i]-srt[j]));

        s^=1; d^=1;
    }

    printf("%lld",dp[s][n]);

    return 0;
}
