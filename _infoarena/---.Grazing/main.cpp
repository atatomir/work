#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair

#define big_dim 311
#define base 100000
#define ll int//long long

#define maxN 311
#define define_size (sizeof(ll) * big_dim)

ll aux[big_dim];
int dimi;

int n, i, l;
ll dp[maxN][big_dim];
ll aux_big[big_dim];

void init(ll *who, ll val) {
    memset(who, 0, define_size);
    who[0] = 1;
    who[1] = val;
}

void sum(ll *A, ll *B) { //! A *= B
    int i, dim;

    A[0] = max(A[0], B[0]);
    dim = A[0];

    for (i = 1; i <= dim; i++) {
        A[i] += B[i];

        A[i + 1] += A[i] / base;
        A[i] %= base;
    }

    if (A[dim + 1] != 0)
        A[0]++;
}

void atrib(ll *A, ll *B) { //! A = B
    memcpy(A, B, define_size);
}

void prod(ll *A, ll val) { //! A *= val
    int i, dim;
    dim = A[0];

    for (i = 1; i <= dim; i++)
        A[i] *= val;

    for (i = 1; i <= A[0]; i++) {
        A[i + 1] += A[i] / base;
        A[i] %= base;

        if (A[ A[0] + 1 ] != 0)
            A[0]++;
    }
}

void div(ll *A, ll val) { //! A /= val
    int i, dim;
    dim = A[0];

    for (i = dim; i > 0; i--) {
        A[i - 1] += base * (A[i] % val);
        A[i] /= val;
    }

    while (dim > 1 && A[dim] == 0)
        dim--;
    A[0] = dim;
}

void print(ll *A) {
    int i, dim;
    dim = A[0];

    printf("%d", A[dim]);

    for (i = dim - 1; i > 0; i--) {
        for (int step = base / 10; step > A[i]; step /= 10)
                printf("0");

        if(A[i]) printf("%d", A[i]);
    }
}

int main()
{
    freopen("grazing.in", "r", stdin);
    freopen("grazing.out", "w", stdout);

    scanf("%d", &n);

    for (i = 1; i <= n; i++)
        init(dp[i], 0);

    init(dp[0], 1);

    for (i = 1; i <= n; i++) {
        atrib(dp[i], dp[i - 1]);

        for (l = 2; l <= i; l++) {
            prod(dp[i - l], i - 1);

            atrib(aux_big, dp[i - l]);

            if (l % 3 != 0 && l > 3) {
                div(aux_big, 2);
                sum(dp[i], aux_big);
                prod(aux_big, l);
            } else {
                prod(aux_big, l);
                div(aux_big, 2);
            }

            sum(dp[i], aux_big);
        }

        //print(dp[i]);
        //printf("\n");
    }

    print(dp[n]);

    return 0;
}
