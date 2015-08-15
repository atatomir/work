#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011

int n,nn,i,m,x,y,last;
vector<int> list[maxN];
bool restricted[maxN];
bool us[maxN];
int ans[maxN];

void dfs(int node){
    us[node] = true;
    for (int dest:list[node]){
        if (!us[dest]) dfs(dest);
    }
}

void dfsAnswer(int node){
    us[node] = true;
    for (int dest:list[node]){
        if (!us[dest]) dfsAnswer(dest);
    }
    ans[ node ] = n--;
}

int main()
{
    freopen("zapada.in","r",stdin);
    freopen("zapada.out","w",stdout);

    scanf("%d%d",&n,&m); nn = n;
    for (i=1;i<=m;i++){
        scanf("%d%d",&y,&x);
        list[x].pb(y);
        restricted[x] = restricted[y] = true;
    }

    for (i=1;i<=n;i++){
        if (restricted[i]) continue;

        us[i]=true;
        ans[i] = n--;
    }

    for (int i=1;i<=n;i++){
        if (us[i]) continue;

        last = i;
        dfs(i);
    }

    memset(us,0,sizeof(us));
    dfsAnswer(last);
    for (i=1;i<=nn;i++) printf("%d\n",ans[i]);


    return 0;
}
