#include <cstdio>
#include <cstring>

using namespace std;

int n,m,finish,i,j,a[10][10],r[10][10],l[40],sol[40];
long min=53000;

void Try_it(int pas,int i,int j,long sum) {
    r[i][j] = 0;
    l[pas] = a[i][j];
    sum += 1L*pas*a[i][j];

    if (sum > min) {
        r[i][j] = 1;
        return;
    }

    if (pas == finish) {
        min = sum;
        for(int pp = 1;pp<=finish;pp++) sol[pp] = l[pp];
    } else {
        if (r[i-1][j-1]) Try_it(pas+1,i-1,j-1,sum);
        if (r[i-1][j+1]) Try_it(pas+1,i-1,j+1,sum);
        if (r[i+1][j-1]) Try_it(pas+1,i+1,j-1,sum);
        if (r[i+1][j+1]) Try_it(pas+1,i+1,j+1,sum);
        if (r[i-1][j]) Try_it(pas+1,i-1,j,sum);
        if (r[i+1][j]) Try_it(pas+1,i+1,j,sum);
        if (r[i][j-1]) Try_it(pas+1,i,j-1,sum);
        if (r[i][j+1]) Try_it(pas+1,i,j+1,sum);
    }

    r[i][j] = 1;
}

int main()
{
    freopen("suma3.in","r",stdin);
    freopen("suma3.out","w",stdout);

    scanf("%d %d\n",&n,&m);
    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            scanf("%d ",&a[i][j]);
            if (a[i][j]) r[i][j] = 1;
        }
    }

    finish = (1L*n*m)/2;

    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            if(a[i][j]) Try_it(1,i,j,0);
        }
    }

    printf("%ld\n",min);
    for(i=1;i<=finish;i++) printf("%d ",sol[i]);

    return 0;
}
