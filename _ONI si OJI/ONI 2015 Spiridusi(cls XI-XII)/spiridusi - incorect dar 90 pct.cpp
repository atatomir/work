#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 100001
#define Good (s[ who[posR] ]-s[ par[ who[posL] ] ] <= c)
#define getVal p[ who[posR] ]-p[ par[ who[posL] ] ]
#define max(a,b) (a<b?b:a)

int n,c,i,x,y;
vector<int> list[maxN];
int s[maxN]; //! cnt spiridusi
long long p[maxN]; //! coeficient
long par[maxN];
bool us[maxN];
long long ans=-(1LL<<60);

int who[maxN];
int posL,posR;

void dfsIni(int node){
    us[node] = true;
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i];
        if(us[newNode]) continue;

        par[newNode] = node;
        s[newNode] += s[node];
        p[newNode] += p[node];
        dfsIni(newNode);
    }
}


void dfs(int node){
    who[++posR] = node;
    while(posL<=posR && !Good) posL++;

    long long val = getVal;
    ans = max(ans,val);

    for(int i=0;i<list[node].size();i++)
        if( par[list[node][i]]==node )
            dfs(list[node][i]);

    posR--;
}

int main()
{
    freopen("spiridusi.in","r",stdin);
    freopen("spiridusi.out","w",stdout);

    scanf("%d %d",&n,&c);
    for(i=1;i<=n;i++) scanf("%d",&s[i]);
    for(i=1;i<=n;i++) scanf("%lld",&p[i]);
    for(i=1;i<n;i++){
        scanf("%d %d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    par[1] = 0;
    dfsIni(1);

    posL=1;posR=0;
    dfs(1);

    printf("%lld",ans);
    cerr << ans;

    return 0;
}
