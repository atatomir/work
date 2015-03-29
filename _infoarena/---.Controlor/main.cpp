#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 1024

long n,i,j;
long a[maxN][maxN];
long act[maxN][maxN];

int main()
{
    freopen("controlor.in","r",stdin);
    freopen("controlor.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++) scanf("%ld",&a[i][j]);

    for(i=n-1;i;i--){
        long long add=0;
        for(j=i+2;j<=n;j++) act[i][j] = act[i+1][j];
        for(j=i+1;j<=n;j++) add += a[i][j];
        for(j=i+1;j<=n;j++,add-=a[i][j-1])
            act[i][j] += add;
    }

    for(i=1;i<n;i++){
        for(j=i+1;j<=n;j++) printf("%ld ",act[i][j]);
        printf("\n");
    }

    return 0;
}
