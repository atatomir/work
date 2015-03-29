#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 20
#define maxBit 18
#define d first
#define c second
#define INF 1000000000

long n,m,i,x,y,cost;
vector<pair<long,long> > list[maxN];
long dp[maxN][1<<maxBit];

long Calc(long nod,long conf){
    if(dp[nod][conf] == -1){
        dp[nod][conf] = INF;
        for(long i=0;i<list[nod].size();i++){
            long newNod = list[nod][i].d;
            if((1<<newNod) & conf){
                long newConf = conf ^ (1<<nod);
                if(newConf != 1 && newNod == 0) continue;
                dp[nod][conf] = min(dp[nod][conf],Calc(newNod,newConf) + list[nod][i].c);
            }
        }
    }
    return dp[nod][conf];
}

int main()
{
    freopen("hamilton.in","r",stdin);
    freopen("hamilton.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&cost);
        list[y].push_back(make_pair(x,cost));
    }

    memset(dp,-1,sizeof(dp));
    dp[0][1] = 0;

    long sol = INF;
    for(i=0;i<list[0].size();i++){
        sol = min(sol,Calc(list[0][i].d,(1<<n)-1)+list[0][i].c);
    }

    if(sol == INF)
        printf("Nu exista solutie");
    else
        printf("%ld",sol);

    return 0;
}
