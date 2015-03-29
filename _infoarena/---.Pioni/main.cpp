#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 20011

long n,m,t,i,x,y,k;
vector<long> list[maxN];
bool vis[maxN];

bool win[maxN];
long son[maxN];
vector<long> ans;

void dfs(long node){
    vis[node] = true;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(!vis[newNode]) dfs(newNode);

        if(win[newNode]==0){
            win[node] = 1;
            son[node] = newNode;
        }
    }
}

int main()
{
    freopen("pioni.in","r",stdin);
    freopen("pioni.out","w",stdout);

    scanf("%ld %ld %ld",&t,&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
    }

    for(i=1;i<=n;i++)
        if(!vis[i]) dfs(i);

    for(;t;t--){
        ans.clear();
        scanf("%ld",&k);
        for(;k;k--){
            scanf("%ld",&x);
            if(win[x]) ans.push_back(x);
        }

        if(ans.size()==0){
            printf("Fumeanu\n");
        } else {
            printf("Nargy\n%ld ",ans.size());
            for(i=0;i<ans.size();i++) printf("%ld %ld ",ans[i],son[ans[i]]);
            printf("\n");
        }
    }

    return 0;
}
