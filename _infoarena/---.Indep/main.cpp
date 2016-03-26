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

#define maxN 1024
#define maxDim 44
#define def 1000
#define base 1000000

struct big_num {
    int dim;
    int data[maxDim];

    void init() {
        memset(data, 0, sizeof(data));
        dim = 1;
    }

    void operator+=(const big_num& who) {
        dim = max(dim, who.dim);

        for (int i = 1; i <= dim; i++) {
            data[i] += who.data[i];
            data[i + 1] += data[i] / base;
            data[i] %= base;
        }
        if (data[dim + 1]) dim++;
    }

    void print() {
        printf("%d", data[dim]);

        for (int i = dim - 1; i > 0; i--) {
            int aux = base / 10;
            while (data[i] < aux) {
                printf("0");
                aux /= 10;
            }

            if (data[i]) printf("%d", data[i]);
        }

    }
};

int n, i, j, x;
int ss, dd;
big_num work[2][maxN];
big_num one;

int gcd(int a, int b) {
    if (a < b) swap(a, b);

    while (b) {
        a %= b;
        swap(a, b);
    }

    return a;
}

int main()
{
    freopen("indep.in","r",stdin);
    freopen("indep.out","w",stdout);

    ss = 0; dd = 1;
    for (i = 1; i <= def; i++) work[ss][i].init();

    one.init();
    one.data[1] = 1;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);

        for (j = 1; j <= def; j++)
            work[dd][j] = work[ss][j];
        for (j = 1; j <= def; j++)
            work[dd][ gcd(j, x) ] += work[ss][j];

        work[dd][x] += one;

        swap(ss, dd);
    }

    work[ss][1].print();


    return 0;
}
