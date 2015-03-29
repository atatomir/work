#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 100011
#define MOD 666013

struct Que{
    long l,r,ans;
}Q[maxN];

bool cmp(const Que& a,const Que& b){
    return a.r<b.r;
}

long n,m,i,j,k;
long aib[maxN],prec[maxN],v[maxN];
long ans[maxN];

inline long zeros(long x){
    return (x^(x-1))&x;
}
void add(long pos,long var){
    while(pos<=n){
        aib[pos] = (aib[pos]+var+MOD)%MOD;
        pos += zeros(pos);
    }
}
long sum(long pos){
    long ans=0;
    while(pos){
        ans += aib[pos];
        if(ans>=MOD) ans%=MOD;
        pos -= zeros(pos);
    }
    return ans;
}

int main()
{
    freopen("distincte.in","r",stdin);
    freopen("distincte.out","w",stdout);

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=n;i++) scanf("%ld",&v[i]);
    for(i=1;i<=k;i++){
        scanf("%ld %ld",&Q[i].l,&Q[i].r);
        Q[i].ans = i;
    }
    sort(Q+1,Q+k+1,cmp);

    j = 1;
    for(i=1;i<=k;i++){
        for(;j<=Q[i].r;j++){
            if(prec[v[j]]) add(prec[v[j]],-v[j]);
            add(j,v[j]);
            prec[v[j]] = j;
        }
        ans[Q[i].ans] = (sum(Q[i].r) - sum(Q[i].l-1)+MOD)%MOD;
    }

    for(i=1;i<=k;i++) printf("%ld\n",ans[i]);

    return 0;
}
