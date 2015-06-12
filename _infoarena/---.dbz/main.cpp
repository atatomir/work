#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 1511
#define PI pair<long,long>
#define mp make_pair
#define dir first
#define cc second
#define def (1<<30)

long n,m,i,x,y,z;
vector< PI > list[maxN];
long id[maxN],cost[maxN],prov[maxN];
bool us[maxN];
vector< pair< pair<long,long>,long > > Edges;

struct cmp{
    bool operator()(long& a,long& b){
        return cost[a] > cost[b];
    }
};

priority_queue<long,vector<long>,cmp> H;

void dijkstra(long nodeS){
    long i;

    memset(id,0,sizeof(id));
    memset(cost,0,sizeof(cost));
    for(i=1;i<=n;i++) cost[i]=def;
    memset(prov,0,sizeof(prov));
    memset(us,0,sizeof(us));

    while(!H.empty()) H.pop();
    id[nodeS] = 1; us[nodeS] = true; cost[nodeS]=0;
    for(i=0;i<list[nodeS].size();i++){
        long newNode = list[nodeS][i].dir;
        id[newNode] = i+2;
        cost[newNode] = list[nodeS][i].cc;
        prov[newNode] = nodeS;
        H.push(newNode);
    }

    while(!H.empty()){
        long node = H.top(); H.pop();
        if(us[node]) continue;
        us[node] = true;
        for(i=0;i<list[node].size();i++){
            long newNode = list[node][i].dir;
            long ccost   = list[node][i].cc;
            if(cost[newNode] > cost[node]+ccost){
                id[newNode] = id[node];
                cost[newNode] = cost[node]+ccost;
                prov[newNode] = node;
                H.push(newNode);
            }
        }
    }
}

long getSolution(){
    long i,ans; ans = def;
    for(i=0;i<Edges.size();i++){
        pair< pair<long,long>,long > act = Edges[i];
        long xx = act.first.first;
        long yy = act.first.second;
        long vv = act.second;

        if(prov[xx]==yy || prov[yy]==xx) continue;
        if(id[xx]==id[yy]) continue;

        ans = min(ans, cost[xx]+cost[yy]+vv );
    }

    if(ans==def) ans = -1;
    return ans;
}

int main()
{
    freopen("dbz.in","r",stdin);
    freopen("dbz.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++) {
        scanf("%ld %ld %ld",&x,&y,&z);
        list[x].push_back( mp(y,z) );
        list[y].push_back( mp(x,z) );
        Edges.push_back( mp( mp(x,y),z ) );
    }

    for(i=1;i<=n;i++){
        dijkstra(i);
        printf("%ld ", getSolution() );
    }


    return 0;
}
