#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100011
#define lSon (node<<1)
#define rSon ((node<<1)|1)

long n,i,p,op;
long qL,qR,v;

struct node{
    long pref,suf,dp;
}aint[maxN<<2];
bool mark[maxN<<2];

void dfs(long node,long l,long r){
    aint[node].dp = aint[node].pref = aint[node].suf = (r-l+1);
    if(l==r) return ;
    dfs(node<<1,l,(l+r)>>1);
    dfs((node<<1)+1,((l+r)>>1)+1,r);
}

void update(long node,long l,long r){
    if(l>=qL&&r<=qR){
        aint[node].dp = aint[node].pref = aint[node].suf = v*(r-l+1);
        mark[node] = true;
        return;
    }

    long m=(l+r)>>1;
    if(mark[node]){
        aint[lSon].dp = aint[lSon].pref = aint[lSon].suf = (aint[node].dp>0)*(m-l+1);
        aint[rSon].dp = aint[rSon].pref = aint[rSon].suf = (aint[node].dp>0)*(r-m);
        mark[lSon] = mark[rSon] = true;
        mark[node] = false;
    }
    if(m+1<=qR) update(rSon,m+1,r);
    if(qL<=m) update(lSon,l,m);

    aint[node].pref = aint[lSon].pref;
    if(aint[lSon].pref == (m-l+1)) aint[node].pref += aint[rSon].pref;
    aint[node].suf = aint[rSon].suf;
    if(aint[rSon].suf == (r-m)) aint[node].suf += aint[lSon].suf;

    aint[node].dp = max(aint[lSon].dp,aint[rSon].dp);
    aint[node].dp = max(aint[node].dp,aint[lSon].suf + aint[rSon].pref);
}

int main()
{
    freopen("hotel.in","r",stdin);
    freopen("hotel.out","w",stdout);

    scanf("%ld %ld",&n,&p);
    dfs(1,1,n);

    for(;p;p--){
        scanf("%ld",&op);
        switch(op){
            case 1: {
                        scanf("%ld %ld",&qL,&qR); v = 0;
                        qR += qL-1;
                        update(1,1,n);
                        break;
                    }
            case 2: {
                        scanf("%ld %ld",&qL,&qR); v = 1;
                        qR += qL-1;
                        update(1,1,n);
                        break;
                    }
            case 3: {
                        printf("%ld\n",aint[1].dp);
                        break;
                    }
        }
    }

    return 0;
}
