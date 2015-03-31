#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define maxN 100011
#define mp make_pair
#define xx first
#define yy second

long n,m,s,d,i,C,I,x,y;
vector<long> list[maxN],rlist[maxN];
vector<pair<long,long> > mb,ans;

bool used[maxN];
stack<long> S;
long ap[maxN],def;

void dfs(long node){
    used[node] = true;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(used[newNode]) continue;
        dfs(newNode);
    }
    S.push(node);
}

void dfs2(long node){
    ap[node]=def;
    for(long i=0;i<rlist[node].size();i++){
        long newNode = rlist[node][i];
        if(ap[newNode]) continue;
        dfs2(newNode);
    }
}

void Strong(){
    long i;
    for(i=1;i<=n;i++){
        if(used[i]) continue;
        dfs(i);
    }

    while(!S.empty()){
        long node = S.top(); S.pop();
        if(ap[node]) continue;
        def++; dfs2(node);
    }
}

int main()
{
    freopen("tarnacop.in","r",stdin);
    freopen("tarnacop.out","w",stdout);

    scanf("%ld%ld%ld%ld",&n,&m,&s,&d);
    for(i=1;i<=m;i++){
        scanf("%ld%ld%ld%ld",&x,&y,&C,&I);
        if(C==0) continue;
        if(C==I) {
            mb.push_back(mp(x,y));
            list[y].push_back(x);

            rlist[x].push_back(y);
        } else {
            list[x].push_back(y);
            if(I) list[y].push_back(x);

            if(I)rlist[x].push_back(y);
            rlist[y].push_back(x);
        }
    }

    Strong();
    for(i=0;i<mb.size();i++){
        pair<long,long> edge=mb[i];
        if(ap[edge.xx]!=ap[edge.yy]) ans.push_back(edge);
    }

    sort(ans.begin(),ans.end());
    printf("%ld\n",ans.size());
    for(i=0;i<ans.size();i++) printf("%ld %ld\n",ans[i].xx,ans[i].yy);

    return 0;
}
