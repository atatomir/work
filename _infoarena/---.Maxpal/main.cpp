#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 2011
#define st first
#define dr second
#define mod 666013
#define mp make_pair

typedef pair<long,long> mPair;

long last,ldir,n;

class Hash{
    public:
        long C[2001011];
        void init(){
            memset(C,-1,sizeof(C));
        }
        inline long getDir(long st,long dr){
            return ((st-1)*(2*n-st+2))/2 + (dr-st+1);
        }
        long count(mPair p){
            ldir =  getDir(p.first,p.second);
            if(C[ldir]==-1) return 0; else return 1;
        }
        void set(mPair p,long ans){
            long dir=getDir(p.first,p.second);
            C[dir]=ans;
        }

};

long i;
long v[maxN];
Hash M,cM;


long cLung(long st,long dr){
    long ans=0;

    if(st == dr) return 1;
    if(st+1==dr) return (v[st]==v[dr])?2:1;
    if(M.count(mp(st,dr))) return M.C[ldir];

    if(v[st]==v[dr]) ans = cLung(st+1,dr-1) + 2;
    else             ans = max(cLung(st+1,dr),cLung(st,dr-1));

    M.set(mp(st,dr),ans);
    return ans;
}

long cCnt(long st,long dr){
    if(st == dr) return 1;
    if(st+1 == dr) return (v[st]==v[dr])?1:2;
    if(cM.count(mp(st,dr))) return cM.C[ldir];

    long ans=0;
    if(v[st]==v[dr]) ans = cCnt(st+1,dr-1) % mod;
    if(cLung(st,dr)==cLung(st+1,dr)) ans = (ans + cCnt(st+1,dr));
    if(cLung(st,dr)==cLung(st,dr-1)) ans = (ans + cCnt(st,dr-1));
    if(cLung(st,dr)==cLung(st+1,dr-1)) ans = (ans - cCnt(st+1,dr-1));
    if(ans < 0) ans += mod;

    while(ans>=mod) ans-=mod;

    cM.set(mp(st,dr),ans);
    return ans;
}

int main()
{
    freopen("maxpal.in","r",stdin);
    freopen("maxpal.out","w",stdout);

    M.init(); cM.init();

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&v[i]);

    printf("%ld %ld",cLung(1,n),cCnt(1,n));

    return 0;
}
