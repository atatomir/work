#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 1011

const long defX[4]={-1,1,0,0};
const long defY[4]={0,0,-1,1};

struct Pos{
    long x,y;
    Pos operator()(long xx,long yy){
        x = xx; y = yy;
        return *this;
    }
    bool operator!=(Pos tmp){
        if(tmp.x==x&&tmp.y==y) return false;
        return true;
    }
};

long n,m,i,j;
long id[maxN][maxN],dp[maxN][maxN];
queue<Pos> Q;
vector<Pos> poss;
Pos ans;long answer;

void Lee(long x,long y){
    Pos p,tmp; p(x,y);
    long cnt;

    poss.clear();
    Q.push(p); id[p.x][p.y] = 1; cnt=1;
    while(!Q.empty()){
        p = Q.front(); Q.pop();
        for(long i=0;i<4;i++){
            tmp = p; tmp.x += defX[i]; tmp.y += defY[i];
            if(id[tmp.x][tmp.y]==2){
                Q.push(tmp);
                id[tmp.x][tmp.y] = 1; cnt++;
            }
            if(id[tmp.x][tmp.y]==0) poss.push_back(tmp);
        }
    }

    if(poss.size()==0) return;
    for(long i=1;i<poss.size();i++)
        if(poss[0]!=poss[i]) return;

    p = poss[0];
    dp[p.x][p.y] += cnt;
}

int main()
{
    freopen("go.in","r",stdin);
    freopen("go.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%ld",&id[i][j]);
            if(id[i][j]!=0) dp[i][j]=-1;
        }
    }

    for(i=0;i<=n+1;i++) id[i][0]=id[i][m+1]=1;
    for(i=0;i<=m+1;i++) id[0][i]=id[n+1][i]=1;

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(id[i][j]!=2) continue;
            Lee(i,j);
        }
    }

    answer = -1;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(answer < dp[i][j]){
                answer = dp[i][j];
                ans.x=i;ans.y=j;
            }
        }
    }

    printf("%ld %ld",ans.x-1,ans.y-1);

    return 0;
}
