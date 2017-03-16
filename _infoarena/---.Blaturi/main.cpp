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

int n, i;
ll t[maxN];
ll c1, e1, c2, e2;
ll sol, aux;

int main()
{
    freopen("blaturi.in","r",stdin);
    freopen("blaturi.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &t[i]);
        t[i] += t[i - 1];
    }

    scanf("%lld%lld%lld%lld", &c1, &e1, &c2, &e2);
    sol = 1LL << 60;
    for (i = 0; i <= n; i++) {
        aux = c1 * t[i] + c2 * (t[n] - t[i]);
        if (i <= n - i)
            aux += 1LL * max(0, n - 2 * i - 1) * e2;
        else
            aux += 1LL * max(0, n - 2 * (n - i) - 1) * e1;

        sol = min(sol, aux);
    }

    printf("%lld", sol);



    return 0;
}
