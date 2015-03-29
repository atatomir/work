#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100111
#define lSon (node<<1)
#define rSon ((node<<1)|1)
#define INF (1LL<<60)

long n,i;
long long sum,elem;
long long aint[maxN<<2],add[maxN<<2],a[maxN];
long prov[maxN<<2];

void getInfo(long node){
    if(aint[lSon]<aint[rSon]||(aint[lSon]==aint[rSon]&&prov[lSon]<prov[rSon])){
        aint[node] = aint[lSon];
        prov[node] = prov[lSon];
    } else {
        aint[node] = aint[rSon];
        prov[node] = prov[rSon];
    }
}
void Expand(long node){
    aint[lSon] += add[node];
    aint[rSon] += add[node];
    add[lSon] += add[node];
    add[rSon] += add[node];
    add[node] = 0;
}

void init(long node,long l,long r){
    if(l==r){
        aint[node] = a[l];
        prov[node] = l;
        return;
    }

    long m=(l+r)>>1;
    init(lSon,l,m);
    init(rSon,m+1,r);
    getInfo(node);
}

void update(long node,long l,long r,long elem){
    if(l==r){
        aint[node] = INF;
        return;
    }

    if(add[node]) Expand(node);

    long m=(l+r)>>1;
    if(elem<=m)
        update(lSon,l,m,elem);
    else
        update(rSon,m+1,r,elem);
    getInfo(node);
}

void multiUpdate(long node,long l,long r,long qL,long qR,long val){
    if(qL>qR) return;
    if(qL<=l&&r<=qR){
        add[node] += val;
        aint[node] += val;
        return;
    }

    if(add[node]) Expand(node);

    long m=(l+r)>>1;
    if(qL<=m) multiUpdate(lSon,l,m,qL,qR,val);
    if(qR> m) multiUpdate(rSon,m+1,r,qL,qR,val);
    getInfo(node);
}

int main()
{
    freopen("biscuiti.in","r",stdin);
    freopen("biscuiti.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
        sum -= a[i];
    }

    init(1,1,n);
    for(i=1;i<=n;i++){
        sum += aint[1];
        elem = prov[1];

        update(1,1,n,elem);
        multiUpdate(1,1,n,1,elem-1,i);
    }

    printf("%lld",sum);

    return 0;
}
