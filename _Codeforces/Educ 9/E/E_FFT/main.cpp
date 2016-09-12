#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define comp complex<long double>

#define sz (1024 * 1024)
#define maxN (sz + 11)
#define eps 1e-4

const double PI = acos(-1);

int n, k, i, x;
comp data[maxN], aux[maxN];
int big_dim;

comp poww(comp a, int b) {
    comp ans = {1, 0};

    while (b) {
        if (b & 1) ans *= a;
        b >>= 1;
        a *= a;
    }

    return ans;
}


void bottom(int l, int r, comp* data) {
    int i, pos;

    if (l == r) return;
    for (i = l; i <= r; i++) aux[i] = data[i];

    pos = l;
    for (i = l; i <= r; i += 2) data[pos++] = aux[i];
    for (i = l + 1; i <= r; i += 2) data[pos++] = aux[i];

    bottom(l, (l + r) >> 1, data);
    bottom(((l + r) >> 1) + 1, r, data);
}

void fft(int dim, comp* data, double sign) {
    int len, i, j;
    comp u, v, w, step;

    bottom(0, dim - 1, data);
    for (len = 1; 2 * len <= dim; len <<= 1) {
        step = { cos(PI / len), sign * sin(PI / len) };

        for (i = 0; i < dim; i += 2 * len) {
            w = {1.00, 0};

            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];

                data[i + j] = u + w * v;
                data[i + len + j] = u - w * v;

                w *= step;
            }
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        data[x - 1] += 1;
    }

    /*n = k = 1000;
    for (i = 0; i < n; i++) data[i] = {1, 0};
    */

    for (big_dim = 1024; data[big_dim].real() == 0; big_dim--);
    big_dim = (big_dim + 1) * k;
    for (; (big_dim & (big_dim - 1)) != 0; big_dim++);

    big_dim = max(big_dim, 16 * 16);
    big_dim = min(big_dim, sz);




    fft(big_dim, data, +1);
    for (i = 0; i < big_dim; i++) data[i] = poww(data[i], k);
    fft(big_dim, data, -1);

    for (i = 0; i < big_dim; i++) {
        data[i] /= big_dim;

        if (data[i].real() > eps)
            printf("%d ", i + k);
    }

    return 0;
}
