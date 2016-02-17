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

#define maxDim 2016

int n, d, k, i;

int dim;
int nr[maxDim];

void prod(int x) {
    int i;

    for (i = 1; i <= dim; i++) nr[i] *= x;

    for (i = 1; i <= dim; i++) {
        nr[i + 1] += nr[i] / 10;
        nr[i] %= 10;

        if (nr[dim + 1]) dim++;
    }
}

void divi(int x) {
    int i;
    for (i = dim; i > 0; i--) {
        nr[i - 1] += 10 * (nr[i] % x);
        nr[i] /= x;
    }

    while (nr[dim] == 0 && dim > 1) dim--;
}

int main()
{
    freopen("expozitie.in","r",stdin);
    freopen("expozitie.out","w",stdout);

    scanf("%d%d%d", &n, &d, &k);

    n -= d * k;
    if (n < 0) {
        printf("0");
        return 0;
    }

    dim = 1;
    nr[1] = 1;

    for (i = 2; i <= n + d - 1; i++) prod(i);
    for (i = 2; i <= n; i++) divi(i);
    for (i = 2; i <= d - 1; i++) divi(i);

    for (i = dim; i > 0; i--) printf("%d", nr[i]);


    return 0;
}
