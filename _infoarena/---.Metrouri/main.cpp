#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, m, k, i, s;
long long ans;
int t[maxN];

int main()
{
    freopen("metrouri.in","r",stdin);
    freopen("metrouri.out","w",stdout);

    scanf("%d%d%d", &n, &m , &k);
    for (i = 1; i <= m; i++) {
        scanf("%d %d", &s, &t[i]);
        t[i] -= s - 1;
    }

    sort(t + 1, t + m + 1);
    for (i = 1; i < m; i++) {
        t[i] = t[i + 1] - t[i];
        ans += t[i];
    }
    m--; k--;
    sort(t + 1, t + m + 1);
    for (i = m; i > 0 && k > 0; i--, k--) ans -= t[i];

    printf("%lld", ans);

    return 0;
}
