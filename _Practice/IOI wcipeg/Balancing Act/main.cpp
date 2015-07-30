#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 20011

int n,i,x,y;
vector<int> list[maxN];
int dad[maxN],dpDown[maxN],dpUp[maxN],dpMax[maxN];

int ans,ansid;

void dfs(int node){
    dpDown[node]=1;
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i];

        if(dad[newNode]!=0) {
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back();
            i--; continue;
        }

        dad[newNode] = node; dfs(newNode);
        dpDown[node] += dpDown[newNode];
    }
}

void dfsUp(int node){
    for(int i =0;i<list[node].size();i++){
        int newNode = list[node][i];
        dpUp[newNode] = dpUp[node]+ dpDown[node]-dpDown[newNode] ;
        dfsUp(newNode);
    }

}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%d",&n);
    for(i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    dad[1] = -1;
    dfs(1);

    dpUp[1] = 0;
    dfsUp(1);

    for(i=1;i<=n;i++)
        for(int j=0;j<list[i].size();j++)
            dpMax[i] = max(dpMax[i], dpDown[ list[i][j] ] );

    ans = 20001;
    for(i=1;i<=n;i++){
        int cc = max(dpUp[i],dpMax[i]);
        if(cc<ans) {
            ans = cc;
            ansid = i;
        }
    }

    printf("%d %d",ansid,ans);

    return 0;
}
