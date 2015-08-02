#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 10011
#define maxU 85
#define def maxU*3

int n,m,u,prov,i,x,y;
int Fighter[maxU];
vector<int> list[maxN];
vector<int> neigh;
vector<int> adj[def];

int C[def][def],F[def][def];
int cost[def][def];
int D,S;
/*
    0        - Source
    1->u     - Fighters
    u+1->... - Neighbours
    D        - Destination
*/


int dist[maxN];
queue<int> Q;
bool inQueue[def];
int wh[maxN];
int ans;

void getCost(int S,int id){
    while(!Q.empty()) Q.pop();
    memset(dist,0,sizeof(dist));

    dist[S] = 1; Q.push(S);
    while(!Q.empty()){
        int node = Q.front(); Q.pop();
        foreach(list[node]){
            if(dist[*it]) continue;
            dist[*it] = dist[node]+1;
            Q.push(*it);
        }
    }

    int i=0;
    foreach(neigh){
        i++;
        C[id][ u+i ] = 1;
        C[ u+i ][id] = 0;

        F[id][ u+i ] = F[ u+i ][id] = 0;
        cost[id][ u+i ] = dist[*it];
        cost[ u+i ][id] = -dist[*it];

        adj[id].pb(u+i);
        adj[u+i].pb(id);
    }
}

bool Flux(){
    memset(inQueue,0,sizeof(inQueue));
    memset(dist,0,sizeof(dist));
    while(!Q.empty()) Q.pop();

    Q.push(S); dist[S] = 1;
    while(!Q.empty()){
        int node = Q.front(); Q.pop();
        inQueue[node] = false;
        if(node==D) continue;

        foreach(adj[node]){
            if(F[node][*it] == C[node][*it]) continue;
            if(!dist[*it] || dist[*it] > dist[node]+cost[node][*it]){
                if(!inQueue[*it]){
                    Q.push(*it);
                    inQueue[*it]=true;
                }
                dist[*it] = dist[node] + cost[node][*it];
                wh[*it] = node;
            }
        }
    }

    if(dist[D]==0) return false;
    for(int node = D;node!=S;node=wh[node]){
        ans += cost[ wh[node] ][ node ];
        F[wh[node]][node]++; F[node][wh[node]]--;
    }

    return true;
}

int main()
{
    freopen("atac2.in","r",stdin);
    freopen("atac2.out","w",stdout);

    scanf("%d %d %d %d",&n,&m,&u,&prov);
    fordef(i,1,u) scanf("%d",&Fighter[i]);

    fordef(i,1,m){
        scanf("%d%d",&x,&y);
        list[x].pb(y);
        list[y].pb(x);

        if(x==prov) neigh.pb(y);
        if(y==prov) neigh.pb(x);
    }

    fordef(i,1,u) getCost(Fighter[i],i);
    S = 0; D = u+neigh.size()+3;

    fordef(i,1,u){
        adj[S].pb(i);
        adj[i].pb(S);

        C[S][i] = 1;
        C[i][S] = 0;
        F[S][i] = F[i][S] = 0;
        cost[S][i] = cost[i][S] = 0;
    }
    fordef(i,u+1,u+neigh.size()){
        adj[D].pb(i);
        adj[i].pb(D);

        C[D][i] = 0;
        C[i][D] = 1;
        F[D][i] = F[i][D] = 0;
        cost[D][i] = cost[i][D] = 0;
    }

    while( Flux() );
    printf("%d",ans-neigh.size());

    return 0;
}
