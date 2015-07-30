#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100111
#define INF 1000000000

long n,i,ant,ans;
long a[maxN],st[maxN],dr[maxN];

int main()
{
    freopen("sir2dif.in","r",stdin);
    freopen("sir2dif.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);

    st[1] = -INF; ant = a[1];
    for(i=2;i<=n;i++){
        st[i] = max(st[i-1],ant-a[i]);
        ant = max(ant,a[i]);
    }

    dr[n] = -INF; ant = a[n];
    for(i=n-1;i;i--){
        dr[i] = max(dr[i+1],a[i]-ant);
        ant = min(ant,a[i]);
    }

    ans = -INF;
    for(i=2;i<=n-2;i++) ans = max(ans,st[i]+dr[i+1]);
    printf("%ld\n",ans);


    return 0;
}
