#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1011

long n,m,i,j,x,y,q;
long dp[maxN][maxN];

int main()
{
    freopen("acces.in","r",stdin);
    freopen("acces.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%ld",&dp[i][j]);
            if(dp[i][j]) dp[i][j] = -1;
        }
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(dp[i][j] == -1) continue;

            if(dp[i-1][j] == -1){
                dp[i][j] = dp[i][j-1] +1;
            } else
            if(dp[i][j-1] == -1){
                dp[i][j] = dp[i-1][j] +1;
            } else {
                x = i-1; y = j-1;
                if(dp[x][y] == -1){
                    while(dp[x-1][y] == -1) x--;
                    while(dp[x][y-1] == -1) y--;
                    x--; y--;
                }
                dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[x][y] + 1;
            }
        }
    }

    scanf("%ld",&q);
    for(i=1;i<=q;i++){
        scanf("%ld %ld",&x,&y);
        printf("%ld\n",dp[x][y]);
    }

    return 0;
}
