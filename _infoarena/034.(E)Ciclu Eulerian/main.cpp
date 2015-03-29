#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct muchie{
    long n1,n2;
    bool used;

    muchie operator()(long nn1,long nn2){
        n1 = nn1; n2 = nn2;
        used = false;
        return *this;
    }
}e;

#define maxN 100010

long n,m,i,x,y,cont;
vector<muchie> G;
vector<long> list[maxN];
bool vis[maxN];
long neigh[maxN];

inline long getDir(long nod,long pos){
    pos = list[nod][pos];
    if(G[pos].n1 == nod) return G[pos].n2;
    else return G[pos].n1;
}

void bfs(long nod){
    queue<long> Q;
    vis[nod] =true; Q.push(nod);
    while(!Q.empty()){
        nod = Q.front(); Q.pop();
        for(long i=0;i<list[nod].size();i++){
            long newNod = getDir(nod,i);
            if(!vis[newNod]) {
                vis[newNod] = true;
                Q.push(newNod);
            }
        }
    }
}

inline bool isEuler() {
    for(i=1;i<=n;i++)
        if((!vis[i]) || (neigh[i] % 2))
         return false;
    return true;
}

void Euler(long nod){
    stack<long> S;
    S.push(nod);
    while(!S.empty()){
        nod = S.top();
        bool gasit = false;
        for(long i=0;i<list[nod].size();i++){
            if(G[list[nod][i]].used) {
                list[nod][i] = list[nod][list[nod].size()-1]; list[nod].pop_back();
                i--;
                continue;
            }
            long newNod = getDir(nod,i);
            G[list[nod][i]].used = true;
            list[nod][i] = list[nod][list[nod].size()-1]; list[nod].pop_back();
            S.push(newNod);
            gasit = true;
            break;
        }
        if(!gasit) {
            if(++cont != 1)printf("%ld ",nod);
            if(!gasit) S.pop();
        }
    }
}

int main()
{
    freopen("ciclueuler.in","r",stdin);
    freopen("ciclueuler.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        G.push_back(e(x,y));
        list[x].push_back(i-1); neigh[x]++;
        list[y].push_back(i-1); neigh[y]++;
    }

    bfs(1);

    if(!isEuler()){
        printf("-1");
    } else {
        Euler(1);
    }
    return 0;
}

