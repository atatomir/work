#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxN 40
#define x first
#define y second.first
#define z second.second
#define mp make_pair

typedef pair<long,pair<long,long> > mPair;

const long defX[6]={-1,1,0,0,0,0};
const long defY[6]={0,0,-1,1,0,0};
const long defZ[6]={0,0,0,0,-1,1};

long n,m,i,j,xx,yy,zz;
short dp[maxN][maxN][maxN];
queue<mPair> Q;

vector<mPair> ans;

void calc(long xx,long yy,long zz){
    mPair act = mp(xx,mp(yy,zz));
    ans.push_back(act);
    for(long i=0;i<6;i++){
        mPair newP;
        newP.x = act.x + defX[i];
        newP.y = act.y + defY[i];
        newP.z = act.z + defZ[i];
        if(dp[newP.x][newP.y][newP.z] == dp[act.x][act.y][act.z]-1) {
            calc(newP.x,newP.y,newP.z);
            return;

        }
    }
}

int main()
{
    freopen("alge.in","r",stdin);
    freopen("alge.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&xx,&yy,&zz);
        dp[xx][yy][zz] = -7;
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            dp[0][i][j] = dp[n+1][i][j] = -7;
            dp[i][0][j] = dp[i][n+1][j] = -7;
            dp[i][j][0] = dp[i][j][n+1] = -7;
        }
    }

    dp[1][1][1] = 1; Q.push(mp(1,mp(1,1)));
    while(!Q.empty()){
        mPair act = Q.front(); Q.pop();
        for(i=0;i<6;i++){
            mPair newP;
            newP.x = act.x + defX[i];
            newP.y = act.y + defY[i];
            newP.z = act.z + defZ[i];
            if(dp[newP.x][newP.y][newP.z] == 0) {
                dp[newP.x][newP.y][newP.z] = dp[act.x][act.y][act.z] + 1;
                Q.push(newP);
            }
        }
    }

    printf("%ld\n",dp[n][n][n]);

    calc(n,n,n);
    for(i=ans.size()-1;i>=0;i--){
        printf("%ld %ld %ld\n",ans[i].x,ans[i].y,ans[i].z);
    }

    return 0;
}
