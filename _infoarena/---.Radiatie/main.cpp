#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<long,pair<long,long> > Edge;

#define cost first
#define n1 second.first
#define n2 second.second
#define maxN 15010
#define maxLog 15
#define cNod nodes[j]
#define dir second
#define mp make_pair

long n,m,t,i,j,x,y,Root,ans;
vector<Edge> G;
Edge tmp;
vector<long> nodes;
vector<pair<long,long> > list[maxN];

long Dad[maxN],Bren[maxN],level[maxN];
long dp[maxLog+3][maxN];
long pay[maxLog+3][maxN];

void init(){
    for(long i=1;i<=n;i++) Dad[i] = i,Bren[i]=1;
}

long Find(long nod){
    long temp=nod;
    while(Dad[temp] != temp) temp = Dad[temp];
    while(nod != temp){
        long loc = Dad[nod];
        Dad[nod] = temp;
        nod = loc;
    }
    return nod;
}

void Merge(long R1,long R2){
    if(Bren[R1] < Bren[R2]){
        Dad[R1] = R2;
        Bren[R2]++;
    } else {
        Dad[R2] = R1;
        Bren[R1]++;
    }
}

void DFS(long nod){
    nodes.push_back(nod);
    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i].dir;
        if(dp[0][newNod] || newNod == G[0].n1) continue;
        dp[0][newNod] = nod; level[newNod] = level[nod]+1;
        pay[0][newNod] = list[nod][i].cost;
        DFS(newNod);
    }
}

void precalcLCA(){
    for(long i=1;i<=maxLog;i++)
        for(long j=0;j<nodes.size();j++)
            dp[i][cNod] = dp[i-1][dp[i-1][cNod]];
}

void precalcPay(){
    for(long i=1;i<=maxLog;i++)
        for(long j=0;j<nodes.size();j++)
            pay[i][cNod] = max(pay[i-1][cNod],pay[i-1][dp[i-1][cNod]]);
}

void makeTree(){
    init();

    long x,y,R1,R2,i;
    for(i=0;i<G.size();i++){
        x = G[i].n1; y = G[i].n2;
        R1 = Find(x); R2 = Find(y);
        if(R1 != R2) {
            Merge(R1,R2);
            list[x].push_back(mp(G[i].cost,y));
            list[y].push_back(mp(G[i].cost,x));
        }
    }

    level[G[0].n1] = 1;
    DFS(G[0].n1);

    precalcLCA();
    precalcPay();
}

void Up(long& a,long p){
    long i=0;
    while(p){
        if(p&1) a = dp[i][a];
        p >>= 1;
        i++;
    }
}

long LCA(long x,long y){
    long temp;
    if(level[x] < level[y]) {temp=x;x=y;y=temp;}
    Up(x,level[x]-level[y]);

    if(x == y) return x;
    for(long i = maxLog;i>=0;i--){
        long xx=dp[i][x],yy=dp[i][y];
        if(xx == 0 || yy == 0) continue;
        if(xx != yy) x = xx,y=yy;
    }
    return dp[0][x];
}

int main()
{
    freopen("radiatie.in","r",stdin);
    freopen("radiatie.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&t);
    for(i=1;i<=m;i++) {
        scanf("%ld %ld %ld",&tmp.n1,&tmp.n2,&tmp.cost);
        G.push_back(tmp);
    }
    sort(G.begin(),G.end());

    makeTree();

    for(;t;t--){
        scanf("%ld %ld",&x,&y);
        Root = LCA(x,y);

        long rLev=level[Root],p,i;

        ans = 0;

        p = level[x]-rLev; i = 0;
        while(p){
            if(p&1) ans = max(ans,pay[i][x]),x = dp[i][x];
            p >>= 1;
            i++;
        }

        p = level[y]-rLev; i=0;
        while(p){
            if(p&1) ans = max(ans,pay[i][y]),y=dp[i][y];
            p >>= 1;
            i++;
        }

        printf("%ld\n",ans);
    }

    return 0;
}
