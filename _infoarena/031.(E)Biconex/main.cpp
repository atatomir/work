#include <iostream>
#include <stack>
#include <vector>
#include <cstdio>

using namespace std;

#define maxN 100011
#define mp make_pair
#define xx first
#define yy second

int n,m,i,x,y;
vector<int> list[maxN];
int lvl[maxN],low[maxN];
stack< pair<int,int> > S;

int id;
vector< vector<int> > ans;
int alrdn[maxN];

void cache(int x,int y){
    vector<int> hh ; hh.clear(); id++;

    while( true ){
        pair<int,int> act = S.top(); S.pop();

        if(alrdn[ act.xx ] != id) hh.push_back( act.xx );
        if(alrdn[ act.yy ] != id) hh.push_back( act.yy );
        alrdn[act.xx]=alrdn[act.yy]=id;

        if(act == mp(x,y)) break;
    }

    ans.push_back( hh );
}

void dfs(int node,int _lvl){
    lvl[node] = low[node] = _lvl;

    for(auto it = list[node].begin();it!=list[node].end();it++  ){
        if(lvl[*it]) {
            low[node] = min(low[node],lvl[*it]);
            continue;
        }

        S.push(mp( node,*it ));
        dfs(*it,_lvl+1);
        low[node] = min(low[node],low[*it]);

        if( lvl[node] <= low[*it] )
            cache( node,*it );
    }
}

int main()
{
    freopen("biconex.in","r",stdin);
    freopen("biconex.out","w",stdout);

    scanf("%d %d",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%d %d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    dfs(1,1);

    printf("%d\n",ans.size());
    for(i=0;i<ans.size();i++){
        for(int j=0;j<ans[i].size();j++)
            printf("%d ",ans[i][j]);
        printf("\n");
    }

    return 0;
}
