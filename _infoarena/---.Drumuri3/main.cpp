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

#define mod 10007
#define maxN 111
#define maxM (maxN * maxN)
#define maxQ 2511
#define dim 100

int aux[dim][dim];

struct Matrix {
    int n, i, j, k;
    int data[dim][dim];

    void reset(int _n) {
        memset(data, 0, sizeof(data));
        n = _n;
    }

    void operator+=(const Matrix who) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                data[i][j] += who.data[i][j];
                if (data[i][j] >= mod) data[i][j] -= mod;
            }
        }
    }

    void operator*=(Matrix who) {
        memcpy(aux, data, sizeof(data));
        memset(data, 0, sizeof(data));

        for (k = 0; k < n; k++)
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++)
                    data[i][j] += (aux[i][k] * who.data[k][j]) % mod;

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                data[i][j] %= mod;
    }
};

int n, m, k, q, i, j, x, y;
Matrix ini, sol;

Matrix combine(const Matrix& A, const Matrix& B, const Matrix& C) {
    static Matrix ans;

    ans = A;
    ans *= C;
    ans += B;

    return ans;
}

Matrix solve(int how) {
    int i, j;
    Matrix ans[2];
    Matrix aux[2];
    bool first = true;

    aux[0] = ini;
    aux[1].reset(n);
    for (i = 0; i < n; i++) aux[1].data[i][i] = 1;

    while (how) {
        if (how & 1) {
            if (first) {
                ans[0] = aux[0];
                ans[1] = aux[1];
            } else {
                ans[1] = combine(aux[0], aux[1], ans[1]);
                ans[0] *= aux[0];
            }

            first = false;
        }

        how >>= 1;

        aux[1] = combine(aux[0], aux[1], aux[1]);
        aux[0] *= aux[0];
    }

    ans[1] += ans[0];
    return ans[1];
}

int main()
{
    freopen("drumuri3.in","r",stdin);
    freopen("drumuri3.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &q);
    ini.reset(n);

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y); x--; y--;
        ini.data[x][y]++;
        ini.data[y][x]++;
    }

    sol = solve(k - 1);
    for (i = 1; i <= q; i++) {
        scanf("%d%d", &x, &y); x--; y--;

        if (k > 1)
            printf("%d\n", sol.data[x][y]);
        else
            printf("1\n");
    }


    return 0;
}
