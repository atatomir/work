#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxN 133
#define x first
#define y second
#define mp make_pair
#define mPair pair<long,long>
#define tmp dp

const long defX[4]={-1,1,0,0};
const long defY[4]={0,0,-1,1};

long n,m,i,j,targ;
long id[maxN][maxN];
long dp[maxN][maxN];

long cnt[4];
char s[maxN];
queue<pair<long,long> > Q;
queue<mPair > Fll;

void fillM(long x,long y){
    long i;
    while(!Fll.empty()) Fll.pop(); Fll.push(mp(x,y));

    while(!Fll.empty()){
        mPair p = Fll.front(); Fll.pop();
        x = p.x; y = p.y;

        for(i=0;i<4;i++){
            long newX = x +defX[i];
            long newY = y + defY[i];

            if(tmp[newX][newY]==targ) {
                Fll.push(mp(newX,newY));
                if(tmp[newX][newY]==1) Q.push(make_pair(newX,newY));
                tmp[newX][newY] = 0;
            }
        }
    }
}

bool good(mPair p){
    if(id[p.x][p.y]==2) {
        if(dp[p.x][p.y]>1) return false;
        return true;
    }
    if(id[p.x][p.y]) return false;
    if(dp[p.x][p.y]) return false;
    return true;
}

int main()
{
    freopen("insule.in","r",stdin);
    freopen("insule.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        scanf("%s\n",s+1);
        for(j=1;j<=m;j++) {
            id[i][j] = s[j] -'0';
        }

    }
    for(i=0;i<=n+1;i++) id[i][0] = id[i][m+1] = -1;
    for(i=0;i<=m+1;i++) id[0][i] = id[n+1][i] = -1;

    for(i=0;i<=n+1;i++)
        for(j=0;j<=m+1;j++) tmp[i][j] = id[i][j];

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(tmp[i][j]>0){
                targ = tmp[i][j]; cnt[targ]++;
                if(tmp[i][j]==1) Q.push(mp(i,j));
                tmp[i][j] = 0;
                fillM(i,j);
            }
        }
    }

    printf("%ld %ld %ld ",cnt[1],cnt[2],cnt[3]);

    while(!Q.empty()){
        mPair p = Q.front(); Q.pop();
        if(id[p.x][p.y] == 2){
            if(dp[p.x][p.y]-1==0) continue;
            printf("%ld",dp[p.x][p.y]-1);

            /*for(i=1;i<=n;i++){
                for(j=1;j<=m;j++) cerr << dp[i][j] << ' ';
                cerr << '\n';
            }*/

            return 0;
        }

        for(i=0;i<4;i++){
            mPair newP;
            newP.x = p.x + defX[i];
            newP.y = p.y + defY[i];

            if(good(newP)) {
                Q.push(newP);
                dp[newP.x][newP.y] = dp[p.x][p.y]+1;
            }
        }
    }


    return 0;
}
