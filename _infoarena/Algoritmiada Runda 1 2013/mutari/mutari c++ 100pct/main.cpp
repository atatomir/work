#include <iostream>
#include <cstdio>


long n,i,a[100005],j;
long sol[1000005],cnt;

int main()
{
    freopen("mutari.in","r",stdin);
    freopen("mutari.out","w",stdout);

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++) scanf("%ld ",&a[i]);

    for(i=2;i<=n;i++)
        if(a[i] % a[1] != 0) {
            printf("-1");
            return 0;
        }

    for(i=2;i<=n;i++){
       for(j=1;j<a[i]/a[1];j++) sol[++cnt] = i;
    }
    for(i=n;i>1;i--) sol[++cnt] = i;

    printf("%ld\n",cnt);
    for(i=1;i<=cnt;i++) printf("%ld\n",sol[i]-1);



    return 0;
}
