#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 300011
#define sum (v[1]+v[2]+v[3])
#define mod 666013

long n,i;
long a[maxN],ans;
long dp[maxN][2][2][2],v[4];

int main()
{
    freopen("minesweeper2.in","r",stdin);
    freopen("minesweeper2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);

    if(n == 1){
        if(a[1] == 0 || a[1] == 1) printf("1"); else printf("0");
    } else
    if(n == 2){
        for(v[1]=0;v[1]<=1;v[1]++)
            for(v[2]=0;v[2]<=1;v[2]++){
                if((a[1] == -1 || a[1] == v[1]+v[2])&&(a[2]==-1 || a[2] == v[1]+v[2])) ans++;
            }
        printf("%ld",ans);
    } else {
        for(v[1]=0;v[1]<=1;v[1]++)
            for(v[2]=0;v[2]<=1;v[2]++)
                for(v[3]=0;v[3]<=1;v[3]++){
                    if((sum == a[2] || a[2] == -1)&&(a[1] == -1 || v[1]+v[2] == a[1])) dp[2][v[1]][v[2]][v[3]] = 1;
                }

        for(i=3;i<n;i++){
            for(v[1]=0;v[1]<=1;v[1]++)
                for(v[2]=0;v[2]<=1;v[2]++)
                    for(v[3]=0;v[3]<=1;v[3]++)
                        if(sum == a[i] || a[i] == -1){
                            for(v[0]=0;v[0]<=1;v[0]++){
                                dp[i][v[1]][v[2]][v[3]] += dp[i-1][v[0]][v[1]][v[2]];
                                dp[i][v[1]][v[2]][v[3]] %= mod;
                            }
                        }
        }


        for(v[1]=0;v[1]<=1;v[1]++)
            for(v[2]=0;v[2]<=1;v[2]++)
                for(v[3]=0;v[3]<=1;v[3]++){
                    if(v[2]+v[3] == a[n] || a[n] == -1) ans += dp[n-1][v[1]][v[2]][v[3]],ans%=mod;
                }

        printf("%ld",ans);
    }

    return 0;
}
