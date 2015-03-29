#include <cstdio>

using namespace std;

struct answer{
    long a,b;
};

long n,i,a[10005],v[4][4][10005],r[4],min,cont=0;
answer sol[10005];

inline void Intersect(long s,long d) {
    min = v[s][d][0];
    if (min > v[d][s][0]) min = v[d][s][0];
    for(i=1;i<=min;i++) {
        cont++;
        sol[cont].a = v[s][d][v[s][d][0]--];
        sol[cont].b = v[d][s][v[d][s][0]--];
    }
}


int main()
{
    freopen("egipt.in","r",stdin);
    freopen("egipt.out","w",stdout);

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++) {
        scanf("%d\n",&a[i]);
        r[a[i]]++;
    }

    for (i=1;i<=r[1];i++) {
        v[1][a[i]][++v[1][a[i]][0]] = i;
    }
    for (i=r[1]+1;i<=r[1]+r[2];i++) {
        v[2][a[i]][++v[2][a[i]][0]] = i;
    }
    for (i=r[1]+r[2]+1;i<=n;i++) {
        v[3][a[i]][++v[3][a[i]][0]] = i;
    }

    Intersect(1,2);
    Intersect(1,3);
    Intersect(2,3);

    r[1] = 0; r[2] = 0; r[3] = 0;
    for(i=2;i<=3;i++)
        if (v[1][i][0]) r[1] = i;
    for(i=1;i<=3;i=i+2)
        if (v[2][i][0]) r[2] = i;
    for(i=1;i<=2;i++)
        if (v[3][i][0]) r[3] = i;

    min = v[1][r[1]][0];
    if (r[1] == 3) {
        for(i=1;i<=min;i++) {
            cont++;
            sol[cont].a = v[1][3][i];
            sol[cont].b = v[2][1][i];

            v[1][3][i] = v[2][1][i];
        }
        for(i=1;i<=min;i++) {
            cont++;
            sol[cont].a = v[1][3][i];
            sol[cont].b = v[3][2][i];
        }
    }
    if (r[1] == 2) {
        for(i=1;i<=min;i++) {
            cont++;
            sol[cont].a = v[1][2][i];
            sol[cont].b = v[3][1][i];

            v[1][2][i] = v[3][1][i];
        }
        for(i=1;i<=min;i++) {
            cont++;
            sol[cont].a = v[1][2][i];
            sol[cont].b = v[2][3][i];
        }
    }

    printf("%ld\n",cont);
    for(i=1;i<=cont;i++) printf("%ld %ld\n",sol[i].a,sol[i].b);

    return 0;
}
