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

struct cc {
    double a, b;


    double imag() {
        return b;
    }

    double imag(double x) {
        return b = x;
    }

    void operator=(double x) {
        a = x;
        b = 0;
    }

    cc operator*(cc who) {
        return {a * who.a - b * who.b, a * who.b + b * who.a};
    }

    cc operator+(cc who) {
        return {a + who.a, b + who.b};
    }

    cc operator-(cc who) {
        return {a - who.a, b - who.b};
    }

    void operator/=(double x) {
        a /= x;
        b /= x;
    }

};

const double PI = acos(-1);
const int dim = 131072 / 2;//262144;
const int maxN = dim + 13;

int n, m, i, k;
char s[maxN], p[maxN];
int ans[maxN];

cc A[maxN], B[maxN];
cc aux[maxN];

void rev(cc *data, int l, int r) {
    int i, pos;

    for (i = l; i <= r; i++) aux[i] = data[i];

    pos = l;
    for (i = l; i <= r; i += 2) data[pos++] = aux[i];
    for (i = l + 1; i <= r; i += 2) data[pos++] = aux[i];

    if (l == r) return;
    int mid = (l + r) >> 1;
    rev(data, l, mid);
    rev(data, mid + 1, r);
}

void conv(int n, cc *data, bool inv) {
    int len, i, j;
    cc w, rat, u, v;

    rev(data, 0, n - 1);

    for (len = 1; 2 * len <= n; len <<= 1) {
        for (i = 0; i < n; i += 2 * len) {
            rat = {cos(PI / len), sin(PI / len)};
            if (inv) rat.imag(-rat.imag());
            w = 1.00;

            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];

                data[i + j] = u + w * v;
                data[i + len + j] = u - w * v;

                w = w * rat;
            }
        }
    }

    if (inv)
        for (i = 0; i < n; i++) data[i] /= n;

}

void solve(char step) {
    int i;

    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));

    for (i = 0; i < n; i++)
        A[i] = (s[i] == step ? 1 : 0);
    for (i = 0; i < m; i++)
        B[m - i] = (p[i] == step ? 1 : 0);

    conv(dim, A, false);
    conv(dim, B, false);

    for (i = 0; i < dim; i++) A[i] = A[i] * B[i];

    conv(dim, A, true);

    for (i = 0; i < n; i++)
        ans[i] += round(A[m + i].a);
}

int main()
{
    freopen("partialmatch.in","r",stdin);
    freopen("partialmatch.out","w",stdout);

    scanf("%s\n%s%d", p, s, &k);
    n = strlen(s);
    m = strlen(p);

    for (char step = 'a'; step <= 'z'; step++)
        solve(step);

    int cnt = 0;
    for (i = 0; i + m <= n; i++)
        if (ans[i] >= m - k)
            cnt++;

    printf("%d\n", cnt);
    for (i = 0; i + m <= n; i++)
        if (ans[i] >= m - k)
            printf("%d\n", i);


    return 0;
}
