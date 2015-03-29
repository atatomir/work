#include <iostream>
#include <cstdio>

using namespace std;

long t,n,sum,x;

int main()
{
    freopen("nim.in","r",stdin);
    freopen("nim.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld",&n); sum = 0;
        for(;n;n--){
            scanf("%ld",&x);
            sum ^= x;
        }
        if(sum) printf("DA\n"); else printf("NU\n");
    }
    return 0;
}
