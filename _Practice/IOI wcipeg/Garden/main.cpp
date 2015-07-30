#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG @atatomir
#define maxN 255
#define INF (1<<25)
#define actSum getSum(ii,jj,i,j)
#define nextSum getSum(ii-1,jj,i,j)
#define lastSum getSum(ii+1,jj,i,j)
#define act dp[def][i][j]

long n,m,i,j,def,x,y,ans;
long k,cnt;
long s[maxN][maxN],a[maxN][maxN];
long dp[2][maxN][maxN];

inline long getSum(long xx1,long yy1,long xx2,long yy2){
    return s[xx2][yy2]-s[xx1-1][yy2]-s[xx2][yy1-1]+s[xx1-1][yy1-1];
}

void solve(){
    long i,j,ii,jj;

    for(i=0;i<=m+1;i++) dp[def][0][i]=dp[def][n+1][i]=INF;
    for(i=0;i<=n+1;i++) dp[def][i][0]=dp[def][i][m+1]=INF;

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            dp[def][i][j] = INF;

            ii=i;jj=j;
            if(getSum(i,j,i,j)==k) act=4;
            if(getSum(i,j,i,j) >k) break;

            while(ii>1 && nextSum<=k ) {
                ii--;
                if( actSum==k ) act = min(act, 2*(i-ii+1 + j-jj+1) );
            }

            while(--jj>0){
                while(ii+1<=i && actSum>k) ii++;
                while(ii+1<=i && lastSum==k) ii++;

                if(actSum==k) act = min(act, 2*(i-ii+1 + j-jj+1) );
            }

        }
    }

    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            dp[def][i][j] = min( dp[def][i][j] , min( dp[def][i-1][j] , dp[def][i][j-1] ) );
}

#ifdef DEBUG
inline void debug(long def){
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) printf("%ld ",dp[def][i][j]);
        printf("\n");
    }
}
#endif

long tmp[maxN][maxN];
void swapAll(){
    long i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            tmp[i][j] = a[i][j];
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            a[i][j] = tmp[ n-i+1 ][ m-j+1 ];
}
void swapDP(){
    long i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            tmp[i][j] = dp[def][i][j];
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            dp[def][i][j] = tmp[ n-i+1 ][ m-j+1 ];
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld %ld",&n,&m,&cnt,&k);
    for(;cnt--;){
        scanf("%ld %ld",&x,&y);
        s[x][y]++; a[x][y]++;
    }

    //! from top-left
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            s[i][j] += s[i-1][j]+s[i][j-1]-s[i-1][j-1];
    def=0;
    solve();

    //! from bottom-right
    swapAll();
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            s[i][j] = a[i][j];
            s[i][j] += s[i-1][j]+s[i][j-1]-s[i-1][j-1];
        }
    def=1;
    solve();
    swapDP();

    //! Try
    ans = INF;
    for(i=1;i<n;i++) ans = min(ans, dp[0][i][m]+dp[1][i+1][1]  );
    for(j=1;j<m;j++) ans = min(ans, dp[0][n][j]+dp[1][1][j+1]  );

    if(ans == INF) printf("NO");
    else           printf("%ld",ans);

    //debug(0); printf("\n");
    //debug(1);

    return 0;
}
