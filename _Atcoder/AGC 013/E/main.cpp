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

#define maxN 100011
#define mod 1000000007

struct matrix {
    ll data[3][3];

    void init() {
        memset(data, 0, sizeof(data));
        data[0][0] = data[1][1] = data[2][2] = 1;
    }

    void set_full() {
        vector<ll> aux = {1, 2, 1,
                          0, 1, 1,
                          1, 2, 2};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                data[i][j] = aux[i * 3 + j];
    }

    void set_deny() {
        vector<ll> aux = {1, 2, 1,
                          0, 1, 1,
                          0, 0, 1};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                data[i][j] = aux[i * 3 + j];
    }

    matrix operator*=(matrix who) {
        static matrix aux;
        static int i, j, k;

        memcpy(aux.data, data, sizeof(data));
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                data[i][j] = 0;
                for (k = 0; k < 3; k++)
                    data[i][j] += aux.data[i][k] * who.data[k][j];
                data[i][j] %= mod;
            }
        }
    }
};

int n, L, i;
int x[maxN];
matrix able, unable;
matrix ans;

matrix poww(matrix a, int b) {
    int i;
    matrix ans;

    ans.init();
    while (b > 0) {
        if (b & 1) ans *= a;
        b >>= 1;
        a *= a;
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &L, &n);
    for (i = 1; i <= n; i++) scanf("%d", &x[i]), x[i]++;
    x[0] = 0;

    able.set_full();
    unable.set_deny();
    ans.init();

    for (i = 1; i <= n; i++) {
        ans *= poww(able, x[i] - x[i - 1] - 1);
        ans *= unable;
    }

    ans *= poww(able, L - x[n]);
    printf("%lld", ans.data[0][2]);



    return 0;
}
