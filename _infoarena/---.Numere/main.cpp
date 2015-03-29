#include <cstdio>

using namespace std;

long t,ti,h,a,b,win;

int main()
{
    freopen("numere.in","r",stdin);
    freopen("numere.out","w",stdout);

    scanf("%ld\n",&t);
    for(ti=1;ti<=t;ti++) {
        scanf("%ld %ld",&a,&b);
        win = 1;

        if (a == b) {printf("%ld\n",win); continue;}

        if (a < b) {h = a; a = b; b = h;}
        while (a / b == 1)
        {
           win ^= 1;
           a %= b;
           h = a; a = b; b = h;
        }
        if (win == 0) win = 2;

        printf("%ld\n",win);
    }

    return 0;
}
