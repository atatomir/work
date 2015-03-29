#include <iostream>
#include <cstdio>

using namespace std;

long t,n,i,a,b;

int main()
{
    freopen("magicsequence.in","r",stdin);
    freopen("magicsequence.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld%ld",&n,&a);
        for(i=2;i<=n-1;i++) scanf("%ld",&b);
        if(n==1) {
            printf("YES\n");
            continue;
        }
        scanf("%ld",&b);
        if(a<b) printf("YES\n"); else printf("NO\n");
    }

    return 0;
}
