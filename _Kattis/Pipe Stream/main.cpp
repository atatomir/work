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

#define eps 1e-5

int tests, act_test;
double L, v1, v2, t, s;


int solve() {
    ll step, gr;
    double limit;

    gr = 1;
    for (step = 0; eps + 1.00 * gr * t < v2 - v1; step++) {
        limit = L / (s * (step + 1)); limit += eps;
        limit = max(limit, v1);
        limit = min(limit, v2);

        ll used = (v2 - limit) / t;
        if ( used >= gr ) return -1;

        v2 -= 1.00 * used * t;
        gr -= used;

        gr *= 2;
    }

    return int(step);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &tests);

    for (act_test = 1; act_test <= tests; act_test++) {
        scanf("%lf%lf%lf%lf%lf", &L, &v1, &v2, &t, &s);

        int ans = solve();
        if (ans == -1)
            printf("impossible\n");
        else
            printf("%d\n", ans);
    }


    return 0;
}
