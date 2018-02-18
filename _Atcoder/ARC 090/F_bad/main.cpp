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

#define mod 1000000007
const ll limit = 1000000000LL;

ll S, i;
vector<ll> events;
ll ans;


ll sum(ll p1, ll p2) {
    ll base, dig, aux;
    ll ans = 0;

    for (base = dig = 1; base <= limit; base *= 10LL, dig++) {
        aux = dig * (min(10LL * base - 1, p2) - max(base, p1) + 1);
        if (aux > 0) ans += aux;
    }

    return ans;
}

ll get_right(ll l) {
    ll ans = l - 1;

    for (ll step = 1LL << 30; step > 0; step >>= 1)
        if (ans + step <= limit * 10LL)
            if (sum(l, ans + step) <= S)
                ans += step;

    return ans;
}

ll get_left(ll r) {
    ll ans = 0;

    for (ll step = 1LL << 30; step > 0; step >>= 1)
        if (ans + step <= r)
            if (get_right(ans + step) < r - 1)
                ans += step;

    ans++;
    return ans;
}

ll cnt_bts(ll x) {
    ll ans = 0;

    while (x > 0) {
        ans++;
        x /= 10;
    }

    return ans;
}

ll gcd(ll x, ll y) {
    if (x < y) swap(x, y);

    while (y > 0) {
        x %= y;
        swap(x, y);
    }

    return x;
}

ll cmmmc(ll x, ll y) {
    return (x * y) / gcd(x, y);
}

void add_solutions(ll p1, ll p2) {
    ll i, l, r;
    ll rm = cnt_bts(p1);
    ll ad, act_sum, dif, adv;

    if (rm > S) return;

    l = p1;
    r = get_right(p1);
    ad = cnt_bts(r + 1);

    act_sum = sum(l, r);
    if (rm == ad) {
        if (act_sum == S) ans += p2 - p1;
        return;
    }

    while (act_sum != S) {
        dif = S - act_sum;
        adv = dif / (ad - rm);

        l += adv;
        r += adv;
        act_sum += adv * (ad - rm);

        if (l >= p2) return;
        if (act_sum == S) break;

        l++;
        act_sum -= rm;
    }

    if (l >= p2) return;
    ll cnt = 1LL + (p2 - p1 - 1) / cmmmc(ad - rm, ad);
    ans += cnt;
}

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void check(ll d) {
    if (d < 10) return;

    ll need = S / d;
    ans += poww(10, d) + mod - poww(10, d - 1) + mod - need + 1;
    //ans += mod - 1;
    ans %= mod;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &S);

    //! add events
    for (ll base = 1; base <= limit; base *= 10LL) {
        events.pb(base);
        events.pb(get_left(base));
    }

    sort(events.begin(), events.end());
    events.resize(unique(events.begin(), events.end()) - events.begin());

    for (i = 0; events[i] != limit; i++)
        add_solutions(events[i], events[i + 1]);

    for (ll d = 1; d * d <= S; d++) {
        if (S % d == 0) {
            check(d);
            if (d * d != S) check(S / d);
        }
    }

    for (ll d = 10; d <= S; d++) {
        ll cc = S / d;
        ll rr = S % d;

        //if (cc <= rr) break;
        if (rr != 0) ans++;
    }

    /*if (S >= 10) {
        ans += S - 9;
        ans %= mod;
    }*/

    ans %= mod;

    cout << ans;



    return 0;
}
