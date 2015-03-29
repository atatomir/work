#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 100011
#define maxLog 19

long N,M,i,x,y;

#define maxBuf 1000000
char Buff[maxBuf];
long pos;
inline bool isDigit(char c){
    return c >= '0' && c <= '9';
}
long getLong(){
    while(!isDigit(Buff[pos])) {
        pos++;
        if(pos == maxBuf) {
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    long Ans=0;
    while(isDigit(Buff[pos])) {
        Ans = Ans*10 + Buff[pos++] - '0';
        if(pos == maxBuf) {
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    return Ans;
}

struct AIB{
    long c[maxN<<1];
    long dim;

    void init(){
        for(long i=0;i<maxN<<1;i++) c[i] = 0;
        dim = 0;
    }

    inline long zeros(long x){
        return (x^(x-1))&x;
    }
    void change(long pos,long val){
        while(pos<=N*2){
            c[pos] += val;
            pos += zeros(pos);
        }
    }
    long getIt(long pos){
        long ans = 0;
        while(pos){
            ans += c[pos];
            pos -= zeros(pos);
        }
        return ans;
    }
    long sum(long a,long b){
        return getIt(b)-getIt(a-1);
    }
};

vector<long> list[maxN];
long Dis[maxN][2],lev[maxN];
bool vis[maxN];
AIB aib;

long LCA[maxLog][maxN];

void startDfs(long nod,long p){
    vis[nod] = true;
    aib.change(++aib.dim,+1); Dis[nod][0] = aib.dim;
    lev[nod] = lev[p]+1; LCA[0][nod] = p;

    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i];
        if(vis[newNod]) continue;
        startDfs(newNod,nod);
    }


    aib.change(++aib.dim,-1); Dis[nod][1] = aib.dim;
}

void preProcess(){
    for(long pas=1;pas<maxLog;pas++){
        for(long i=1;i<=N;i++){
            LCA[pas][i] = LCA[pas-1][LCA[pas-1][i]];
        }
    }
}

long Up(long a,long b){
    long pas = 0;
    while(b){
        if(b&1) a = LCA[pas][a];
        b >>= 1;
        pas++;
    }
    return a;
}

long getLCA(long a,long b){
    b = Up(b,lev[b]-lev[a]);

    if(a==b) return a;

    long pasL=maxLog-2;
    for(long pas=1<<maxLog-2;pas;pas>>=1,pasL--){
        if(LCA[pasL][a] == LCA[pasL][b]) continue;
        a = LCA[pasL][a]; b = LCA[pasL][b];
    }

    return LCA[0][a];
}

void removeEdge(long a,long b){
    if(lev[a] > lev[b]) {long t=a;a=b;b=t;}
    aib.change(Dis[b][0],-1);
    aib.change(Dis[b][1],+1);
}
bool query(long a,long b){
    if(lev[a] > lev[b]) {long t=a;a=b;b=t;}
    long R = getLCA(a,b);

    long need1 = lev[a] - lev[R];
    long need2 = lev[b] - lev[R];


    if(aib.sum(Dis[R][0]+1,Dis[a][0]) != need1 || aib.sum(Dis[R][0]+1,Dis[b][0]) != need2) return false;
    return true;
}

int main()
{
    freopen("disconnect.in","r",stdin);
    freopen("disconnect.out","w",stdout);
    fread(Buff,1,maxBuf,stdin);

    N = getLong(); M = getLong();
    aib.init();
    for(i=1;i<N;i++){
        x = getLong(); y = getLong();
        list[x].push_back(y);
        list[y].push_back(x);
    }
    startDfs(1,0);
    preProcess();



////////////////////////////////////////////////
    int V = 0;

for (int i = 0; i < M; ++i) {
    int type, x, y; type = getLong(); x = getLong(); y = getLong();

    int a = x xor V;
    int b = y xor V;

    if (type == 1) {
        removeEdge(a, b);
    } else
        if (query(a, b)) {
            printf("YES\n");
            V = a;
        } else {
            printf("NO\n");
            V = b;
        }
}
//////////////////////////////////////////////////


    return 0;
}
