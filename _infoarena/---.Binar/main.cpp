#include <cstdio>

using namespace std;

long n,m,i,j,ind[2005];
char a[2005][2005];

void MySort(long pas,long l,long h) {
    if (pas > n) return;

    //printf("%ld %ld\n",l,h);

    long i=l,j=h,y;
    char pre=a[pas][ind[l-1]],suc = a[pas][ind[h+1]];
    a[pas][ind[l-1]] = '0'; a[pas][ind[h+1]] = '1';

    do {
        while (a[pas][ind[i]] == '0') i++;
        while (a[pas][ind[j]] == '1') j--;
        if (i <= j) {
            y = ind[i]; ind[i] = ind[j]; ind[j] = y;
            i++; j--;
        }
    } while (i<=j);

    y = l-1; while (a[pas][ind[y+1]] == '0') y++;

    a[pas][ind[l-1]] = pre; a[pas][ind[h+1]] = suc;

    if (l < y) MySort(pas+1,l,y);
    if (y+1 < h) MySort(pas+1,y+1,h);
}

int main()
{
    freopen("binar.in","r",stdin);
    freopen("binar.out","w",stdout);

    scanf("%ld %ld\n",&n,&m);
    for(i=1;i<=n;i++) scanf("%s\n",a[i]+1);
    for(i=0;i<=m+1;i++) ind[i] = i;

    MySort(1,1,m);

    for (i=1;i<=m;i++) printf("%ld ",ind[i]);

    return 0;
}
