#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 32111
#define maxLog 15

long n,m,i,x,y,par,root;
long pct[maxN];
vector<long> list[maxN];

long l[maxN];
long lca[maxLog+3][maxN];

long ans=-1,ansX=50000,ansY=50000;
bool used[maxN];

void dfs(long node,long lev){
    l[node] = lev; long cnt=0;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(l[newNode]) continue;
        list[node][cnt++] = newNode;
        lca[0][newNode] = node;
        dfs(newNode,lev+1);
    }
    list[node].resize(cnt);
}

void preCalc(){
    long i,j;
    for(i=1;i<=maxLog;i++){
        for(j=1;j<=n;j++)
            lca[i][j] = lca[i-1][lca[i-1][j]];
    }
}

long Up(long x,long p){
    long i=0;
    while(p){
        if(p&1) x = lca[i][x];
        p>>=1;
        i++;
    }
    return x;
}

long getLCA(long x,long y){
    if(l[x]<l[y]){
        y = Up(y,l[y]-l[x]);
    } else
    if(l[x]>l[y])
        x = Up(x,l[x]-l[y]);

    if(x==y) return x;
    for(long i=maxLog;i>=0;i--){
        if(!(lca[i][x]==lca[i][y])){
            x = lca[i][x];
            y = lca[i][y];
        }
    }
    return lca[0][x];
}

int main()
{
    freopen("concurs.in","r",stdin);
    freopen("concurs.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%ld",&pct[i]);

    for(i=1;i<n;i++){
        scanf("%ld%ld",&x,&y);
        list[x].push_back(y);
        used[y] = true;
    }
    for(i=1;i<=n;i++)
        if(!used[i]) {root = i;break;}

    dfs(root,1);
    preCalc();

    for(;m;m--){
        scanf("%ld %ld",&x,&y);
        par = getLCA(x,y);
        if(pct[par]>ans||(pct[par]==ans&&ansX>x)||(pct[par]==ans&&ansX==x&&ansY>y)){
            ans = pct[par];
            ansX = x;
            ansY = y;
        }
    }

    printf("%ld %ld %ld",ans,ansX,ansY);

    return 0;
}
