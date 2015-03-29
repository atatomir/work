#include <cstdio>
using namespace std;

char a[2000005],b[2000005];
long pr[2000005],v[1005],n,m,i,q;

inline void make_pref() {
    pr[1] = 0; q =0;
    for(i=2;i<=n;i++) {
        while((q != 0)&&(a[q+1] != a[i])) q = pr[q];
        if (a[q+1] == a[i]) q++;
        pr[i] = q;
    }
}

int main()
{
    freopen("strmatch.in","r",stdin);
    freopen("strmatch.out","w",stdout);

    scanf("%s\n%s",a+1,b+1);

    n = 0;
    while (a[n+1] != '\0') n++;
    m = 0;
    while (b[m+1] != '\0') m++;

    make_pref();

    v[0] = 0;

    q = 0;
    for(i=1;i<=m;i++) {
        while ((q != 0)&&(a[q+1] != b[i])) q = pr[q];
        if (a[q+1] == b[i]) q++;
        if (q == n) {
            v[0]++;
            if (v[0] <= 1000) v[v[0]] = i-q;
            q = pr[q];
        }
    }

    printf("%ld\n",v[0]);
    if (v[0] > 1000) v[0] = 1000;
    for(i=1;i<=v[0];i++) printf("%ld ",v[i]);

    return 0;
}
