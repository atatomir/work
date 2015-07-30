#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

//#define DEBUG
#define maxN 200011
#define INF (1<<30)
#define PI pair<long,long long>
#define mp make_pair
#define dir first
#define cc second

#define modH 375
class Hash{
    private:
        vector<PI> C[modH];
        long getId(long long xx){
            return xx%modH;
        }

    public:
        void init(){
            for(long i=0;i<modH;i++) C[i].clear();
        }
        long isThere(long long v){
            long key = getId(v);
            for(long i=0;i<C[key].size();i++)
                if(C[key][i].cc == v) return i;
            return -1;
        }
        void add(PI act){
            long key = getId(act.cc);
            long wh = isThere(act.cc);
            if(wh==-1) C[key].push_back(act);
            else C[key][wh] = act;
        }
        long getValue(long long v){
            long key = getId(v);
            for(long i=0;i<C[key].size();i++)
                if(C[key][i].cc == v) return C[key][i].dir;
            return -1;
        }
};

long n,m,i,x,y,ans=INF;
vector< PI > list[maxN];
bool del[maxN];
long long k,v;

Hash H;
vector< PI > lazy;

//! This is used to find the Root
long target,allSums;
long us[maxN],idUs;
long tmp[maxN];
void dfsRoot(long node){
    if(us[node] == idUs || del[node]) return;
    long i;
    us[node]=idUs;

    tmp[node]=1;
    for(i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(us[act.dir] == idUs || del[act.dir]) continue;
        dfsRoot(act.dir);

        tmp[node] += tmp[act.dir];
    }
}
long dfsGood(long node){
    if(us[node] == idUs || del[node]) return -1;
    long i,mm;
    us[node]=idUs; mm=-1;

    bool isGood=true;
    for(i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(us[act.dir]==idUs || del[act.dir]) continue;
        mm = max( dfsGood(act.dir) , mm);

        if(tmp[act.dir] > target) isGood=false;
    }
    if(allSums-tmp[node] > target) isGood=false;
    if(isGood) mm = node;
    return mm;
}
long findRoot(long S){
    long i;
    idUs++;

    dfsRoot(S);
    allSums = tmp[S];
    target = allSums/2;

    idUs++;
    return dfsGood(S);
}
//! -----------------------------

void dfsForWin(long node,long long vv,long cnt){
    if(del[node]) return;
    if(vv>k) return;
    if( H.getValue(k-vv) != -1 ) ans = min(ans, H.getValue(k-vv)+cnt );
    lazy.push_back( mp(cnt,vv) );
    us[node] = idUs;

    for(long i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(us[act.dir]!=idUs) dfsForWin(act.dir,vv+act.cc,cnt+1);
    }
}

void solve(long node){
    if(del[node]) return;

    long R = findRoot(node);
    H.init(); H.add(mp(INF,k)); H.add(mp(0,0));
    for(long i=0;i<list[R].size();i++){
        PI act = list[R][i];
        lazy.clear();
        idUs++; us[R]=idUs;
        dfsForWin(act.dir,act.cc,1);
        for(long j=0;j<lazy.size();j++){
            PI who = lazy[j];
            if(H.getValue(who.cc)==-1)
                H.add(mp(who.dir,who.cc));
            else
            if(H.getValue(who.cc) > who.dir)
                H.add(mp(who.dir,who.cc));
        }
    }

    del[R] = true;
    for(long i=0;i<list[R].size();i++){
        PI act = list[R][i];
        solve(act.dir);
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %lld",&n,&k);
    m=n-1;
    for(i=1;i<=m;i++){
        scanf("%ld %ld %lld",&x,&y,&v); x++;y++;
        list[x].push_back( mp(y,v) );
        list[y].push_back( mp(x,v) );
    }

    solve(1);
    if(ans==INF) ans =-1;
    printf("%ld",ans);

    return 0;
}
