#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 55

int n,i,j,x;
vector<int> list[maxN];
vector<int> tmp[maxN];

int deny;
bool vis[maxN];
int ans[maxN];

int low[maxN],lvl[maxN];
int dad[maxN];

int how[maxN];

vector<int> a,b;

void dfs(int node){
    vis[node]=true;
    if(node==deny) return;
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i];
        if(vis[newNode]) continue;
        dfs(newNode);
    }
}
bool unavoidable(int node){
    memset(vis,0,sizeof(vis));
    deny = node;

    dfs(1); ans[node] |= 4;
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i];
        if(vis[newNode]) {
            ans[node] ^= 4;
            break;
        }
    }
    return !vis[n];
}

void biconex(int node,int _lvl){
    lvl[node]=low[node]=_lvl;
    int nr=1; if(node==1) nr--;
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i];

        if(dad[newNode]==node) continue;
        if(lvl[newNode]){
            low[node] = min(low[node],low[newNode]);
            continue;
        }

        dad[newNode] = node;
        biconex(newNode,_lvl+1);
        low[node] = min(low[node],low[newNode]);

        if(low[newNode] >= lvl[node] ) nr++;
    }

    if(nr==2) ans[node] |= 2;
    how[node]=nr;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    while(true){
        scanf("%d",&x); n++;
        if(x==-1) break;

        while(x!=-2){
            x++;
            if(x!=n)list[n].push_back(x);
            scanf("%d",&x);
        }
    }

    for(i=2;i<n;i++)
        if( unavoidable(i) ) ans[i] |= 1;

    for(i=1;i<=n;i++)
        for(j=0;j<list[i].size();j++)
            tmp[ list[i][j] ].push_back( i );
    for(i=1;i<=n;i++)
        for(j=0;j<tmp[i].size();j++)
            list[ i ].push_back( tmp[i][j] );

    biconex(1,1);
    for(i=2;i<n;i++){
        if((ans[i]&1)==1) a.push_back(i-1);
        if((ans[i]&7)==7) b.push_back(i-1);
    }

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    printf("%d ",a.size());
    for(i=0;i<a.size();i++) printf("%d ",a[i]); printf("\n");
    printf("%d ",b.size());
    for(i=0;i<b.size();i++) printf("%d ",b[i]); printf("\n");

    return 0;
}
