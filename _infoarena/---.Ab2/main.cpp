#include <iostream>
#include <cstdio>

using namespace std;

long n,a,b,i,j;
long gr,semi,cresc,need;

int main()
{
    freopen("ab2.in","r",stdin);
    freopen("ab2.out","w",stdout);

    scanf("%ld %ld %ld",&n,&a,&b);

    gr = n / b;
    while(1){
        need = a - gr;
        if(need >= 0 && n- gr*b >= need) break;

        gr--;
    }

    need = a-gr;
    n = n - gr*b;
    if(need == n){
        cresc = need;
    } else {
        cresc = need-1;
    }
    semi = n - cresc;

    for(i=1;i<=cresc;i++) printf("%ld ",i);
    for(i=cresc+semi;i>cresc;i--) printf("%ld ",i);
    for(j=1;j<=gr;j++)
        for(i=b;i;i--) printf("%ld ",cresc+semi+(j-1)*b + i);

    return 0;
}
