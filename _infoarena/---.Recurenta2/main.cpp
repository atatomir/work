#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define mod 666013
#define matrixDim 8
#define ll long long

//#define DEBUG


ll aux[matrixDim][matrixDim];
ll aux2[matrixDim][matrixDim];

template<class T>
struct matrix {
    int n, m, i, j, k;
    T data[matrixDim][matrixDim];

    void init(int _n, int _m, vector<T> from) {
        n = _n; m = _m;

        int pos = 0;

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++, pos++)
                data[i][j] = from[pos];
    }

    void operator=(const matrix &who) {
        n = who.n; m = who.m;
        memcpy(data, who.data, sizeof(data));
    }

    void operator*=(const matrix &who) {
        memcpy(aux, data, sizeof(data));
        memcpy(aux2, who.data, sizeof(data));
        memset(data, 0, sizeof(data));

        int kk = m;
        m = who.m;

        for (k = 1; k <= kk; k++)
            for (i = 1; i <= n; i++)
                for (j = 1; j <= m; j++)
                    data[i][j] = (data[i][j] + 1LL * aux[i][k] * aux2[k][j]) % mod;
    }

    T getVal(int x, int y) {
        return data[x][y];
    }
};

int n, i;
int A, B, C, X1, X2;

matrix<ll> firstMat;
matrix<ll> useMat;

matrix<ll> ans;

void powIt(matrix<ll> aux, int how) {
    bool firstMult = true;

    while (how) {
        if (how & 1) {
            if (firstMult)
                ans = aux;
            else
                ans *= aux;
            firstMult = false;
        }

        how >>= 1;
        aux *= aux;
    }
}

int main()
{
    freopen("recurenta2.in","r",stdin);
    freopen("recurenta2.out","w",stdout);

    scanf("%d%d%d%d%d%d", &A, &B, &C, &X1, &X2, &n);

    firstMat.init(1,
                  7,
                  {(X1 + 2 * X2) % mod,
                    X1,
                    X2,
                    (3 * X1) % mod,
                    (3 * X2) % mod,
                    3,
                    1} );

    useMat.init(7,
                7,
                {1, 0, 0, 0, 0, 0, 0,
                 0, 0, B, 0, B, 0, 0,
                 0, 1, A, 1, A, 0, 0,
                 B, 0, 0, 0, B, 0, 0,
                 A, 0, 0, 1, A, 0, 0,
                 C, 0, 0, 0, C, 1, 0,
                 0, 0, C, 0, C, 1, 1});

    for (i = 1; i <= 7; i++)
        cerr << firstMat.getVal(1, i) << ' ';
    cerr << '\n';

    powIt(useMat, n - 2);

    if (n == 2) {
        printf("%lld", (X1 + 2 * X2) % mod);
        return 0;
    }

    firstMat *= ans;
    printf("%lld", firstMat.getVal(1, 1));

    for (i = 1; i <= 7; i++)
        cerr << firstMat.getVal(1, i) << ' ';


#ifdef DEBUG
    int vv[100011];
    vv[1] = X1;
    vv[2] = X2;

    for (i = 3; i <= n; i++) vv[i] = (vv[i - 2] * B + vv[i - 1] * A + C) % mod;
    long long sumi = 0;
    for (i = 1; i <= n; i++) sumi = (sumi + 1LL * i * vv[i]) % mod;
    if (sumi != firstMat.getVal(1, 1)) cerr << "\nERROR!";
#endif

    return 0;
}
