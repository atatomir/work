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

#define maxN 2016
#define inf 1000000000000000000LL

int n, m, i, j;
ll ln[maxN], co[maxN];
ll best_ln[maxN], best_co[maxN];
ll ans, aux;

int main()
{
    freopen("maxsubsum.in","r",stdin);
    freopen("maxsubsum.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &ln[i]);
        best_ln[i] = -inf;
    }

    for (i = 1; i <= m; i++) {
        scanf("%lld", &co[i]);
        best_co[i] = -inf;
    }

    for (i = 1; i <= n; i++) {
        aux = 0;
        for (j = i; j <= n; j++) {
            aux += ln[j];
            best_ln[j - i + 1] = max(best_ln[j - i + 1], aux);
        }
    }

    for (i = 1; i <= m; i++) {
        aux = 0;
        for (j = i; j <= m; j++) {
            aux += co[j];
            best_co[j - i + 1] = max(best_co[j - i + 1], aux);
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            ans = max(ans, i * best_co[j] + j * best_ln[i]);

    printf("%lld", ans);

    return 0;
}
