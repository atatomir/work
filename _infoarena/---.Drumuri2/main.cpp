#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define maxN 111*2
#define INF 2000000000
#define In(x) (x)
#define Out(x) ((x)+n)

long n,m,i,s,d,x,y,flow;
vector<long> list[maxN];
long F[maxN][maxN],C[maxN][maxN];

long prov[maxN];
bool used[maxN];
queue<long> Q;

inline void addEdge(long ss,long dd,long cap,long flow,bool must){
    list[ss].push_back(dd);
    if(!must)list[dd].push_back(ss);

    C[ss][dd] = cap;
    F[ss][dd] = flow;
    F[dd][ss] = -flow;
}

bool BF(){
    memset(used,0,sizeof(used));
    used[s] = true; Q.push(s);

    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        if(node==d) continue;

        for(long i=0;i<list[node].size();i++){
            long newNode = list[node][i];
            if(used[newNode] || C[node][newNode]==F[node][newNode]) continue;
            used[newNode] = true;
            Q.push(newNode); prov[newNode] = node;
        }
    }

    if(!used[d]) return false;

    for(long i=0;i<list[d].size();i++){
        long newNode = list[d][i];
        if(!used[newNode]) continue;

        prov[d]=newNode;
        long actFlow=INF;
        for(long node=d;node!=s;node=prov[node])
            actFlow=min(actFlow,C[prov[node]][node]-F[prov[node]][node]);

        for(long node=d;node!=s;node=prov[node]){
            F[prov[node]][node] += actFlow;
            F[node][prov[node]] -= actFlow;
        }

        flow -= actFlow;
    }


    return true;
}

int main()
{
    freopen("drumuri2.in","r",stdin);
    freopen("drumuri2.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    s=0; d = maxN-3;
    for(i=1;i<=n;i++) addEdge(s,In(i),1,1,false);
    for(i=1;i<=n;i++) addEdge(In(i),Out(i),INF,1,true);
    for(i=1;i<=n;i++) addEdge(Out(i),d,1,1,false);

    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        addEdge(Out(x),In(y),INF,0,false);
    }

    flow = n; long t=s;s=d;d=t;
    for(;BF(););
    printf("%ld",flow);

    return 0;
}
