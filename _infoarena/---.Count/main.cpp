#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>

using namespace std;

#define maxN 30011
#define itt set<long>::iterator

long n,m,i,x,y,node,j;
set<long> list[maxN];
long gr[maxN];

long long ans[10];
queue<long> Q;

bool us[10],alrdn[maxN];
long tot;

bool Check(){
    vector<long> nodes; nodes.clear(); nodes.push_back(node);
    long i,j;

    itt it=list[node].begin();
    for(i=0;i<list[node].size();i++,it++){
        if(!us[i]) continue;
        nodes.push_back(*it);
    }

    for(i=0;i<nodes.size();i++){
        for(j=i+1;j<nodes.size();j++){
            if(!list[nodes[i]].count(nodes[j])) return false;
        }
    }
    return true;
}

void Try(long pas){
    if(pas==list[node].size()){
        if(tot!=2 && tot!=3) return;
        if(Check()){
            if(tot==2) ans[3]++;
            else       ans[4]++;
        }

        return;
    }

    tot++; us[pas] = true; Try(pas+1);
    tot--; us[pas] = false; Try(pas+1);
}

int main()
{
    freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        gr[x]++; gr[y]++;
        list[x].insert(y);
        list[y].insert(x);
    }

    ans[1]= n; ans[2] = m;
    ans[3] = ans[4] = 0;

    for(i=1;i<=n;i++) if(list[i].size()<=5) {Q.push(i);alrdn[i]=true;}

    while(!Q.empty()){
        //! Incerc sa formez subgrafuri complete
        node = Q.front(); Q.pop();
        if(list[node].size()<2) continue;
        Try(0);

        //! Elimin nodul
        for(itt it=list[node].begin();it!=list[node].end();it++){
            long newNode = *it;

            gr[newNode]--;
            list[newNode].erase(node);
        }

        //! Adaug noduri noi in coada
        for(itt it=list[node].begin();it!=list[node].end();it++){
            long newNode = *it;

            if(alrdn[newNode]) continue;
            if(list[newNode].size()==5) {
                Q.push(newNode);
                alrdn[newNode] = true;
            }
        }
    }

    if(ans[4]) printf("%ld %lld",4,ans[4]); else
    if(ans[3]) printf("%ld %lld",3,ans[3]); else
               printf("%ld %lld",2,ans[2]);

    return 0;
}
