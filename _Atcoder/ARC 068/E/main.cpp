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

#define maxN 300011

int n, m, i, x, y;
vector< pair<int, int> > intr;
vector<int> qq[maxN];

ll ans[maxN], sum[maxN];
ll aib[maxN], p;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int v) {
    while (pos <= m) {
        aib[pos] += v;
        pos += zrs(pos);
    }
}

ll sumi(int pos) {
    ll ans = 0;

    while (pos > 0) {
        ans += aib[pos];
        pos -= zrs(pos);
    }

    return ans;
}

void pre() {
    int i, d, x;

    ans[1] = n;

    for (auto e : intr)
        sum[e.first]++, sum[e.second + 1]--;

    for (i = 1; i <= m; i++) sum[i] += sum[i - 1];

    for (d = 2; d <= m; d++) {
        for (x = d; x <= m; x += d) {
            ans[d] += sum[x];
            if (x != d) qq[x - d].pb(d);
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        intr.pb(mp(x, y));
    }

    sort(intr.begin(), intr.end());
    pre();

    p = 0;
    for (i = 1; i <= m; i++) {
        while (p < intr.size()) {
            if (intr[p].first > i) break;
            add(intr[p].second, +1);
            p++;
        }

        for (auto e : qq[i]) {
            ans[e] -= p - sumi(i + e - 1);
        }
    }

    for (i = 1; i <= m; i++)
        printf("%lld\n", ans[i]);



    return 0;
}
