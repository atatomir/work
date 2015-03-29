#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 100011

struct elem{
    long v,id;
};
bool cmp(const elem& a,const elem& b){
    return a.v > b.v;
}

long n,i;
elem E[maxN<<1];
long e1[maxN],e2[maxN];
bool alrd[maxN];

int main()
{
    freopen("echipe2.in","r",stdin);
    freopen("echipe2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld%ld",&E[2*i-1].v,&E[2*i].v);
        E[2*i-1].id=E[2*i].id=i;
    }

    n<<=1;
    sort(E+1,E+n+1,cmp);
    for(i=1;i<=n;i++){
        if(alrd[E[i].id]) {
            e2[++e2[0]] = E[i].v;
        } else {
            e1[++e1[0]] = E[i].v;
            alrd[E[i].id] = true;
        }
    }

    n >>= 1;
    long ans = max(e1[1]-e1[n],e2[1]-e2[n]);
    printf("%ld",ans);

    return 0;
}
