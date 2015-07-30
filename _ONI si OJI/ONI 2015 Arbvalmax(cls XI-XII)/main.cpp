#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 300011
#define forall(V) for(auto it=V.begin();it!=V.end();it++)
#define max(a,b) (a>b?a:b)
#define INF 2000000001

int n,m,i,x,y;
vector<int> list[maxN];
int val[maxN];

int dpSub   [maxN]; //! subarborele lui node
int dpUp    [maxN]; //! tot inafara de lantul 1-node si subarborele lui node
int dpVaj   [maxN]; //! tot inafara de subarborele lui node
int dpSubVaj[maxN]; //! subarborele lui node fara node

void make_dpSub(int node){
    dpSub[node] = val[node]; dpSubVaj[node] = -INF;
    forall(list[node]) {
        make_dpSub(*it);
        dpSub[node] = max(dpSub[node],dpSub[*it]);
        dpSubVaj[node] = max(dpSubVaj[node],dpSub[*it]);
    }
}
bool cmp(const int& a,const int& b){
    return dpSub[a] > dpSub[b];
}
void make_dpUp(int node){
    if(list[node].empty()) return;
    if(list[node].size()==1){
        dpUp[ list[node][0] ] = dpUp[node];
        make_dpUp( list[node][0] );
    }else{
        dpUp[ list[node][0] ] = max(dpUp[node], dpSub[ list[node][1] ] );
        make_dpUp( list[node][0] );

        auto it = list[node].begin();it++;
        for(;it!=list[node].end();it++){
            dpUp[ *it ] = max(dpUp[node],dpSub[ list[node][0] ]);
            make_dpUp( *it );
        }
    }
}
void make_dpVaj(int node){
    if(list[node].empty()) return;
    if(list[node].size()==1){
        dpVaj[list[node][0]] = max(dpVaj[node],val[node]);
    } else {
        dpVaj[list[node][0]] = max(dpVaj[node],val[node]);
        dpVaj[list[node][0]] = max(dpVaj[list[node][0]], dpSub[ list[node][1] ] );
        make_dpVaj( list[node][0] );

        auto it = list[node].begin();it++;
        for(;it!=list[node].end();it++){
            dpVaj[ *it ] = max(dpVaj[node],dpVaj[ list[node][0] ]);
            dpVaj[ *it ] = max(dpVaj[*it],val[node]);
            make_dpVaj( *it );
        }
    }
}

int main()
{
    freopen("arbvalmax.in","r",stdin);
    freopen("arbvalmax.out","w",stdout);

    scanf("%d%d",&n,&m);
    for(i=2;i<=n;i++){
        scanf("%d",&x);
        list[x].push_back(i);
    }
    for(i=1;i<=n;i++) scanf("%d",&val[i]);

    //! initialization
    make_dpSub(1);
    for(i=1;i<=n;i++) sort(list[i].begin(),list[i].end(),cmp);

    dpUp[1] = -INF;
    make_dpUp(1);

    dpVaj[i] = dpUp[1];
    make_dpVaj(1);
    //! --------------

    for(;m--;){
        scanf("%d %d",&x,&y);
        int ans = max(dpUp[y],dpVaj[x]);
            ans = max(ans,dpSubVaj[y]);
        printf("%d\n",ans);
    }

    return 0;
}
