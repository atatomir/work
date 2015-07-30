#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG
#define maxN 55
#define x1 xx1
#define x2 xx2
#define y1 yy1
#define y2 yy2
#define act dp[x1][y1][x2][y2]

long dp[maxN][maxN][maxN][maxN];
long a[maxN][maxN];
long n,m,i,j;

long getRaisins(long x1,long y1,long x2,long y2){
    return a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1];
}

long makeDp(long x1,long y1,long x2,long y2){
    if(x1==x2 && y1==y2) return 0;
    if(act) return act;

    long i;
    act = (1<<30);
    for(i=x1;i<x2;i++) act = min(act, makeDp(x1,y1,i,y2) + makeDp(i+1,y1,x2,y2) );
    for(i=y1;i<y2;i++) act = min(act, makeDp(x1,y1,x2,i) + makeDp(x1,i+1,x2,y2) );

    act += getRaisins(x1,y1,x2,y2);
    return act;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%ld",&a[i][j]);
            a[i][j] += a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }
    }

    printf("%ld", makeDp(1,1,n,m) );

    return 0;
}
