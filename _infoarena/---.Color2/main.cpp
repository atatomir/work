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
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 16033

int n,i,x,y;
vector<int> list[maxN];
bool us[maxN];
int how[maxN][2];
int tip[maxN];
vector<int> ans;

void dfs(int node){
    us[node] = true;
    how[node][0] = how[node][1] = 0;

    foreach(list[node]){
        if(us[*it]) continue;
        dfs(*it);

        how[node][ tip[*it] ]++;
    }
    if(how[node][1]) tip[node]=0;
    else             tip[node]=1;
}

void move(int S,int D){
    how[S][ tip[D] ]--;
    if(how[S][1]) tip[S]=0;
    else          tip[S]=1;

    how[D][ tip[S] ]++;
    if(how[D][1]) tip[D]=0;
    else          tip[D]=1;
}

void smen(int node){
    us[node]=true;
    if(tip[node]) ans.pb(node);

    foreach(list[node]){
        if(us[*it]) continue;

        move(node,*it);
        smen(*it);
        move(*it,node);
    }
}


int main()
{
    freopen("color2.in","r",stdin);
    freopen("color2.out","w",stdout);

    scanf("%d",&n);
    fordef(i,2,n){
        scanf("%d%d",&x,&y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);

    memset(us,0,sizeof(us));
    smen(1);

    sort(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    foreach(ans) printf("%d ",*it);

    return 0;
}
