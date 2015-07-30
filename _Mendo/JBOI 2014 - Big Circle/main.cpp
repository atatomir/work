#include <cstdio>
#include <cmath>

using namespace std;

struct point {
    double x,y,tg;
};

inline double sqr(double x) { return ((x)*(x));}

long n,i,ind[100005];
point a[100005];
double x,y;

void QSort(long l,long h) {
    long i=l,j=h;
    double x=a[ind[(i+j)/2]].tg,y;
    do {
      while (a[ind[i]].tg < x) i++;
      while (a[ind[j]].tg > x) j--;
      if (i <= j) {
        y = ind[i]; ind[i] = ind[j]; ind[j] = y;
        i++; j--;
      }
    } while (i <= j);
    if (l < j) QSort(l,j);
    if (i < h) QSort(i,h);
}

int main()
{
    /*FILE *f,*fo;
    f = fopen("bc.in","r");
    fo = fopen("bc.out","w"); */

    scanf("%ld",&n);

    double minx = 1000005;
    long mini;
    for (i = 1;i<=n;i++) {
        scanf("%lf %lf",&a[i].x,&a[i].y);
        if (a[i].x < minx) {
            minx = a[i].x;
            mini = i;
        }
    }

    x = a[mini].x; y= a[mini].y;
    a[mini] = a[n]; n--;

    double v1,v2;
    for (i=1;i<=n;i++) {
        v1 = y-a[i].y;
        v2 = x-a[i].x;
        if (v2 == 0)
            a[i].tg = 72256929.4422;
        else
            a[i].tg = v1/v2;
        ind[i] = i;
    }

    QSort(1,n);

    double min = 1500000,dist;
    for (i = 1;i<n;i++) {
        dist = sqrt(sqr(a[ind[i]].y-a[ind[i+1]].y) + sqr(a[ind[i]].x-a[ind[i+1]].x));
        if (dist < min) min = dist;
    }

    dist = sqrt(sqr(a[ind[1]].y-y) + sqr(a[ind[1]].x-x));
        if (dist < min) min = dist;
    dist = sqrt(sqr(a[ind[n]].y-y) + sqr(a[ind[n]].x-x));
        if (dist < min) min = dist;

    printf("%.2f",min);


    /* fclose(f);
    fclose(fo); */
    return 0;
}
