#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 50005

long n,m,i,x,y,nod;
bool vis[maxN];
long parents[maxN];
vector<long> list[maxN];
queue<long> Q,nQ;

int main()
{
    freopen("sortaret.in","r",stdin);
    freopen("sortaret.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
        parents[y]++;
    }

    for(i=1;i<=n;i++){
        if(!parents[i]){
            nQ.push(i);
        }
    }

    while(!nQ.empty()){
        x = nQ.front();
        nQ.pop();

        Q.push(x);
        while(!Q.empty()){
            nod = Q.front(); Q.pop();
            printf("%ld ",nod);
            for(i=0;i<list[nod].size();i++){
                long newNod = list[nod][i];
                parents[newNod]--;
                if(parents[newNod] == 0) Q.push(newNod);
            }
        }

    }

    return 0;
}
