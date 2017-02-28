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

ll n, q, i, j, x;
vector<ll> ops;
ll todo[maxN];

ll sums[maxN], k;
ll cnt[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &q);
    ops = {n};
    for (i = 1; i <= q; i++) {
        scanf("%lld", &x);

        while (!ops.empty()) {
            if (ops.back() < x) break;
            ops.pop_back();
        }

        ops.pb(x);
    }

    q = ops.size();
    for (i = 0; i < ops.size(); i++)
        todo[i + 1] = ops[i];

    cnt[q] = 1;
    for (i = q; i > 1; i--) {
        if (cnt[i] == 0) continue;
        k = todo[i];

        while (k >= todo[1]) {
            ll pos = upper_bound(todo + 1, todo + q + 1, k) - todo - 1;
            pos = min(pos, i - 1);

            cnt[pos] += (k / todo[pos]) * cnt[i];
            k %= todo[pos];
        }

        sums[k] += cnt[i];
        cnt[i] = 0;
    }

    sums[todo[1]] += cnt[1];
    for (i = n; i > 0; i--)
        sums[i] += sums[i + 1];

    for (i = 1; i <= n; i++)
        printf("%lld\n", sums[i]);

    return 0;
}
