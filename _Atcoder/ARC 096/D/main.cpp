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

const int maxN = 100011;

int n, i;
ll C, x[maxN], v[maxN];
ll dpl[maxN], dpr[maxN];

ll solve() {
    int i, j;
    ll act;

    dpl[0] = act = 0;
    for (i = 1; i <= n; i++) {
        act += v[i];
        dpl[i] = max(dpl[i - 1], act - 2LL * x[i]);
    }

    dpr[n + 1] = act = 0;
    for (i = n; i >= 1; i--) {
        act += v[i];
        dpr[i] = max(dpr[i + 1], act - (C - x[i]));
    }

    ll ans = 0;
    for (i = 0; i <= n; i++) ans = max(ans, dpl[i] + dpr[i + 1]);
    return ans;
}


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%lld", &n, &C);
    for (i = 1; i <= n; i++) scanf("%lld%lld", &x[i], &v[i]);

    ll ans = solve();
    for (i = 1; i <= n; i++) x[i] = C - x[i];
    reverse(x + 1, x + n + 1);
    reverse(v + 1, v + n + 1);

    ans = max(ans, solve());

    printf("%lld", ans);

    return 0;
}
