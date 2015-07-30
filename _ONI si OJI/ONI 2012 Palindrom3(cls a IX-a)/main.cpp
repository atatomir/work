#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 1000500
#define myDef 99999999
#define pow poww

long t[10],i,n,def,ant,k,val,pos,j,v1,v2,rest;
long corr[10][10],ans[maxN];
char s[maxN];
long dp[maxN/2][25][2],pow[maxN];

int main()
{
    freopen("palindrom3.in","r",stdin);
    freopen("palindrom3.out","w",stdout);

    for(i=0;i<10;i++) scanf("%ld",&t[i]);
    scanf("\n%s\n%ld",s+1,&k);
    n = strlen(s+1);

    for(i=0;i<10;i++){
        corr[i][i] = 1; ant = i; val = 1;
        while(1){
            ant = t[ant];
            if(corr[i][ant]) break;
            corr[i][ant] = ++val;
        }
    }

    def = n/2;

    for(i=1;i<=def;i++){
        pos = n-i+1;
        for(j=9;j>=0;j--){
            if(corr[s[i]-'0'][j] && corr[s[pos]-'0'][j]){
                ans[i] = j;
                printf("%ld",ans[i]);
                break;
            }
        }
    }
    for(i=def;i;i--) printf("%ld",ans[i]);
    printf("\n");

    pow[1] = 1;
    for(i=2;i<=n;i++) pow[i] = (pow[i-1]*10)%k;

    for(j=1;j<=def+1;j++)
    for(i=0;i<k;i++) dp[j][i][0] = myDef;
    dp[def+1][0][0] = 0;

    for(i=def;i;i--){
        pos = n-i+1; v1 = s[i] - '0'; v2 = s[pos] - '0';

        for(rest = 0;rest < k;rest++) {
            for(j=9;j>=0;j--){
                if(i == 1 && j == 0) continue;

                if(corr[v1][j] && corr[v2][j]){
                    long add = corr[v1][j] + corr[v2][j];
                    long lastR = rest - j*(pow[i] + pow[pos]);
                    while(lastR < 0) lastR += k;

                    if(dp[i][rest][0] > dp[i+1][lastR][0]+add){
                        dp[i][rest][0] = dp[i+1][lastR][0]+add;
                        dp[i][rest][1] = j;
                    }
                }
            }
        }
    }

    rest = 0;
    for(i=1;i<=def;i++){
        ans[i] = dp[i][rest][1];
        rest -= ans[i] * (pow[i] + pow[n-i+1]);
        while(rest < 0) rest += k;
    }

    for(i=1;i<=def;i++) printf("%ld",ans[i]);
    for(i=def;i;i--)    printf("%ld",ans[i]);

    return 0;
}
