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
#define maxM 511
#define maxK maxM
#define maxL 277
#define mod 666013

int n, l, k, m, i, j, p, used, last;
int dims[maxK];
pair<int, int> pos[maxM];
vector<int> sets;
int deny[maxL];
ll dp[maxN];
ll ans, square;


int main()
{
    freopen("trotuar.in","r",stdin);
    freopen("trotuar.out","w",stdout);

    scanf("%d%d%d%d", &n, &l, &k, &m);
    for (i = 1; i <= k; i++) scanf("%d", &dims[i]);
    for (i = 1; i <= m; i++) scanf("%d%d", &pos[i].second, &pos[i].first);

    sort(dims + 1, dims + k + 1);
    sort(pos + 1, pos + m + 1, [](const pair<int, int>& a, const pair<int, int>& b)->bool const {
        return mp(a.second, a.first) < mp(b.second, b.first);
    });

    p = 1;
    for (j = 1; j <= n; j++) {
        while (p <= m && pos[p].second == j) {
            deny[ pos[p].first ] = 1;
            p++;
        }

        used = 0;
        for (i = 1; i <= l; i++)
            if (deny[i])
                used++;

        if (used == l) {
            for (i = 1; i <= l; i++) deny[i]--;
            continue;
        }
        if (used == 0) {
            if (p > m) {
                sets.pb(n - j + 1);
                break;
            } else {
                sets.pb(pos[p].second - j);
                j = pos[p].second - 1;
                continue;
            }
        }

        last = 0;
        for (i = 1; i <= l; i++) {
            if (deny[i] != 0) {
                if (last)
                    sets.pb(last);
                last = 0;
            } else {
                deny[i] = l;
                last++;
            }
        }

        if (last) sets.pb(last);
        for (i = 1; i <= l; i++) deny[i]--;
    }

    dp[0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= k; j++) {
            if (i - dims[j] < 0) break;
            dp[i] += dp[i - dims[j]];
        }

        if (i == l) square = dp[l];
        if (i >= l) dp[i] += dp[i - l] * (square - (dims[k] == l ? 1 : 0));
        dp[i] %= mod;
    }

    /*ll area = 0;
    for (auto e : sets)
        area += l * e;
    area += m;
    cerr << area << ' ' << n * l << '\n';*/

    ans = 1;
    for (auto e : sets)
        ans = (ans * dp[e]) % mod;

    printf("%lld", ans);
    cerr << ans;


    return 0;
}
