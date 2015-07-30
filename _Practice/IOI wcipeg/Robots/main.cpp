#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

//#define DEBUG
#define maxN (1<<20)
#define maxAB 50011
#define PI pair<long,long>
#define W first
#define S second
#define mp make_pair

long n,a,b,i,cnt;
PI Toys[maxN],rem[maxN];
long ww[maxAB],ss[maxAB];

struct cmp{
    bool operator()(long a,long b){
        return Toys[a].S < Toys[b].S;
    }
};
priority_queue<long,vector<long>,cmp> H;

bool invCmp(const PI& a,const PI& b){
    return a.S<b.S;
}

bool allDone(long lim){
    long i,pos,how;

    //! Rezolv pt W
    while(!H.empty()) H.pop();
    pos = 1;
    for(i=1;i<=a;i++){
        while(Toys[pos].W<ww[i] && pos<=n) H.push( pos++ );

        how = lim;
        while(how && !H.empty()){
            how--;
            H.pop();
        }
    }

    //! Vad ce a ramas
    cnt = 0;
    while(pos<=n) rem[++cnt] = Toys[pos++];
    while(!H.empty()){
        rem[++cnt] = Toys[H.top()];
        H.pop();
    }
    sort(rem+1,rem+cnt+1,invCmp);

    //! Rezolv pt S
    pos = 1; how =0;
    for(i=1;i<=b;i++){
        while(rem[pos].S<ss[i] && pos<=cnt) {how++;pos++;}
        how = max((long)0,how-lim);
    }

    if(how || pos<=cnt) return false;
    return true;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld",&a,&b,&n);
    for(i=1;i<=a;i++) scanf("%ld",&ww[i]);
    for(i=1;i<=b;i++) scanf("%ld",&ss[i]);
    for(i=1;i<=n;i++) scanf("%ld%ld",&Toys[i].W,&Toys[i].S);

    sort(Toys+1,Toys+n+1);
    sort(ww+1,ww+a+1);
    sort(ss+1,ss+b+1);

    long cbI=1,cbJ=n,mid;
    while(cbI<=cbJ){
        mid = (cbI+cbJ)>>1;
        if(allDone(mid))
            cbJ = mid-1;
        else
            cbI = mid+1;
    }

    if(cbI==n+1) cbI=-1;
    printf("%ld",cbI);

    return 0;
}
