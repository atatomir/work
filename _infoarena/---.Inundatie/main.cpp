#include <cstdio>

using namespace std;

long i,j,k=0,q;
long long s[300*300+10],a[300*300+10],n,m,x;

void QSort(long l,long h) {
    long i=l,j=h,x=a[(i+j)/2],y;
    do {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i<=j) {
            y = a[i]; a[i] = a[j]; a[j] = y;
            i++; j--;
        }
    }   while (i <= j);
    if (l < j) QSort(l,j);
    if (i < h) QSort(i,h);
}

long cb(long x) {
    long i=1,j=n,m;
    do {
      m = (i+j)/2;
      if (x <= a[m])
        j = m-1;
      else
        i = m+1;
    }   while (i <= j);
    return j;
}

int main()
{
    freopen("inundatie.in","r",stdin);
    freopen("inundatie.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) {
        for (j=1;j<=n;j++) {
            k++;
            scanf("%ld",&a[k]);
        }
    }

    n = k;
    QSort(1,n);

    s[0] = 0;
    for(i=1;i<=n;i++) s[i] = s[i-1] + a[i];

    scanf("%ld",&q);
    long long loc;
    for (i=1;i<=q;i++) {
        scanf("%ld",&x);
        x--;
        loc = cb(x);
        if (x < 0) x = 0;
        printf("%ld\n",s[loc]+x*(n-loc));
    }

    return 0;
}
