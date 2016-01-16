#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 33
#define double long double

double rez[maxN][maxN];
double rez2[maxN][maxN];

struct Matrix {
    int n, m;
    double data[maxN][maxN];

    void init(int _n, int _m) {
        n = _n; m = _m;
        memset(data, 0, sizeof(data));
    }

    void operator*=(const Matrix& who) {
        memcpy(rez, data, sizeof(data));
        memcpy(rez2, who.data, sizeof(data));

        int i, j, k;
        memset(data, 0, sizeof(data));

        for (k = 1; k <= m; k++)
            for (i = 1; i <= n; i++)
                for (j = 1; j <= who.m; j++)
                    data[i][j] += rez[i][k] * rez2[k][j];

        m = who.m;
    }
};

int n, m, i, j;
double v[maxN];
double pond[maxN];
double corr[maxN];

Matrix ini;
Matrix work;
Matrix aux;

void my_pow(int how) {
    how--;
    aux = work;

    while (how > 0) {
        if (how & 1) work *= aux;
        how >>= 1;
        aux *= aux;
    }
}

int main()
{
    freopen("ecu.in","r",stdin);
    freopen("ecu.out","w",stdout);

    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%llf", &v[i]);
    for (i = 1; i <= n; i++)
        scanf("%llf", &pond[i]);
    for (i = 1; i <= n; i++)
        scanf("%llf", &corr[i]);

    ini.init(1, n + 1);
    for (i = 1; i <= n; i++) ini.data[1][i] = v[i];
    ini.data[1][n + 1] = 1;

    work.init(n + 1, n + 1);
    for (j = 1; j <= n; j++) {
        work.data[j][j] = pond[j];
        work.data[j + 1][j] = 1 - pond[j + 1];
        work.data[n + 1][j] = corr[j];
    }
    work.data[n + 1][n + 1] = 1;

    work.data[1][n] = 1 - pond[1];

    if (m > 0) {
        my_pow(m);
        ini *= work;
    }

    for (i = 1; i <= n; i++)
        printf("%.3llf ", ini.data[1][i]);

    return 0;
}
