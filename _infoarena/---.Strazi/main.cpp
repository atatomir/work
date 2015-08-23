#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 300

int n,m,i,x,y;
vector<int> list[maxN];
int le[maxN],ri[maxN];
bool us[maxN];

vector<int> ans;
vector< pair<int,int> > Edges;

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (auto neigh:list[node]){
        if (ri[neigh]) continue;
        le[node] = neigh;
        ri[neigh] = node;
        return true;
    }

    for (auto neigh:list[node]){
        if ( !pairUp(ri[neigh]) ) continue;
        le[node] = neigh;
        ri[neigh] = node;
        return true;
    }

    return false;
}

void complete(int node) {
    us[node] = true;
    ans.pb(node);

    if( !le[node] ) return;
    complete( le[node] );
}

int main()
{
    freopen("strazi.in","r",stdin);
    freopen("strazi.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d",&x,&y);
        list[x].pb(y);
    }

    for(bool need = true; need;) {
        need = false;
        memset(us,0,sizeof(us));

        for (i = 1; i <= n; i++)
            if (!le[i]) need |= pairUp(i);
    }

    memset(us,0,sizeof(us));
    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        if (ri[i]) continue;

        if (ans.empty() == false) Edges.push_back( mp( ans[ans.size()-1],i ) );
        complete(i);
    }

    printf("%d\n",Edges.size());
    for (auto e:Edges) printf("%d %d\n",e.first,e.second);
    for (auto e:ans)   printf("%d ",e);


    return 0;
}
