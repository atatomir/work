#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxN 100011

int n, i;
int v[maxN];
long long ans = 0;

long long compute(int l, int r) {
    return 1LL * v[l] * (r - l) + 1LL * v[r] * (n - r + 1);
}

int compute(int l, int r, int qL, int qR) {
    if (l > r) return 0;

    int mid = (l + r) / 2;

    int prov = max(qL, mid + 1);
    long long how = compute(mid, prov);

    for (int i = prov; i <= qR; i++) {
        long long aux = compute(mid, i);
        if (aux > how) {
            how = aux;
            prov = i;
        }
    }

    ans = max(ans, how);
    compute(l, mid - 1, qL, prov);
    compute(mid + 1, r, prov, qR);
}

int main()
{
    freopen("avioane.in", "r", stdin);
    freopen("avioane.out", "w", stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);
    v[++n] = 0;
    sort(v + 1, v + n + 1);

    compute(1, n, 1, n);

    printf("%lld", ans);

    return 0;
}
