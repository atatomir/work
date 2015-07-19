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

#define maxN 100011

int n,i,x,y;
vector<int> list[maxN];
int last[maxN];
bool us[maxN];
int dp[maxN];
int ans[maxN];

void dfs(int node){
    vector<int> v; v.clear();
    us[node] = true;
    foreach(list[node]){
        if(us[*it]) continue;
        dfs(*it);
        v.push_back(dp[*it]);
    }

    //! solve
    sort(v.begin(),v.end());
    last[node] = 0;
    int tmp = 0;

    foreach(v){
        if(*it > tmp) tmp++;
        else last[node] = *it;
    }
    dp[node] = tmp+1;
}

void reLoad(int node,int val){
    vector<int> v; v.clear();

    foreach(list[node]){
        if(!us[*it]) continue;
        v.pb( dp[*it] );
    }
    v.pb(val);

    sort(v.begin(),v.end());
    last[node] = 0;
    int tmp = 0;

    foreach(v){
        if(*it > tmp) tmp++;
        else last[node] = *it;
    }
    dp[node] = tmp+1;
    ans[node] = tmp+1;
}

void vaj(int node){
    us[node] = false;
    foreach(list[node]){
        if(!us[*it]) continue;

        //!----------------

        if(last[node] >= dp[*it]) reLoad(*it,dp[node]);
        else                      reLoad(*it,dp[node]-1);

        //!----------------

        vaj(*it);
    }
}

int main()
{
    freopen("trib.in","r",stdin);
    freopen("trib.out","w",stdout);

    scanf("%d",&n);
    fordef(i,2,n){
        scanf("%d%d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    dfs(1);
    ans[1] = dp[1];

    vaj(1);
    int sol = ans[1];
    fordef(i,1,n) sol=max(sol,ans[i]);
    printf("%d",sol);

    return 0;
}
