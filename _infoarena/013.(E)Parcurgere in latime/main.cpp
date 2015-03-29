#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 100005

long n,m,i,s,x,y;
vector<long> list[maxN];
queue<long> Q;
long dp[maxN];

int main()
{
    freopen("bfs.in","r",stdin);
    freopen("bfs.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&s);
    for(i=1;i<=m;i++) {
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
    }

    dp[s] = 1; Q.push(s);
    while(!Q.empty()){
        x = Q.front(); Q.pop();
        for(i=0;i<list[x].size();i++){
            long newNod = list[x][i];
            if(!dp[newNod]) dp[newNod] = dp[x] + 1,Q.push(newNod);
        }
    }

    for(i=1;i<=n;i++) printf("%ld ",dp[i]-1);
    return 0;
}
