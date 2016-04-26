#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define mod 666013

ll aux[101][101];
int aux2[101][101];

struct matrix {
    int n, m, i, j, k;
    int data[101][101];

    void init(int _n, int _m) {
        n = _n; m = _m;
        memset(data, 0, sizeof(data));
    }

    void operator*=(matrix &who) {
        memset(aux, 0, sizeof(aux));
        memcpy(aux2, who.data, sizeof(who.data));

        for (k = 1; k <= m; k++)
            for (i = 1; i <= n; i++)
                for (j = 1; j <= who.m; j++)
                    aux[i][j] = aux[i][j] + 1LL * data[i][k] * aux2[k][j];

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                data[i][j] = aux[i][j] % mod;
    }
};

int n, m, s, i, j, x;
matrix ini;
matrix work;
matrix ans;

void magic() {
    s--;
    ans = work;

    while (s) {
        if (s & 1) ans *= work;
        s >>= 1;
        work *= work;
    }
}

int main()
{
    freopen("icrisop.in","r",stdin);
    freopen("icrisop.out","w",stdout);

    ini.init(1, 100);
    ini.data[1][100] = 1;

    work.init(100, 100);
    for (j = 1; j < 100; j++)
        work.data[j + 1][j] = 1;

    scanf("%d%d", &n, &s);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        work.data[101 - x][100]++;
    }

    magic();
    ini *= ans;

    printf("%d", ini.data[1][100] % mod);


    return 0;
}
