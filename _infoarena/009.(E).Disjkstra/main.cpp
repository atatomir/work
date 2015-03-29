#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define maxN 50010
#define nod first
#define cost second
#define inf 1000000000

typedef pair<long,long> heapElem;

struct compare{
    bool operator()(const heapElem& a,const heapElem& b){
        return a.second > b.second;
    }
};

long n,m,i,x,y,cost,nod,newNod,newCost;
long ans[maxN];
priority_queue<heapElem,vector<heapElem>,compare> H;
vector<heapElem> list[maxN];
heapElem e;

int main()
{
    freopen("dijkstra.in","r",stdin);
    freopen("dijkstra.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&cost);
        list[x].push_back(make_pair(y,cost));
    }

    for(i=2;i<=n;i++) ans[i] = inf;
    H.push(make_pair(1,0));

    while(!H.empty()){
        e = H.top(); H.pop();

        if(ans[e.nod] < e.cost) continue;
        nod = e.nod;

        for(i=0;i<list[nod].size();i++){
            newNod = list[nod][i].nod;
            newCost = ans[nod] + list[nod][i].cost;
            if(ans[newNod] > newCost) {
                ans[newNod] = newCost;
                H.push(make_pair(newNod,newCost));
            }
        }
    }

    for(i=2;i<=n;i++) {
        if(ans[i] == inf) ans[i] = 0;
        printf("%ld ",ans[i]);
    }

    return 0;
}
