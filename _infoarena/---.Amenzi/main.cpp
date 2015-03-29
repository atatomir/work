#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 170
#define nod first
#define cost second
#define maxT 3600
#define mp make_pair

long n,m,k,p,i,x,y,cost;
vector<pair<long,long> > list[maxN];
long dp[maxT][maxN],amenda[maxT][maxN];

void preprocess() {
    long i,t,j;
    dp[0][1] = 0;
    for(i=2;i<=n;i++) dp[0][i] = -1;

    for(t=1;t<=3500;t++){
        for(i=1;i<=n;i++){
            dp[t][i] = dp[t-1][i];
            if(dp[t][i] != -1) dp[t][i] += amenda[t][i];

            long ans = -1;
            for(j=0;j<list[i].size();j++){
                long newNod = list[i][j].nod;
                long newCost = list[i][j].cost;
                if(t - newCost < 0) continue;
                ans = max(ans,dp[t-newCost][newNod]);
            }
            if(ans != -1)
                if(dp[t][i] < ans + amenda[t][i])
                    dp[t][i] = ans + amenda[t][i];
        }
    }
}

int main()
{
    freopen("amenzi.in","r",stdin);
    freopen("amenzi.out","w",stdout);

    scanf("%ld %ld %ld %ld",&n,&m,&k,&p);

    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&cost);
        list[x].push_back(mp(y,cost));
        list[y].push_back(mp(x,cost));
    }

    for(i=1;i<=k;i++){
        scanf("%ld %ld %ld",&x,&y,&cost);
        amenda[y][x] += cost;
    }

    preprocess();

    for(i=1;i<=p;i++){
        scanf("%ld %ld",&x,&y);
        printf("%ld\n",dp[y][x]);
    }

    return 0;
}
