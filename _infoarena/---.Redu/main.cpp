#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 511
#define INF 2000000000

long n,i,j;
char s[maxN],c1,c2;
long c['z'+10]['z'+10];
long dp[maxN][maxN];

long calcDP(long l,long r){
    if(dp[l][r]!=INF) return dp[l][r];
    if(l+1==r){
        dp[l][r] = c[s[l]][s[r]];
        return dp[l][r];
    }

    long i;
    for(i=l+1;i<=r;i+=2) dp[l][r]=min(dp[l][r],calcDP(l+1,i-1)+calcDP(i+1,r)+c[s[l]][s[i]]);

    return dp[l][r];
}

int main()
{
    freopen("redu.in","r",stdin);
    freopen("redu.out","w",stdout);

    scanf("%ld\n%s\n",&n,s+1);
    for(c1='a';c1<='z';c1++)
        for(c2='a';c2<='z';c2++)
            scanf("%ld",&c[c1][c2]);

    for(i=1;i<=n;i++)
        for(j=i;j<=n;j++) dp[i][j]=INF;

    printf("%ld",calcDP(1,n));

    return 0;
}
