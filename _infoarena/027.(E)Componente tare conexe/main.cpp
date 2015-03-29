#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define maxN 100010

long n,i,m,x,y;
vector<long> gIn[maxN],gOut[maxN];
bool vis[maxN],ctc[maxN];
stack<long> S;
vector<vector<long> > ans;
vector<long> V;

void BFF(long nod){
    vis[nod] = true;
    for(long i=0;i<gOut[nod].size();i++){
        long newNod = gOut[nod][i];
        if(!vis[newNod]) BFF(newNod);
    }
    S.push(nod);
}

void BFB(long nod){
    ctc[nod] = true; V.push_back(nod);
    for(long i=0;i<gIn[nod].size();i++){
        long newNod = gIn[nod][i];
        if(!ctc[newNod]) BFB(newNod);
    }
}

int main()
{
    freopen("ctc.in","r",stdin);
    freopen("ctc.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        gOut[x].push_back(y);
        gIn[y].push_back(x);
    }

    for(i=1;i<=n;i++){
        if(!vis[i]) BFF(i);
    }

    while(!S.empty()){
        long nod=S.top(); S.pop();
        if(!ctc[nod]){
            V.clear();
            BFB(nod);
            ans.push_back(V);
        }
    }

    printf("%ld\n",ans.size());
    for(i=0;i<ans.size();i++){
        for(long j=0;j<ans[i].size();j++)
            printf("%ld ",ans[i][j]);
        printf("\n");
    }

    return 0;
}
