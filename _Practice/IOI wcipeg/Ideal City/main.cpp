#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;

//#define DEBUG
#define maxN 100011
#define x first
#define y second
#define mp make_pair
#define mod 1000000000

long n,i;
pair<long,long> P[maxN];
long long ans;
long cnt;

class Hash{
    private:
        #define hMod 130133
        vector< pair<long,long> > C[hMod];

        inline long getKey(long act){
            return ( P[act].x + P[act].y )%hMod;
        }
        inline long getKeyPro( pair<long,long>& pct ){
            return (pct.x+pct.y)%hMod;
        }

    public:
        void init(){
            for(long i=0;i<hMod;i++) C[i].clear();
        }
        void add(long id,long Gid){
            C[ getKey(id) ].push_back( mp(id,Gid) );
        }
        long get( pair<long,long> pct ){
            long key = getKeyPro(pct);
            for(long i=0;i<C[key].size();i++)
                if( pct == P[ C[key][i].first ] ) return C[key][i].second;
            return 0;
        }
};

Hash H;
vector<long> list[maxN];
long long how[maxN],howi[maxN];
long long dp[maxN];
bool us[maxN];

void normalize(long id){
    return ;
    //! nothing useful to be done


    sort(list[id].begin(),list[id].end());
    long how = 1;
    for(long i=1;i<list[id].size();i++){
        if(list[id][i-1] != list[id][i])
            list[id][how++] = list[id][i];
    }
    list[id].resize(how);
}

void dfs(long node){
    us[node] = true;
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(us[newNode]) {
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back();
            i--; continue;
        }
        dfs(newNode);
        how[node] += how[newNode];
        if(how[node] >= mod) how[node] -= mod;
    }

    for(long i=0;i<list[node].size();i++){
        long Node1 = list[node][i];
        for(long j=i+1;j<list[node].size();j++){
            long Node2 = list[node][j];

            ans += (2LL*how[Node1]*how[Node2])%mod;
            ans += (1LL*how[Node1]*dp[Node2])%mod;
            ans += (1LL*how[Node2]*dp[Node1])%mod;
            ans %= mod;
        }

        dp[node] += dp[Node1] + how[Node1];
        while(dp[node]>=mod) dp[node] -= mod;
    }

    ans += (dp[node]*howi[node])%mod;
    if(ans >= mod) ans -= mod;
}

void do_magic(){
    long i;

    sort(P+1,P+n+1); H.init();
    cnt=0;
    for(i=0;i<maxN;i++) {list[i].clear(),how[i]=0;}

    for(long pos=1;pos<=n;pos++){
        long dpos=pos; cnt++;
        while(dpos<n && P[dpos].x == P[dpos+1].x && P[dpos].y+1==P[dpos+1].y) dpos++;
        how[cnt] = howi[cnt] = dpos-pos+1;
        for(i=pos;i<=dpos;i++) {
            H.add( i,cnt );
            long rez = H.get( mp(P[i].x-1,P[i].y) );
            if(rez) {
                list[rez].push_back(cnt);
                list[cnt].push_back(rez);
            }
        }

        pos = dpos;
    }

    for(i=1;i<=cnt;i++) {normalize(i);us[i]=false;dp[i]=0;}
    for(i=1;i<=cnt;i++){
        if(us[i]) continue;
        dfs(i);
        break;
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld %ld",&P[i].x,&P[i].y);

    do_magic();
    //! ...
    for(i=1;i<=n;i++) swap( P[i].x,P[i].y );
    //! ...
    do_magic();

    printf("%lld",ans);

    return 0;
}
