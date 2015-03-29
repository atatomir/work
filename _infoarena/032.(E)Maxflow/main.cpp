#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define maxN 1024
#define itt vector<long>::iterator
#define INF (1<<30)

long n,m,i,flow,x,y,c;
long C[maxN][maxN],F[maxN][maxN];
long from[maxN];
vector<long> list[maxN];
bool vis[maxN];

queue<long> Q;

bool BF(){
    memset(vis,0,sizeof(vis));

    vis[1] = true; Q.push(1);
    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        if(node==n) continue;
        for(itt it=list[node].begin();it!=list[node].end();it++){
            if((F[node][*it]==C[node][*it]) || vis[*it]) continue;
            vis[*it] = true; from[*it]=node;
            Q.push(*it);
        }
    }
    return vis[n];
}

int main()
{
    freopen("maxflow.in","r",stdin);
    freopen("maxflow.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld%ld%ld",&x,&y,&c);
        list[x].push_back(y);
        list[y].push_back(x);
        C[x][y] += c;
    }

    for(flow=0;BF();){
        for(itt it=list[n].begin();it!=list[n].end();it++){
            if(!vis[*it]) continue;
            from[n] = *it;

            long node = n,fMin=INF;
            while(node!=1){
                fMin = min(fMin,C[from[node]][node]-F[from[node]][node]);
                node = from[node];
            }

            node = n;
            while(node!=1){
                F[from[node]][node] += fMin;
                F[node][from[node]] -= fMin;
                node = from[node];
            }

            flow += fMin;
        }
    }

    printf("%ld",flow);

    return 0;
}
