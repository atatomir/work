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

#define maxN 200011

int n, i;
ll a[maxN], sum, way;
ll ans[maxN];

ll act, rat;
ll aux[maxN];

void no_sol() {
    printf("NO");
    exit(0);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }

    way = 1LL * (n + 1) * n;
    way >>= 1;

    if (sum % way != 0)
        no_sol();

    sum /= way;
    a[0] = a[n];

    for (i = 1; i <= n; i++) {
        ll aux = a[i] - a[i - 1];
        aux -= sum;
        aux *= -1;

        if (aux < 0) no_sol();
        if (aux % n != 0) no_sol();

        ans[i] = aux / n;
    }

    act = rat = 0;
    for (i = 1; i <= 2 * n; i++) {
        rat += ans[i];
        act += rat;

        if (i > n) {
            act -= ans[i - n] * (n + 1);
            rat -= ans[i - n];
        }

        aux[i] = act;
    }

    for (i = 1; i <= n; i++)
        if (a[i] != aux[i] + aux[i + n])
            no_sol();

    printf("YES");


    return 0;
}
