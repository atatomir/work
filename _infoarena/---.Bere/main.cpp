#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 15005

long n,m,i,pos,val,ans;
long a[maxN<<1];

long cb(long x){
    long i=1,j=n*2,m;
    while(i<=j){
        m = (i+j)/2;
        if(x < a[m])
            j = m-1;
        else
            i = m+1;
    }
    return j;
}

int main()
{
    freopen("br.in","r",stdin);
    freopen("br.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);
        a[n+i] = a[i];
    }

    for(i=2;i<=2*n;i++) a[i] += a[i-1];
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&pos,&val);
        ans = cb(val+a[pos-1]);
        ans = ans - pos+1;
        ans = min(ans,n);
        printf("%ld\n",ans);
    }

    return 0;
}
