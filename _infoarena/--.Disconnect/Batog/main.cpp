#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
 
using namespace std;
 
#define maxN 100111
#define goBack 10000
 
long N,M,i,x,y;
vector<long> list[maxN];
long par[maxN],lev[maxN];
long S[maxN];
 
bool vis[maxN];
long maxLev,Boss,Smax;
 
void dfsReconf(long nod){
    if(lev[nod] > maxLev) return;
    par[nod] = Boss;
    for(long i=0;i<list[nod].size();i++){
        dfsReconf(list[nod][i]);
    }
}
 
void removeEdge(long a,long b){
    long i;
 
    if(lev[a] > lev[b]) {long t=a;a=b;b=t;}
 
    for(i=0;i<list[a].size();i++){
        if(list[a][i] == b){
            list[a][i] = list[a][list[a].size()-1];
            list[a].pop_back();
            break;
        }
    }
    maxLev = lev[b] + goBack; Boss = b;
    dfsReconf(b);
}
bool query(long a,long b){
    while(par[a] != a) a = par[a];
    while(par[b] != b) b = par[b];
    return a==b;
}
 
void dfs(long nod){
    vis[nod] = true; S[++S[0]] = nod;
    lev[nod] = S[0];
 
    long dest = S[0]-goBack;
    if(dest < 1) dest = 1;
    par[nod] = S[dest];
 
    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i];
        if(vis[newNod]){
            list[nod][i] = list[nod][list[nod].size()-1];
            list[nod].pop_back();
            i--; continue;
        }
        dfs(newNod);
    }
    S[0]--;
}
 
int main()
{
    freopen("disconnect.in","r",stdin);
    freopen("disconnect.out","w",stdout);
 
    scanf("%ld %ld",&N,&M);
    for(i=1;i<N;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }
 
    srand(time(NULL));
    dfs(rand()%N+1);
 
    ////////////////////////////////////////////
    int V = 0;
 
for (int i = 0; i < M; ++i) {
    int type, x, y; scanf("%ld %ld %ld",&type,&x,&y);
 
    int a = x xor V;
    int b = y xor V;
 
    if (type == 1) {
        removeEdge(a, b);
    } else
        if (query(a, b)) {
            printf("YES\n");
            V = a;
        } else {
            printf("NO\n");
            V = b;
        }
}
   /////
}