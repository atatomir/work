#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 16011
#define foreach(V) for(auto it=V.begin();it!=V.end();it++)

int n,k,i,x,y;
vector<int> list[maxN];
int R[maxN];

bool us[maxN];
int V[maxN];
int sum[maxN];

int ans;
vector<int> sol;

int FromTo(int s,int d){
    if(s>d) d+=k;
    return d-s;
}

void dfsIni(int node){
    us[node]=true;
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i];
        if(us[newNode]){
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back();
            i--; continue;
        }

        V[newNode] = FromTo(R[node],R[newNode]);
        sum[1] += V[newNode];
        dfsIni(newNode);
    }
}

void dfs(int node){
    //! sum[node] is already computed

    foreach(list[node]){
        sum[*it] = sum[node] ;

        sum[*it] -= R[node];
        sum[*it] += R[*it];

        sum[*it] -= FromTo(R[node],R[*it]);
        sum[*it] += FromTo(R[*it],R[node]);

        if(sum[*it] == ans) sol.push_back(*it); else
        if(sum[*it] <  ans){
            ans = sum[*it];
            sol.clear(); sol.push_back(*it);
        }

        dfs(*it);
    }
}

int main()
{
    freopen("asmin.in","r",stdin);
    freopen("asmin.out","w",stdout);

    scanf("%d %d",&n,&k);
    for(i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }
    for(i=1;i<=n;i++) scanf("%d",&R[i]);

    sum[1] = V[1] = R[1];
    dfsIni(1);

    ans = sum[1];
    sol.clear(); sol.push_back(1);
    dfs(1);

    sort(sol.begin(),sol.end());
    printf("%d %d\n",ans,sol.size());
    foreach(sol) printf("%d ",*it);

    return 0;
}
