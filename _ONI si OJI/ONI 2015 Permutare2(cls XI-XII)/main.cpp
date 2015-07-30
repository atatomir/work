#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 100011

int n,m,i;
long long v[maxN<<1],vr[maxN<<1];
int vraja;
long long whL[maxN<<1];
long long whR[maxN<<1];
long long rL[maxN<<1],rR[maxN<<1];

long long ans = (1LL<<60);

void Try(int l,int r){
    int dim = r-l+1; dim = ((dim+1)>>1);
    int wh = v[l+dim-1];

    long long cost = whL[r]-whL[l+dim-1] - rL[ l+dim-1 ]*(r-(l+dim-1)) +
                     whR[l]-whR[l+dim-1] - rR[ l+dim-1 ]*(dim-1);
    ans = min(ans,cost);
}

int main()
{
    freopen("permutare2.in","r",stdin);
    freopen("permutare2.out","w",stdout);

    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++) scanf("%d",&vraja); v[1] = 0;
    for(i=2;i<=m;i++) scanf("%lld",&v[i]);

    sort(v+1,v+m+1);
    for(i=m+1;i<=2*m;i++) v[i] = v[i-m]+n;

    for(i=1;i<=2*m;i++) vr[i] = v[i+1]-v[i]; v[2*m] = 0;
    for(i=2*m;i;i--)    v [i] = v[i]-v[i-1]; v[1]   = 0;

    for(i=1;i<=2*m;i++) whL[i] = whL[i-1]+v[i]; //! 1..i
    for(i=2*m;i;i--) whR[i] = whR[i+1]+vr[i]; //! 2*n..

    for(i=1;i<=2*m;i++) {rL[i]=whL[i]; rR[i]=whR[i];}

    for(i=1;i<=2*m;i++) whL[i] += whL[i-1];
    for(i=2*m;i;i--) whR[i] += whR[i+1];

    for(i=1;i<=m;i++) Try(i,i+m-1);
    printf("%lld",ans);

    return 0;
}
