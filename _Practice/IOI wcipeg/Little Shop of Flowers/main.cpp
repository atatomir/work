#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 105
#define INF 1000000000

long n,m,i,j,pos;
long a[maxN][maxN];
long dp[maxN][maxN],prov[maxN][maxN];

long ans[maxN];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%ld%ld",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%ld",&a[i][j]);

    for(i=1;i<=n;i++){
        dp[1][0] = -INF;
        for(j=1;j<=m;j++){
            dp[i][j] = dp[i][j-1];
            prov[i][j] = prov[i][j-1];

            if(j<i) {
                dp[i][j] = -INF;
                continue;
            }
            long newV = dp[i-1][j-1]+a[i][j];
            if(newV > dp[i][j]){
                dp[i][j] = newV;
                prov[i][j] = j;
            }
        }
    }

    pos = m;
    for(i=n;i;i--) {
        ans[i] = pos = prov[i][pos];
        pos--;
    }

    printf("%ld\n",dp[n][m]);
    for(i=1;i<=n;i++) printf("%ld ",ans[i]);

    return 0;
}
