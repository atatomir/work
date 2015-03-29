#include <iostream>
#include <cstdio>>

using namespace std;

#define maxN 555
#define maxLog 10

long n,m,i,j,k,x,y,l,ll;
long rmq[maxLog][maxN][maxN];

int main()
{
    freopen("plantatie.in","r",stdin);
    freopen("plantatie.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            scanf("%ld",&rmq[0][i][j]);

    for(k=1;k<maxLog;k++){
        l = 1<<(k-1);
        for(i=1;i<=n-l-l+1;i++)
            for(j=1;j<=n-l-l+1;j++)
                rmq[k][i][j] = max(max(rmq[k-1][i][j],rmq[k-1][i+l][j]),max(rmq[k-1][i][j+l],rmq[k-1][i+l][j+l]));
    }

    for(;m;m--){
        scanf("%ld%ld%ld",&x,&y,&l);
        k=0;while((1<<(k+1))<=l ) k++;
        long ll = 1<<k;

        long ans = max(max(rmq[k][x][y],rmq[k][x+l-ll][y]),max(rmq[k][x][y+l-ll],rmq[k][x+l-ll][y+l-ll]));
        printf("%ld\n",ans);
    }

    return 0;
}
