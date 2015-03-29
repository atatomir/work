#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 19

long t,n,m,i,lim,x,y;
long dp[1<<maxN],rLow[maxN],rHigh[maxN],rComp[maxN];
long Answer=0;

long cBiti(long conf){
    long ans=0;
    while(conf){
        ans++;
        conf = conf&(conf-1);
    }
    return ans;
}

bool check(long conf){
    long deny=0;
    for(long i=0;i<lim;i++){
        if(conf & (1<<i)){
            deny |= rLow[i+1];
        }
        if(deny&conf) return false;
    }
    return true;
}

void Try(long pas,long conf,long deny,long denyComp){
    if(pas+lim==n+1){
        long useful = ((1<<lim)-1)^denyComp;
        long ans = cBiti(conf) + dp[useful];

        Answer = max(ans,Answer);
    } else {
        long newDeny = deny | rHigh[pas];
        long newConf = conf | (1<<(pas-1));

        if((newConf&newDeny) == 0) Try(pas+1,newConf,newDeny,denyComp | rComp[pas]);
        Try(pas+1,conf,deny,denyComp);
    }
}

int main()
{
    freopen("alianta.in","r",stdin);
    freopen("alianta.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld %ld",&n,&m); lim=n/2; Answer=0;
        memset(dp,0,sizeof(dp));
        memset(rLow,0,sizeof(rLow));
        memset(rHigh,0,sizeof(rHigh));
        memset(rComp,0,sizeof(rComp));

        for(i=1;i<=m;i++){
            scanf("%ld%ld",&x,&y);
            if(x>y) swap(x,y);
            if(y<=lim){
                rLow[x] |= 1 << (y-1);
                rLow[y] |= 1 << (x-1);
            }
            if(x>lim){
                x-=lim; y-=lim;
                rHigh[x] |= 1 << (y-1);
                rHigh[y]  |= 1 << (x-1);
            }
            if(x<=lim && y > lim){
                rComp[y-lim] |= 1 << (x-1);
            }
        }

        for(long conf=0;conf<(1<<lim);conf++){
            if(check(conf)){
                dp[conf] = cBiti(conf);
            } else {
                for(i=0;i<lim;i++){
                    if(conf & (1<<i)){
                        dp[conf] = max(dp[conf],dp[conf^(1<<i)]);
                    }
                }
            }
        }

        Try(1,0,0,0);
        printf("%ld\n",Answer);
    }


    return 0;
}
