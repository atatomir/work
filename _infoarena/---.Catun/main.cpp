#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define nod first
#define cost second
#define nodH first.first
#define costH first.second
#define prov second
#define inf 1000000000
#define maxN 37000
#define mp make_pair

typedef pair<long,long> listElem;
typedef pair<pair<long,long>,long> heapElem;

struct compare{
    bool operator()(const heapElem& a,const heapElem& b){
        return a.costH > b.costH;
    }
};

long n,m,k,i,x,y,cost;
vector<listElem> list[maxN];
priority_queue<heapElem,vector<heapElem>,compare> H;
long ans[maxN],ap[maxN];
heapElem e;
long nod,nprov;

int main()
{
    freopen("catun.in","r",stdin);
    freopen("catun.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&k);

    for(i=1;i<=n;i++) ans[i] = inf;

    for(i=1;i<=k;i++){
        scanf("%ld",&x);
        ans[x] = 0; ap[x] = 0;
        H.push(mp(mp(x,0),x));
    }

    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&cost);
        list[x].push_back(mp(y,cost));
        list[y].push_back(mp(x,cost));
    }

    while(!H.empty()){
        e = H.top(); H.pop();
        nod = e.nodH; nprov = e.prov;
        if(ans[nod] < e.costH) continue;

        for(i=0;i<list[nod].size();i++){
            long newNod = list[nod][i].nod;
            long newCost = ans[nod] + list[nod][i].cost;

            if(ans[newNod] > newCost || (ans[newNod] == newCost && ap[newNod] > nprov)){
                ans[newNod] = newCost;
                ap[newNod] = nprov;
                H.push(mp(mp(newNod,newCost),nprov));
            }
        }
    }

    for(i=1;i<=n;i++) printf("%ld ",ap[i]);


    return 0;
}
