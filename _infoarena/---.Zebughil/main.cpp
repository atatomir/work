#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 17

long n,i,G;
long g[maxN+11];
long cnt[1<<maxN],act[1<<maxN];

long antCnt,antAct;

void solveIt(){
    scanf("%ld%ld",&n,&G);
    memset(cnt,0,sizeof(cnt));
    memset(act,0,sizeof(act));
    cnt[0]=0; act[0] = G+1;

    for(i=1;i<=n;i++) scanf("%ld",&g[i]);
    for(long conf=1;conf<(1<<n);conf++){
        for(i=0;i<n;i++){
            if(conf&(1<<i)){
                antCnt = cnt[conf]; antAct = act[conf];
                if(antCnt==0) antCnt = 25;

                long newConf = conf ^ (1<<i);
                if(act[newConf] + g[i+1]<=G){
                    act[conf] = act[newConf] + g[i+1];
                    cnt[conf] = cnt[newConf];
                } else {
                    act[conf] = g[i+1];
                    cnt[conf] = cnt[newConf]+1;
                }

                if(cnt[conf]>antCnt || (cnt[conf]==antCnt && act[conf]>antAct)){
                    cnt[conf] = antCnt;
                    act[conf] = antAct;
                }
            }
        }
    }

    printf("%ld\n",cnt[(1<<n)-1]);
}

int main()
{
    freopen("zebughil.in","r",stdin);
    freopen("zebughil.out","w",stdout);

    for(long testC=3;testC;testC--){
        solveIt();
    }

    return 0;
}
