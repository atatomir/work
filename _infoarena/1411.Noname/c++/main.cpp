#include <iostream>
#include <cstdio>

using namespace std;

long n,i,j,sol[1005][1005],l[1005],c[1005];

int main()
{
    freopen("noname.in","r",stdin);
    freopen("noname.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) {
        scanf("%ld",&j);
        l[j] = i;
    }
    for(i=1;i<=n;i++) {
        scanf("%ld",&j);
        c[j] = i;
    }

    printf("1\n");
    for(i=1;i<=n;i++){
        for(j=n-i+1;j<=n;j++){
            sol[l[i]][c[j]] ^= 1;
        }
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++) printf("%ld ",sol[i][j]);
        printf("\n");
    }

    return 0;
}
