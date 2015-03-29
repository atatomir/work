#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1011
#define maxLog 10

long n,i,j;
char s[2][maxN][maxN];
short dp[2][maxN][maxN];

short rmq[maxLog][maxN];
short ans[maxN][maxN];

long Answer;

void calcDP(long mat,long ln){
    #define act dp[mat][ln][i]

    s[mat][ln][0] = '@'; s[mat][ln][n+1] = '#';
    long C=0,fC=0,i;
    for(i=1;i<=n;i++){
        if(fC >= i) dp[mat][ln][i] = min((long)dp[mat][ln][2*C-i],fC-i);
        for(;s[mat][ln][i-act-1] == s[mat][ln][i+act+1];act++);

        if(fC < i+act){
            fC = i+act;
            C = i;
        }
    }
}

void calcRMQ(long mat,long co){
    long i,j,bits;
    for(i=1;i<=n;i++) rmq[0][i] = dp[mat][i][co];
    for(i=1,bits=2;bits<=n;i++,bits<<=1){
        for(j=1;j<=n-bits+1;j++) rmq[i][j] = min(rmq[i-1][j],rmq[i-1][j+(bits >> 1)]);
    }
}
long getMin(long bg,long en){
    long dim = en-bg+1,bits,p;
    bits = 1; p = 0;
    while((bits<<1)<= dim) { bits <<= 1; p++; }
    return min(rmq[p][bg],rmq[p][en-bits+1]);
}

short getDim(long mat,long co){
    long i=0,j=min(co-1,n-co),m;
    while(i<=j){
        m = (i+j)>>1;
        if(getMin(co-m,co+m) >= m)
            i = m+1;
        else
            j = m-1;
    }
    return j;
}

int main()
{
    freopen("pscpld2d.in","r",stdin);
    freopen("pscpld2d.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%s",s[0][i]+1);
        for(j=1;j<=n;j++) s[1][j][i] = s[0][i][j];
    }

    for(i=1;i<=n;i++){
        calcDP(0,i);
        calcDP(1,i);
    }

    for(i=1;i<=n;i++){
        calcRMQ(1,i);
        for(j=1;j<=n;j++){
            ans[i][j] = getDim(0,j);
        }
    }
     for(i=1;i<=n;i++){
        calcRMQ(0,i);
        for(j=1;j<=n;j++){
            ans[j][i] = min(ans[j][i],getDim(1,j));
            Answer += ans[j][i];
        }
    }

    printf("%ld",Answer+n*n);

    return 0;
}
