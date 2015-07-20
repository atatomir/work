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

#define maxN 100011

int n,m,i,x,y,c,R;
vector< pair<int,int> > list[maxN];
int cc[maxN];
int valid[maxN];
long long dp[maxN],ans;

bool us[maxN];

void dfs_del(int node){
    us[node] = true;
    foreach(list[node]){
        if(us[it->first]) continue;
        dfs_del(it->first);
        valid[node] += valid[it->first];
    }
}

void make_dp(int node){
    us[node] = true;
    dp[node] = 0;

    foreach(list[node]){
        if(us[it->first]) continue;

        make_dp(it->first);
        dp[node] += dp[it->first] + 2LL*it->second;
        dp[node] += 1LL*cc[node];
    }
}

void clean(int node){
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i].first;
        if(!valid[newNode]){
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back();
            i--;
        }
    }
}

void move(int dir,int edge){
    dp[R] -= 2LL*edge+cc[R] + dp[dir];
    dp[dir] += 2LL*edge+cc[dir] + dp[R];

    swap(R,dir);
}

void dfs(int node){
    //! R == node
    long long cnt = list[R].size();
    ans = min(ans, dp[R]-cc[R]*cnt );
    us[node] = true;

    foreach(list[node]){
        if(us[it->first]) continue;

        move(it->first,it->second);
        dfs(it->first);
        move(node,it->second);
    }
}

int main()
{
    freopen("posta2.in","r",stdin);
    freopen("posta2.out","w",stdout);

    scanf("%d%d",&n,&m);
    fordef(i,1,n-1){
        scanf("%d%d%d",&x,&y,&c);
        list[x].pb(mp(y,c));
        list[y].pb(mp(x,c));
    }
    fordef(i,1,n) scanf("%d",&cc[i]);
    fordef(i,1,m){
        scanf("%d",&x);
        if(!R) R = x;
        valid[x]++;
    }

    memset(us,0,sizeof(us));
    dfs_del(R);
    for(int i=1;i<=n;i++) clean(i);
    //! dont use the nodes with valid==0

    memset(us,0,sizeof(us));
    make_dp(R);

    ans = dp[R] - cc[R]*list[R].size();
    memset(us,0,sizeof(us));
    dfs(R);

    printf("%lld",ans);
    cerr << ans;

    return 0;
}
