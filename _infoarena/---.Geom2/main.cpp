#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxN 50011

int n, k, i;
double v[maxN];
double aux[maxN];
int ans_left, ans_right;

bool check(double lim) {
    int i, prov = 0;
    double min_aux;

    for (i = 1; i <= n; i++) aux[i] = aux[i - 1] + v[i] - lim;
    min_aux = 0;

    for (i = k; i <= n; i++) {
        if (aux[i - k] < min_aux) {
            min_aux = aux[i - k];
            prov = i - k;
        }

        if (aux[i] - min_aux >= 0) {
            ans_left = prov + 1;
            ans_right = i;
            return true;
        }
    }

    return false;
}

int main()
{
    freopen("geom2.in", "r", stdin);
    freopen("geom2.out", "w", stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%lf", &v[i]);
        v[i] = log(v[i]);
    }

    double l = -1000.00, r = 1000.00, mid;
    int step = 30;

    while (step--) {
        mid = (l + r)/2.00;
        if ( check(mid) )
            l = mid;
        else
            r = mid;
    }


    check(l);

    printf("%d %d", ans_left, ans_right);

    return 0;
}
