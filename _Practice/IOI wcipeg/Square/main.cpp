#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1024

long n,i,j;
long s[maxN][maxN];
long ans,cnt;
bool us[maxN][maxN];

long sum(long x,long y,long xx,long yy){
    return s[xx][yy]-s[x-1][yy]-s[xx][y-1]+s[x-1][y-1];
}

long getDim(long x,long y){
    long _x = x,_y=y;
    for(long pas = 1024;pas;pas>>=1)
        if( x+pas<=n && y+pas<=n )
            if( sum(_x,_y,x+pas,y+pas)==0 ) {x+=pas;y+=pas;}
    return x-_x+1;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%ld",&s[i][j]);

            if(s[i][j]) s[i][j] = 0; else s[i][j] = 1;

            if(s[i][j]) us[i][j]=true;
            s[i][j] += s[i-1][j]+s[i][j-1]- s[i-1][j-1];
        }
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(us[i][j]) continue;
            long dim = getDim(i,j);

            if(dim == ans) cnt++; else
            if(dim >  ans){
                ans = dim;
                cnt = 1;
            }
        }
    }

    printf("%lld",1LL*cnt*ans);


    return 0;
}
