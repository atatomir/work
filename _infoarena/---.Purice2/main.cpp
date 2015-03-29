#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 57

long t,n,i,j,act;
long a[maxN];

long cmmdc(long a,long b){
    if(a<b) swap(a,b);
    while(b){
        a %= b;
        swap(a,b);
    }
    return a;
}

int main()
{
    freopen("purice2.in","r",stdin);
    freopen("purice2.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld",&n);
        for(i=1;i<=n;i++) scanf("%ld",&a[i]);
        sort(a+1,a+n+1);
        act = a[2]-a[1];
        for(i=1;i<=n;i++)
            for(j=i+1;j<=n;j++) act = cmmdc(act,a[j]-a[i]);

        if(act==1) printf("1\n"); else printf("0\n");
    }

    return 0;
}
