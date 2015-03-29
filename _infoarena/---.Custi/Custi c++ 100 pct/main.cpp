#include <iostream>
#include <cstdio>

using namespace std;

long n,i,j,a[1005][1005],sol[1005];
int x;

int main()
{
    freopen("custi.in","r",stdin);
    freopen("custi.out","w",stdout);

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%d",&x);
            if(x){
                a[i][j] = min(a[i-1][j],min(a[i][j-1],a[i-1][j-1]))+1;
                sol[a[i][j]]++;
            }
        }
    }
    for(i=n;i;i--) sol[i] += sol[i+1];
    for(i=1;i<=n;i++) printf("%ld\n",sol[i]);

    return 0;
}
