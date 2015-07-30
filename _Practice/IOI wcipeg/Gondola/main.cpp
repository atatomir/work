#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>


using namespace std;

//#define DEBUG
#define maxN 100011
#define maxRep 250011
#define mod 1000000009
#define ull long long

long n,i,op;
long seq[maxN],t[maxN];
long pos[maxRep];
vector<long> rep;

ull myPow(ull a,ull b){
    ull ans = 1;
    while(b){
        if(b&1) ans = (ans*a)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return ans;
}

bool valid(){
    long i,cnt=0;
    long fDif=0;

    for(i=1;i<=n;i++)
        if(seq[i]<=n) {fDif=i; break;}

    for(i=1;i<=n;i++) t[i]=seq[i];
    sort(t+1,t+n+1);
    for(i=1;i<n;i++)
        if(t[i]==t[i+1]) return false;

    if(!fDif) return true;
    cnt = seq[fDif];
    for(i=fDif+1;i<=n;i++){
        cnt++; if(cnt==n+1) cnt=1;
        if(seq[i]<=n && seq[i]!=cnt) return false;
    }
    for(i=1;i<fDif;i++){
        cnt++; if(cnt==n+1) cnt=1;
        if(seq[i]<=n && seq[i]!=cnt) return false;
    }
    return true;
}

void replaceSeq(){
    long i,l=0;
    long wh=0,whBig=1;
    rep.clear();

    for(i=1;i<=n;i++)
        if(seq[i]<=n) { wh=i; break; }

    seq[0]=0;
    long cnt=seq[wh]-1;
    for(i=wh;i<=n;i++){
        cnt++; if(cnt==n+1) cnt=1;
        t[i]=cnt;
    }
    for(i=1;i<wh;i++){
        cnt++; if(cnt==n+1) cnt=1;
        t[i]=cnt;
    }


    for(i=1;i<=n;i++){
        if(seq[i] > seq[whBig]) whBig = i;
        pos[ seq[i] ] = i;
    }

    for(i=n+1;i<=seq[whBig];i++){
        if(pos[i]==0) pos[i] = whBig;
        rep.push_back( t[ pos[i] ] );
        t[pos[i]] = i;
    }

    printf("%ld ",rep.size());
    for(vector<long>::iterator it=rep.begin();it!=rep.end();it++)
        printf("%ld ",*it);
}

void countSeq(){
    if(!valid()) { printf("0"); return; }
    long i;

    rep.clear(); rep.push_back(0);
    for(i=1;i<=n;i++)
        if(seq[i]>n) rep.push_back(seq[i]-n);

    sort(rep.begin(),rep.end());
    ull ans = 1,r=(ull)rep.size();
    for(i=1;i<rep.size();i++){
        ull dif = 1LL+rep[i]-rep[i-1]-2LL;
        r--;
        ans = (ans * myPow(r,dif) )%mod;
    }

    if(rep.size()==n+1) ans = (ans*(ull)n)%mod;

    printf("%llu",ans);
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld",&op,&n);
    if(op<=3) op=1; else
    if(op<=6) op=2; else
              op=3;
    for(i=1;i<=n;i++) scanf("%ld",&seq[i]);

    if(op==1){
        if( valid() ) printf("1");
        else          printf("0");
    } else
    if(op==2){
        replaceSeq();
    } else {
        countSeq();
    }

    return 0;
}


