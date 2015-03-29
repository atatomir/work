#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 2015

struct Show{
    long st,en;
    long cnt;

    bool inside(Show& who){
        long dim ; dim = (en-st)/5;
        long st1 ; st1 = st+2*dim;
        long dr1 ; dr1 = st1+dim;

        if(st1<=who.st && who.en<=dr1) return true;
        return false;
    }
};
bool cmpDim(const Show& a,const Show& b){return (a.en-a.st<b.en-b.st);}
bool cmp(const Show& a,const Show& b) {return a.en<b.en;}

long n,i,j;
Show sh[maxN];
long dp[maxN];

Show tmp[maxN];
long nn,dpt[maxN];

long cb(long x){
    long i=1,j=nn,m;
    while(i<=j){
        m = (i+j)>>1;
        if(x<tmp[m].en)
            j = m-1;
        else
            i = m+1;
    }
    return j;
}

inline long getCnt(Show S){
    long i; nn = 0;
    for(i=1;i<=n;i++)
        if(S.inside(sh[i])) tmp[++nn] = sh[i];

    sort(tmp+1,tmp+nn+1,cmp);
    for(i=1;i<=nn;i++)
        dpt[i] = max(dpt[i-1],dpt[cb(tmp[i].st)]+tmp[i].cnt);
    return dpt[nn];
}

int main()
{
    freopen("intfm.in","r",stdin);
    freopen("intfm.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld%ld",&sh[i].st,&sh[i].en);

    sort(sh+1,sh+n+1,cmpDim); //! sort by dimension
    for(i=1;i<=n;i++){
        sh[i].cnt = getCnt(sh[i])+1;
    }

    sort(sh+1,sh+n+1,cmp);
    for(i=1;i<=n;i++){
        dp[i] = dp[i-1];
        for(j=i-1;sh[j].en>sh[i].st;j--);
        dp[i] = max(dp[i],dp[j]+sh[i].cnt);
    }

    printf("%ld",dp[n]);

    return 0;
}
