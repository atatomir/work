#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

#define maxN 211
#define eps 0.0000000000001

long n,m,x,y,i;
double c,flow;
vector<long> list[maxN];
double C[maxN][maxN],F[maxN][maxN];

queue<long> Q;
long prov[maxN];
bool used[maxN];

inline void addEdge(long x,long y,double c){
    list[x].push_back(y);
    list[y].push_back(x);

    C[x][y] = C[y][x] = c;
}

bool BF(){
    memset(used,0,sizeof(used));
    used[1]=true; Q.push(1);
    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        if(node==n) continue;
        for(long i=0;i<list[node].size();i++){
            long newNode = list[node][i];
            if(used[newNode] || C[node][newNode]-F[node][newNode] <= eps) continue;
            used[newNode] = true;
            Q.push(newNode); prov[newNode] = node;
        }
    }

    if(!used[n]) return false;

    for(long i=0;i<list[n].size();i++){
        long dir = list[n][i];
        if(!used[dir]) continue;

        prov[n] = dir;
        double actFlow = 1000000000000000.00;
        for(long node=n;node!=1;node=prov[node])
            actFlow=min(actFlow,C[prov[node]][node]-F[prov[node]][node]);

        for(long node=n;node!=1;node=prov[node]){
            F[prov[node]][node] += actFlow;
            F[node][prov[node]] -= actFlow;
        }

        flow += actFlow;
    }

    return true;
}

int main()
{
    freopen("fear.in","r",stdin);
    freopen("fear.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %lf",&x,&y,&c);
        addEdge(x,y,log(c));
    }

    for(;BF(););
    printf("%.4lf",exp(flow));

    return 0;
}
