#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 128

long n,m,i,j;
char a[maxN][maxN];
long dp[maxN][maxN],dpp[maxN][maxN];

void make_line(long id){
    long C=0,Cf=0;
    for(long i=1;i<=m;i++){
        if(C+Cf>=i) dp[id][i] = min(dp[id][2*C-i],C+Cf-i);
        while(a[id][i+dp[id][i]+1]==a[id][i-dp[id][i]-1]) dp[id][i]++;
        if(i+dp[id][i]>Cf){
            C = i;
            Cf = dp[id][i];
        }
    }
}

void make_column(long id){
    long C=0,Cf=0;
    for(long i=1;i<=n;i++){
        if(C+Cf>=i) dpp[i][id] = min(dpp[2*C-i][id],C+Cf-i);
        while(a[i+dpp[i][id]+1][id]==a[i-dpp[i][id]-1][id]) dpp[i][id]++;
        if(i+dpp[i][id]>Cf){
            C = i;
            Cf = dpp[i][id];
        }
    }
}

int main()
{
    freopen("cruce.in","r",stdin);
    freopen("cruce.out","w",stdout);

    scanf("%ld%ld\n",&n,&m);
    for(i=1;i<=n;i++) scanf("%s\n",a[i]+1);

    for(i=0;i<=n+1;i++) {a[i][0]='#';a[i][m+1]='@';}
    for(i=0;i<=m+1;i++) {a[0][i]='@';a[n+1][i]='#';}

    for(i=1;i<=n;i++) make_line(i);
    for(i=1;i<=m;i++) make_column(i);

    long long ans=0;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            ans = ans + dp[i][j]*dpp[i][j];
        }
    }
    printf("%lld",ans);

    return 0;
}
