#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 100011

long n,m,i,x,y;
bool vis[maxN];
long C[maxN];
vector<long> list[maxN];

long s[maxN];
bool found;

void dfs(long nod,long col){
    vis[nod] = true; C[nod] = col;
    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i];
        if(vis[newNod]) continue;
        dfs(newNod,col);
    }
}

void dfsCic(long nod){
    if(found) return;
    vis[nod] = true; s[++s[0]] = nod;

    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i];
        if(found) return;

        if(newNod == s[s[0]] || newNod == s[s[0]-1]) continue;
        if(!vis[newNod]){
            dfsCic(newNod);
        } else {
            found = true;
            long j;

            for(j=1;j<=n;j++) vis[j] = 0;
            vis[s[s[0]]] = vis[s[s[0]-1]] = vis[s[s[0]-2]] = true;
            C[s[s[0]]] = 1; C[s[s[0]-1]] = 2; C[s[s[0]-2]] = 3;

            dfs(s[s[0]],1); dfs(s[s[0]-1],2); dfs(s[s[0]-2],3);

            return;
        }
    }

    s[0]--;
}

int main()
{
    freopen("something.in","r",stdin);
    freopen("something.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    s[0] = 2;
    dfsCic(1);

    if(!found){
        printf("-1");
        return 0;
    }
    for(i=1;i<=n;i++) printf("%ld ",C[i]);
    return 0;
}
