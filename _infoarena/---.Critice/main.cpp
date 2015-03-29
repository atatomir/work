#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxN 1024
#define itt vector<long>::iterator
#define yep ans.push_back(id[i][j]);

long n,m,i,j,x,y,c;
vector<long> list[maxN];
long C[maxN][maxN],F[maxN][maxN],id[maxN][maxN];
long from[maxN];

bool vis[maxN],rvis[maxN];
queue<long> Q;
vector<long> ans;

bool BF(){
    memset(vis,0,sizeof(vis));

    vis[1]=true; Q.push(1);
    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        if(node==n) continue;
        for(itt it=list[node].begin();it!=list[node].end();it++){
            if(vis[*it] || C[node][*it]==F[node][*it]) continue;
            vis[*it]=true; from[*it]=node;
            Q.push(*it);
        }
    }

    for(itt it=list[n].begin();it!=list[n].end();it++){
        if(!vis[*it]) continue;
        from[n]=*it;

        long mFlow = (1<<30);
        for(long node=n;node!=1;node=from[node])
            mFlow=min(mFlow,C[from[node]][node]-F[from[node]][node]);

        for(long node=n;node!=1;node=from[node]) {
            F[from[node]][node]+=mFlow;
            F[node][from[node]]-=mFlow;
        }
    }

    return vis[n];
}

void maxFlow(){
    while(BF()){}
}
void revBF(){
    memset(rvis,0,sizeof(rvis));

    rvis[n]=true; Q.push(n);
    while(!Q.empty()){
        long node = Q.front(); Q.pop();
        if(node==1) continue;
        for(itt it=list[node].begin();it!=list[node].end();it++){
            if(rvis[*it] || C[*it][node]==F[*it][node]) continue;
            rvis[*it]=true;
            Q.push(*it);
        }
    }
}

int main()
{
    freopen("critice.in","r",stdin);
    freopen("critice.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld%ld%ld",&x,&y,&c);
        list[x].push_back(y);
        list[y].push_back(x);
        C[x][y]+=c; C[y][x]+=c;
        id[x][y] = i; id[y][x] = i;
    }

    maxFlow();
    revBF();

    for(i=1;i<n;i++){
        for(j=i+1;j<=n;j++){
            if(!id[i][j]) continue;
            if(F[i][j]==C[i][j]){
                if(vis[i]&&rvis[j]) yep;
            } else {
                if(F[j][i]!=C[j][i]) continue;
                if(vis[j]&&rvis[i]) yep;
            }
        }
    }

    sort(ans.begin(),ans.end());
    printf("%ld\n",ans.size());
    for(i=0;i<ans.size();i++) printf("%ld\n",ans[i]);

    return 0;
}
