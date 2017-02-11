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
int a[maxN], b[maxN], p[maxN], wh[maxN];
int aib[maxN];
ll ans;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int x) {
    while (pos <= n) {
        aib[pos] += x;
        pos += zrs(pos);
    }
}

int sum(int x) {
    int ans = 0;

    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }

    return ans;
}

void solve(int *a, int *b) {
    int i;
    ll act = 0;

    for (i = 1; i <= n; i++) wh[b[i]] = i;
    for (i = 1; i <= n; i++) p[i] = p[i + n] = wh[ a[i] ];
    memset(aib, 0, sizeof(aib));

    for (i = 1; i <= 2 * n; i++) {
        act += sum(n) - sum(p[i]);
        add(p[i], +1);

        if (i > n) {
            act -= sum(p[i - n] - 1);
            add(p[i - n], -1);
        }

        if (i >= n) ans = min(ans, act);
    }
}

int main()
{
    freopen("mincross.in","r",stdin);
    freopen("mincross.out","w",stdout);

    ans = 1LL << 60;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (i = 1; i <= n; i++) scanf("%d", &b[i]);

    solve(a, b);
    solve(b, a);

    printf("%lld", ans);

    return 0;
}
