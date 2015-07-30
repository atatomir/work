#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 122

long n,i,j;
long tr[maxN][maxN];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%ld",&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=i;j++) scanf("%ld",&tr[i][j]);

    for(i=n-1;i;i--)
        for(j=1;j<=i;j++)
            tr[i][j] += max(tr[i+1][j],tr[i+1][j+1]);
    printf("%ld",tr[1][1]);

    return 0;
}
