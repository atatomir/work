#include <cstdio>

//////////////// ATENTIE LA ...if(a = b)... in loc de ...if(a == b)...

using namespace std;

struct {
    long x,y,v;
} c[1000015];

long n,m,i,j,ci=1,cj=0,ii,ij,oi,oj,dr[1005][1005],rez[1005][1005],a[1005][1005],x,y,v,def,mij,sol;
char s[1005][1005];
inline void add(long x,long y,long v) {
    dr[x][y] = v;
    cj++;
    c[cj].x = x; c[cj].y = y; c[cj].v = v;
}

void Recurs(long i,long j) {
    if ((i==oi)&&(j==oj)){    //// ATENTIE la ...if(j=oj).. in loc de ...if(j==oj)...
        sol = 1;
        return;
    }

    a[i][j] = 0;
    if((a[i][j-1] == def)&&(dr[i][j-1] >= mij)) Recurs(i,j-1);
    if (sol == 1) return;
    if((a[i][j+1] == def)&&(dr[i][j+1] >= mij)) Recurs(i,j+1);
    if (sol == 1) return;
    if((a[i-1][j] == def)&&(dr[i-1][j] >= mij)) Recurs(i-1,j);
    if (sol == 1) return;
    if((a[i+1][j] == def)&&(dr[i+1][j] >= mij)) Recurs(i+1,j);
}

inline int check() {
    long i,j;
    sol=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            a[i][j] = rez[i][j];
    if (dr[ii][ij] >= mij)
        Recurs(ii,ij);
    return sol;
}

int main()
{
    freopen("barbar.in","r",stdin);
    freopen("barbar.out","w",stdout);

    scanf("%ld %ld\n",&n,&m);
    for(i=1;i<=n;i++) scanf("%s\n",s[i]+1);
    def = n*m;


    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            switch (s[i][j]) {
                case '.':  dr[i][j] = def;
                           break;
                case 'D':  add(i,j,0);
                           break;
                case '*':  dr[i][j] = -1;
                           break;
                case 'I':  ii = i; ij = j;
                           dr[i][j] = def;
                           break;
                case 'O':  oi = i; oj = j;
                           dr[i][j] = def;
                           break;
            }

            rez[i][j] = dr[i][j];
        }
    }

    while (ci <= cj) {
        i = c[ci].x; j = c[ci].y; v = c[ci].v;
        if(dr[i][j-1] == def) add(i,j-1,v+1);
        if(dr[i][j+1] == def) add(i,j+1,v+1);
        if(dr[i-1][j] == def) add(i-1,j,v+1);
        if(dr[i+1][j] == def) add(i+1,j,v+1);
        ci++;
    }

    i = 1; j = n+m-1;
    do {
        mij = (i+j)/2;
        if (!check())
            j = mij-1;
        else
            i = mij+1;
    }   while (i<=j);

    if ((j==0)||(j == n+m)) j = -1;
    printf("%ld\n",j);

    /*for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) printf("%ld ",dr[i][j]);
        printf("\n");
    }*/

    return 0;
}
