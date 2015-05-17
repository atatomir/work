#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 85
#define maxDim 23

long n,i,j,s,d,c,p,h2,h5,u;
long long dp[2][maxN<<1][maxN<<1][maxDim];
long long cnt,p2[maxDim],p5[maxDim];

void preProc(){
    long def2,def5;
    for(long pp5=1,def5=0;pp5<=200;pp5*=5,def5++){
        for(long pp2=1,def2=0;pp2*pp5<=200;pp2<<=1,def2++){
            p2[++cnt] = def2;
            p5[  cnt] = def5;
        }
    }
}

int main()
{
    freopen("procente.in","r",stdin);
    freopen("procente.out","w",stdout);

    preProc();
    scanf("%ld\n%c%ld",&n,&c,&p);
    if(c=='-') p = 100-p; else p+=100;

    h2 = 0;
    while((p&1)==0) {h2++; p>>=1;}
    while(p%5==0)   {h5++; p /=5;}
    if(p!=1){
        printf("0");
        return 0;
    }

    s=0; d= 1;
    for(i=1;i<=cnt;i++) dp[s][h2][h5][i] = 1;

    for(long tmp=n-1;tmp--;){
        memset(dp[d],0,sizeof(dp[d]));
        for(h2=0;h2<=160;h2++){
            for(h5=0;h5<=160;h5++){
                for(u=1;u<=cnt;u++){
                    long ph2 = h2-p2[u];
                    long ph5 = h5-p5[u];

                    dp[d][h2][h5][u] = dp[d][h2][h5][u-1];
                    if(ph2<0 || ph5<0)continue;
                    dp[d][h2][h5][u] += dp[s][ph2][ph5][u];
                }
            }
        }

        s^=1; d^=1;
    }

    printf("%lld",dp[s][2*n][2*n][cnt]);

    return 0;
}
