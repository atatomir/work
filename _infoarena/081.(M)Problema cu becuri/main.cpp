#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 100005

long n,m,k,i,x,y;
vector<long> list[maxN];
queue<long> Q;
long dp[maxN];

int main()
{
    freopen("pcb.in","r",stdin);
    freopen("pcb.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        list[x-1].push_back(y);
        list[y].push_back(x-1);
    }

    dp[0] = 1; Q.push(0);
    while(!Q.empty()){
        x = Q.front(); Q.pop();
        if(x == k) break;
        for(i=0;i<list[x].size();i++){
            long newNod = list[x][i];
            if(!dp[newNod]){
                dp[newNod] = dp[x]+1;
                Q.push(newNod);
            }
        }
    }

    printf("%ld",dp[k]-1);

    return 0;
}
