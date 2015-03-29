#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 1024
#define maxK 12

struct Edge{
    double c;
    short dir;
};
Edge mp(short _dir,double _c){
    Edge ans;
    ans.dir = _dir; ans.c = _c;
    return ans;
}

struct hElem{
    short node,still;
    double c;
};
hElem mpp(short _node,short _still,double _c){
    hElem ans;
    ans.node = _node; ans.still = _still; ans.c = _c;
    return ans;
}

struct cmp{
    bool operator()(const hElem& a,const hElem& b){
        return a.c > b.c;
    }
};

long n,m,k,i,x,y,c;
vector<Edge> list[maxN];
double ans[maxN][maxK];
bool used[maxN][maxK];
priority_queue<hElem,vector<hElem>,cmp> H;

int main()
{
    freopen("retea.in","r",stdin);
    freopen("retea.out","w",stdout);

    scanf("%ld%ld%ld",&n,&m,&k);
    for(i=1;i<=m;i++){
        scanf("%ld%ld%ld",&x,&y,&c);
        list[x].push_back(mp(y,c));
        list[y].push_back(mp(x,c));
    }

    H.push(mpp(1,k,0));
    while(!H.empty()){
        hElem act = H.top(); H.pop();

        if(used[act.node][act.still]) continue;

        used[act.node][act.still] = true;
        ans[act.node][act.still] = act.c;

        for(i=0;i<list[act.node].size();i++){
            long newNode = list[act.node][i].dir;
            double newCost = list[act.node][i].c;
            for(long fast=0;fast<=act.still;fast++){
                if(used[newNode][act.still-fast]) continue;
                double myCost = act.c + newCost/(1<<fast);
                if(ans[newNode][act.still-fast]==0 || ans[newNode][act.still-fast]>myCost){
                    H.push(mpp(newNode,act.still-fast,myCost));
                    ans[newNode][act.still-fast] = myCost;
                }
            }
        }

        if(used[n][0]) break;
    }

    printf("%.4lf",ans[n][0]);

    return 0;
}
