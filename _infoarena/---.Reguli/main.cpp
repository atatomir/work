#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 500011

long n,i,q,ans;
long long a[maxN],pr[maxN];

int main()
{
    freopen("reguli.in","r",stdin);
    freopen("reguli.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%lld",&pr[i]); n--;
    for(i=1;i<=n;i++) a[i] = pr[i+1]-pr[i];

    memset(pr,0,sizeof(pr));

    //!!********************

    q = 0;
    for(i=2;i<=n;i++){
        while(q && a[q+1]!=a[i]) q=pr[q];
        if(a[q+1]==a[i]) q++;
        pr[i] = q;
    }

    //!!********************

    ans = n - pr[n]; printf("%ld\n",ans);
    for(i=1;i<=ans;i++) printf("%lld\n",a[i]);

    return 0;
}
