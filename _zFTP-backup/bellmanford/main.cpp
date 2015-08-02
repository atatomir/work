#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<long,long> arc;

#define maxN 50005

long n,m,i,x,y,cost,nod;
vector<arc> list[maxN];
queue<long> Q;
long vis[maxN],ans[maxN];
bool inQueue[maxN];

int main()
{
    freopen("bellmanford.in","r",stdin);
    freopen("bellmanford.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&cost);
        list[x].push_back(make_pair(y,cost));
    }

    Q.push(1);
    inQueue[1] = true;

    while(!Q.empty()){
        nod = Q.front(); Q.pop();
        inQueue[nod] = false;

        for(i=0;i<list[nod].size();i++){
            long newNod = list[nod][i].first;
            long newCost = list[nod][i].second;
            if(!vis[newNod] || (vis[newNod] && ans[newNod] > ans[nod] + newCost)){
                ans[newNod] = ans[nod] + newCost;
                if(!inQueue[newNod]){
                    Q.push(newNod); inQueue[newNod] = true;
                    vis[newNod]++;
                    if(vis[newNod] > n) {printf("Ciclu negativ!");return 0;}
                }
            }
        }
    }

    for(i=2;i<=n;i++) printf("%ld ",ans[i]);

    return 0;
}
