#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 50011

long n,m,i,x,y,j;
long a[maxN],dp[maxN];

int main()
{
    freopen("saracsaurege.in","r",stdin);
    freopen("saracsaurege.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);

    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        if(!dp[x] || dp[x] > y){
            dp[x] = x;
            for(j=x+1;j<=y;j++){
                if(dp[j]){
                   if(a[dp[j]] < a[dp[x]]) break;
                   if(dp[j] <= y) {
                        dp[x] = dp[j];
                        break;
                   }
                }
                if(a[j] > a[dp[x]]){
                    dp[x] = j;
                }
            }
        }
        printf("%ld\n",a[dp[x]]);
    }
    return 0;
}
