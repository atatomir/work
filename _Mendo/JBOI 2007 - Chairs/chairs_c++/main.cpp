#include <cstdio>

using namespace std;

long v[2005];
int op[2005];

void QSort(long l,long h) {
  long i=l,j=h,x=v[(i+j)/2],x2=op[(i+j)/2],y;
  do {
    while ((v[i] < x)||((v[i] == x)&&(op[i] > x2))) i++;
    while ((v[j] > x)||((v[j] == x)&&(op[j] < x2))) j--;
    if (i<= j) {
        y = v[i]; v[i] = v[j]; v[j] = y;
        y = op[i]; op[i] = op[j]; op[j]= y;
        i++; j--;
    }
  } while (i <= j);
  if (l < j) QSort(l,j);
  if (i < h) QSort(i,h);
}

int main()
{
    long n,i;
    long h,m,s,h2,m2,s2,t;

    scanf("%ld",&n);
    for (i=1;i<=n;i++) {
       scanf("%d:%d:%d %d:%d:%d",&h,&m,&s,&h2,&m2,&s2);
       t = 2*(i-1)+1;
       v[t] = 3600*h+60*m+s; op[t] = 1;
       v[t+1] = 3600*h2+60*m2+s2; op[t+1] = -1;
    }
    n *= 2;

    QSort(1,n);

    long ent=0,max = 0;
    for (i = 1 ; i<= n; i++) {
        ent = ent + op[i];
        if (ent > max) max = ent;
    }
    printf("%ld",max);

    return 0;
}
