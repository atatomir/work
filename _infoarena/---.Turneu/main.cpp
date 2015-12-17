#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define pb push_back
#define mp make_pair

int t, n, i;
vector<double> vals;
double v;

bool check() {
    int i;
    sort(vals.begin(), vals.end());

    if (vals[0] < 0)
        return false;
    if (vals[n - 1] > n - 1)
        return false;

    for (i = 0; i < n; i++)
        if ( int(vals[i] * 2) != vals[i] * 2 )
            return false;

    for (i = 2; i <= n; i++) {
        vals[i - 1] += vals[i - 2];
        if (vals[i - 1] < 0.50 * i * (i - 1))
            return false;
    }

    if (vals[n - 1] != 0.50 * n * (n - 1))
        return false;

    return true;
}

int main()
{
    freopen("turneu.in", "r", stdin);
    freopen("turneu.out", "w", stdout);

    scanf("%d", &t);
    for (; t > 0; t--) {
        vals.clear();
        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%lf", &v);
            vals.pb(v);
        }

        if (check())
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
