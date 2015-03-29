#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 100010

long n,m,i,x,pos;
long a[maxN],b[maxN];
long ans,ant;

long cb(long x){
    long i=ant+1,j=m,mid;
    while(i<=j){
        mid = (i+j)/2;
        if(x <= b[mid])
            j = mid-1;
        else
            i = mid+1;
    }
    return i;
}

int main()
{
    freopen("cocochanel.in","r",stdin);
    freopen("cocochanel.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%ld",&a[i]);
    for(i=1;i<=m;i++) scanf("%ld",&b[i]);
    sort(b+1,b+m+1);

    for(i=1;i<=n;i++){
        ant = ans = 0;
        x = a[i];

        while(1){
            pos = cb(x);
            if(pos == m+1) break;
            ans++;
            x <<= 1;
            ant = pos;
        }

        printf("%ld\n",ans);
    }

    return 0;
}
