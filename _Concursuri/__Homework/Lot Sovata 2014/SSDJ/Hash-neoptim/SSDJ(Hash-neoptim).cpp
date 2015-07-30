#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define bigPair pair<pair<long,long>,pair<long,long> >
#define mod 167397
#define ff first
#define ss second

class Hash{
    public:
        vector<bigPair > C[mod];
        void init(){
            for(long i=0;i<mod;i++) C[i].clear();
        }
        long getId(bigPair p){
            long idd = p.ff.ff*p.ss.ss + p.ff.ss + p.ss.ff;
            return idd%mod;
        }
        bool isIn(bigPair p){
            long id = getId(p);
            for(long i=0;i<C[id].size();i++)
                if(C[id][i]==p) return true;
            return false;
        }
        void addIn(bigPair p){
            long id = getId(p);
            C[id].push_back(p);
        }
};

#define maxN 1011
#define INF 5000
#define mmp make_pair

struct Line{
    long pos,h;
};
Line mp(long ppos,long hh){
    Line tmp;
    tmp.pos = ppos; tmp.h = hh;
    return tmp;
}

long n,i,j,k,ans;
char a[maxN][maxN];
long dp[maxN][maxN];
char ch;

Line S[maxN];
long cnt;

void make_dp(){
    long i,j;
    for(i=1;i<=n;i++) dp[0][i] = INF;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(a[i][j]>ch)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i-1][j]+1;
        }
    }
}

int main()
{
    freopen("ssdj.in","r",stdin);
    freopen("ssdj.out","w",stdout);

    Hash H; H.init();

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%s\n",a[i]+1);

    for(ch='a';ch<'z';ch++){
        memset(dp,0,sizeof(dp));
        make_dp();

        for(i=1;i<=n;i++){
            cnt = 0;
            for(j=1;j<=n;j++){
                if(a[i][j]<=ch){ //!! 0
                    if(cnt)
                    while(S[cnt].h>=dp[i][j]){
                        cnt--;
                        if(cnt==0) break;
                    }
                    S[++cnt] = mp(j,dp[i][j]);
                } else { //!! 1
                    long hT = dp[i-1][j]+1;
                    if(cnt)
                    while(S[cnt].h>=hT){
                        cnt--;
                        if(cnt==0) break;
                    }

                    for(k=1;k<=cnt;k++){
                        long x1 = i-S[k].h+1;
                        long y1 = S[k].pos;

                        if(S[k].h>=INF) continue;

                        pair<long,long> p1 = mmp(x1,y1);
                        pair<long,long> p2 = mmp(i,j);

                        if(H.isIn(mmp(p1,p2))) continue;
                        H.addIn(mmp(p1,p2));
                        ans++;
                    }

                    cnt=0;
                }
            }
        }
    }

    printf("%ld",ans);

    return 0;
}
