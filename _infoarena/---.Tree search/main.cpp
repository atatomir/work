#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 100111
#define INF 2000000001

long n,q,x,y,i,cnt;
long c[maxN];
vector<long> list[maxN];

long fDown[maxN],fUp[maxN];
long betterDown[maxN],betterUp[maxN];
long id[maxN];
bool used[maxN];

long fComplex[maxN];

bool cmp(long a,long b){
    return betterDown[a]>betterDown[b];
}

void dfsDown(long node,long idd){
    id[node]  = idd; used[node] = true;

    long cnt=0,i;
    for(i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(used[newNode]) continue;
        list[node][cnt++] = list[node][i];
    }list[node].resize(cnt);


    if(list[node].size()) fDown[node]=-INF;
    for(i=0;i<list[node].size();i++){
        long newNode = list[node][i];

        dfsDown(newNode,idd);
        fDown[node] = max(fDown[node],fDown[newNode]);
    }

    fDown[node] += c[node];
}

void dfsUp(long node,long v){
    fUp[node] = v;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        dfsUp(newNode,v+c[newNode]);
    }
}

void dfsBetterDown(long node){
    long i;
    betterDown[node] = c[node];
    for(i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        dfsBetterDown(newNode);
        betterDown[node] = max(betterDown[node],betterDown[newNode]+c[node]);
    }
}

void dfsBetterUp(long node,long v){
    betterUp[node] = c[node];
    if(v>0) betterUp[node] += v;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        dfsBetterUp(newNode,betterUp[node]);
    }
}

void dfsComplex(long node,long v){
    fComplex[node] = v + c[node];
    if(list[node].size()==0) return;
    if(list[node].size()==1){
        dfsComplex(list[node][0],fComplex[node]);
    } else {
        long val = max(fComplex[node],betterDown[list[node][1]]+c[node]);
        dfsComplex(list[node][0],val);

        val = max(fComplex[node],betterDown[list[node][0]]+c[node]);
        for(long i=1;i<list[node].size();i++){
            long newNode = list[node][i];
            dfsComplex(newNode,val);
        }
    }
}

void getCase3(long& ans,long node){
    if(list[node].size()<2) return;
    long v = betterDown[list[node][0]]+betterDown[list[node][1]]+c[node];
    ans = max(ans,v);
}

int main()
{
    freopen("treesearch.in","r",stdin);
    freopen("treesearch.out","w",stdout);

    scanf("%ld%ld",&n,&q);
    for(i=1;i<=n;i++) scanf("%ld",&c[i]);

    for(i=1;i<n;i++){
        scanf("%ld%ld",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    fDown[1] = -INF; used[1] = true;
    for(i=0;i<list[1].size();i++){
        long newNode = list[1][i];
        dfsDown(newNode,i+1);
        fDown[1] = max(fDown[1],fDown[newNode]);
    } fDown[1] += c[1];
    dfsUp(1,c[1]);

    dfsBetterDown(1);
    dfsBetterUp(1,0);

    for(i=1;i<=n;i++)sort(list[i].begin(),list[i].end(),cmp);
    dfsComplex(1,0);

    for(i=1;i<=q;i++){
        scanf("%ld",&x);
        long s = id[x];

        long ans = betterUp[x]+betterDown[x]-c[x];
        if(x!=1)ans = max(ans,fComplex[x]+betterDown[x]-c[x]);
        getCase3(ans,x);
        printf("%ld\n",ans);
    }

    //!! fUp,fDown nu folosesc la nimic... doar de decor

    return 0;
}
