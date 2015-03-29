#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 100005

long n,m,i,cont,x,y;
vector<long> list[maxN];
long vis[maxN];

void dfs(long nod){
    vis[nod] = true;
    for(long i=0;i<list[nod].size();i++)
        if(!vis[list[nod][i]]) dfs(list[nod][i]);
}

int main()
{
    freopen("dfs.in","r",stdin);
    freopen("dfs.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    for(i=1;i<=n;i++)
        if(!vis[i]) cont++,dfs(i);

    printf("%ld",cont);

    return 0;
}
