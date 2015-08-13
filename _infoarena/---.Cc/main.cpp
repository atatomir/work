#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100
#define def (maxN*3)
#define inf (1<<30)

int n,i,j,x,S,D;

int Flow,Pay;
int C[def][def];
int F[def][def];
int cost[def][def];
vector<int> list[def];
int dist[def];
queue<int> Q;
bool inQueue[def];
int prov[def];

void addEdge(int _S,int _D,int _cap,int _cost){
    list[_S].pb(_D);
    list[_D].pb(_S);

    C[_S][_D] = _cap;
    C[_D][_S] = 0;
    F[_S][_D] = F[_D][_S] = 0;
    cost[_S][_D] =  _cost;
    cost[_D][_S] = -_cost;
}

bool Flux(){
    int i;

    for (i=S;i<=D;i++) dist[i]=inf;
    while (!Q.empty()) Q.pop();

    dist[S]=0; Q.push(S); inQueue[S]=true;
    while (!Q.empty()){
        int node = Q.front(); Q.pop();
        inQueue[node] = false;
        if (node==D) continue;

        for (auto e:list[node]){
            int newCost = dist[node] + cost[node][e];
            if (F[node][e]==C[node][e] || newCost >= dist[e]) continue;

            dist[e] = newCost;
            prov[e] = node;
            if (!inQueue[e]){
                Q.push(e);
                inQueue[e] = true;
            }
        }
    }

    if (dist[D]==inf) return false;

    int act_pay=0;
    for (int node=D;node!=S;node=prov[node]) act_pay += cost[ prov[node] ][ node ];
    for (int node=D;node!=S;node=prov[node]){
        F[ prov[node] ][ node ]++;
        F[ node ][ prov[node] ]--;
    }
    Flow++;
    Pay += act_pay;

    return true;
}

int main()
{
    freopen("cc.in","r",stdin);
    freopen("cc.out","w",stdout);

    scanf("%d",&n); S = 0; D = 2*n+3;
    for (i=1;i<=n;i++) addEdge(S,i,1,0);
    for (i=1;i<=n;i++) addEdge(n+i,D,1,0);

    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&x);
            addEdge(i,n+j,1,x);
        }
    }

    while ( Flux() );
    printf("%d",Pay);

    if(Flow!=n) cerr << "Error " << Flow << '/' << n;

    return 0;
}
