#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011

int n,m,i,x,y,top;
vector<int> list[maxN];
int low[maxN],lvl[maxN],dad[maxN];
bool us[maxN],good[maxN];
vector<int> comp;
vector<int> ans;

void dfs(int node){
    us[node] = true;
    int nr=1; if(top==node) nr--;
    low[node] = lvl[node];

    foreach(list[node]){
        if(us[*it]){
            if(*it==dad[node]) continue;
            low[node] = min(low[node],lvl[*it]);

            continue;
        }

        dad[*it] = node;
        lvl[*it] = lvl[node]+1;
        dfs(*it);

        low[node] = min(low[node],low[*it]);

        if(low[*it] >= lvl[node]) nr++;
    }

    if(nr>1) good[node]=true;
}

int main()
{
    freopen("pamant.in","r",stdin);
    freopen("pamant.out","w",stdout);

    scanf("%d%d",&n,&m);
    fordef(i,1,m){
        scanf("%d%d",&x,&y);
        list[x].pb(y);
        list[y].pb(x);
    }

    fordef(i,1,n){
        if(us[i]) continue;

        comp.pb(i); top=i; lvl[i]=1;
        dfs(i);
    }

    fordef(i,1,n)
        if(good[i])
            ans.pb(i);

    printf("%d\n",comp.size());
    foreach(comp) printf("%d ",*it); printf("\n");
    printf("%d\n",ans.size());
    foreach(ans) printf("%d ",*it); printf("\n");

    return 0;
}
