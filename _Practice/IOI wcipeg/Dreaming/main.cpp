#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

//#define DEBUG @atatomir
#define maxN 100011
#define PI pair<long,long>
#define mp make_pair
#define dir first
#define cc second

long n,m,i,x,y,z;
vector< PI > list[maxN];
vector< PI > tmp;
bool us[maxN],del[maxN];
long long dp[maxN],dpup[maxN];
long long l,vv,def,rez;

vector<long long> ans;

//! find d max
long wh=0;
long long lvl[maxN],dd;
void findDeepest(long node){
    if(wh==0 || lvl[wh]<lvl[node]) wh=node;
    for(long i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(lvl[act.dir]) continue;
        lvl[act.dir] = lvl[node]+1LL*act.cc;
        findDeepest(act.dir);
    }
}
void findLvl(long node){
    dd=min(dd,lvl[node]);
    for(long i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(lvl[act.dir]<=0) continue;
        lvl[act.dir] = lvl[node]-act.cc;
        findLvl(act.dir);
    }
}
//!....

bool cmp(const PI& a,const PI& b){
    return 1LL+dp[a.dir]+a.cc > 1LL+dp[b.dir]+b.cc;
}

bool usUpper[maxN];
void dfsUpper(long node){


    if(usUpper[node]) return;
    usUpper[node]=true;

    tmp.clear();
    for(long i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(usUpper[act.dir]) continue;
        tmp.push_back(act);
    }

    sort(tmp.begin(),tmp.end(),cmp);
    if(tmp.size())
    if(tmp.size()==1) dpup[tmp[0].dir] = dpup[node]+tmp[0].cc; else{
        dpup[tmp[0].dir] = max(dpup[node]+tmp[0].cc , dp[tmp[1].dir]+tmp[0].cc+tmp[1].cc );
        for(long i=1;i<tmp.size();i++)
            dpup[tmp[i].dir] = max(dpup[node]+tmp[i].cc , dp[tmp[0].dir]+tmp[0].cc+tmp[i].cc );
    }

    for(long i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(usUpper[act.dir]) continue;
        dfsUpper(act.dir);
    }
}
void dfs(long node){
    if(us[node]) return;
    if(del[node]) return;
    us[node]=true;
    dp[node]=0; tmp.clear();
    for(long i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(us[act.dir]) continue;

        dfs(act.dir);
        dp[node] = max(dp[node],  dp[act.dir]+1LL*act.cc);
    }
}
void dfsBest(long node){
    if(!us[node]) return;
    us[node]=false;
    del[node]=true;

    long long valMax=0;

    for(long i=0;i<list[node].size();i++){
        PI act = list[node][i];
        if(!us[act.dir]) continue;
        dfsBest(act.dir);

        valMax=max(valMax,dp[act.dir]+1LL*act.cc);
    }
    valMax = max(valMax,dpup[node]);

    vv = min(valMax,vv);
}
void solve(long node){
    dfs(node);
    dfsUpper(node);
    vv = (1LL<<55);
    dfsBest(node);


    ans.push_back(vv);

    //! fa diametrul
    lvl[node]=1; dd=1;
    findDeepest(node); lvl[wh]=0;
    findLvl(wh);
    dd*=-1;
    rez = max(rez,dd);
}

long getMax(){
    long pos=-1;
    long long val = -1;
    for(long i=0;i<ans.size();i++){
        if(val < ans[i]){
            val=ans[i];
            pos=i;
        }
    }
    return pos;
}


int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld",&n,&m,&l);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&z); x++;y++;
        list[x].push_back( mp(y,z) );
        list[y].push_back( mp(x,z) );
    }

    rez = 0;
    for(i=1;i<=n;i++)
        if(!del[i])
            solve(i);

    if(ans.size()==1) printf("%lld",rez); else
    if(ans.size()==2) printf("%lld",max(rez,  ans[0]+ans[1]+l)); else{
        long pos;
        long long aa,bb,cc;

        pos = getMax();
        aa = ans[pos]; ans[pos] = -1;
        pos = getMax();
        bb = ans[pos]; ans[pos] = -1;
        pos = getMax();
        cc = ans[pos]; ans[pos] = -1;

        rez = max(rez,aa+bb+l);
        rez = max(rez, cc + max(aa,bb+l)+l );

        printf("%lld",rez);
    }

    //for(i=1;i<=n;i++) cerr << dpup[i] << '\n';

    return 0;
}


