#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back

#define maxN 21011

int n,t,m,i,x,y;
vector<int> list[maxN];
int lvl[maxN];
queue<int> Q;

int bfs(){
    int i,j;
    int ans = 1;

    lvl[1] = 1;
    while(!Q.empty()) Q.pop();
    Q.push(1);

    while(!Q.empty()){
        int node = Q.front(); Q.pop();

        foreach(list[node]){
            if(lvl[*it]) continue;
            lvl[*it] = lvl[node]+1;
            ans = max(ans,lvl[*it]);

            Q.push(*it);
        }
    }

    return ans;
}

int main()
{
    freopen("amici2.in","r",stdin);
    freopen("amici2.out","w",stdout);

    for(scanf("%d",&t);t--;){
        scanf("%d%d",&n,&m);
        fordef(i,1,n) { list[i].clear();lvl[i]=0; }
        fordef(i,1,m){
            scanf("%d%d",&x,&y);
            list[y].push_back(x);
            list[x].push_back(y);
        }

        int how = bfs();
        for(i=0;(1<<i) < how;i++) ;
        printf("%d\n",i);
    }


    return 0;
}
