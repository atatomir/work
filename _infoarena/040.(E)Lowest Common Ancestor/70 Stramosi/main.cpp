#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 100010
#define maxLog 20

long n,m,i,x,y,t,lim;
long dp[maxLog+5][maxN];
vector<long> list[maxN];
long level[maxN];

void preProc(){
    bool util;

    for(long i=1;i<=maxLog;i++){
        util = false;
        for(long j=1;j<=n;j++){
            dp[i][j] = dp[i-1][dp[i-1][j]];
            if(dp[i][j]) util = true;
        }
        if(!util) break;
    }
    lim = i-1;
}

void DFS(long nod){
    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i];
        level[newNod] = level[nod] + 1;
        DFS(newNod);
    }
}

void BFS(){
    queue<long> Q;
    long i;

    level[1] = 1; Q.push(1);
    while(!Q.empty()){
        long nod = Q.front(); Q.pop();
        for(i=0;i<list[nod].size();i++){
            long newNod = list[nod][i];
            level[newNod] = level[nod] + 1;
            Q.push(newNod);
        }
    }
}

void Up(long& nod,long p){
    long i=0;
    while(p){
        if(p&1) nod = dp[i][nod];
        p >>= 1;
        i++;
    }
}

long LCA(long x,long y){
    long xx,yy;
    for(long i=maxLog;i>=0;i--){
        xx = dp[i][x]; yy = dp[i][y];
        if(xx == 0 || yy == 0) continue;
        if(xx != yy) x=xx,y=yy;
    }
    return dp[0][x];
}

int main()
{
    freopen("lca.in","r",stdin);
    freopen("lca.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=2;i<=n;i++) {
        scanf("%ld",&dp[0][i]);
        list[dp[0][i]].push_back(i);
    }

    preProc();
    //DFS(1);
    BFS();

    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        if(level[x] > level[y]) {t=x;x=y;y=t;}

        Up(y,level[y]-level[x]);
        if(x == y){
            printf("%ld\n",x);
        } else {
            printf("%ld\n",LCA(x,y));
        }
    }

    return 0;
}
