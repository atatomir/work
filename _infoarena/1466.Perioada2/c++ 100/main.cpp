#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 10000005

long n,i,q,p;
char s[maxN];
long pr[maxN];
long long divs=1;

int main()
{
    freopen("perioada2.in","r",stdin);
    freopen("perioada2.out","w",stdout);

    scanf("%ld\n",&n);
    scanf("%s",s+1);

    q = 0;
    for(i=2;i<=n;i++){
        while(q != 0 && s[q+1] != s[i]) q = pr[q];
        if(s[q+1] == s[i]) q++;
    }

    n = n/(n-q);
    for(i=2;i*i<=n;i++){
        if(n % i == 0){
            p = 1;
            while(n % i == 0) p++,n/=i;
            divs = divs*p;
        }
    }
    if(n != 1) divs = divs * 2;

    printf("%lld",divs-1);
    return 0;
}
