#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int n,i;
int a[10];

int main()
{
    freopen("permutari.in","r",stdin);
    freopen("permutari.out","w",stdout);

    scanf("%d",&n);
    for(i=1;i<=n;i++){
        a[i] = i;
        printf("%d ",i);
    } printf("\n");
    while(next_permutation(a+1,a+n+1)) {
        for(i=1;i<=n;i++) printf("%d ",a[i]); printf("\n");
    }

    return 0;
}
