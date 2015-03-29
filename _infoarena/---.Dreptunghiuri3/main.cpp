#include <cstdio>

using namespace std;


struct drept {
    long x,y,x2,y2,v;
};

long n,m,k,lc[2][2005];
long i,j,vect,ms[2005][2005];
drept a[1005];
long long l[2005],c[2005];

void QSort(long l,long h) {
    long i=l,j=h,x=lc[vect][(i+j)/2],y;
    do {
       while (lc[vect][i] < x) i++;
       while (lc[vect][j] > x) j--;
       if (i<=j) {
          y = lc[vect][i]; lc[vect][i] = lc[vect][j]; lc[vect][j] = y;
          i++; j--;
       }
    } while(i<=j);
    if (l < j) QSort(l,j);
    if (i < h) QSort(i,h);
}

long cbx(long x) {
    long i=1,j=n,mij;
    do {
        mij = (i+j)/2;
        if (x <= l[mij])
            j = mij-1;
        else
            i = mij+1;
    }   while (i <= j);
    return i;
}

long cby(long x) {
    long i=1,j=m,mij;
    do {
        mij = (i+j)/2;
        if (x <= c[mij])
            j = mij-1;
        else
            i = mij+1;
    }   while (i <= j);
    return i;
}


int main()
{
    freopen("dreptunghiuri3.in","r",stdin);
    freopen("dreptunghiuri3.out","w",stdout);

    scanf("%ld %ld %ld\n",&n,&m,&k);

    for(i=1;i<=k;i++) {
        scanf("%ld %ld %ld %ld %ld\n",&a[i].x,&a[i].y,&a[i].x2,&a[i].y2,&a[i].v);
        lc[0][2*i-1] = a[i].x; lc[0][2*i] = a[i].x2+1;
        lc[1][2*i-1] = a[i].y; lc[1][2*i] = a[i].y2+1;
    }

    vect = 0;
    QSort(1,2*k);
    vect = 1;
    QSort(1,2*k);

    n = 1; l[1] = lc[0][1];
    m = 1; c[1] = lc[1][1];
    k *= 2;

    for (i=2;i<=k;i++) {
        if (lc[0][i] != lc[0][i-1]) {
            n++;
            l[n] = lc[0][i];
        }
        if (lc[1][i] != lc[1][i-1]) {
            m++;
            c[m]= lc[1][i];
        }
    }

    k /= 2;
    long x,y,x2,y2;
    for (i=1;i<=k;i++) {
        x = a[i].x; x = cbx(x);
        x2 = a[i].x2 ; x2 = cbx(x2+1);
        y = a[i].y; y = cby(y);
        y2 = a[i].y2; y2 = cby(y2+1);

        ms[x][y] += a[i].v;
        ms[x2][y2] += a[i].v;
        ms[x][y2] -= a[i].v;
        ms[x2][y] -= a[i].v;
    }

    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            ms[i][j] += ms[i][j-1] + ms[i-1][j] - ms[i-1][j-1];
        }
    }


    long maxim = 0;
    long long maxi =0;
    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            if (ms[i][j] > maxim) {
                maxim = ms[i][j];
                maxi = 1LL*(c[j+1]-c[j])*(l[i+1]-l[i]);
            } else
            if (ms[i][j] == maxim) maxi += 1LL*(c[j+1]-c[j])*(l[i+1]-l[i]);
        }
    }

    printf("%ld %lld",maxim,maxi);

    return 0;
}
