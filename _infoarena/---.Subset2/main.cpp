#include <cstdio>

using namespace std;

long n,nl,lim,k,rez=1;

int main()
{
    freopen("subset2.in","r",stdin);
    freopen("subset2.out","w",stdout);

    scanf("%ld %ld",&n,&k);

    if (!(k & 1)) rez++;

    lim = (k-1) / 2;
    rez += lim*(n/k);

    n %= k;
    if (n < lim) lim=n;
    rez += lim;

    printf("%ld\n",rez);

    return 0;
}
