#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxN 150111

long n,m,i,j,x,y,p;
vector<long> list[maxN],rList[maxN],cList[maxN];
bool used[maxN];
long ap[maxN];

stack<long> S;
long cnt;
vector<long> Comp[maxN];

long in[maxN],lung[maxN],l,nr;
vector<long> ext[maxN];
vector<long> ans;

void dfs(long node){
    used[node]=true;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(used[newNode]) continue;
        dfs(newNode);
    }
    S.push(node);
}

void dfsC(long node){
    ap[node] = cnt; Comp[cnt].push_back(node);
    for(long i=0;i<rList[node].size();i++){
        long newNode = rList[node][i];
        if(ap[newNode]) continue;
        dfsC(newNode);
    }
}

void add_comp(long c){
    for(long i=0;i<Comp[c].size();i++)
        ans.push_back(Comp[c][i]);
}

void elim_comp(long c){
    for(long i=0;i<cList[c].size();i++){
        long newComp = cList[c][i];
        if(--in[newComp] == 0) ext[lung[newComp]].push_back(newComp),nr++;
    }
}

int main()
{
    freopen("drumuri5.in","r",stdin);
    freopen("drumuri5.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
        rList[y].push_back(x);
    }

    for(i=1;i<=n;i++){
        if(used[i]) continue;
        dfs(i);
    }

    while(!S.empty()){
        long node = S.top(); S.pop();
        if(ap[node]) continue;

        cnt++;
        dfsC(node);
    }

    for(i=1;i<=n;i++){
        long ap1 = ap[i];
        for(j=0;j<list[i].size();j++){
            long ap2 = ap[list[i][j]];
            if(ap1==ap2) continue;
            cList[ap1].push_back(ap2);
        }
    }

    for(i=1;i<=cnt;i++) {
        if(cList[i].size()==0) continue;
        sort(cList[i].begin(),cList[i].end());
        p=1; in[cList[i][0]]++;
        for(j=1;j<cList[i].size();j++)
            if(cList[i][j]!=cList[i][j-1]){
                cList[i][p++] = cList[i][j];
                in[cList[i][j]]++;
            }
        cList[i].resize(p);
    }

    for(i=cnt;i;i--){
        lung[i] = 1;
        for(j=0;j<cList[i].size();j++){
            long newNode = cList[i][j];
            lung[i] = max(lung[i],lung[newNode]+1);
        }
    }

    for(i=1;i<=cnt;i++)
        if(in[i]==0)
            ext[lung[i]].push_back(i),nr++;

    for(l=cnt;l;l--){
        if(ext[l].size()==0)continue;
        if(nr==1){
            add_comp(ext[l][0]);
        }

        for(i=0;i<ext[l].size();i++){
            elim_comp(ext[l][i]);
            nr--;
        }
    }


    sort(ans.begin(),ans.end());
    printf("%ld\n",ans.size());
    for(i=0;i<ans.size();i++) printf("%ld ",ans[i]);

    return 0;
}
