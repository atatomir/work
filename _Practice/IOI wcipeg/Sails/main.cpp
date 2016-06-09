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

#define maxN 100111
#define lim 100010

int n, i;
pair<int, int> sail[maxN];
int aib[maxN];
ll ans;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

int sum(int x) {
    int ans = 0;
    while (x) {
        ans += aib[x];
        x -= zrs(x);
    }
    return ans;
}

int add(int x, int v) {
    while (x <= lim) {
        aib[x] += v;
        x += zrs(x);
    }
}

int aib_lower_bound(int v) {
    int ans = 0;
    int act = 0;

    for (int step = (1 << 16); step > 0; step >>= 1)
        if (ans + step < lim)
            if (act + aib[ans + step] > v)
                ans += step, act += aib[ans];

    return ans + 1;
}


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d", &sail[i].first, &sail[i].second);
    sort(sail + 1, sail + n + 1);

    for (i = 1; i <= n; i++) {
        int h = sail[i].first;
        int need = sail[i].second;

        int gr = sum(h - need + 1);
        int p1 = aib_lower_bound(gr);
        int p2 = aib_lower_bound(gr - 1) - 1;

        p2 = min(p2, h);

        add(p2 + 1, +1);
        add(h + 1, -1);

        add(p1, +1);
        add(p1 + (need - (h - p2)), -1);
    }

    for (i = 1; i <= 100000; i++) {
        int act = sum(i);
        //cerr << i << ' ' << act << '\n';

        if (act == 0) break;
        ans += (1LL * act * (act - 1)) / 2LL;
    }

    printf("%lld", ans);

    return 0;
}
