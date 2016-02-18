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

#define maxN 55

int n, k, i, op, need;
ll v[maxN];

ll limit_low = 1;
ll limit_high = 2000000000;

void _insert(int pos, ll val) {
    for (int i = n; i >= pos; i--) v[i + 1] = v[i];
    v[pos] = val;
    n++;
}

bool is_good(ll a, ll b, ll c) {
    return a + b <= c;
}

void try_add() {
    v[0] = -limit_high;
    v[n + 1] = 5 * limit_high;

    if ( is_good(limit_low, v[1], v[2]) ) {
        _insert(1, limit_low);
        return;
    }

    if ( is_good(v[n - 1], v[n], limit_high) ) {
        _insert(n + 1, limit_high);
        return;
    }

    for (i = 1; i < n; i++) {
        ll _low = max(v[i], v[i - 1] + v[i]);
        ll _high = min(v[i + 1], min( v[i + 1] - v[i], v[i + 2] - v[i] ));

        if (_low <= _high) {
            _insert(i + 1, _low);
            return;
        }
    }
}

int main()
{
    freopen("triunghi5.in","r",stdin);
    freopen("triunghi5.out","w",stdout);

    scanf("%d%d%d", &op, &n, &k);
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    sort(v + 1, v + n + 1);

    if (op == 1) {
        n = 1;
        v[2] = v[1];

        for (i = 3; i <= k; i++)
            v[i] = v[i - 1] + v[i - 2];
    } else {
        while (n < k) try_add();
    }

    for (i = 1; i <= k; i++) printf("%d ", v[i]);

    return 0;
}
