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

namespace FFT{

    /* -------------------- Complex definition ------------------ */

    struct Complex {
        double a, b;

        Complex operator*(Complex who);
        Complex operator/(double x);
        Complex operator+(Complex who);
        Complex operator-(Complex who);
        void print();
        void print_real();
    };

    Complex Complex::operator*(Complex who) {
        return {a * who.a - b * who.b, a * who.b + b * who.a};
    }

    Complex Complex::operator/(double x) {
        return {a / x, b / x};
    }

    Complex Complex::operator+(Complex who) {
        return {a + who.a, b + who.b};
    }

    Complex Complex::operator-(Complex who) {
        return {a - who.a, b - who.b};
    }

    void Complex::print() {
        printf("(%.2lf + %.2lf i) ", a, b);
    }

    void Complex::print_real() {
        printf("%.2lf ", a);
    }

    /* -------------------- useful resources ------------------ */
    const double PI = acos(-1);
    double sign = 1.00;

    vector<double> pre_sin, pre_cos;

    vector<Complex> A, B, C;
    vector<Complex> res_A, res_B, res_C;
    vector<Complex> aux;

    /* -------------------- Functions ------------------ */

    void FFT(int n, Complex* a, Complex* ans) {
        int i, half;
        Complex w, rat, A, B;

        if (n == 1) {
            ans[0] = a[0];
            return;
        }

        half = n / 2;
        w = {1.00, 0.00};
        rat = {pre_cos[n], sign * pre_sin[n]};

        for (i = 0; i < n; i++) aux[i] = a[i];
        for (i = 0; i < n; i += 2) a[i / 2] = aux[i];
        for (i = 1; i < n; i += 2) a[(i / 2) + half] = aux[i];

        FFT(half, a, ans);
        FFT(half, a + half, ans + half);

        for (i = 0; i < half; i++) {
            A = ans[i];
            B = ans[i + half];

            ans[i] = A + w * B;
            ans[i + half] = A - w * B;
            w = w * rat;
        }
    }

    vector<Complex> Multiply(vector<Complex> _A, vector<Complex> _B) {
        int n, m, dim, big_pow, i;

        A = _A; B = _B;

        n = A.size(); m = B.size();
        dim = max(A.size(), B.size());

        // precompute sin and cos
        pre_sin.resize(dim * 4);
        pre_cos.resize(dim * 4);

        for (big_pow = 1; big_pow / 2 < dim; big_pow <<= 1) {
            pre_sin[big_pow] = sin(2.00 * PI / big_pow);
            pre_cos[big_pow] = cos(2.00 * PI / big_pow);
        }
        pre_sin[big_pow] = sin(2.00 * PI / big_pow);
        pre_cos[big_pow] = cos(2.00 * PI / big_pow);

        dim = big_pow;
        while (A.size() < dim) A.pb({0, 0});
        while (B.size() < dim) B.pb({0, 0});

        res_A.resize(dim);
        res_B.resize(dim);
        res_C.resize(dim); C.resize(dim);
        aux.resize(dim);

        sign = 1.00;
        FFT(dim, &A[0], &res_A[0]);
        FFT(dim, &B[0], &res_B[0]);

        for (i = 0; i < dim; i++) res_C[i] = res_A[i] * res_B[i];

        sign = -1.00;
        FFT(dim, &res_C[0], &C[0]);
        C.resize(n + m - 1);

        for (i = 0; i < C.size(); i++)
            C[i] = C[i] / dim;

        return C;
    }

};

//! ATTENTION ! If T is integer you must use round (e.a)
template<typename T>
vector<T> poly_multiply(vector<T> A, vector<T> B) {
    static vector< FFT::Complex > AA, BB, CC;
    static vector< T > C;
    int i;

    AA.clear(); BB.clear();
    for (i = 0; i < A.size(); i++) AA.pb({A[i], 0.00});
    for (i = 0; i < B.size(); i++) BB.pb({B[i], 0.00});

    CC = FFT::Multiply(AA, BB);
    C.clear();

    for (auto e : CC)
        C.pb(e.a);

    return C;
}


int n, m, i;
double x;
vector<double> A, B, C;

int main()
{
    freopen("fft.in","r",stdin);
    freopen("fft.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lf", &x);
        A.pb(x);
    }
    for (i = 1; i <= m; i++) {
        scanf("%lf", &x);
        B.pb(x);
    }

    C = poly_multiply(A, B);
    for (auto e : C)
        printf("%.2lf ", e);

    return 0;
}
