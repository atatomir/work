#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 20
#define maxL 30011
#define maxLog (1<<18)
#define c second
#define d first
#define INF 1000000000

long n,i,q,j,conf,act,mask;
char str[maxN][maxL];
long pr[maxN][maxL],len[maxN];
vector<pair<long,long> > list[maxN];

long dp[maxN][maxLog];
long prov[maxN][maxLog];

long Sol,nSol;
bool unable[maxN];

long KMP(long a,long b){
    long i,q;
    long pref[maxL];

    pref[1] = 0; q = 0;
    for(i=1;i<=len[a];i++){
        while(q && str[a][i] != str[b][q+1]) q = pr[b][q];
        if(str[a][i] == str[b][q+1]) q++;
        pref[i] = q;
        if(q == len[b]) {
            mask &= ((1<<n)-1) ^ (1<<(b-1));
            unable[b] = true;
            return 0;
        }
    }
    return len[b] - pref[len[a]];
}

long Calc(long nod,long conf){
    if(dp[nod][conf] == -1){
        dp[nod][conf] = INF;
        for(long i=0;i<list[nod].size();i++){
            long newNod = list[nod][i].d;
            if(conf & 1<<(newNod-1)){
                long newConf = conf ^ (1 << (nod-1));
                if(dp[nod][conf] > Calc(newNod,newConf) + list[nod][i].c){
                    dp[nod][conf] = Calc(newNod,newConf) + list[nod][i].c;
                    prov[nod][conf] = i;
                }
            }
        }
    }
    return dp[nod][conf];
}

int main()
{
    freopen("adn.in","r",stdin);
    freopen("adn.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%s",str[i]+1);

        q=0; len[i] = strlen(str[i]+1);
        for(j=2;j<=len[i];j++){
            while(q && str[i][j] != str[i][q+1]) q = pr[i][q];
            if(str[i][j] == str[i][q+1]) q++;
            pr[i][j] = q;
        }
    }

    mask = (1 << n)-1;

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j) continue;
            if(unable[i] || unable[j]) continue;

            long sizee = KMP(i,j);
            list[i].push_back(make_pair(j,sizee));
        }
    }

    memset(dp,-1,sizeof(dp));
    for(i=1;i<=n;i++) {
        dp[i][1<<(i-1)] = 0;
        prov[i][1<<(i-1)] = 0;
    }

    Sol = INF;
    for(i=1;i<=n;i++){
        if(unable[i]) continue;

        if(Sol > len[i] + Calc(i,mask)){
            Sol = len[i] + Calc(i,mask);
            nSol = i;
        }
    }

    if(Sol == INF){
        for(i=1;i<=n;i++)
            if(!unable[i]){
                Sol = len[i];
                nSol = i; break;
            }
    }

    act = nSol;
    for(i=1;i<=len[act];i++) printf("%c",str[act][i]);

    conf = mask ;
    while(conf){
        if(list[act].size() == 0) break;
        long newNod = list[act][prov[act][conf]].d;
        long need   = list[act][prov[act][conf]].c;

        conf ^= 1 <<(act-1);
        if(conf)
        for(i=len[newNod]-need+1;i<=len[newNod];i++) printf("%c",str[newNod][i]);
        act = newNod;
    }


    return 0;
}
