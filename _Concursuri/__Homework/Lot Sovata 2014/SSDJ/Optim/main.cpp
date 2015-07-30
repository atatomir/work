#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define maxN 1011
#define INF 5000
#define mmp make_pair

struct Line{
    long pos,h;
};
Line mp(long ppos,long hh){
    Line tmp;
    tmp.pos = ppos; tmp.h = hh;
    return tmp;
}

long n,i,j,k,ans;
char a[maxN][maxN];
long dp[maxN][maxN];
char ch;

Line S[maxN];
long cnt,cntAct;

void make_dp(){
    long i,j;
    for(i=1;i<=n;i++) dp[0][i] = INF;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(a[i][j]>ch)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i-1][j]+1;
        }
    }
}

int main()
{
    freopen("ssdj.in","r",stdin);
    freopen("ssdj.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%s\n",a[i]+1);

    for(ch='a';ch<'z';ch++){
        memset(dp,0,sizeof(dp));
        make_dp();

        for(i=1;i<=n;i++){
            cnt = 0; cntAct = 0;
            for(j=1;j<=n;j++){
                if(a[i][j]<=ch){ //!! 0
                    if(cnt)
                    while(S[cnt].h>=dp[i][j]){
                        cntAct -= S[cnt].pos; cnt--;
                        if(cnt==0) break;
                    }
                    S[++cnt] = mp(0,dp[i][j]);
                    if(S[cnt].h>=INF) cnt--;
                    if(dp[i][j]<INF)
                        if(a[i-dp[i][j]+1][j]==ch+1) cntAct++,S[cnt].pos=1;
                } else { //!! 1
                    long hT = dp[i-1][j]+1;
                    if(cnt)
                    while(S[cnt].h>=hT){
                        cntAct -= S[cnt].pos; cnt--;
                        if(cnt==0) break;
                    }

                    if(a[i][j]==ch+1) ans += cnt;
                    else              ans += cntAct;

                    cnt=0; cntAct=0;
                }
            }
        }
    }

    printf("%ld",ans);

    return 0;
}
