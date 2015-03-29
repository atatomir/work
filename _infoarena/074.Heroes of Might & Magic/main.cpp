#include <cstdio>

using namespace std;

struct elem {
    char x,y;
};

long n,m,i,j,k,x,t,cont=0,cl = 0;
char ok[105][105],s,d;
long a[2][105][105];
long total=0;
long x1,x2,y1,y2,xl,yl;
elem c[10005];

inline void Renew(char v) {
    long i,j;
    for (i=0;i<=n+1;i++)
        for (j=0;j<=m+1;j++)
            a[v][i][j] = 0;
}

inline void Expand(char x,char y) {
    if (ok[x-1][y] == 0) { cont++; c[cont].x = x-1; c[cont].y = y; ok[x-1][y] = 1;}
    if (ok[x+1][y] == 0) { cont++; c[cont].x = x+1; c[cont].y = y; ok[x+1][y] = 1;}
    if (ok[x][y-1] == 0) { cont++; c[cont].x = x; c[cont].y = y-1; ok[x][y-1] = 1;}
    if (ok[x][y+1] == 0) { cont++; c[cont].x = x; c[cont].y = y+1; ok[x][y+1] = 1;}
}

int main()
{
    freopen("homm.in","r",stdin);
    freopen("homm.out","w",stdout);

    scanf("%d %d %d\n",&n,&m,&k);

    for(i=0;i<=n+1;i++)
        for(j=0;j<=m+1;j++)
            ok[i][j] = 1;

    for(i = 1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            scanf("%ld",&x);
            if (x == 0) ok[i][j] = 0;
        }
    }

    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);

    s = 0; d = 1;
    Renew(s);
    a[s][x1][y1] = 1; cont++; c[cont].x = x1; c[cont].y = y1; ok[x1][y1] = 1;
    Expand(x1,y1);

    total = a[s][x2][y2];

    for(t=1;t<=k;t++) {
        Renew(d);
        cl = cont;
        for(i=1;i<=cl;i++) {
            xl = c[i].x; yl = c[i].y;
            a[d][xl][yl] = a[s][xl-1][yl] + a[s][xl+1][yl] + a[s][xl][yl-1] + a[s][xl][yl+1];
            Expand(xl,yl);
        }
        total+= a[d][x2][y2];
        s ^= 1; d^=1;
    }

    printf("%ld\n",total);

    return 0;
}
