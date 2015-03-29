#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 50010
#define n1 first
#define n2 second
#define mp make_pair

long n,m,i,x,y,cont,j,pos;
vector<long> list[maxN];
bool used[maxN];
long grad[maxN];
vector<pair<long,long> > G;

vector<long> loc,tmp;
vector<vector<long> > ans;

inline long getDir(long nod,long edge){
    if(G[edge].first == nod) return G[edge].second;
    return G[edge].first;
}

void dfs(long nod){
    used[nod] = true;
    if(grad[nod]&1) {
        cont++;
        G.push_back(mp(nod,n+1));
        list[nod].push_back(G.size()-1);
        list[n+1].push_back(G.size()-1);
    }
    for(long i=0;i<list[nod].size();i++){
        long newNod = getDir(nod,list[nod][i]);
        if(!used[newNod]) dfs(newNod);
    }
}

void Euler(long nod){
    long i;
    for(i=0;i<list[nod].size();i++){
        if(G[list[nod][i]].first == -1){
            list[nod][i] = list[nod][list[nod].size()-1]; list[nod].pop_back();
            i--; continue;
        }

        long newNod = getDir(nod,list[nod][i]);
        G[list[nod][i]].first = -1;
        Euler(newNod);
    }
    loc.push_back(nod);
}

int main()
{
    freopen("johnie.in","r",stdin);
    freopen("johnie.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        G.push_back(mp(x,y));

        list[x].push_back(i-1); grad[x]++;
        list[y].push_back(i-1); grad[y]++;
    }

    for(i=1;i<=n;i++){
        if(!used[i]){
            cont = 0; loc.clear();
            dfs(i);

            if(!cont) Euler(i); else Euler(n+1);
            if(!cont){
                ans.push_back(loc);
            } else {
                cont >>= 1;
                pos = 1;

                for(j=1;j<=cont;j++){
                    tmp.clear();
                    while(loc[pos] != n+1) tmp.push_back(loc[pos++]);
                    pos++;

                    ans.push_back(tmp);
                }
            }
        }
    }

    cont = ans.size();
    for(i=0;i<ans.size();i++)
        if(ans[i].size()==1) cont--;

    printf("%ld\n",cont);
    for(i=0;i<ans.size();i++){
        if(ans[i].size() == 1) continue;

        printf("%ld ",ans[i].size());
        for(j=0;j<ans[i].size();j++) printf("%ld ",ans[i][j]);
        printf("\n");
    }

    return 0;
}
