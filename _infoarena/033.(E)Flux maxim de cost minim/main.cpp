#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

#define maxN 375
#define INF 2000000000

long n,m,s,d,i,x,y,z,c;
vector<long> list[maxN];
long C[maxN][maxN],F[maxN][maxN];
long pay[maxN][maxN];
long long Ans;

queue<long> Q;
long bCost[maxN],prov[maxN];
bool inQueue[maxN];

bool bellman(){
    for(i=1;i<=n;i++) bCost[i] = INF;
    memset(inQueue,0,sizeof(inQueue));
    memset(prov,0,sizeof(prov));

    Q.push(s); inQueue[s]=true; bCost[s] = 0;

    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        inQueue[node] = false;

        for(i=0;i<list[node].size();i++){
            long newNode = list[node][i];
            long newCost = bCost[node]+pay[node][newNode];

            if(C[node][newNode]==F[node][newNode] || newCost >= bCost[newNode]) continue;
            bCost[newNode] = newCost;
            if(!inQueue[newNode]){inQueue[newNode] = true; Q.push(newNode);}
            prov[newNode] = node;
        }
    }

    if(bCost[d]==INF) return false;

    long flux=INF;
    for(long node=d;node!=s;node=prov[node]) flux = min(flux,C[prov[node]][node]-F[prov[node]][node]);
    Ans = Ans + bCost[d]*flux;
    for(long node=d;node!=s;node=prov[node]) {
        F[prov[node]][node] += flux;
        F[node][prov[node]] -= flux;
    }

    return true;
}

int main()
{
    freopen("fmcm.in","r",stdin);
    freopen("fmcm.out","w",stdout);

    scanf("%ld %ld %ld %ld",&n,&m,&s,&d);
    for(i=1;i<=m;i++){
        scanf("%ld%ld%ld%ld",&x,&y,&c,&z);
        list[x].push_back(y);
        list[y].push_back(x);

        C[x][y] = c;
        pay[x][y] = z;
        pay[y][x] = -z;
    }

    for(;bellman(););
    printf("%lld",Ans);

    return 0;
}
