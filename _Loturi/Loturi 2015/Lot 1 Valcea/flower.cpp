#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 200024
#define lSon (node<<1)
#define rSon ((node<<1)|1)

long n,t,i,op;
long long aint[maxN<<2];
long long c,m,p;
long l,r;

void Update(long node,long l,long r,long qL,long qR,long long st,long long diff){
    if(l==r){
        aint[node] = max(aint[node], st );
        return;
    }

    long mid = (l+r)>>1;
    long long how ; if(qL<=mid) how = mid-qL+1; else how=0;
    if(qL<=mid) Update(lSon,l,mid, qL , min(qR,mid) , st , diff);
    if(qR> mid) Update(rSon,mid+1,r, max(qL,mid+1) , qR , st+how*diff , diff );

    aint[node] = min(aint[lSon],aint[rSon]);
}

long long Query(long node,long l,long r,long qL,long qR){
    if(qL<=l && r <=qR) return aint[node];

    long long ans = (1LL<<60);
    long mid = (l+r)>>1;
    if(qL <= mid) ans = min(ans, Query(lSon,l,mid,qL,qR) );
    if(qR >  mid) ans = min(ans, Query(rSon,mid+1,r,qL,qR) );
    return ans;
}

int main()
{
    freopen("flower.in","r",stdin);
    freopen("flower.out","w",stdout);

    scanf("%ld %ld",&n,&t);
    for(i=1;i<=4*n;i++) aint[i]=-(1LL<<60);
    for(;t--;){
        scanf("%ld",&op);
        if(op==1){
            scanf("%lld %lld %lld",&c,&m,&p);
            Update(1,1,n,c,n,m,-p);
            if(c!=1) Update(1,1,n,1,c-1, m-p*(c-1) ,+p);
        } else {
            scanf("%ld %ld",&l,&r);
            long long ans = Query(1,1,n,l,r);
            printf("%lld\n",ans);
        }
    }


    return 0;
}
