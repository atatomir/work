#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define maxN 200011
#define mod 666013
#define mp make_pair
#define xx first
#define yy second

int n,m,i,x,y;
vector<int> list[maxN];
int lvl[maxN],low[maxN];

int how[maxN];
int dad[maxN];

void dfs(int node,int _lvl){
    low[node]=lvl[node]= _lvl;

    int nr = 1; if(node==1) nr--;

    for(auto it=list[node].begin();it!=list[node].end();it++){
        if(dad[node]==*it) continue;
        if(lvl[*it]){
            low[node] = min(low[node],lvl[*it]);
            continue;
        }

        dad[*it]=node;
        dfs(*it,_lvl+1);
        low[node] = min(low[node],low[*it]);

        if(low[*it] >= lvl[node]) nr++;
    }

    how[node] = nr;
}

int myPow(int _a,int b){
    long long ans = 1,a=1LL*_a;
    while(b){
        if(b&1) ans = (ans*a)%mod;
        b >>= 1;
        a = (a*a)%mod;
    }
    return ans;
}

int main()
{
    freopen("clepsidra.in","r",stdin);
    freopen("clepsidra.out","w",stdout);

    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    dfs(1,1);
    for(i=1;i<=n;i++){
        long long ans = myPow(2,how[i])-2; if(ans<0) ans+=mod;
        printf("%lld\n",ans);
        continue;
    }


    return 0;
}

