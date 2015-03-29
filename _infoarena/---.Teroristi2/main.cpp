#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 128

struct Must{
    long s,d;
};
Must mp(long _s,long _d){
    Must ans;
    ans.s=_s; ans.d=_d;
    return ans;
}

long n,m,mod,i,k,x,y;
bool used[maxN];
long nor[maxN];
vector<Must> G;
vector<long> list[maxN];

long dp[1<<20];
long C[maxN][maxN];


inline bool check(long state,long id){
    for(long i=0;i<list[id].size();i++){
        long act = list[id][i];
        if((state&(1<<(act-1)))==0) return false;
    }
    return true;
}

inline void Expand(long state){
    long i,bit=1;
    for(i=0;i<k;i++){
        if(i) bit<<=1;
        if((bit&state)) continue;

        if(check(state,i+1)){
            long newState = state | bit;
            dp[newState] += dp[state];
            if(dp[newState]>=mod) dp[newState]-=mod;
        }
    }
}

void makeDP(long state,long pos,long still){
    if(pos==k){
        Expand(state);
        return;
    }

    if(still) makeDP(state|(1<<pos),pos+1,still-1);
    if(k-pos!=still) makeDP(state,pos+1,still);
}

void makeComb(){
    for(long i=1;i<=n;i++){
        C[i][1]=i;
        for(long j=2;j<=i&&j<=k;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
}

int main()
{
    freopen("teroristi2.in","r",stdin);
    freopen("teroristi2.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&mod);
    for(i=1;i<=m;i++){
        scanf("%ld%ld",&x,&y);
        G.push_back(mp(x,y));
        used[x]=used[y]=true;
    }

    for(i=1;i<=n;i++){
        if(!used[i]) continue;
        nor[i]=++k;
    }
    for(i=0;i<G.size();i++){
        long ss = G[i].s;
        long dd = G[i].d;
        list[nor[dd]].push_back(nor[ss]);
    }

    dp[0]=1;
    for(i=0;i<k;i++) makeDP(0,0,i);
    makeComb();

    long long ans= ((long long)C[n][k]*(long long)dp[(1<<k)-1])%mod;
    for(i=2;i<=n-k;i++) ans= (ans*i)%mod;
    printf("%lld",ans);

    return 0;
}
