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

ll q, qi, A, B;

ll get(ll cnt, ll x) {
    ll p1 = x;
    ll p2 = cnt - x + 1;

    if (p1 >= A) p1++;
    if (p2 >= B) p2++;

    return p1 * p2;
}

bool check(ll cnt) {
    ll lo, hi, mid, p1, p2;

    mid = (1 + cnt) / 2;
    lo = max(1LL, mid - 30);
    hi = min(cnt, mid + 30);
    for (ll i = lo; i <= hi; i++)
        if (get(cnt, i) >= A * B) return false;

    return true;


    lo = 1;
    hi = cnt;
    while (lo < hi) {
        mid = (lo + hi) >> 1;

        if (get(cnt, mid) <= get(cnt, mid + 1))
            lo = mid + 1;
        else
            hi = mid;
    }

    return (get(cnt, lo) < A * B);
}

ll solve() {
    ll ans = min(A, B) - 1;
    ll limit = 4LL * max(A, B) - 1;

    for (ll step = 1LL << 40; step > 0; step >>= 1) {
        if (ans + step > limit) continue;
        if (check(ans + step)) ans += step;
    }

    //for (ll i = 1; i <= ans; i++)
    //    cerr << get(ans, i) << ' ';

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &q);
    for (qi = 1; qi <= q; qi++) {
        scanf("%lld%lld", &A, &B);
        printf("%lld\n", solve());
    }


    return 0;
}
