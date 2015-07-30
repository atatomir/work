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
int n,m,i,x,y;
vector< pa(int,int) > list[maxN];
int ans[maxN];
int gr[maxN];
vector<int> dif;
bool us[maxN];
bool alrdn[maxN];

int vaj[maxN];

void dfs(int node){
    us[node] = true;

    for(int i=0;i<list[node].size();i++){
        pa(int,int) act = list[node][i];
        if(alrdn[act.second]) {
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back();
            i--; continue;
        }

        alrdn[act.second] = true;
        dfs(act.first);
        ans[ act.second ] = node;
        vaj[node]++; vaj[act.first]--;
    }
}

int main()
{
    freopen("fotbal2.in","r",stdin);
    freopen("fotbal2.out","w",stdout);

    scanf("%d%d",&n,&m);
    fordef(i,1,m){
        scanf("%d%d",&x,&y);
        list[x].pb(mp(y,i));
        list[y].pb(mp(x,i));
        gr[x]++; gr[y]++;
    }

    fordef(i,1,n) if(gr[i]%2==1) dif.pb(i);

    if(dif.empty()) printf("0\n"); else printf("2\n");
    int cnt=m;
    foreach(dif){
        list[*it].pb(mp(n+1,++cnt));
        list[n+1].pb(mp(*it,cnt));
    }

    fordef(i,1,n){
        if(!us[i])
            dfs(i);
    }
    fordef(i,1,m) printf("%d\n",ans[i]);

    return 0;
}
