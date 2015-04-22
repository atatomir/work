#include <iostream>
#include <cstdio>

using namespace std;

long t,n,m,i,ans,h;

int main()
{
    freopen("ceasuri.in","r",stdin);
    freopen("ceasuri.out","w",stdout);

    scanf("%ld",&t);
    for(;t--;){
        scanf("%ld %ld",&n,&m); n >>= 1;
        ans = 0;

        for(h=1;h<n-1;h++){
            if( (h* (m-1) )%(n-1) == 0 ) ans++;
        }

        printf("%ld\n",(ans+1)<<1);
    }

    return 0;
}
