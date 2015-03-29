#include <cstdio>
#include <cmath>

using namespace std;

long n,i,pr[30]={0},h;
long total = 0;

void Rezolva(long pas,long sel,long prod) {
    if (pas > pr[0]) {
        if (sel > 1) prod *= (1 << (sel-1));
        total += prod;
    } else {
        Rezolva(pas+1,sel,prod);
        Rezolva(pas+1,sel+1,prod*pr[pas]);
    }
}

int main()
{
    freopen("perechi.in","r",stdin);
    freopen("perechi.out","w",stdout);

    scanf("%d",&n);

    for(i=2;i<=sqrt((double)n);i++) {
        if (n % i == 0) {
            pr[0]++; h = 0;
            while (n % i == 0) { n /= i; h++; }
            pr[pr[0]] = h;
        }
    }
    if (n != 1) {
        pr[0]++;
        pr[pr[0]] = 1;
    }

    Rezolva(1,0,1);

    printf("%ld",total);

    return 0;
}
